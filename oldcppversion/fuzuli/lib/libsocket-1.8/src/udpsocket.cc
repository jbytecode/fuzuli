/*
** udpsocket.cc
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sun Mar  2 01:01:49 2003 Julien Lemoine
** $Id: udpsocket.cc,v 1.3 2004/11/14 19:37:46 speedblue Exp $
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

#include <string.h>
#include "udpsocket.hh"

namespace Network
{
  void	UdpSocket::connect(const std::string& hostname, int port)
  {
    _port = port;
    _socket = _bind(port, hostname);
  }

  void	UdpSocket::connect(int port)
  {
    _socket = _bind(port);
    _port = port;
  }

  void	UdpSocket::close()
  {
    if (_socket > 0)
      _close(_socket);
    _socket = 0;
  }

  std::string	UdpSocket::_read_line_bin(int socket, unsigned int size)
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
#ifdef LIBSOCKET_WIN
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

  std::string	UdpSocket::_read_line_bin(int socket, int& port,
					  std::string& host, 
					  unsigned int pkg_size)
  {
    char			chr[MAXPKTSIZE];
    std::string			str = "";
    int				res = 1;
    struct sockaddr_in		addr;
#ifdef IPV6_ENABLED
    struct sockaddr_in6		addr6;
#endif
#ifdef LIBSOCKET_WIN
    int				size;
#else
    socklen_t			size;
#endif
    bool			end = false;

#ifdef IPV6_ENABLED
    if (V4 == _version)
#endif
      size = sizeof(addr);
#ifdef IPV6_ENABLED
    else
      size = sizeof(addr6);
#endif
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
#ifdef LIBSOCKET_WIN
	  int flags = 0;
#else
	  int flags = MSG_TRUNC;
#endif
#ifdef IPV6_ENABLED
	  if (V4 == _version)
#endif
	    res = recvfrom(socket, chr, MAXPKTSIZE, flags,
			   (struct sockaddr *) &addr, &size);
#ifdef IPV6_ENABLED
	  else
	    res = recvfrom(socket, chr, MAXPKTSIZE, flags,
			   (struct sockaddr *) &addr6, &size);
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
#ifdef IPV6_ENABLED
    if (V4 == _version)
      {
#endif
	host = std::string(inet_ntoa(addr.sin_addr));
	port = ntohs(addr.sin_port);
#ifdef IPV6_ENABLED
      }
    else
      {
	char buf[INET6_ADDRSTRLEN];
	if (inet_ntop(AF_INET6, &addr6.sin6_addr, buf, INET6_ADDRSTRLEN) == 0)
	  throw InetntopError("Not a valid address", HERE);
	host = std::string(buf);
	port = ntohs(addr6.sin6_port);
      }
#endif
    return str;
  }

}
