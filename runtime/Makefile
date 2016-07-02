CPP=clang++
CFLAGS=-c -Wall

all: fuzuli
	echo "Running"
	./fuzuli test.fzl

fuzuli: main.o sourcecode.o token.o parser.o expression.o
	$(CPP) main.o sourcecode.o parser.o token.o expression.o -o fuzuli

main.o: main.cpp
	$(CPP) $(CFLAGS) main.cpp

sourcecode.o: sourcecode.cpp
	$(CPP) $(CFLAGS) sourcecode.cpp

token.o: token.cpp
	$(CPP) $(CFLAGS) token.cpp

parser.o: parser.cpp
	$(CPP) $(CFLAGS) parser.cpp

expression.o: expression.cpp
	$(CPP) $(CFLAGS) expression.cpp

clean:
	rm *.o

