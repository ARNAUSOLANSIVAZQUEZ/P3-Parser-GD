
#include "main.h"



int getTokens(const char* filename){

    // Open the file
    FILE* input_file = fopen(filename, "rb"); // open as binary
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return MAIN_ERROR_CANT_READ_FILE; // TODO: cahnge for define error
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Check if a file name is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MISSING_FILENAME);
        return MAIN_ERROR_MISSING_FILENAME;
    }
    
    // Call the getTokens function with the filename
    int tokenList = getTokens(argv[1]);
    
    // TODO: Handle error when  list of tokens is empty

    return SCANNER_SUCCESS;
}







