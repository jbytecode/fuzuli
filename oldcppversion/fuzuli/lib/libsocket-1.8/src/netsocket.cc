/*
** netsocket.cc
** Login : Julien Lemoine <speedblue@happycoder.org>
** Started on  Mon May 12 22:23:27 2003 Julien Lemoine
** $Id: netsocket.cc,v 1.14 2006/12/28 17:49:58 speedblue Exp $
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
#include <iostream>
#include "netsocket.hh"
#include "socket.hxx"

namespace Network
{

  struct sockaddr_in	NetSocket::_get_addr(const std::string& host,
					     int port) const
  {
    struct hostent	*he;
    struct sockaddr_in	addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));
    he = gethostbyname(host.c_str());
    if (!he)
      throw HostnameError("Unknown Hostname", HERE);
    addr.sin_addr = *((struct in_addr *)he->h_addr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    return addr;
  }

#ifdef IPV6_ENABLED
  struct sockaddr_in6	NetSocket::_get_addr6(const std::string& host,
					      int port) const
  {
    struct sockaddr_in6	addr;

    memset(&addr, 0, sizeof(struct sockaddr_in6));
    if ( inet_pton(AF_INET6, host.c_str(), &addr.sin6_addr) == 0 )
      throw InetptonError("Unknown Hostname", HERE);
    addr.sin6_port = htons(port);
    addr.sin6_family = AF_INET6;
    return addr;
  }
#endif

  struct sockaddr_in	NetSocket::_get_addr(int port) const
  {
    struct sockaddr_in	addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    return addr;
  }

#ifdef IPV6_ENABLED
  struct sockaddr_in6	NetSocket::_get_addr6(int port) const
  {
    struct sockaddr_in6	addr;

    memset(&addr, 0, sizeof(struct sockaddr_in6));
    if ( inet_pton(AF_INET6, "0::0", &addr.sin6_addr) == 0 )
      throw InetptonError("Not a valid address", HERE);
    addr.sin6_port = htons(port);
    addr.sin6_family = AF_INET6;
    return addr;
  }
#endif

  int		NetSocket::_bind(int port, const std::string& host)
  {
    int			s;

    if (_kind == UDP)
      {
#ifdef IPV6_ENABLED
	if (_version == V4)
#endif
	  s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef IPV6_ENABLED
	else
	  s = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
#endif
      }
    else if (_kind == TCP)
      {
#ifdef IPV6_ENABLED
	if (_version == V4)
#endif
	  s = socket(PF_INET, SOCK_STREAM, 0);
#ifdef IPV6_ENABLED
	else
	  s = socket(PF_INET6, SOCK_STREAM, 0);
#endif
      }
    else
      throw Exception("Unknown Protocole", HERE);

    if (s < 0)
      throw SocketError("Socket error", HERE);
#ifdef IPV6_ENABLED
    if (_version == V4)
#endif
      _addr = _get_addr(host, port);
#ifdef IPV6_ENABLED
    else
      _addr6 = _get_addr6(host, port);
#endif
    return s;
  }

  int		NetSocket::_bind(int port)
  {
    int			s, on;

    if (_kind == TCP)
      {
#ifdef IPV6_ENABLED
	if (_version == V4)
#endif
	  s = socket(PF_INET, SOCK_STREAM, 0);
#ifdef IPV6_ENABLED
	else
	  s = socket(PF_INET6, SOCK_STREAM, 0);
#endif
      }
    else if (_kind == UDP)
      {
#ifdef IPV6_ENABLED
	if (_version == V4)
#endif
	  s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef IPV6_ENABLED
	else
	  s = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
#endif
      }
    else
      throw Exception("Unknown Protocole", HERE);
    if (s < 0)
      throw SocketError("Socket error", HERE);
    on = 1;

    if (_kind == TCP && setsockopt(s, SOL_SOCKET,
				   SO_REUSEADDR, (void *)&on,
				   sizeof (on)) == -1)
      throw SetsockoptError("setsockopt error", HERE);

#ifdef IPV6_ENABLED
    if (_version == V4)
      {
#endif
	struct sockaddr_in	addr;
	addr = _get_addr(port);
	if (bind(s,(struct sockaddr*)&addr, (int)sizeof(addr)) == -1)
	  throw BindError("Bind error", HERE);
#ifdef IPV6_ENABLED
      }
    else
      {
	struct sockaddr_in6	addr6;
	addr6 = _get_addr6(port);
	if (bind(s,(struct sockaddr*)&addr6, (int)sizeof(addr6)) == -1)
	  throw BindError("Bind error", HERE);
      }
#endif
    return s;
  }

  void	NetSocket::_connect(int socket, int port,
			    const std::string& host) const
  {
#ifdef IPV6_ENABLED
    if (_version == V4)
      {
#endif
	struct sockaddr_in	addr;
	addr = _get_addr(host, port);
	if (connect(socket, (struct sockaddr *)&addr,
		    sizeof (addr)) < 0)
	  throw ConnectError("Unable to connect", HERE);
#ifdef IPV6_ENABLED
      }
    else
      {
	struct sockaddr_in6	addr6;
	addr6 = _get_addr6(host, port);
	if (connect(socket, (struct sockaddr *)&addr6,
		    sizeof (addr6)) < 0)
	  throw ConnectError("Unable to connect", HERE);
      }
#endif
  }

  int		NetSocket::_accept(int port, int socket) const
  {
#ifdef LIBSOCKET_WIN
    int				size;
#else
    socklen_t			size;
#endif
    int			s;
    struct sockaddr_in	addr;
#ifdef IPV6_ENABLED
    struct sockaddr_in6	addr6;

    if (_version == V4)
      {
#endif
	addr = _get_addr(port);
	size = sizeof(addr);
	s = accept(socket, (struct sockaddr*)&addr, &size);
#ifdef IPV6_ENABLED
      }
    else
      {
	addr6 = _get_addr6(port);
	size = sizeof(addr6);
	s = accept(socket, (struct sockaddr*)&addr6, &size);
      }
#endif
    if (s < 0)
      throw AcceptError("Accept Error", HERE);
    return s;
  }

  std::string	NetSocket::_get_ip(int port, int socket) const
  {
    struct sockaddr_in        addr;
#ifdef LIBSOCKET_WIN
    int				size;
#else
    socklen_t			size;
#endif

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    size = sizeof(addr);
    getpeername(socket, (struct sockaddr *)&addr, &size);
    return(std::string(inet_ntoa(addr.sin_addr)));
  }

  std::string	NetSocket::_read_line(int socket)
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
	  if (_state_timeout)
	    _set_timeout(true, _socket, _state_timeout);
	  if (_kind == UDP)
#ifdef LIBSOCKET_WIN
	    res = recv(socket, chr, MAXPKTSIZE, 0);
#else
	    res = recv(socket, chr, MAXPKTSIZE, MSG_TRUNC);
#endif
	  else
#ifdef TLS
	    if (_tls)
	      res = gnutls_record_recv(_session, chr, MAXPKTSIZE);
	    else
#endif
	      res = recv(socket, chr, MAXPKTSIZE, 0);
	  if (_check_answer(res, str))
	    return str;
	  _buffer += std::string(chr, res);
	  if (_update_buffer(delim, i, str))
	    end = true;
	}
    _state_timeout = 0;
    return str;
  }

  std::string	NetSocket::_read_line(int socket, int& port,
				      std::string& host)
  {
    char			chr[MAXPKTSIZE];
    std::string			str = "";
    int				res = 1, i;
    std::pair<int, int>		delim;
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
    if (!_update_buffer(delim, i, str))
      while (!end)
	{
	  if (_state_timeout)
	    _set_timeout(true, _socket, _state_timeout);
	  if (_kind == UDP)
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
	    }
	  else
	    {
#ifdef TLS
	      if (_tls)
		res = gnutls_record_recv(_session, chr, MAXPKTSIZE);
	      else
#endif
		res = recvfrom(socket, chr, MAXPKTSIZE, 0, NULL, 0);
#ifdef IPV6_ENABLED
	      if (V4 == _version)
		{
#endif
		  if (getpeername(socket, (struct sockaddr *) &addr, &size) < 0)
		    throw GetpeernameError("getpeername error", HERE);
#ifdef IPV6_ENABLED
		}
	      else
		if (getpeername(socket, (struct sockaddr *) &addr6, &size) < 0)
		  throw GetpeernameError("getpeername error", HERE);
#endif
	    }
	  if (_check_answer(res, str))
	    return str;
	  _buffer += std::string(chr, res);
	  if (_update_buffer(delim, i, str))
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
    _state_timeout = 0;
    return str;
  }

  void	NetSocket::_write_str(int socket, const std::string& str,
			      const std::string& host, int port) const
  {
    struct sockaddr_in		addr;
#ifdef IPV6_ENABLED
    struct sockaddr_in6		addr6;
#endif
    int				res = 1;
    const char			*buf = str.c_str();
    unsigned int		count = 0;

#ifdef IPV6_ENABLED
    if (V4 == _version)
#endif
      addr = _get_addr(host, port);
#ifdef IPV6_ENABLED
    else
      addr6 = _get_addr6(host, port);
#endif
    if (socket < 0)
      throw NoConnection("No Socket", HERE);
    while (res && count < str.size())
      {
#ifdef IPV6_ENABLED
	if (V4 == _version)
#endif
#ifdef TLS
	  if (_tls)
	    res = gnutls_record_send(_session, buf + count, str.size() - count);
	  else
#endif
	    res = sendto(socket, buf + count,
			 str.size() - count, SENDTO_FLAGS,
			 (const struct sockaddr*)&addr, sizeof(_addr));
#ifdef IPV6_ENABLED
	else
	  res = sendto(socket, buf + count,
		       str.size() - count, SENDTO_FLAGS,
		       (const struct sockaddr*)&addr6, sizeof(_addr6));
#endif
	if (res <= 0)
	  throw ConnectionClosed("Connection Closed", HERE);
	count += res;
      }
  }

  void	NetSocket::_write_str_bin(int socket, const std::string& str,
				  const std::string& host, int port) const
  {
    struct sockaddr_in		addr;
#ifdef IPV6_ENABLED
    struct sockaddr_in6		addr6;
#endif
    int				res = 1;
    unsigned int		count = 0;
    char*			buf = new char[str.size() + 2];

    buf[0] = str.size() / 256;
    buf[1] = str.size() % 256;
    memcpy(buf + 2, str.c_str(), str.size());
#ifdef IPV6_ENABLED
    if (V4 == _version)
#endif
      addr = _get_addr(host, port);
#ifdef IPV6_ENABLED
    else
      addr6 = _get_addr6(host, port);
#endif
    if (socket < 0)
      {
	delete[] buf;
	throw NoConnection("No Socket", HERE);
      }
    while (res && count < str.size() + 2)
      {
#ifdef IPV6_ENABLED
	if (V4 == _version)
#endif
#ifdef TLS
	  if (_tls)
	    res = gnutls_record_send(_session, buf + count, str.size() + 2 - count);
	  else
#endif
	    res = sendto(socket, buf + count, str.size() + 2 - count, 
			 SENDTO_FLAGS,
			 (const struct sockaddr*)&addr, sizeof(_addr));
#ifdef IPV6_ENABLED
	else
	  res = sendto(socket, buf + count, str.size() + 2 - count, 
		       SENDTO_FLAGS,
		       (const struct sockaddr*)&addr6, sizeof(_addr6));
#endif
	if (res <= 0)
	  {
	    delete[] buf;
	    throw ConnectionClosed("Connection Closed", HERE);
	  }
	count += res;
      }
    delete[] buf;
  }

  void	NetSocket::writeto(const std::string& str,
			   const std::string& host, int port)
  {
    if (_proto_kind == binary)
      _write_str_bin(_socket, str, host, port);
    else
      _write_str(_socket, str, host, port);
  }

  std::string	NetSocket::read(int& port, std::string& host)
  {
    if (_proto_kind == binary)
      return _read_line_bin(_socket, port, host, 0);
    else
      return _read_line(_socket, port, host);
  }

  std::string	NetSocket::read(int& port, std::string& host, int timeout)
  {
    if (_proto_kind == binary)
      {
	_set_timeout(true, _socket, timeout);
	return _read_line_bin(_socket, port, host, 0);
      }
    else
      {
	_state_timeout = timeout;
	return _read_line(_socket, port, host);
      }
  }

  std::string	NetSocket::read()
  {
    if (_proto_kind == binary)
      return _read_line_bin(_socket, 0);
    else
      return _read_line(_socket);
  }

  std::string	NetSocket::read(int timeout)
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

  std::string	NetSocket::readn(int& port, std::string& host,
				 unsigned int size)
  {
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, port, host, size);
  }

  std::string	NetSocket::readn(int& port, std::string& host, int timeout,
				 unsigned int size)
  {
    if (!size || size > _buffer.size())
      _set_timeout(true, _socket, timeout);
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, port, host, size);
  }

  std::string	NetSocket::readn(unsigned int size)
  {
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, size);
  }

  std::string	NetSocket::readn(int timeout, unsigned int size)
  {
    if (!size || size > _buffer.size())
      _set_timeout(true, _socket, timeout);
    // _read_line_bin is bufferised with the same buffer as textual
    // protocols, so this function can be used for binary and text
    // protocols.
    return _read_line_bin(_socket, size);
  }
}
