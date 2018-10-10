/*
** localsocket.hh
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Sun Mar  2 00:53:36 2003 Julien Lemoine
** $Id: localsocket.hh,v 1.4 2006/12/28 18:01:03 speedblue Exp $
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

#include "socket.hh"

#ifndef LIBSOCKET_WIN

#ifndef   	LOCAL_SOCKET_HH_
# define   	LOCAL_SOCKET_HH_

namespace Network
{
  /// @brief This class represent a local connection (client and server)
  /// @author Julien Lemoine <speedblue at happycoders dot org>
  class LocalSocket : public Socket
  {
  public:
    LocalSocket() :
      Socket(LOCAL), _filename("")
    {}
    LocalSocket(PROTO_KIND pkind) :
      Socket(LOCAL, pkind), _filename("")
    {}

    virtual ~LocalSocket()
    {
      close();
    }

  public:
    /// @brief function used to send a msg to a specific named socket
    void		writeto(const std::string& str,
				const std::string& filename);

    /// @brief function used by >> operator (read a string on
    /// current socket)
    std::string	read();
    /// @brief read a string with a timeout
    std::string	read(int timeout);
    /// @brief read a string and put the client named socket name in filename
    std::string	read(std::string& filename);
    /// @brief read a string and put the client named socket name in
    /// filename with a timeout
    std::string	read(std::string& filename, int timeout);
    /// @brief read a string from socket
    /// @param size represente the number of byte to read
    std::string	readn(unsigned int size);
    /// @brief read a string with a timeout
    /// @param size represente the number of byte to read
    std::string	readn(int timeout, unsigned int size);
    /// @brief read a string and put the client named socket name in filename
    /// @param size represente the number of byte to read
    std::string	readn(std::string& filename, unsigned int size);
    /// @brief read a string and put the client named socket name in
    /// filename with a timeout
    /// @param size represente the number of byte to read
    std::string	readn(std::string& filename, int timeout, unsigned int size);

    /**
     * Here is an example of named socket server using libsocket :
     * <pre>
     * #include <stdlib.h>
     * #include <iostream>
     * #include <string>
     * #include "socket/localsocket.hh"
     * 
     * int main(int argc, char **argv)
     * {
     *   Network::LocalSocket		server;
     *   std::string			filename, client, str("");
     * 
     *   if (argc < 2)
     *     {
     *       std::cout << "Use: " << argv[0] << " filename" << std::endl;
     *       exit(0);
     *     }
     *   try
     *     {
     *       filename = std::string(argv[1]);
     *       server.init(filename);
     *       server.add_delim("\n");
     *       while (str != "quit")
     * 	     {
     * 	       //server.read(filename 30); //read with a timeout of 30 seconds
     * 	       //server >> str; //read without geting the named name
     * 	       //(cannot sent data)
     * 	       str = server.read(client);
     * 	       std::string msg = "ok, I received [" + str + "]";
     * 	       server.writeto(msg, client);
     * 	       std::cout << "[" << str << "] from : " << client << std::endl;
     * 	     }
     *       server.close();
     *       exit (0);
     *     }
     *   catch (Network::Timeout e)
     *     {
     *       std::cerr << e;
     *       std::cerr << "No connection during last 30s, closing connection" 
     * 		<< std::endl;
     *       exit (1);
     *     }
     *   catch (Network::Exception e)
     *     {
     *       std::cerr << e;
     *       exit(1);
     *     }
     * }
     * 
     * </pre>
     * Here is an example of named socket client using libsocket :
     * <pre>
     #include <stdlib.h>
     * #include <iostream>
     * #include <string>
     * #include "socket/localsocket.hh"
     * 
     * int main(int argc, char **argv)
     * {
     *   Network::LocalSocket		client;
     *   std::string			client_filename, server_filename, str(""), msg;
     * 
     *   if (argc < 3)
     *     {
     *       std::cout << "Use: " << argv[0] << " <client_filename> " 
     * 		<< "<server_filename>" << std::endl;
     *       exit(0);
     *     }
     *   try
     *     {
     *       client_filename = std::string(argv[1]);
     *       server_filename = std::string(argv[2]);
     * 
     *       client.init(client_filename);
     *       client.add_delim("\n");
     *       while (str != "quit")
     *       {
     * 	       std::cout << "Msg: ";
     * 	       std::cin >> str;
     * 	       client.writeto(str, server_filename);
     * 	       client >> msg;
     * 	       std::cout << "[received] " << msg << std::endl;
     * 	     }
     *       client.close();
     *       exit (0);
     *     }
     *   catch (Network::Timeout e)
     *     {
     *       std::cerr << e;
     *       std::cerr << "No connection during last 30s, closing connection" 
     * 		<< std::endl;
     *       exit (1);
     *     }
     *   catch (Network::Exception e)
     *     {
     *       std::cerr << e;
     *       exit(1);
     *     }
     * }
     * 
     * </pre>
     */
    /// @brief Initialize a local socket (server)
    void	init(const std::string& filename);
    /// @brief connect to a local socket (client)
    void	close();

  protected:
    /// @brief Initialize a local socket connection (server in UDP)
    /// create a named socket with name filename
    /// @exception NoConnection when there is no open socket
    /// @exception BindError when bind libc function return a
    /// negative value 
    int		_bind(const std::string& filename);
    /// @brief Get a line from socket (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line(int socket);
    /// @brief Get a line from socket and give client socket filename
    /// (for named socket) (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line(int socket, std::string& filename);
    /// @brief Get a line from socket (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line_bin(int socket, unsigned int size);
    /// @brief Get a line from socket and give client socket filename
    /// (for named socket) (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    std::string	_read_line_bin(int socket, std::string& filename,
			       unsigned int pkg_size);
    /// @brief Write a string to a socket to a particular named socket
    /// (when used with textual protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    void	_write_str(int socket, const std::string& str,
			   const std::string& filename) const;
    /// @brief Write a string to a socket to a particular named socket
    /// (when used with binary protocol)
    /// @exception NoConnection when there is no open socket
    /// @exception ConnectionClosed when there is no more connection
    void	_write_str_bin(int socket, const std::string& str,
			       const std::string& filename) const;

  protected:
    std::string		_filename;
  };
}

#endif	    /* !LOCAL_SOCKET_HH_ */
#endif
