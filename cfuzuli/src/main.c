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
#include "fmemory.h"

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

void runFile(char *filename, int argc, char **argv)
{
    String *sourcecode;
    sourcecode = sourcecode_load_from_file(filename);
    LinkedList *list = LexerExtractTokens(sourcecode);
    ParserState *state = ParserStateNew(LinkedListLength(list));
    Environment *env = EnvironmentNew(NULL);
    EnvironmentRegisterGlobals(env);
    EnvironmentRegisterCommandLineArguments(env, argc, argv);
    FuzuliValue *returnValue;
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
            //if(returnValue != NULL && returnValue->links == 0 && returnValue->protected == 0){
            //    FuzuliValueFree(returnValue);
            //}
        }
    }
    //FuzuliValuePrint(returnValue);
}

void runCommand(char *code, Environment *env){
        String *sourcecode = StringNew(code);
        LinkedList *list = LexerExtractTokens(sourcecode);
        ParserState *state = ParserStateNew(LinkedListLength(list));
        StringClear(sourcecode);
        FuzuliValue *returnValue;
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
                returnValue = eval(expr, env);
                if(returnValue != NULL && returnValue->type != FTYPE_NULL){
                    FuzuliValuePrint(returnValue);
                }
                /*
                printf("\n* return value is %s in type %d with links %d\n", returnValue->tag, 
                    returnValue->type, returnValue->links);
                printf("Memory alloced: %d freed: %d holding: %d\n", 
                        FuzuliMemoryGetAllocated(), FuzuliMemoryGetFreed(),
                        FuzuliMemoryGetAllocated() - FuzuliMemoryGetFreed());
                        */
                if(returnValue->links >0){
                    FuzuliValueFree(returnValue);
                    ffree(expr->tag);
                }
            }
        }
        ffree(state);
}

void runRepl(int argc, char **argv)
{
    Environment *env = EnvironmentNew(NULL);
    EnvironmentRegisterGlobals(env);
    EnvironmentRegisterCommandLineArguments(env, argc, argv);
    char chars[1024];
    while (1)
    {
        printf("\nFuzuli> ");
        char *str = fgets(chars, 1024, stdin);
        if(str[0] == '(' && str[0] != '\n'){
            runCommand(str, env);
        }
    }
}

int main(int argc, char **argv)
{
    String *sourcecode;
    if (argc == 1)
    {
        puts("Fuzuli C edition 0.0.1");
        puts("Arguments:");
        puts("fuzuli --repl: starts the read-eval-print-loop");
        puts("fuzuli filename: loads and executes the script file");
    }
    if (argc == 2)
    {
        if (strcmp(argv[1], "--repl") == 0)
        {
            runRepl(argc, argv);
        }
        else
        {
            runFile(argv[1], argc, argv);
        }
    }
    return (0);
}
