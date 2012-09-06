CXX		= g++
CXXFLAGS	= -O2
INCLUDES	= -I.. -I../..
LIBS		= ../.libs/libsocket.a -lgnutls

all: server client

server: server.cc
	$(CXX) $(CXXFLAGS) server.cc -o server $(INCLUDES) $(LIBS) -lpthread

client: client.cc
	$(CXX) $(CXXFLAGS) client.cc -o client $(INCLUDES) $(LIBS)

clean:
	rm -f *~ server client
