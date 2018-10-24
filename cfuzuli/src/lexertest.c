#include <stdio.h>
#include <string.h>
#include "../src/fuzulitypes.h"
#include "../src/linkedlist.h"
#include "../src/constants.h"
#include "../src/stringexpression.h"
#include "../src/printexpression.h"
#include "../src/eval.h"
#include "../src/lexer.h"

unsigned int lexertest_leftParanth(){
    String sourceString = StringNew("(123)");
    char *chars = sourceString.chars;
    LexerState *state = LexerCreateState(0, 0, sourceString.length);
    state->sourcecode = chars;
    String firstParanth = LexerGetNextToken(state);
    return(firstParanth.chars[0] == '(');
}

int main(int argc, char **argv){
    puts("Lexer test");
    printf("lexertest_leftParanth: %d\n", lexertest_leftParanth());
    
    return 0;
}