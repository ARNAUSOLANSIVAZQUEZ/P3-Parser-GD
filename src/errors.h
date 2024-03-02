#ifndef ERRORS_H
#define ERRORS_H

/* ----------General errors----------------------- */
#define PARSER_SUCCESS 0
#define MEMORY_ALLOCATION_ERROR 12
#define ARGS_ERROR -1
const char* ERROR_MESSAGE_SCANNER_SUCCESS;
const char* ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED;
const char* ERROR_ARGS;

/* ----------Specific Errors----------------------- */

//Main.c
const char* ERROR_MESSAGE_CANT_OPEN_FILE;
const char* ERROR_MESSAGE_CANT_READ_FILE;
const char* ERROR_MESSAGE_INVALID_TOKEN_FORMAT;

//Datastructures.c


//Monads.c

/* -----------Literals---------------------------- */
const char* TOKEN_LENGTH;
const char* TOKENS;


#endif
