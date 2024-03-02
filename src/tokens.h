#ifndef TOKENS_HEADER 
#define TOKENS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "errors.h"
#include "datastructures.h"






/**
 * Splits a string into an array of string tokens based on '<' and '>' delimiters.
 *
 * @param input The input string to be tokenized.
 * @return An array of string tokens. Each token represents a substring between '<' and '>'.
 *         The last element of the array is set to NULL to mark the end.
 *         If memory allocation fails during tokenization, the function terminates with an error message.
 */
char** getStringToken(const char* input, int* len); 
//char** getStringToken(const char* input);

/**
 * Converts an array of string tokens to an array of Token structs.
 *
 * @param stringTokens An array of string tokens.
 * @return An array of Token structs representing the string tokens.
 */
Token* stringToToken(char** stringTokens);

/**
 * Numerates the category of a token based on its string representation.
 *
 * @param category The string representation of the category.
 * @return An integer representing the category:
 *         - NUMERIC_NUMBER_CAT for numeric number category.
 *         - NUMERIC_OPERAND_CAT for numeric operand category.
 *         - NUMERIC_SPECIALCHAR_CAT for numeric special character category.
 *         - -1 for unrecognized category.
 */
int numerateCategory(char* category);

/**
 * Parses the content of a file into a list of tokens.
 *
 * @param filename The name of the file to be parsed.
 * @return Result<Token*, int>: A dynamically allocated array of Token structs representing the tokens parsed from the file.
 *         If the file content cannot be retrieved or parsed successfully, NULL is returned, and an error message is printed to stderr.
 *         If memory allocation fails during token parsing, NULL is returned, and an error message is printed to stderr.
 */
Result* getTokens(const char* filename); 
//Token* getTokens(const char* filename);


/**
 * Reads the content of a file and returns it as a dynamically allocated string.
 *
 * @param filename The name of the file to be read.
 * @return A dynamically allocated string containing the content of the file.
 *         If the file cannot be opened, NULL is returned, and an error message is printed to stderr.
 *         If memory allocation fails during file content reading, NULL is returned, and an error message is printed to stderr.
 *         If an error occurs while reading the file, NULL is returned, and an error message is printed to stderr.
 */
char* getFileContent(const char* filename);

/**
 * Calculates the length of a token list.
 *
 * @param tokenList The list of tokens.
 * @return The number of tokens in the list.
 */
int calculateTokenListLength(Token* tokenList);












#endif