#include "errors.h"

/* ----------General errors----------------------- */
const char* ERROR_MESSAGE_SCANNER_SUCCESS = "Success";
const char* ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED = "Memory allocation failed";
const char* ERROR_ARGS = "Argc is different than 2. Right comand: ./parser <input_file.txt>\n";

/* ----------Specific Errors----------------------- */

//Main.c
const char* ERROR_MESSAGE_CANT_OPEN_FILE = "Cannot open file";
const char* ERROR_MESSAGE_CANT_READ_FILE = "Cannot read file";
const char* ERROR_MESSAGE_INVALID_TOKEN_FORMAT = "Invalid token format -> ";

//Datastructures.c


//Monads.c

/* --------------Literals----------------------- */
const char* TOKEN_LENGTH = "Length of tokenList: %d\n";
const char* TOKENS = "Token %d -> {Id: %s, Id_length: %d, Category: %d}\n";




// ^shouldn't this be constants ? 
// #dfine ERROR_MESSAGE "Everything went wrong"