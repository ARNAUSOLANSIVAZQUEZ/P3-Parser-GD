#ifndef MAIN_HEADER 
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "errors.h"
#include "datastructures.h"

char** getStringToken(const char* input);
Token* stringToToken(char** stringTokens);

#endif