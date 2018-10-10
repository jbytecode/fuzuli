/*
** udpsocket.hh
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sun Mar  2 00:53:36 2003 Julien Lemoine
** $Id: udpsocket.hh,v 1.3 2006/12/28 18:01:03 speedblue Exp $
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

#ifndef   	UDP_SOCKET_HH_
# define   	UDP_SOCKET_HH_

#include "netsocket.hh"

namespace Network
{
  /// @brief This class represent a udp connection (client and server)
  /// @author Julien Lemoine <speedblue at happycoders dot org>
  class UdpSocket : public NetSocket
  {
  public:
    UdpSocket(SOCKET_VERSION version = V4) :
      NetSocket(UDP, version)
    {}
    UdpSocket(PROTO_KIND pkind, SOCKET_VERSION version = V4) :
      NetSocket(UDP, pkind, version)
    {}

    virtual ~UdpSocket()
    {
      close();
    }

  public:
    /// @brief Connect as an UDP client
    /**
     * Here is an example of an UDP client using libsocket:
     * <pre>
     * #include <stdlib.h>
     * #include <iostream>
     * #include <string>
     * #include "socket/udpsocket.hh"
     *
     * int main(int argc, char **argv)
     * {
     *   Network::UdpSocket            client;
     *   //Network::UdpSocket            client(Network::V6);
     *   // For IPV6 mode
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
     *       while (str != "quit")
     *         {
     *           std::cin >> str;
     *           client << str;
     *         }
     *       client.close();
     *       exit(0);
     *     }
     *   catch (Network::Exception e)
     *     {
     *       std::cerr << e;
     *       exit(1);
     *     }
     * }
     * </pre>
     */
    void	connect(const std::string& hostname, int port);
    /// @brief Connect as an UDP server
    /**
     * Here is an example of an UDP server using libsocket :
     * <pre>
     * #include <stdlib.h>
     * #include <iostream>
     * #include <string>
     * #include "socket/udpsocket.hh"
     * #include "exception/exception.hh"
     *
     * int main(int argc, char **argv)
     * {
     *   Network::UdpSocket            server;
     *   std::string                   str, host;
     *
     *   if (argc < 2)
     *     {
     *       std::cout << "Use: " << argv[0] << " port" << std::endl;
     *       exit(0);
     *     }
     *   try
     *     {
     *       server.connect(strtol(argv[1], NULL, 10));
     *       server.add_delim("\n");
     *       while (str != "quit")
     *         {
     * 	         //read with a timeout of 30 seconds and get client host and port
     * 	         str = server.read(port, host, 30);
     * 	         std::cout << "Received [" << str << "] from : " << host
     * 		           << ":" << port << "]" << std::endl;
     * 	       }
     *       server.close();
     *       exit (0);
     *     }
     *   catch (Network::Timeout e)
     *     {
     *       std::cerr << e;
     *       std::cerr << "No connection during last 30s, closing connection"
     *                 << std::endl;
     *       exit (1);
     *     }
     *   catch (Network::Exception e)
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
			       std::string& host,
			       unsigned int pkg_size);
    /// @brief Get a line from socket (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line_bin(int socket, unsigned int size);
  };
}

#endif	    /* !UDP_SOCKET_HH_ */
