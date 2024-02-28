
#include "main.h"



int main(int argc, char** argv) {

    if(argc != 1) {
        printf("Usage: ./parser <input_file.txt>\n"); 
        return 1; 
    }

    FILE* input_file = fopen(argv[0], "rb"); 

    if(input_file == NULL) {
        printf("Cannot open file. \n"); 
        return 2; 
    }



    fclose(input_file); 
    return 0; 
}







