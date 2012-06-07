/*
** udp_client.cc
** Login : <speedblue@debian.org>
** Started on  Sun Mar  2 02:42:35 2003 Julien LEMOINE
** $Id: udp_client.cc,v 1.3 2004/04/23 23:09:47 speedblue Exp $
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

#include <stdlib.h>
#include <iostream>
#include <string>
#include "udpsocket.hh"
#include "socketexception.hh"

int main(int argc, char **argv)
{
  Network::UdpSocket		client;
  std::string			str;

  if (argc < 3)
    {
      std::cout << "Use: " << argv[0] << " port hostname" << std::endl;
      exit(0);
    }
  try
    {
      client.connect(std::string(argv[2]), strtol(argv[1], NULL, 10));
      while (str != "quit")
	{
	  std::cin >> str;
	  client << str;
	}
      client.close();
      exit(0);
    }
  catch (Network::Exception e)
    {
      std::cerr << e;
      exit(1);
    }
}
