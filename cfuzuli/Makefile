CC=clang
OUT_DIR=build
FLAGS=-fPIC
.PHONY: all

$(shell mkdir -p $(OUT_DIR))

all: main

clean: 
	rm -Rf build


$(OUT_DIR)/fmemory.o:	src/fmemory.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fmemory.o src/fmemory.c

$(OUT_DIR)/ferror.o:	src/ferror.c src/ferror.h
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/ferror.o src/ferror.c

$(OUT_DIR)/fstdlib.o:	src/fstdlib.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fstdlib.o src/fstdlib.c

$(OUT_DIR)/fstdarithmatic.o:	src/fstdarithmatic.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fstdarithmatic.o src/fstdarithmatic.c

$(OUT_DIR)/fstdstring.o:	src/fstdstring.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fstdstring.o src/fstdstring.c


$(OUT_DIR)/environment.o:	src/environment.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/environment.o src/environment.c

$(OUT_DIR)/expression.o:	src/expression.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/expression.o src/expression.c

$(OUT_DIR)/parser.o:	src/parser.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/parser.o src/parser.c

$(OUT_DIR)/token.o:	src/token.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/token.o src/token.c

$(OUT_DIR)/fuzulitypes.o:	src/fuzulitypes.c	 
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/fuzulitypes.o src/fuzulitypes.c

$(OUT_DIR)/linkedlist.o: src/linkedlist.h src/linkedlist.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/linkedlist.o src/linkedlist.c

$(OUT_DIR)/string.o: src/string.c src/string.h
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/string.o src/string.c

$(OUT_DIR)/stringexpression.o:	src/stringexpression.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/stringexpression.o src/stringexpression.c

$(OUT_DIR)/sourcecode.o:	src/sourcecode.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/sourcecode.o src/sourcecode.c

$(OUT_DIR)/eval.o:	src/eval.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/eval.o src/eval.c

$(OUT_DIR)/lexer.o: src/lexer.c
	$(CC) $(FLAGS) -c -o $(OUT_DIR)/lexer.o src/lexer.c
	
$(OUT_DIR)/libfuzuli.so:	$(OUT_DIR)/fstdlib.o $(OUT_DIR)/string.o $(OUT_DIR)/linkedlist.o\
	$(OUT_DIR)/stringexpression.o $(OUT_DIR)/eval.o\
	$(OUT_DIR)/fuzulitypes.o $(OUT_DIR)/sourcecode.o $(OUT_DIR)/lexer.o $(OUT_DIR)/token.o\
	$(OUT_DIR)/parser.o $(OUT_DIR)/expression.o $(OUT_DIR)/environment.o $(OUT_DIR)/ferror.o\
	$(OUT_DIR)/fmemory.o $(OUT_DIR)/fstdarithmatic.o $(OUT_DIR)/fstdstring.o
	
	$(CC) -shared -o $(OUT_DIR)/libfuzuli.so $(OUT_DIR)/string.o $(OUT_DIR)/linkedlist.o \
	$(OUT_DIR)/eval.o $(OUT_DIR)/stringexpression.o $(OUT_DIR)/fuzulitypes.o \
	$(OUT_DIR)/sourcecode.o $(OUT_DIR)/lexer.o $(OUT_DIR)/token.o $(OUT_DIR)/parser.o \
	$(OUT_DIR)/expression.o $(OUT_DIR)/fstdlib.o $(OUT_DIR)/environment.o \
	$(OUT_DIR)/ferror.o $(OUT_DIR)/fmemory.o $(OUT_DIR)/fstdarithmatic.o $(OUT_DIR)/fstdstring.o
 
main:	$(OUT_DIR)/libfuzuli.so	
	$(CC) -o $(OUT_DIR)/fuzuli src/main.c $(OUT_DIR)/libfuzuli.so

test:	main test_string test_linkedlist test_fuzulitypes
	@echo "Performing tests...\n________________________"
	@echo $(shell ./$(OUT_DIR)/stringtest)
	@echo $(shell ./$(OUT_DIR)/linkedlisttest)
	@echo $(shell ./$(OUT_DIR)/fuzulitypestest)
	@echo "Fuzuli source tests: \n___________________________"
	@echo "Single line comment: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/singlelinecomment.fzl)
	@echo "Let test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/lettest.fzl)
	@echo "equalints test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/equalints.fzl)
	@echo "if1 test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/if1.fzl)
	@echo "while1 test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/while1.fzl)	
	@echo "typeof test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/typeof.fzl)	
	@echo "list1 test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/list1.fzl)	
	@echo "rm & isnull test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/rm.fzl)	
	@echo "inc test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/inc.fzl)	
	@echo "arithmetic test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/arithmetic.fzl)	
	@echo "string test: " $(shell ./$(OUT_DIR)/fuzuli ./ftest/string.fzl)	
	

test_string:	main
	$(CC) -o $(OUT_DIR)/stringtest test/stringtest.c $(OUT_DIR)/libfuzuli.so

test_fuzulitypes:	main
	$(CC) -o $(OUT_DIR)/fuzulitypestest test/fuzulitypestest.c $(OUT_DIR)/libfuzuli.so


test_linkedlist:	main
	$(CC) -o $(OUT_DIR)/linkedlisttest test/linkedlisttest.c $(OUT_DIR)/libfuzuli.so

run: main
	./build/fuzuli ftest/printtest.fzl

