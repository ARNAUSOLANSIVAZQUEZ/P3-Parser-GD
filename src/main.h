#ifndef MAIN_HEADER 
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "errors.h"
/* #include "datastructures.h" */

typedef struct struct_token {
    char* identifier;
    int id_length;
    int category;
} Token;


char** getStringToken(const char* input);
Token* stringToToken(char** stringTokens);
int numerateCategory(char* category);
Token* getTokens(const char* filename);
char* getFileContent(const char* filename);
int calculateTokenListLength(Token *tokenList);

#endif