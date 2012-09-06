/*
** local_cp_bin.cc
** Login : <speedblue@debian.org>
** Started on  Tue May 13 02:05:10 2003 Julien LEMOINE
** $Id: local_cp_bin.cc,v 1.2 2003/06/28 16:11:48 speedblue Exp $
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
#include "localsocket.hh"

#define SERVER_FILE "/tmp/server"
#define CLIENT_FILE "/tmp/client"
#define END "<<END OF SOCKET TRANSMITION>>"
#define ACK "<<ACK>>"
#define BSIZE 1024

void server(char *filename)
{
  Network::LocalSocket		server(Network::binary);
  std::string			s, fserver(SERVER_FILE), fclient, ack(ACK);
  std::ofstream			o(filename, std::ios::binary);

  try
    {
      server.init(fserver);
      while (s != END)
	{
	  s = server.read(fclient, 5); //timeout of 5 seconds
	  server.writeto(ack, fclient);
	  if (s != END)
	    o.write(s.c_str(), s.size());
	}
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
  Network::LocalSocket		client(Network::binary);
  std::string			s;
  std::ifstream			file(filename, std::ios::binary | 
				     std::ios::ate);
  char				buff[1024];

  try
    {
      std::string client_filename = std::string(CLIENT_FILE);
      std::string server_filename = std::string(SERVER_FILE);

      client.init(client_filename);
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
	  client.writeto(s, server_filename);
	  client.read(5); // wait server ack during 5 seconds
	}
      if (file.read(buff, size % BSIZE))
	{
	  s = std::string(buff, size % BSIZE);
	  client.writeto(s, server_filename);
	  client.read(5); // wait server ack during 5 seconds
	}
      s = std::string(END);
      client.writeto(s, server_filename);
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
