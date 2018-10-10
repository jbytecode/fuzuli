/*
** test_bind.cc
** Login : <speedblue@vodka.all-3rd.net>
** Started on  Sat May 17 21:50:07 2003 Julien LEMOINE
** $Id: test_bind.cc,v 1.2 2003/06/28 16:11:48 speedblue Exp $
** 
** Copyright (C) 2003 Julien LEMOINE
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

#include <iostream>
#include "tcpsocket.hh"
#include "udpsocket.hh"
#include "localsocket.hh"

#define PORT 42042
#define FILE "server"

int main(int argc, char **argv)
{
  try
    {
      Network::TcpSocket		tcp;
      Network::UdpSocket		udp;
#if !defined(_MSC_VER) && !defined(__MINGW32__)
      Network::LocalSocket		local;
#endif

      std::cout << "=== multiple bindings Test ===" << std::endl;
      for (unsigned int i = 0; i < 10; i++)
	{
	  tcp.connect(PORT);
	  tcp.close();
	  std::cout << "TCP: OK" << std::endl;
	  udp.connect(PORT);
	  udp.close();
	  std::cout << "UDP: OK" << std::endl;
#if !defined(_MSC_VER) && !defined(__MINGW32__)
	  local.init(FILE);
	  local.close();
	  std::cout << "LOCAL: OK" << std::endl;
#endif
	}
    }
  catch(Network::Exception e)
    {
      std::cerr << "FAILED : " << e;
      return 1;
    }
  std::cout << "OK" << std::endl;
  return 0;
}
