
#Compiling
EXTRA_DIST= test_bind test_cp test_cp_bin textfiles/Artistic 	\
	    textfiles/GPL textfiles/LGPL			\
	    textfiles/LGPL-2.1 textfiles/BSD    		\
	    textfiles/GPL-2 textfiles/LGPL-2

INCLUDES = -I$(top_srcdir)/src

TESTS=test_bind test_cp_bin test_cp
check_PROGRAMS= udp_server udp_client tcp_server 	\
	        tcp_client local_server local_client 	\
		tcp_cp udp_cp local_cp tcp_cp_bin       \
		tcp6_client tcp6_server udp_cp_bin	\
		local_cp_bin udp6_client udp6_server	\
		test_bind

udp_server_SOURCES = udp_server.cc
udp_server_LDFLAGS = -L$(top_srcdir)/src  
udp_server_LDADD   = -lsocket @EXTRALIB@

udp_client_SOURCES = udp_client.cc
udp_client_LDFLAGS = -L$(top_srcdir)/src 
udp_client_LDADD   = -lsocket @EXTRALIB@

udp6_server_SOURCES = udp6_server.cc
udp6_server_LDFLAGS = -L$(top_srcdir)/src
udp6_server_LDADD   = -lsocket @EXTRALIB@

udp6_client_SOURCES = udp6_client.cc
udp6_client_LDFLAGS = -L$(top_srcdir)/src
udp6_client_LDADD   = -lsocket @EXTRALIB@

tcp_server_SOURCES = tcp_server.cc
tcp_server_LDFLAGS = -L$(top_srcdir)/src
tcp_server_LDADD   = -lsocket @EXTRALIB@

tcp_client_SOURCES = tcp_client.cc
tcp_client_LDFLAGS = -L$(top_srcdir)/src
tcp_client_LDADD   = -lsocket @EXTRALIB@

tcp6_server_SOURCES = tcp6_server.cc
tcp6_server_LDFLAGS = -L$(top_srcdir)/src
tcp6_server_LDADD   = -lsocket @EXTRALIB@

tcp6_client_SOURCES = tcp6_client.cc
tcp6_client_LDFLAGS = -L$(top_srcdir)/src
tcp6_client_LDADD   = -lsocket @EXTRALIB@

local_server_SOURCES = local_server.cc
local_server_LDFLAGS = -L$(top_srcdir)/src
local_server_LDADD   = -lsocket @EXTRALIB@

local_client_SOURCES = local_client.cc
local_client_LDFLAGS = -L$(top_srcdir)/src
local_client_LDADD   = -lsocket @EXTRALIB@

tcp_cp_SOURCES = tcp_cp.cc
tcp_cp_LDFLAGS = -L$(top_srcdir)/src
tcp_cp_LDADD   = -lsocket @EXTRALIB@

udp_cp_SOURCES = udp_cp.cc
udp_cp_LDFLAGS = -L$(top_srcdir)/src
udp_cp_LDADD   = -lsocket @EXTRALIB@

local_cp_SOURCES = local_cp.cc
local_cp_LDFLAGS = -L$(top_srcdir)/src
local_cp_LDADD   = -lsocket @EXTRALIB@

tcp_cp_bin_SOURCES = tcp_cp_bin.cc
tcp_cp_bin_LDFLAGS = -L$(top_srcdir)/src
tcp_cp_bin_LDADD   = -lsocket @EXTRALIB@

udp_cp_bin_SOURCES = udp_cp_bin.cc
udp_cp_bin_LDFLAGS = -L$(top_srcdir)/src
udp_cp_bin_LDADD   = -lsocket @EXTRALIB@

local_cp_bin_SOURCES = local_cp_bin.cc
local_cp_bin_LDFLAGS = -L$(top_srcdir)/src
local_cp_bin_LDADD   = -lsocket @EXTRALIB@

test_bind_SOURCES = test_bind.cc
test_bind_LDFLAGS = -L$(top_srcdir)/src
test_bind_LDADD   = -lsocket @EXTRALIB@

CLEANFILES = *~
