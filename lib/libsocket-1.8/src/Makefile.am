SUBDIRS = tests

#Compiling
INCLUDES = -I$(top_srcdir)/src

EXTRA_DIST 		= example/Makefile example/server.cc example/client.cc
hcincludedir            = $(includedir)/happycoders/socket
hcinclude_HEADERS       = socket.hh udpsocket.hh tcpsocket.hh 	\
			  localsocket.hh netsocket.hh socketexception.hh
			  socket.hxx

hclibdir                = $(libdir)/happycoders/
hclib_LTLIBRARIES       = libsocket.la

libsocket_la_SOURCES    = socket.hh socket.cc udpsocket.cc 	\
			  udpsocket.hh tcpsocket.hh tcpsocket.cc\
			  localsocket.hh localsocket.cc		\
			  netsocket.hh netsocket.cc		\
			  socketexception.hh socketexception.cc	\
			  socket.hxx
libsocket_la_LIBADD	= @EXTRALIB@
libsocket_la_LDFLAGS    = -version-info @LIBSOCKET_SO_VERSION@

CLEANFILES = *~
