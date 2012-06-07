/*
** localsocket.cc
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sun May 11 22:19:51 2003 Julien Lemoine
** $Id: localsocket.cc,v 1.10 2006/12/28 17:49:58 speedblue Exp $
**
** Copyright (C) 2003,2004 Julien Lemoine
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "localsocket.hh"
#include <stddef.h>
#include <string.h>

#ifndef LIBSOCKET_WIN

#include <sys/types.h>
#include <sys/un.h>
#include "socket.hxx"

namespace Network
{
  void	LocalSocket::init(const std::string& filename)
  {
    _socket = _bind(filename);
    _filename = filename;
  }

  void	LocalSocket::close()
  {
    if (_socket > 0)
      _close(_socket);
    _socket = 0;
    unlink(_filename.c_str());
    _filename = "";
  }

  int		LocalSocket::_bind(const std::string& filename)
  {
    int				s;
    struct sockaddr_un		name;
    size_t			size;

    s = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (s < 0)
      throw NoConnection("Socket error", HERE);
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, filename.c_str(), sizeof (name.sun_path));
    name.sun_path[sizeof (name.sun_path) - 1] = '\0';
    size = (offsetof (struct sockaddr_un, sun_path)
	    + strlen (name.sun_path) + 1);
    if (bind (s, (struct sockaddr *) &name, size) < 0)
      throw BindError("Bind error", HERE);
    return s;
  }

  void	LocalSocket::_write_str(int socket, const std::string& str,
				const std::string& filename) const
  {
    int				res = 1;
    const char			*buf = str.c_str();
    unsigned int		count = 0;
    struct sockaddr_un		name;

    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, filename.c_str(), sizeof (name.sun_path));
    name.sun_path[sizeof (name.sun_path) - 1] = '\0';

    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    while (res && count < str.size())
      {
	res = sendto(socket, buf + count,
		     str.size() - count, SENDTO_FLAGS,
		     (const struct sockaddr*)&name, sizeof(name));
	if (res <= 0)
	  throw ConnectionClosed("Connection Closed", HERE);
	count += res;
      }
  }

  void	LocalSocket::_write_str_bin(int socket, const std::string& str,
				    const std::string& filename) const
  {
    int				res = 1;
    unsigned int		count = 0;
    struct sockaddr_un		name;
    char			*buf = new char[str.size() + 2];

    buf[0] = str.size() / 256;
    buf[1] = str.size() % 256;
    memcpy(buf + 2, str.c_str(), str.size());
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, filename.c_str(), sizeof (name.sun_path));
    name.sun_path[sizeof (name.sun_path) - 1] = DEFAULT_DELIM;

    if (socket < 0)
      {
	delete[] buf;
	throw NoConnection("No Socket", HERE);
      }
    while (res && count < str.size() + 2)
      {
	res = sendto(socket, buf + count, str.size() + 2 - count, SENDTO_FLAGS,
		     (const struct sockaddr*)&name, sizeof(name));
	if (res <= 0)
	  {
	    delete[] buf;
	    throw ConnectionClosed("Connection Closed", HERE);
	  }
	count += res;
      }
    delete[] buf;
  }

  std::string	LocalSocket::_read_line(int socket,
					std::string& filename)
  {
    char		chr[MAXPKTSIZE];
    std::string		str = "";
    int			res = 1, i;
    std::pair<int, int> delim;
    struct sockaddr_un	addr;
    size_t		size;
    bool		end = false;

    size = sizeof(addr);
    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    if (!_update_buffer(delim, i, str))
      while (!end)
	{
#ifdef __CYGWIN__
	  res = recvfrom(socket, chr, MAXPKTSIZE, 0,
			 (struct sockaddr*)&addr,
			 (socklen_t*)&size);
#else
	  res = recvfrom(socket, chr, MAXPKTSIZE, MSG_TRUNC,
			 (struct sockaddr*)&addr,
			 (socklen_t*)&size);
#endif
	  if (res <= 0)
	    throw ConnectionClosed("Connection Closed", HERE);
	  _buffer += std::string(chr, res);
	  if (_update_buffer(delim, i, str))
	    end = true;
	}
    filename = std::string(addr.sun_path);
    _state_timeout = 0;
    return str;
  }

  std::string	LocalSocket::_read_line_bin(int socket, unsigned int size)
  {
    char		chr[MAXPKTSIZE];
    std::string		str = "";
    int			res = 1;
    bool		end = false;

    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    if (_buffer.size() >= 2 && !size)
      {
	size = (unsigned char)_buffer[0] * 256 + (unsigned char)_buffer[1];
	_buffer = _buffer.substr(2, _buffer.size() - 2);
      }
    if (size && _buffer.size() >= size)
      {
	str = _buffer.substr(0, size);
	_buffer = _buffer.substr(size, _buffer.size() - size);
      }
    else
      while (!end)
	{
	  memset(chr, 0, MAXPKTSIZE);
#ifdef __CYGWIN__
	  res = recv(socket, chr, MAXPKTSIZE, 0);
#else
	  res = recv(socket, chr, MAXPKTSIZE, MSG_TRUNC);
#endif
	  if (res <= 0)
	    throw ConnectionClosed("Connection Closed", HERE);
	  // _buffer += all octets received
	  _buffer += std::string(chr, res);
	  if (!size)
	    {
	      // extract size from _buffer and reduce it
	      size = (unsigned char)_buffer[0] * 256 + (unsigned char)_buffer[1];
	      _buffer = _buffer.substr(2, _buffer.size() - 2);
	    }
	  if (_buffer.size() > size - str.size())
	    {
	      str += _buffer.substr(0, size - str.size());
	      _buffer = _buffer.substr(size - str.size(), 
				       _buffer.size() - size - str.size());
	    }
	  else
	    {
	      str += _buffer;
	      _buffer = "";
	    }
	  if (str.size() >= size)
	    end = true;
	}
    return str;
  }

  std::string	LocalSocket::_read_line(int socket)
  {
    char		chr[MAXPKTSIZE];
    std::string		str = "";
    int			res = 1, i;
    std::pair<int, int> delim;
    bool		end = false;

    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    if (!_update_buffer(delim, i, str))
      while (!end)
	{
	  memset(chr, 0, MAXPKTSIZE);
#ifdef __CYGWIN__
	  res = recv(socket, chr, MAXPKTSIZE, 0);
#else
	  res = recv(socket, chr, MAXPKTSIZE, MSG_TRUNC);
#endif
	  if (res <= 0)
	    throw ConnectionClosed("Connection Closed", HERE);
	  _buffer += std::string(chr, res);
	  if (_update_buffer(delim, i, str))
	    end = true;
	}
    _state_timeout = 0;
    return str;
  }

  std::string	LocalSocket::_read_line_bin(int socket,
					    std::string& filename,
					    unsigned int pkg_size)
  {
    char		chr[MAXPKTSIZE];
    std::string		str = "";
    int			res = 1;
    struct sockaddr_un	addr;
    size_t		size;
    bool		end = false;

    size = sizeof(addr);
    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    if (_buffer.size() >= 2 && !pkg_size)
      {
	pkg_size = (unsigned char)_buffer[0] * 256 + (unsigned char)_buffer[1];
	_buffer = _buffer.substr(2, _buffer.size() - 2);
      }
    if (pkg_size && _buffer.size() >= pkg_size)
      {
	str = _buffer.substr(0, pkg_size);
	_buffer = _buffer.substr(pkg_size, _buffer.size() - pkg_size);
      }
    else
      while (!end)
	{
#ifdef __CYGWIN__
	  res = recvfrom(socket, chr, MAXPKTSIZE, 0,
			 (struct sockaddr*)&addr,
			 (socklen_t*)&size);
#else
	  res = recvfrom(socket, chr, MAXPKTSIZE, MSG_TRUNC,
			 (struct sockaddr*)&addr,
			 (socklen_t*)&size);
#endif
	  if (res <= 0)
	    throw ConnectionClosed("Connection Closed", HERE);
	  // _buffer += all octets received
	  _buffer += std::string(chr, res).substr(0, res);
	  if (!pkg_size)
	    {
	      // extract size from _buffer and reduce it
	      pkg_size = (unsigned char)_buffer[0] * 256 + 
		(unsigned char)_buffer[1];
	      _buffer = _buffer.substr(2, _buffer.size() - 2);
	    }
	  if (_buffer.size() > pkg_size - str.size())
	    {
	      str += _buffer.substr(0, pkg_size - str.size());
	      _buffer = _buffer.substr(pkg_size - str.size(), 
				       _buffer.size() - pkg_size - str.size());
	    }
	  else
	    {
	      str += _buffer;
	      _buffer = "";
	    }
	  if (str.size() >= pkg_size)
	    end = true;
	}
    filename = std::string(addr.sun_path);
    return str;
  }

  void LocalSocket::writeto(const std::string& str,
			    const std::string& filename)
  {
    if (_proto_kind == binary)
      _write_str_bin(_socket, str, filename);
    else
      _write_str(_socket, str, filename);
  }

  std::string	LocalSocket::readn(unsigned int size)
  {
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, size);
  }

  std::string	LocalSocket::readn(int timeout, unsigned int size)
  {
    if (!size || size > _buffer.size())
      _set_timeout(true, _socket, timeout);
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, size);
  }

  std::string	LocalSocket::readn(std::string& filename, unsigned int size)
  {
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, filename, size);
  }

  std::string	LocalSocket::readn(std::string& filename,
				   int timeout, unsigned int size)
  {
    if (!size || size > _buffer.size())
      _set_timeout(true, _socket, timeout);
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, filename, size);
  }

  std::string	LocalSocket::read()
  {
    if (_proto_kind == binary)
      return _read_line_bin(_socket, 0);
    else
      return _read_line(_socket);
  }

  std::string	LocalSocket::read(int timeout)
  {
    if (_proto_kind == binary)
      {
	_set_timeout(true, _socket, timeout);
	return _read_line_bin(_socket, 0);
      }
    else
      {
	_state_timeout = timeout;
	return _read_line(_socket);
      }
  }

  std::string	LocalSocket::read(std::string& filename)
  {
    if (_proto_kind)
      return _read_line_bin(_socket, filename, 0);
    else
      return _read_line(_socket, filename);
  }

  std::string	LocalSocket::read(std::string& filename, int timeout)
  {
    if (_proto_kind == binary)
      {
	_set_timeout(true, _socket, timeout);
	return _read_line_bin(_socket, filename, 0);
      }
    else
      {
	_state_timeout = timeout;
	return _read_line(_socket, filename);
      }
  }
}

#endif
