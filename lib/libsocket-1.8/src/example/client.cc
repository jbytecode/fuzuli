/*
** test2.cc
** Login : <speedblue@morpheus>
** Started on  Mon May 24 21:04:55 2004 Julien Lemoine
** $Id: client.cc,v 1.2 2004/06/06 20:45:57 speedblue Exp $
** 
** Copyright (C) 2004 Julien Lemoine
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include "tcpsocket.hh"

int main(int argc, char **argv)
{
  int			port;
  Network::TcpSocket	client;

  if (argc != 2 && argc != 3)
    {
      std::cerr << "Usage : " << argv[0] << " port" << std::endl;
      std::cerr << "Usage : " << argv[0] << " port --enable-tls" << std::endl;
      exit (1);
    }
  port = strtol(argv[1], 0, 10);
  if (port <= 0)
    {
      std::cerr << "Invalid port" << std::endl;
      exit (1);
    }
  try
    {
      if (argc > 2)
	client.init_tls(Network::LIBSOCKET_TLS);
      client.connect(std::string("localhost"), port);
      if (argc > 2)
	client.enable_tls();
      client.add_delim("\n");
    }
  catch (Network::Exception &e)
    {
      std::cerr << e;
      exit (1);
    }
  try
    {
      std::cout << "Connected on port [" << port << "]" << std::endl;
      std::string str;
      client >> str;
      std::cout << "server token [" << str << "]" << std::endl;
      client << "TOKEN\n";
      client >> str;
      std::cout << "answer [" << str << "]" << std::endl;
      client >> str;
    }
  catch (Network::Exception &e)
    {
      std::cerr << e << std::endl;
      exit (1);
    }
  return 0;
}
