#ifndef ERRORS_H
#define ERRORS_H

/* ----------General errors----------------------- */
#define PARSER_SUCCESS 0
#define MEMORY_ALLOCATION_ERROR 12
#define ARGS_ERROR -1
extern const char* ERROR_MESSAGE_SCANNER_SUCCESS;
extern const char* ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED;
extern const char* ERROR_ARGS;

/* ----------Specific Errors----------------------- */

//Main.c
#define NO_VALID_TOKENS_ERROR -2
extern const char* ERROR_MESSAGE_CANT_OPEN_FILE;
extern const char* ERROR_MESSAGE_CANT_READ_FILE;
extern const char* ERROR_MESSAGE_INVALID_TOKEN_FORMAT;
extern const char* ERROR_MESSAGE_NOT_VALID_TOKENS;


//Datastructures.c


//Monads.c

/* -----------Literals---------------------------- */
extern const char* TOKEN_LENGTH;
extern const char* TOKENS;


#endif