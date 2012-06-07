/*
** local_server.cc
** Login : <speedblue@speedblue.org>
** Started on  Sun Mar  2 02:15:35 2003 Julien LEMOINE
** $Id: local_server.cc,v 1.3 2004/04/23 23:09:47 speedblue Exp $
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
#include "localsocket.hh"
#include "socketexception.hh"

int main(int argc, char **argv)
{
  Network::LocalSocket		server;
  std::string			filename, client, str("");

  if (argc < 2)
    {
      std::cout << "Use: " << argv[0] << " filename" << std::endl;
      exit(0);
    }
  try
    {
      filename = std::string(argv[1]);
      server.init(filename);
      while (str != "quit")
	{
	  //server.read(filename 30); //read with a timeout of 30 seconds
	  //server >> str; //read without geting the named name
	  //(cannot sent data)
	  str = server.read(client);
	  std::string msg = "ok, I received [" + str + "]";
	  server.writeto(msg, client);
	  std::cout << "[" << str << "] from : " << client << std::endl;
	}
      server.close();
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
