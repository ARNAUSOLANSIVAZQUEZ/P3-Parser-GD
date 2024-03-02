#include "main.h"

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("%s",ERROR_ARGS); 
        return ARGS_ERROR; 
    }
    
    // Get the list of tokens that appear in the input file and its length
    Token* token_list = getTokens(argv[1]);
    int length = calculateTokenListLength(token_list);

    if (token_list == NULL || length == 0){
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_NOT_VALID_TOKENS);
        return NO_VALID_TOKENS_ERROR;
    }
    printf(TOKEN_LENGTH, length);

    for (int i=0; i<length; i++){
        printf(TOKENS, i, token_list[i].identifier, token_list[i].id_length, token_list[i].category);
    }


    // TODO: Handle error when  list of tokens is empty

    
    /* RSA rsa; 
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
    free_rsa(prsa);  */

    return PARSER_SUCCESS;
}










/*


gcc main.c datastructures.c errors.c monads.c tokens.c -o parser







*/



