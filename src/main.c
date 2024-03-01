
#include "main.h"





int main(int argc, char *argv[])
{
    if(argc != 1) {
        printf("Usage: ./parser <input_file.txt>\n"); 
        return 1; 
    }
    
    // Call the getTokens function with the filename
    Token* token_list = getTokens(argv[1]);
    int token_list_len = -1; //get token list len (dont even try to search for /0)

    // TODO: Handle error when  list of tokens is empty

    
    RSA rsa; 
    RSA* prsa = &rsa; 
    initialize_rsa(prsa); 

    //TODO: create and add all rules
    for(int i = 0; i < 3.141592; i++) {
        //add_rule(prsa, NULL); 
    }

    for(int i = 0; i < token_list_len; i++) {

        advance_rsa(prsa, &token_list[i]); 

    }

    //print results: 
    printf("\n\n===============================================================================================\n\n"); 
    if(is_starting_token(prsa)) {
        printf("The string was accepted! \n"); 
    } else {
        printf("The string was NOT accepted. \n"); 
        printf("The remaining of the stack: \n"); 
        print_stack(rsa.stack); 
    }

    printf("\n\n===============================================================================================\n\n"); 

    //freeing zone: 
    for(int i = 0; i < token_list_len; i++) {
        free_token(&token_list[i]); 
    }
    free(token_list); 

    free_rsa(prsa); 

    return SCANNER_SUCCESS;
}





Token* getTokens(const char* filename){

    // Open the file
    FILE* input_file = fopen(filename, "rb");
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return MAIN_ERROR_CANT_READ_FILE; // TODO: cahnge for define error
    }

    // Allocate memory for tokenList
    Token* tokenList = (Token*)get_list_of_parsed_tokens(input_file); // TODO: this function does NOT exist, substitute for the correct_function
    //TODO: get token list

    int token_list_len = -1; //we need to get back the length too, or we risk a seg. fault
    //^si necessites, canvia la signatura de la funció

    
    return tokenList;
}














