/*
** test.cc
** Login : <speedblue@morpheus>
** Started on  Mon May 24 20:47:37 2004 Julien Lemoine
** $Id: server.cc,v 1.2 2004/06/06 20:45:57 speedblue Exp $
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
#include <pthread.h>
#include "config.h"
#include "tcpsocket.hh"

class Server
{
public:
  Network::TcpSocket	*socket;
  pthread_t		thread;
  std::list<pthread_t>	*list;
};

void *client_function(void *arg)
{
  Server *s = (Server*)arg;
  Network::TcpSocket *client = s->socket;
      
  try
    {
      std::string str;
      (*client) << PACKAGE_STRING"\n";
      (*client) >> str;
      std::cout << "[" << str << "]" << std::endl;
      (*client) << str + "\n";
      client->close();
    }
  catch (Network::Exception &e)
    {
      std::cerr << e;
    }
  delete client;
  s->list->push_back(s->thread);
  return NULL;
}

int main(int argc, char **argv)
{
  try
    {
      pthread_t		thread;
      pthread_attr_t	thread_attr;
      int			port;
      Network::TcpSocket	server, *client;
      unsigned int		nbclient = 0;
      std::list<pthread_t>	list;
      std::list<pthread_t>::iterator it, it2;

      pthread_attr_init(&thread_attr);
      pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
      pthread_attr_setscope(&thread_attr,  PTHREAD_SCOPE_SYSTEM);

      if (argc < 2 || (argc != 2 && argc != 4))
	{
	  std::cerr << "Usage : " << argv[0] << " port" << std::endl;
	  std::cerr << "Usage : " << argv[0] << " port cert.pem key.pem" 
		    << std::endl;
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
	  server.connect(port);
	  server.add_delim("\n");
	  server.add_delim("\r\n");
	}
      catch (Network::Exception &e)
	{
	  std::cerr << e;
	  exit (1);
	}
      std::cout << "Binded on port [" << port << "]" << std::endl;
      while (true)
	{
	  if (argc > 2)
	    server.init_tls(Network::LIBSOCKET_TLS, 1024, argv[2], argv[3]);
	  client = server.accept();
	  std::cout << "Ip [" << server.get_ip(client) << "]" << std::endl;
	  nbclient++;
	  client->add_delim("\n");
	  client->add_delim("\r\n");
	  Server *s = new Server();
	  s->socket = client;
	  s->list = &list;
      
	  for (it = list.begin(); it != list.end(); )
	    {
	      it2 = it;
	      ++it;
	      pthread_join(*it2, 0);
	      list.erase(it2);
	    }
	  // Do not use thread for the moment, we need a libgcrypt
	  //	  that support thread (a least 1.2).

	  //	  int res = pthread_create(&s->thread, &thread_attr,
	  //	  client_function, (void*)s);
	  client_function((void*)s); // simulate thread.
	  int res = 0;
	  if (res != 0)
	    {
	      perror(0);
	      std::cerr << "Error creating thread" << std::endl;;
	      std::cerr << "Number of clients [" << nbclient << "]" << std::endl;
	      exit (1);
	    }
	}
    }
  catch (Network::Exception &e)
    {
      std::cerr << e;
      exit (1);
    }
  return 0;
}
