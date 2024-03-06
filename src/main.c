#include "main.h"

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("%s",ERROR_ARGS); 
        return ARGS_ERROR; 
    }
    
    // Get the list of tokens that appear in the input file and its length
    Result* result_tok_list = getTokens(argv[1]); 
    if(!result_tok_list->is_ok) {
        //TODO: handle errors 
        int* error_num_ptr = result_tok_list->error; 
        int error_num = error_num_ptr[0]; 
        free(error_num_ptr); 
        free_result(result_tok_list); 

        if(error_num == 0) {
            // error reading file, message already displayed
            return 1; 
        }

        if(error_num == TOKEN_SCAN_ERROR) {
            fprintf(stderr, "%s", ERROR_MESSAGE_PARSING_TOKEN_ERROR);
            return 1; 
        }

        if(error_num = MEMORY_ALLOCATION_ERROR) {
            fprintf(stderr, "Error while requesting memory. \n");
            return 1; 
        }
    
    }
    Token* token_list = unwrap_ok(result_tok_list); 
    int token_list_len = result_tok_list->value_size_bytes / sizeof(Token); 
    //calculateTokenListLength(token_list); 
    free_result(result_tok_list); 

    filter_token(token_list, &token_list_len); //removes unwanted tokens
    
    printf(TOKEN_LENGTH, token_list_len);

    /*
    //print all tokens
    for (int i = 0; i < token_list_len; i++){
        printf(TOKENS, i, token_list[i].identifier, token_list[i].id_length, token_list[i].category);
    }*/


    initialize_gloval_tokens(); 
    
    
    
    RSA rsa; 
    RSA* prsa = &rsa; 
    initialize_rsa(prsa); 

    set_rules_rsa_1(prsa); 

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
    
    
    

    return PARSER_SUCCESS;
}










/*


gcc main.c datastructures.c errors.c monads.c tokens.c -o parser

Use: 

./parser test1.txtscn





*/



