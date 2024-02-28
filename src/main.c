
#include "main.h"

Token* getTokens(const char* filename){

    // Open the file
    FILE* input_file = fopen(filename, "r");
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return MAIN_ERROR_CANT_READ_FILE; // TODO: cahnge for define error
    }

    // Allocate memory for tokenList
    Token* tokenList = malloc(sizeof(Token)); // Allocate memory for one token
    if (tokenList == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return NULL;
    }
    //TODO: create list of tokens
    
    return tokenList;
}

int main(int argc, char *argv[])
{
    if(argc != 1) {
        printf("Usage: ./parser <input_file.txt>\n"); 
        return 1; 
    }
    
    // Call the getTokens function with the filename
    Token* tokenList = getTokens(argv[1]);
    
    // TODO: Handle error when  list of tokens is empty

    return SCANNER_SUCCESS;
}







