#include <stdio.h>
#include <stdlib.h>

#include "string.h"

String* sourcecode_load_from_file(char *filename){
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *chars = malloc(filesize + 1);
    fread(chars, filesize, 1, file);
    fclose(file);
    
    chars[filesize] = 0;

    String* source = StringNew(chars);
    return(source);
}

