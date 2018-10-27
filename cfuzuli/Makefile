CC=clang
OUT_DIR=build
FLAGS=-fPIC
.PHONY: all

$(shell mkdir -p $(OUT_DIR))

all: main

clean: 
	rm -Rf build

ferror.o:	src/ferror.c src/ferror.h
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/ferror.o src/ferror.c

fstdlib.o:	src/fstdlib.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fstdlib.o src/fstdlib.c

environment.o:	src/environment.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/environment.o src/environment.c

expression.o:	src/expression.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/expression.o src/expression.c

parser.o:	src/parser.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/parser.o src/parser.c

token.o:	src/token.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/token.o src/token.c

fuzulitypes.o:	src/fuzulitypes.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fuzulitypes.o src/fuzulitypes.c

linkedlist.o: src/linkedlist.h src/linkedlist.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/linkedlist.o src/linkedlist.c

string.o: src/string.c src/string.h
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/string.o src/string.c

stringexpression.o:	src/stringexpression.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/stringexpression.o src/stringexpression.c

sourcecode.o:	src/sourcecode.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/sourcecode.o src/sourcecode.c

eval.o:	src/eval.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/eval.o src/eval.c

lexer.o: src/lexer.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/lexer.o src/lexer.c
	
libfuzuli.so:	fstdlib.o string.o linkedlist.o stringexpression.o eval.o fuzulitypes.o \
                sourcecode.o lexer.o token.o parser.o expression.o environment.o ferror.o
	$(CC) -shared -o $(OUT_DIR)/libfuzuli.so $(OUT_DIR)/string.o $(OUT_DIR)/linkedlist.o \
	$(OUT_DIR)/eval.o $(OUT_DIR)/stringexpression.o $(OUT_DIR)/fuzulitypes.o \
	$(OUT_DIR)/sourcecode.o $(OUT_DIR)/lexer.o $(OUT_DIR)/token.o $(OUT_DIR)/parser.o \
	$(OUT_DIR)/expression.o $(OUT_DIR)/fstdlib.o $(OUT_DIR)/environment.o $(OUT_DIR)/ferror.o 
 
main:	libfuzuli.so	
	$(CC) -o $(OUT_DIR)/fuzuli src/main.c $(OUT_DIR)/libfuzuli.so

test:	main test_string test_linkedlist
	@echo "Performing tests..."
	@echo $(shell ./$(OUT_DIR)/stringtest)
	@echo $(shell ./$(OUT_DIR)/linkedlisttest)
	@echo "Fuzuli source tests: "
	@echo "Let test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/lettest.fzl)

test_string:	main
	$(CC) -o $(OUT_DIR)/stringtest test/stringtest.c $(OUT_DIR)/libfuzuli.so

test_linkedlist:	main
	$(CC) -o $(OUT_DIR)/linkedlisttest test/linkedlisttest.c $(OUT_DIR)/libfuzuli.so

run: main
	./build/fuzuli ftest/printtest.fzl

