/*
** tcpsocket.hh
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sun Mar  2 01:17:01 2003 Julien Lemoine
** $Id: tcpsocket.hh,v 1.5 2006/12/28 18:01:03 speedblue Exp $
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

#ifndef   	TCPSOCKET_HH_
# define   	TCPSOCKET_HH_

#include "netsocket.hh"

namespace Network
{
  /// @brief This class represent a tcp connection (client and server)
  /// @author Julien Lemoine <speedblue at happycoders dot org>
  class TcpSocket : public NetSocket
  {
  public:
    TcpSocket(SOCKET_VERSION version = V4) :
      NetSocket(TCP, version)
    {}
    TcpSocket(PROTO_KIND pkind, SOCKET_VERSION version = V4) :
      NetSocket(TCP, pkind, version)
    {}
    TcpSocket(int socket, SOCKET_VERSION version = V4) :
      NetSocket(TCP, version)
    {
      _socket = socket;
    }
    TcpSocket(int socket, PROTO_KIND pkind, SOCKET_VERSION version = V4) :
      NetSocket(TCP, pkind, version)
    {
      _socket = socket;
    }

    virtual ~TcpSocket()
    {
      close();
    }

  public:
    /// @brief Connect as an TCP client
    /**
     * Here is an example of tcp client using libsocket :
     * <pre>
     * #include <stdlib.h>
     * #include <iostream>
     * #include <string>
     * #include "socket/tcpsocket.hh"
     *
     * int main(int argc, char **argv)
     * {
     *   Network::TcpSocket            client;
     *   std::string                   str;
     *
     *   if (argc < 3)
     *     {
     *       std::cout << "Use: " << argv[0] << " port hostname" << std::endl;
     *       exit(0);
     *     }
     *   try
     *     {
     *       client.connect(std::string(argv[2]), strtol(argv[1], NULL, 10));
     *       client.add_delim("\n");
     *       client >> str;
     *       std::cout << str << std::endl;
     *
     *       while (str != "quit")
     *         {
     *           std::cin >> str;
     *           client << str;
     *           client >> str;
     *         }
     *       client.close();
     *       exit (0);
     *     }
     *   catch (Network::Exception e) // catch all libsocket errors
     *     {
     *       std::cerr << e;
     *       exit(1);
     *     }
     *
     * }
     * </pre>
     */
    void	connect(const std::string& hostname, int port);
    /// @brief return ip of client (after an accept)
    std::string	get_ip(TcpSocket *client) const;

    /// @brief accept a new client (For server only)
    TcpSocket*	accept() const;
    /// @brief Connect as an TCP server (echo server)
    /**
     * Here is an example of tcp server using libsocket :
     * <pre>
     * #include <stdlib.h>
     * #include <iostream>
     * #include <string>
     * #include "socket/tcpsocket.hh"
     *
     * int main(int argc, char **argv)
     * {
     *   Network::TcpSocket            server;
     *   Network::TcpSocket            *client;
     *   std::string                   str;
     *
     *   if (argc < 2)
     *     {
     *       std::cout << "Use: " << argv[0] << " port" << std::endl;
     *       exit(0);
     *     }
     *   try
     *     {
     *       std::cout << "--- echo server ---" << std::endl;
     *       server.connect(strtol(argv[1], NULL, 10));
     *       server.add_delim("\n");
     *       client = server.accept();
     *       client->add_delim("\n");
     *       (*client) << "Welcome on test server";
     *       while (str != "quit")
     * 	       {
     *
     * 	         //(*client) >> str;
     * 	         // read with a timeout of 30 second and get port and host
     * 	         str = client->read(port, host, 30);
     * 	         std::cout << "[" << str << "] from [" << host << ":"
     * 		           << port << "]" << std::endl;
     * 	         (*client) << str;
     * 	       }
     *       server.close();
     *       exit (0);
     *     }
     *   catch (Network::Exception e) // catch all libsocket errors
     *     {
     *       std::cerr << e;
     *       exit(1);
     *     }
     * }
     * </pre>
     */
    void	connect(int port);
    /// @brief Close the connection
    void	close();

  protected:
    /// @brief Get a line from socket and store client hostname and
    /// port in port and host variable (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    /// @exception GetpeernameError when getpeername libc function
    /// return a negative value
    std::string	_read_line_bin(int socket, int& port,
			       std::string& host, unsigned int psize);
    /// @brief Get a line from socket (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line_bin(int socket, unsigned int psize);
  };
}

#endif	    /* !TCPSOCKET_HH_ */
