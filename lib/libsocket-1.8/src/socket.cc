/*
** socket.cc
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sat Mar  1 23:01:09 2003 Julien Lemoine
** $Id: socket.cc,v 1.17 2006/12/28 17:49:58 speedblue Exp $
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
#include <fstream>
#include <sys/types.h>
#include "socket.hh"

namespace Network
{

  Socket::Socket(SOCKET_KIND kind, SOCKET_VERSION version) :
    _kind(kind), _version(version), _state_timeout(0),
    _socket(0), _recv_flags(kind), _proto_kind(text), _empty_lines(false),
    _buffer(""), _tls(false)
  {
    _delim.push_back("\0");
#ifdef LIBSOCKET_WIN
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(1, 1), &wsadata) != 0)
      throw WSAStartupError("WSAStartup failed", HERE);
#endif
#ifndef IPV6_ENABLED
    if (version == V6)
      throw Ipv6SupportError("lib was not compiled with ipv6 support", HERE);
#endif
  }

  Socket::Socket(SOCKET_KIND kind, PROTO_KIND pkind, SOCKET_VERSION version) :
    _kind(kind), _version(version), _state_timeout(0),
    _socket(0), _recv_flags(kind), _proto_kind(pkind), _empty_lines(false),
    _buffer(""), _tls(false)
  {
    _delim.push_back("\0");
#ifdef LIBSOCKET_WIN
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(1, 1), &wsadata) != 0)
      throw WSAStartupError("WSAStartup failed", HERE);
#endif
#ifndef IPV6_ENABLED
    if (version == V6)
      throw Ipv6SupportError("lib was not compiled with ipv6 support", HERE);
#endif
  }

  Socket::~Socket()
  {
  }

  void	Socket::enable_tls()
  {
#ifdef TLS
    int		ret;

    if (_kind != TCP)
      throw TLSError("You need to have a TCP connection", HERE);
    if (!connected())
      throw NoConnection("You need to have a connection", HERE);
    
    gnutls_transport_set_ptr(_session, (gnutls_transport_ptr)_socket);
    ret = gnutls_handshake(_session);
    if (ret < 0)
      {
	close(_socket);
	gnutls_deinit(_session);
	throw TLSError(gnutls_strerror(ret), HERE);
      }
#else
    throw TLSSupportError("lib was not compiled with TLS support", HERE);
#endif
  }

  void	Socket::init_tls(GnuTLSKind kind,
			 unsigned size, const std::string &certfile,
			 const std::string &keyfile,
			 const std::string &trustfile,
			 const std::string &crlfile)
  {
#ifdef TLS
    static bool					init = false;
    static gnutls_dh_params			dh_params;
    const int protocol_tls[] = { GNUTLS_TLS1, 0 };
    const int protocol_ssl[] = { GNUTLS_SSL3, 0 };
    const int cert_type_priority[] = { GNUTLS_CRT_X509, 
				       GNUTLS_CRT_OPENPGP, 0 };

    if (!init)
      {
	gnutls_global_init();
	init = true;
      }
    _tls = true;
    _tls_main = true;
    gnutls_certificate_allocate_credentials(&_x509_cred);
    if (keyfile.size() > 0 && certfile.size() > 0)
      {
	std::ifstream key(keyfile.c_str()), cert(certfile.c_str());
	if (!key.is_open() || !cert.is_open())
	  throw InvalidFile("key or cert invalid", HERE);
	key.close();
	cert.close();
	// Only for server...
	_nbbits = size;
	if (trustfile.size() > 0)
	  gnutls_certificate_set_x509_trust_file(_x509_cred, trustfile.c_str(), 
						 GNUTLS_X509_FMT_PEM);
	if (crlfile.size() > 0)
	  gnutls_certificate_set_x509_crl_file(_x509_cred, crlfile.c_str(), 
					       GNUTLS_X509_FMT_PEM);
	gnutls_certificate_set_x509_key_file(_x509_cred, certfile.c_str(), 
					     keyfile.c_str(), 
					     GNUTLS_X509_FMT_PEM);
	gnutls_dh_params_init(&dh_params);
	gnutls_dh_params_generate2(dh_params, _nbbits);
	gnutls_certificate_set_dh_params(_x509_cred, dh_params);

	if (gnutls_init(&_session, GNUTLS_SERVER))
	  throw TLSError("gnutls_init failed", HERE);
      }
    else
      {
	if (gnutls_init(&_session, GNUTLS_CLIENT))
	  throw TLSError("gnutls_init failed", HERE);
      }
    
    gnutls_set_default_priority(_session);
    if (kind == TLS)
      gnutls_protocol_set_priority(_session, protocol_tls);
    else
      gnutls_protocol_set_priority(_session, protocol_ssl);

    if (keyfile.size() > 0 && certfile.size() > 0)
      {
	gnutls_credentials_set(_session, GNUTLS_CRD_CERTIFICATE, _x509_cred);
	gnutls_certificate_server_set_request(_session, GNUTLS_CERT_REQUEST);
	gnutls_dh_set_prime_bits(_session, _nbbits);
      }
    else
      {
	gnutls_certificate_type_set_priority(_session, cert_type_priority);
	gnutls_credentials_set(_session, GNUTLS_CRD_CERTIFICATE, _x509_cred);
      }
#else
    throw TLSSupportError("lib was not compiled with TLS support", HERE);
#endif
  }

  void	Socket::_close(int socket) const
  {
#ifndef LIBSOCKET_WIN
    if (socket < 0 || close(socket) < 0)
      throw CloseError("Close Error", HERE);
    socket = 0;
#else
    if (socket < 0 || closesocket(socket) < 0)
      throw CloseError("Close Error", HERE);
    socket = 0;
#endif
#ifdef TLS
    if (_tls)
      {
	std::cout << "Deletion..." << std::endl;
	gnutls_deinit(_session);
	if (_tls_main)
	  {
	    gnutls_certificate_free_credentials(_x509_cred);
	    gnutls_global_deinit();
	  }
      }
#endif
  }

  void	Socket::_listen(int socket) const
  {
    if (socket < 0 || listen(socket, 5) < 0)
      throw ListenError("Listen Error", HERE);
  }

  void	Socket::_write_str(int socket, const std::string& str) const
  {
    int				res = 1;
    unsigned int		count = 0;
    const char			*buf;

    buf = str.c_str();
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
	    res = sendto(socket, buf + count, str.size() - count, SENDTO_FLAGS,
			 (const struct sockaddr*)&_addr, sizeof(_addr));
#ifdef IPV6_ENABLED
	else
	  res = sendto(socket, buf + count, str.size() - count, SENDTO_FLAGS,
		       (const struct sockaddr*)&_addr6, sizeof(_addr6));
#endif
	if (res <= 0)
	  throw ConnectionClosed("Connection Closed", HERE);
	count += res;
      }
  }

  void	Socket::_write_str_bin(int socket, const std::string& str) const
  {
    int				res = 1;
    unsigned int		count = 0;
    char*			buf = new char[str.size() + 2];

    buf[0] = str.size() / 256;
    buf[1] = str.size() % 256;
    memcpy(buf + 2, str.c_str(), str.size());
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
	    res = sendto(socket, buf + count, str.size() + 2 - count, SENDTO_FLAGS,
			 (const struct sockaddr*)&_addr, sizeof(_addr));
#ifdef IPV6_ENABLED
	else
	  res = sendto(socket, buf + count, str.size() + 2 - count, SENDTO_FLAGS,
		       (const struct sockaddr*)&_addr6, sizeof(_addr6));
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

  void	Socket::_set_timeout(bool enable, int socket, int timeout)
  {
    fd_set		fdset;
    struct timeval	timetowait;
    int		res;

    if (enable)
      timetowait.tv_sec = timeout;
    else
      timetowait.tv_sec = 65535;
    timetowait.tv_usec = 0;
    FD_ZERO(&fdset);
    FD_SET(socket, &fdset);
    if (enable)
      res = select(socket + 1, &fdset, NULL, NULL, &timetowait);
    else
      res = select(socket + 1, &fdset, NULL, NULL, NULL);
    if (res < 0)
      throw SelectError("Select error", HERE);
    if (res == 0)
      throw Timeout("Timeout on socket", HERE);
  }

  void	Socket::write(const std::string& str)
  {
    if (_proto_kind == binary)
      _write_str_bin(_socket, str);
    else
      _write_str(_socket, str);
  }

  bool	Socket::connected() const
  {
    return _socket != 0;
  }

  void	Socket::allow_empty_lines()
  {
    _empty_lines = true;
  }

  int	Socket::get_socket()
  {
    return _socket;
  }

  void	Socket::add_delim(const std::string& delim)
  {
    _delim.push_back(delim);
  }

  void	Socket::del_delim(const std::string& delim)
  {
    std::list<std::string>::iterator	it, it2;

    for (it = _delim.begin(); it != _delim.end(); )
      {
	if (*it == delim)
	  {
	    it2 = it++;
	    _delim.erase(it2);
	  }
	else
	  it++;
      }
  }

  std::pair<int, int>	Socket::_find_delim(const std::string& str, int start) const
  {
    int						i = -1;
    int						pos = -1, size = 0;
    std::list<std::string>::const_iterator	it;

    // Looking for the first delimiter.
    if (_delim.size() > 0)
      {
	it = _delim.begin();
	while (it != _delim.end())
	  {
	    if (*it == "")
	      i = str.find('\0', start);
	    else
	      i = str.find(*it, start);
	    if ((i >= 0) && ((unsigned int)i < str.size()) &&
		(pos < 0 || i < pos))
	      {
		pos = i;
		size = it->size() ? it->size() : 1;
	      }
	    it++;
	  }
      }
    return std::pair<int, int>(pos, size);
  }

  Socket&	operator<<(Socket& s, const std::string& str)
  {
    s.write(str);
    return s;
  }

  Socket&	operator>>(Socket& s, std::string& str)
  {
    str = s.read();
    return s;
  }
}
