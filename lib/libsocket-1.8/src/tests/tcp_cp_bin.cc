/*
** tcp_cp_bin.cc
** Login : <speedblue@debian.org>
** Started on  Tue May 13 02:05:10 2003 Julien LEMOINE
** $Id: tcp_cp_bin.cc,v 1.2 2003/06/28 16:11:48 speedblue Exp $
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

#define SERVER_PORT	42042
#define BSIZE		1024
#define END "<<END OF SOCKET TRANSMITION>>"

void server(char *filename)
{
  Network::TcpSocket		server(Network::binary), *client;
  std::string			s;
  std::ofstream			o(filename, std::ios::binary);
  try
    {
      server.connect(SERVER_PORT);
      client = server.accept();
      while (s != END)
	{
	  s = client->read(5); //timeout of 5 seconds
	  if (s!= END)
	    o.write(s.c_str(), s.size());
	}
      (*client) << END;
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
  Network::TcpSocket		client(Network::binary);
  std::string			s;
  std::ifstream			file(filename, std::ios::binary | 
				     std::ios::ate);
  char				buff[1024];

  try
    {
      client.connect(std::string("localhost"), SERVER_PORT);
      if (!file.is_open())
	{
	  std::cerr << "Unavailable to open file : " << filename << std::endl;
	  exit (1);
	}
      unsigned int size = file.tellg();
      file.seekg(0, std::ios::beg);
      for (unsigned int i = 0; i < size / BSIZE && file.read(buff, BSIZE); i++)
	{
	  s = std::string(buff, BSIZE);
	  client << s;
	}
      if (file.read(buff, size % BSIZE))
	{
	  s = std::string(buff, size % BSIZE);
	  client << s;
	}
      client << END;
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
