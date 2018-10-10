/*
** socketexception.hh
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Mon May 12 22:50:50 2003 Julien Lemoine
** $Id: socketexception.hh,v 1.7 2006/12/28 17:49:58 speedblue Exp $
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

#ifndef   	SOCKETEXCEPTION_HH_
# define   	SOCKETEXCEPTION_HH_

#define HERE    __FILE__, __LINE__

#include <iostream>
#include <string>

#define NEW_EXCEPTION(Name)						\
  class Name : public Exception						\
  {									\
  public:								\
    Name(const std::string& desc, const char * file, int line) :	\
      Exception(desc, file, line)					\
    {}									\
    Name() : Exception() {}						\
    Name(const char *file, int line) : Exception(file, line) {}		\
  }

namespace Network
{

  /// @author Julien Lemoine <speedblue at happycoders dot org>
  /// @brief This class is the top exception class used in libsocket
  class Exception
  {
  public:
    Exception() :
      _error("Exception Occured"), _file(0x0), _line(0)
    {}

    Exception(const char *file, int line) :
      _error("Exception Occured"), _file(file), _line(line)
    {}

    Exception(const std::string& err, const char* file, int line) :
      _file(file), _line(line)
    {
      _error = "Exception: " + err;
    }

    void print(std::ostream& stream) const;
    const std::string& get_error() const;
    const char* get_file() const;
    int get_line() const;

  protected:
    std::string       _error;
    const char*       _file;
    int               _line;
  };

  std::ostream& operator<<(std::ostream& stream, Exception& e);
  
  /// @brief exception launched when a hostname is incorrect
  NEW_EXCEPTION(HostnameError);
  /// @brief exception launched when user want ipv6, but lib is not
  /// compiled with
  NEW_EXCEPTION(Ipv6SupportError);
  /// @brief exception launched when error is received during TLS
  /// initialization
  NEW_EXCEPTION(TLSError);
  /// @brief exception launched when a file does not exist
  NEW_EXCEPTION(InvalidFile);
  /// @brief exception launched when user want TLS, but lib is not
  /// compiled with
  NEW_EXCEPTION(TLSSupportError);
  /// @brief exception launched when a addr is invalid pour inet_pton
  NEW_EXCEPTION(InetptonError);
  /// @brief exception launched when the addr is not valid for inet_ntop
  NEW_EXCEPTION(InetntopError);
  /// @brief exception launched when connection is closed
  NEW_EXCEPTION(ConnectionClosed);
  /// @brief exception launched when there is no active connection
  NEW_EXCEPTION(NoConnection);
  /// @brief exception launched when there is a timeout
  NEW_EXCEPTION(Timeout);
  /// @brief exception launched when bind libc function return an error
  NEW_EXCEPTION(BindError);
  /// @brief exception launched when socket libc function return an error
  NEW_EXCEPTION(SocketError);
  /// @brief exception launched when listen libc function return an error
  NEW_EXCEPTION(ListenError);
  /// @brief exception launched when setsockopt libc function return an error
  NEW_EXCEPTION(SetsockoptError);
  /// @brief exception launched when close libc function return an error
  NEW_EXCEPTION(CloseError);
  /// @brief exception launched when select libc function return an error
  NEW_EXCEPTION(SelectError);
  /// @brief exception launched when connect libc function return an error
  NEW_EXCEPTION(ConnectError);
  /// @brief exception launched when accept libc function return an error
  NEW_EXCEPTION(AcceptError);
  /// @brief exception launched when getpeername libc function return an error
  NEW_EXCEPTION(GetpeernameError);
  /// @brief exception launched when WSAStartup windows function
  /// return an error
  NEW_EXCEPTION(WSAStartupError);

}

#endif	    /* !SOCKETEXCEPTION_HH_ */
