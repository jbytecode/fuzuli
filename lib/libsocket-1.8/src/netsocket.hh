/*
** netsocket.hh
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Mon May 12 22:23:32 2003 Julien Lemoine
** $Id: netsocket.hh,v 1.2 2004/06/01 21:30:53 speedblue Exp $
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

#ifndef   	NETSOCKET_HH_
# define   	NETSOCKET_HH_

#include "socket.hh"

namespace Network
{
  /// @author Julien Lemoine <speedblue at happycoders dot org>
  /// @brief This class represent an abstract socket connection (udp
  /// | tcp server | tcp client)
  class NetSocket : public Socket
  {
  public:
    NetSocket(SOCKET_KIND kind, SOCKET_VERSION version = V4) :
      Socket(kind, version), _port(0)
    {
    }
    NetSocket(SOCKET_KIND kind, PROTO_KIND pkind, SOCKET_VERSION version = V4) :
      Socket(kind, pkind, version), _port(0)
    {
    }
    
    virtual ~NetSocket() {}

  public:
    /// @brief function used to send a msg to a specific host (UDP)
    virtual void writeto(const std::string& str,
			 const std::string& host, int port);

    /// @brief function used by >> operator (read a string on
    /// current socket)
    std::string	read();
    /// @brief read a string with a timeout
    std::string	read(int timeout);
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable
    std::string	read(int& port, std::string& host);
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable (with a timeout on listen)
    std::string	read(int& port, std::string& host, int timeout);
    /// @brief read a string from socket
    /// @param size represente the number of byte to read
    std::string	readn(unsigned int size);
    /// @brief read a string with a timeout
    /// @param size represente the number of byte to read
    std::string	readn(int timeout, unsigned int size);
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable
    /// @param size represente the number of byte to read
    std::string	readn(int& port, std::string& host, unsigned int size);
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable (with a timeout on listen)
    /// @param size represente the number of byte to read
    std::string	readn(int& port, std::string& host, int timeout,
		      unsigned int size);

  protected:
    /// @brief internal function (construct a sockaddr)
    struct sockaddr_in	_get_addr(int port) const;
#ifdef IPV6_ENABLED
    struct sockaddr_in6	_get_addr6(int port) const;
#endif

    /// @brief internal function (construct a sockaddr)
    /// @exception HostnameError when host is incorrect
    struct sockaddr_in	_get_addr(const std::string& host,
				  int port) const;
#ifdef IPV6_ENABLED
    struct sockaddr_in6	_get_addr6(const std::string& host,
				   int port) const;
#endif
    /// @brief Bind a UDP server
    /// @exception SocketError when socket libc function return a
    /// negative value
    /// @exception Exception if the selected protocole is incorrect
    /// (is you receive this exception, please submit a bug report)
    int		_bind(int port, const std::string& host);
    /// @brief Bind a TCP server
    /// @exception SocketError when socket libc function return a
    /// negative value
    /// @exception SetsockoptError when setsockopt libc function return a
    /// negative value
    /// @exception BindError when bind libc function return a
    /// negative value
    /// @exception Exception if the selected protocole is incorrect
    /// (is you receive this exception, please submit a bug report)
    int		_bind(int port);
    /// @brief Wait for a client
    /// @exception AcceptError when accept libc function return a
    /// negative value
    int		_accept(int port, int server_socket) const;
    /// @brief Get Client Ip
    std::string	_get_ip(int port, int socket) const;
    /// @brief Connect to a hostname
    /// @exception ConnectError when connect libc function return a
    /// negative value
    void		_connect(int socket, int port,
				 const std::string& host) const;
    /// @brief Get a line from socket (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line(int socket);
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    /// @exception GetpeernameError when getpeername libc function
    /// return a negative value
    std::string	_read_line(int socket, int& port,
			   std::string& host);
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    /// @exception GetpeernameError when getpeername libc function
    /// return a negative value
    virtual std::string	_read_line_bin(int socket, int& port,
				       std::string& host,
				       unsigned int pkg_size) = 0;
    /// @brief Get a line from socket (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    virtual std::string	_read_line_bin(int socket, unsigned int size) = 0;

    /// @brief Write a string to a socket to a particular host (UDP)
    /// (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    void	_write_str(int socket, const std::string& str,
			   const std::string& host, int port) const;
    /// @brief Write a string to a socket to a particular host (UDP)
    /// (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    void	_write_str_bin(int socket, const std::string& str,
			       const std::string& host, int port) const;

  protected:
    int			_port;
  };
}


#endif	    /* !NETSOCKET_HH_ */
