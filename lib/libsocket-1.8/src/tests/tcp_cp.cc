/*
** tcp_cp.cc
** Login : <speedblue@debian.org>
** Started on  Tue May 13 02:05:10 2003 Julien LEMOINE
** $Id: tcp_cp.cc,v 1.3 2004/04/23 23:09:47 speedblue Exp $
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
#include <string>
#include <fstream>
#include "tcpsocket.hh"

#define SERVER_PORT 42042
#define END "<<END OF SOCKET TRANSMITION>>"

void server(char *filename)
{
  Network::TcpSocket		server, *client;
  std::string			s;
  std::ofstream			o(filename);
  try
    {
      server.connect(SERVER_PORT);
      server.add_delim("\n");
      client = server.accept();
      client->add_delim("\n");
      std::cout << "Started" << std::endl;
      while (s != END)
	{
	  s = client->read(); //timeout of 5 seconds
	  if (s != END)
	    o << s << std::endl;
	}
      (*client) << END"\n";
      s = client->read(5);  // timeout of 5 seconds
                            // (wait for client deconnection)
      server.close();
    }
  catch (Network::ConnectionClosed e)
    {}
  catch (Network::Exception e)
    {
      std::cerr << e;
    }
  o.close();
}

void client(char *filename)
{
  Network::TcpSocket		client;
  std::string			s;
  std::ifstream			file(filename);
  char				buff[1024];

  try
    {
      client.connect(std::string("localhost"), SERVER_PORT);
      client.add_delim("\n");
      if (!file.is_open())
	{
	  std::cerr << "Unavailable to open file : " << filename << std::endl;
	  exit (1);
	}
      while (!file.eof() && file.getline(buff, 1024, '\n'))
	{
	  s = std::string(buff);
	  s += "\n";
	  client << s;
	}
      client << END"\n";
      s = client.read(5); //read with a timeout of 5 seconds
      client.close();
    }
  catch (Network::Exception e)
    {
      std::cerr << e;
    }
}

int main(int argc, char **argv)
{
  if (argc < 3 || (std::string(argv[1]) != "server" &&
		   std::string(argv[1]) != "client"))
    {
      std::cout << "Use: " << argv[0]
		<< " server <filename_save>" << std::endl;
      std::cout << "Use: " << argv[0]
		<< " client <filename_read>" << std::endl;
      exit(0);
    }
  if (std::string(argv[1]) == "server")
    server(argv[2]);
  else
    client(argv[2]);
  return 0;
}
