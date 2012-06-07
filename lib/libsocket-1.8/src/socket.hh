/*
** socket.hh
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sat Mar  1 23:20:24 2003 Julien Lemoine
** $Id: socket.hh,v 1.12 2006/12/28 17:49:58 speedblue Exp $
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

#ifndef   	SOCKET_HH_
# define   	SOCKET_HH_

#include <iostream>
#include <list>
#include <string>

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
# define LIBSOCKET_WIN
#endif

#ifdef LIBSOCKET_WIN
# include <winsock.h>
#else
# include <sys/types.h>	// for connect(), bind(), accept(),
# include <sys/time.h>   // for struct timeval
#endif

#ifdef LIBSOCKET_WIN
# define SENDTO_FLAGS 0
#else
# if defined(__APPLE__) && defined(__MACH__)
#  define SENDTO_FLAGS 0
# else
#  define SENDTO_FLAGS MSG_NOSIGNAL
# endif
# include <sys/socket.h>// for connect(), listen(), bind() accept(),
# include <netinet/in.h>// for ntons(), htonl(), etc...
# include <arpa/inet.h>	// for inet_addre()
# include <netdb.h>	// for gethostbyname()
# include <unistd.h>	// for read()
#endif

#ifdef TLS
# include <gnutls/gnutls.h>
#endif

#include "socketexception.hh"

/// Network namespace represent all networks connection
namespace Network
{
  typedef enum e_gnutls_kind
    {
      LIBSOCKET_TLS,
      LIBSOCKET_SSL
    } GnuTLSKind;

  typedef enum e_pkind
    {
      text,
      binary
    } PROTO_KIND;

  typedef enum e_kind
    {
      TCP,
      UDP,
      LOCAL
    } SOCKET_KIND;

  typedef enum e_version
    {
      V4,
      V6
    } SOCKET_VERSION;

  // ip header 20 bytes
  // udp header 8 bytes
  static const int	MAXPKTSIZE	=	65507;

  static const char	DEFAULT_DELIM	=	'\0';

  /// @author Julien Lemoine <speedblue at happycoders dot org>
  /// @brief This class represent an abstract socket connection (udp
  /// | tcp server | tcp client)
  class Socket
  {
  public:
    Socket(SOCKET_KIND kind, SOCKET_VERSION version = V4);
    Socket(SOCKET_KIND kind, PROTO_KIND pkind, SOCKET_VERSION version = V4);
    virtual ~Socket();

  public:
    /// @brief function used by << operator (write a string on
    /// current socket)
    void		write(const std::string& str);

    ///@brief return true when socket is connected
    bool		connected() const;

    /// @brief get socket (fd)
    /// warning: be very carefull with this method
    int			get_socket();
    ///@brief set the delimitor for the text mode
    void		add_delim(const std::string& delim);
    ///@brief delete this delimitor for the socket
    void		del_delim(const std::string& delim);
    ///@brief, if set, empty lines will be returned in text procols
    ///(if not, they are skipped)
    void		allow_empty_lines();

    // Initialize GNUTLS support
    /// @exception TLSSupportError when TLS is not enabled
    void	init_tls(GnuTLSKind kind,
			 unsigned size = 1024,
			 const std::string &certfile = "",
			 const std::string &keyfile = "",
			 const std::string &trustfile = "",
			 const std::string &crlfile = "");

    /// Enable TLS on socket
    void	enable_tls();

    /// @brief function used by >> operator (read a string on
    /// current socket)
    virtual std::string	read() = 0;
    /// @brief read a string with a timeout
    virtual std::string	read(int timeout) = 0;
    /// @brief read a string from socket
    /// @param size represente the number of byte to read
    virtual std::string	readn(unsigned int size) = 0;
    /// @brief read a string with a timeout
    /// @param size represente the number of byte to read
    virtual std::string	readn(int timeout, unsigned int size) = 0;

  protected:
    /// @brief Close a connnection
    /// @exception CloseException when close libc function return a
    /// negative value
    void	_close(int socket) const;
    /// @brief Listen on port
    /// @exception ListenException when listen libc function return a
    /// negative value
    void	_listen(int socket) const;
    /// @brief Get a line from socket (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    virtual std::string	_read_line(int socket) = 0;
    /// @brief Get a line from socket (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    virtual std::string	_read_line_bin(int socket, unsigned int size) = 0;
    /// @brief Write a string to a socket (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    void	_write_str(int socket, const std::string& str) const;
    /// @brief Write a string to a socket (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    void	_write_str_bin(int socket, const std::string& str) const;
    /// @brief set a timeout on a socket
    /// @param timeout is in second
    /// @exception Timeout when there is a timeout
    /// @exception SelectError when select libc function return a
    /// negative value
    void	_set_timeout(bool enable, int socket, int timeout);
    // @brief find the index and the size of the delimiter.
    std::pair<int, int>		_find_delim(const std::string& str, int start) const;
    /// @brief look delimiter and remove delimiter at begining of
    /// buffer if needed
    bool _update_buffer(std::pair<int, int> &delim, int &i, std::string &str);
    /// @brief return the content of the buffer is there is 
    bool _check_answer(int res, std::string &str);

  protected:
    SOCKET_KIND			_kind;
    SOCKET_VERSION		_version;
    unsigned			_state_timeout;
    int				_socket;
    int				_recv_flags;
    struct sockaddr_in		_addr;
# ifdef IPV6_ENABLED
    struct sockaddr_in6		_addr6;
# endif
    PROTO_KIND			_proto_kind;
    std::list<std::string>	_delim;
    bool			_empty_lines;
    std::string			_buffer;
    bool			_tls;
# ifdef TLS
    gnutls_session			_session;
    gnutls_certificate_credentials	_x509_cred;
    unsigned				_nbbits;
    bool				_tls_main;
# endif
  };

  /// @brief write a string on current socket
  Socket&	operator<<(Socket& s, const std::string& str);
  /// @brief read a string on current socket
  Socket&	operator>>(Socket& s, std::string& str);
}

#endif	    /* !SOCKET_HH_ */
