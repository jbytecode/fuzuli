/*
** tcpsocket.cc
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sun Mar  2 01:18:46 2003 Julien Lemoine
** $Id: tcpsocket.cc,v 1.8 2006/12/28 17:49:58 speedblue Exp $
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
#include "tcpsocket.hh"

namespace Network
{

  void	TcpSocket::connect(const std::string& hostname, int port)
  {
    _port = port;
    _socket = _bind(port, hostname);
    _connect(_socket, port, hostname);
  }

  void	TcpSocket::connect(int port)
  {
    _port = port;
    _socket = _bind(port);
    _listen(_socket);
  }

  TcpSocket*	TcpSocket::accept() const
  {
    TcpSocket* res;

#ifdef IPV6_ENABLED
    if (V4 == _version)
#endif
      res = new TcpSocket(_accept(_port, _socket));
#ifdef IPV6_ENABLED
    else
      res = new TcpSocket(_accept(_port, _socket), V6);
#endif
    res->_port = _port;
    res->_proto_kind = _proto_kind;
#ifdef TLS
    if (_tls)
      {
	res->_tls = true;
	res->_tls_main = false;
	res->_session = _session;
	res->_x509_cred = _x509_cred;
	res->enable_tls();
      }
#endif
    return res;
  }

  std::string	TcpSocket::get_ip(TcpSocket *client) const
  {
    return _get_ip(_port, client->_socket);
  }

  void	TcpSocket::close()
  {
    if (_socket > 0)
      _close(_socket);
    _socket = 0;
  }

  std::string	TcpSocket::_read_line_bin(int socket, unsigned int psize)
  {
    char		chr[MAXPKTSIZE];
    std::string		str = "";
    int			res = 1;
    unsigned int	size = 0, read = 0, buffsize;
    bool		end = false;

    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    if (_buffer.size() >= 2 && !psize)
      {
	size = (unsigned char)_buffer[0] * 256 + (unsigned char)_buffer[1];
	str = _buffer.substr(2, size);
	if (_buffer.size() > size + 2)
	  _buffer = _buffer.substr(size + 2, _buffer.size() - size - 2);
	else
	  _buffer = "";
	read = str.size();
      }
    if (psize && _buffer.size() >= psize)
      {
	str = _buffer.substr(0, psize);
	_buffer = _buffer.substr(psize, _buffer.size() - psize);
	return str;
      }
    else if (!psize)
      {
	// _buffer.size() is 0 or 1
#ifdef TLS
	if (_tls)
	  res = gnutls_record_recv(_session, chr, 2 - _buffer.size());
	else
#endif
	  res = recv(socket, chr, 2 - _buffer.size(), 0);
	if (res <= 1)
	  throw ConnectionClosed("Connection Closed", HERE);
	if (_buffer.size())
	  size = (unsigned char)_buffer[0] * 256 + (unsigned char)chr[0];
	else
	  size = (unsigned char)chr[0] * 256 + (unsigned char)chr[1];
	_buffer = "";
      }
    else
      {
	// _buffer contains less characters than size, so copy
	// _bufer in str and clear _buffer.
	str = _buffer;
	_buffer = "";
	size = psize;
	read = str.size();
      }
    while (!end)
      {
	memset(chr, 0, MAXPKTSIZE);
	buffsize = (size - read > (unsigned)MAXPKTSIZE) ? MAXPKTSIZE : size - read;
#ifdef TLS
	if (_tls)
	  res = gnutls_record_recv(_session, chr, buffsize);
	else
#endif
	  res = recv(socket, chr, buffsize, 0);
	if (res <= 0)
	  throw ConnectionClosed("Connection Closed", HERE);
	str += std::string(chr, res).substr(0, res);
	read += res;
	if (read >= size)
	  end = true;
      }
    return str;
  }

  std::string	TcpSocket::_read_line_bin(int socket, int& port,
					  std::string& host,
					  unsigned int psize)
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
    unsigned int		pkg_size = 0, read = 0, buffsize;

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
    if (_buffer.size() >= 2 && !psize)
      {
	pkg_size = (unsigned char)_buffer[0] * 256 + (unsigned char)_buffer[1];
	str = _buffer.substr(2, pkg_size);
	if (_buffer.size() > pkg_size + 2)
	  _buffer = _buffer.substr(pkg_size + 2, _buffer.size() - pkg_size - 2);
	else
	  _buffer = "";
	read = str.size();
      }
    if (psize && _buffer.size() >= psize)
      {
	str = _buffer.substr(0, psize);
	_buffer = _buffer.substr(psize, _buffer.size() - psize);
	return str;
      }
    else if (!psize)
      {
	// _buffer.size() is 0 or 1
#ifdef TLS
	if (_tls)
	  res = gnutls_record_recv(_session, chr, 2 - _buffer.size());
	else
#endif
	  res = recv(socket, chr, 2 - _buffer.size(), 0);
	if (res <= 1)
	  throw ConnectionClosed("Connection Closed", HERE);
	if (_buffer.size())
	  pkg_size = (unsigned char)_buffer[0] * 256 + (unsigned char)chr[0];
	else
	  pkg_size = (unsigned char)chr[0] * 256 + (unsigned char)chr[1];
	_buffer = "";
      }
    else
      {
	// _buffer contains less characters than size, so copy
	// _bufer in str and clear _buffer.
	str = _buffer;
	_buffer = "";
	pkg_size = psize;
	read = str.size();
      }
    while (!end)
      {
	buffsize = (size - read > (unsigned)MAXPKTSIZE ? MAXPKTSIZE : size - read);
#ifdef TLS
	if (_tls)
	  res = gnutls_record_recv(_session, chr, buffsize);
	else
#endif
	  res = recv(socket, chr, buffsize, 0);
#ifdef IPV6_ENABLED
	if (V4 == _version)
#endif
	  if (getpeername(socket, (struct sockaddr *) &addr, &size) < 0)
	    throw GetpeernameError("getpeername error", HERE);
#ifdef IPV6_ENABLED
	else
	  if (getpeername(socket, (struct sockaddr *) &addr6, &size) < 0)
	    throw GetpeernameError("getpeername error", HERE);
#endif
	if (res <= 0)
	  throw ConnectionClosed("Connection Closed", HERE);
	str += std::string(chr, res).substr(0, res);
	read += res;
	if (read >= pkg_size)
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
