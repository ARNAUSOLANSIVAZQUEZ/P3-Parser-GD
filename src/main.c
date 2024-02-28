
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
    if(argc != 1) {
        printf("Usage: ./parser <input_file.txt>\n"); 
        return 1; 
    }
    
    // Call the getTokens function with the filename
    int tokenList = getTokens(argv[1]);
    
    // TODO: Handle error when  list of tokens is empty

    return SCANNER_SUCCESS;
}







