/*
** local_cp.cc
** Login : <speedblue@debian.org>
** Started on  Tue May 13 02:05:10 2003 Julien LEMOINE
** $Id: local_cp.cc,v 1.3 2004/04/23 23:09:47 speedblue Exp $
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

void server(char *filename)
{
  Network::LocalSocket		server;
  std::string			s, fserver(SERVER_FILE), fclient, ack(ACK"\n");
  std::ofstream			o(filename);

  try
    {
      server.init(fserver);
      server.add_delim("\n");
      while (s != END)
	{
	  s = server.read(fclient, 5); //timeout of 5 seconds
	  server.writeto(ack, fclient);
	  if (s!= END)
	    o << s << std::endl;
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
  Network::LocalSocket		client;
  std::string			client_filename, server_filename, s;
  std::ifstream			file(filename);
  char				buff[1024];

  try
    {
      client_filename = std::string(CLIENT_FILE);
      server_filename = std::string(SERVER_FILE);

      client.init(client_filename);
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
	  client.writeto(s, server_filename);
	  client.read(5); // wait ack with a timeout of 5 seconds
	}
      s = std::string(END"\n");
      client.writeto(s, server_filename);
      client.close();
      exit (0);
    }
  catch (Network::Timeout e)
    {
      std::cerr << e;
      std::cerr << "No connection during last 30s, closing connection" 
		<< std::endl;
      exit (1);
    }
  catch (Network::Exception e)
    {
      std::cerr << e;
      exit(1);
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
