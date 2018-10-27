#include <stdio.h>
#include <string.h>
#include "string.h"

#include "sourcecode.h"
#include "lexer.h"
#include "linkedlist.h"
#include "constants.h"
#include "expression.h"
#include "parser.h"
#include "eval.h"
#include "environment.h"

void printtokenlist(LinkedList *list)
{
    LinkedListElement *element = list->first;
    while (TRUE)
    {
        if (element == NULL)
        {
            break;
        }
        Token *tok = (Token *)element->value;
        printf("%s, ", tok->content);
        element = element->next;
    }
}

void runFile(char *filename)
{
    String *sourcecode;
    //printf("Source code loading\n");
    sourcecode = sourcecode_load_from_file(filename);
    //printf("Lexing\n");
    LinkedList *list = LexerExtractTokens(sourcecode);
    ParserState *state = ParserStateNew(LinkedListLength(list));
    Environment *env = EnvironmentNew(NULL);
    EnvironmentRegisterGlobals(env);
    FuzuliValue *returnValue;
    //printf("Running\n");
    while (TRUE)
    {
        Expression *expr = getNextExpression(list, state);
        if (expr == NULL)
        {
            if (state->index < state->end - 1)
            {
                state->index++;
            }
            else
            {
                break;
            }
        }
        if (expr != NULL)
        {
            //ExpressionPrint(expr, 0);
            returnValue = eval(expr, env);
        }
    }
    //FuzuliValuePrint(returnValue);
}

void runRepl()
{
    Environment *env = EnvironmentNew(NULL);
    EnvironmentRegisterGlobals(env);
    char chars[1024];
    while (1)
    {
        printf("\nFuzuli> ");
        char *str = fgets(chars, 1024, stdin);
        String *sourcecode = StringNew(&chars[0]);
        LinkedList *list = LexerExtractTokens(sourcecode);
        ParserState *state = ParserStateNew(LinkedListLength(list));
        while (TRUE)
        {
            Expression *expr = getNextExpression(list, state);
            if (expr == NULL)
            {
                if (state->index < state->end - 1)
                {
                    state->index++;
                }
                else
                {
                    break;
                }
            }
            if (expr != NULL)
            {
                eval(expr, env);
                //ExpressionPrint(expr);
            }
        }
    }
}

int main(int argc, char **argv)
{
    String *sourcecode;
    if (argc == 1)
    {
        puts("Fuzuli C edition 0.0.1");
    }
    if (argc == 2)
    {
        if (strcmp(argv[1], "--repl") == 0)
        {
            runRepl();
        }
        else
        {
            runFile(argv[1]);
        }
    }
    return (0);
}
