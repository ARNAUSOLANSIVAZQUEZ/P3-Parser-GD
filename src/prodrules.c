

#include "prodrules.h"



/*Sets up the rules for the first rsa*/
void set_rules_rsa_1(RSA* rsa) {

    /*
        Rules:

    1: s -> e
    2: e ->  e + t
    3:     | t
    4: t -> t * f
    5:     | f
    6: f -> (e)
    7:    | NUM

    */

    Rule r1; //1: s -> e
    {
        Token r1_token; //initial
        initialize_token(&r1_token, NULL, NON_TERMINAL_STARTING_CAT); 

        int token_list_len = 1; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_EXPRESSION_CAT); 


        initialize_rule(&r1, token_list, token_list_len, r1_token);
    }

    Rule r2; //2: e ->  e + t
    {
        Token r2_token; //initial
        initialize_token(&r2_token, NULL, NON_TERMINAL_EXPRESSION_CAT); 


        int token_list_len = 3; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_EXPRESSION_CAT); 

        char* plus_str = (char*)malloc(sizeof(char) * 2); 
        strcpy(plus_str, "+"); 
        initialize_token(&token_list[1], plus_str, NUMERIC_NUMBER_CAT); 

        initialize_token(&token_list[2], NULL, NON_TERMINAL_TERM_CAT); 


        initialize_rule(&r2, token_list, token_list_len, r2_token);
    }

    Rule r3; //3:     | t
    {
        Token r3_token; //initial
        initialize_token(&r3_token, NULL, NON_TERMINAL_EXPRESSION_CAT); 


        int token_list_len = 1; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_TERM_CAT); 


        initialize_rule(&r3, token_list, token_list_len, r3_token);
    }

    Rule r4; //4: t -> t * f
    {
        Token r4_token; //initial
        initialize_token(&r4_token, NULL, NON_TERMINAL_TERM_CAT); 


        int token_list_len = 3; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_TERM_CAT); 
        
        char* mult_sing = (char*)malloc(sizeof(char) * 2); 
        strcpy(mult_sing, "*"); 
        initialize_token(&token_list[1], mult_sing, NUMERIC_OPERAND_CAT); 
        
        initialize_token(&token_list[2], NULL, NON_TERMINAL_FACTOR_CAT); 


        initialize_rule(&r4, token_list, token_list_len, r4_token);
    }

    Rule r5; //5:     | f
    {
        Token r5_token; //initial
        initialize_token(&r5_token, NULL, NON_TERMINAL_TERM_CAT); 


        int token_list_len = 1; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_FACTOR_CAT); 
        
        initialize_rule(&r5, token_list, token_list_len, r5_token);
    }


    Rule r6; //6: f -> (e)
    {
        Token r6_token; //initial
        initialize_token(&r6_token, NULL, NON_TERMINAL_TERM_CAT); 


        int token_list_len = 3; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        char* parenthesis_open_string = (char*)malloc(sizeof(char) * 2); 
        strcpy(parenthesis_open_string, "("); 
        initialize_token(&token_list[0], parenthesis_open_string, NUMERIC_SPECIALCHAR_CAT); //parenthesis ()
        
        initialize_token(&token_list[1], NULL, NON_TERMINAL_EXPRESSION_CAT); 
        
        char* parenthesis_close_string = (char*)malloc(sizeof(char) * 2); 
        strcpy(parenthesis_close_string, ")"); 
        initialize_token(&token_list[2], parenthesis_close_string, NUMERIC_SPECIALCHAR_CAT); //parenthesis ()
        

        initialize_rule(&r6, token_list, token_list_len, r6_token);
    }

    Rule r7; //7:    | NUM
    {
        Token r7_token; //initial
        initialize_token(&r7_token, NULL, NON_TERMINAL_TERM_CAT); 


        int token_list_len = 1; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NUMERIC_NUMBER_CAT); 
        

        initialize_rule(&r7, token_list, token_list_len, r7_token);
    }



    add_rule(rsa, r1); 
    add_rule(rsa, r2); 
    add_rule(rsa, r3); 
    add_rule(rsa, r4); 
    add_rule(rsa, r5); 
    add_rule(rsa, r6); 
    add_rule(rsa, r7); 


}




