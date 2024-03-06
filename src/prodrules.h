#ifndef P3_PARSER_GD_PRODRULES_H
#define P3_PARSER_GD_PRODRULES_H

#include "datastructures.h"

#define L1R1 "<e,s>"
#define L1R2 "<e+t,e>"
#define L1R3 "<t,e>"
#define L1R4 "<t*f,t>"
#define L1R5 "<f,t>"
#define L1R6 "<(e),f>"
#define L1R7 "<NUM,f>"

extern Token starting_token;
extern Token expression_token;
extern Token term_token;
extern Token factor_token;

void initialize_gloval_tokens()
{
    initialize_token(&starting_token, NULL, NON_TERMINAL_STARTING_CAT);
    initialize_token(&expression_token, NULL, NON_TERMINAL_EXPRESSION_CAT);
    initialize_token(&term_token, NULL, NON_TERMINAL_TERM_CAT);
    initialize_token(&factor_token, NULL, NON_TERMINAL_FACTOR_CAT);
}

/*Sets up the rules for the first rsa*/
void set_rules_rsa_1(RSA *rsa)
{

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

    Rule r1;
    {
        Token r1_token = starting_token; //initial


        int token_list_len = 1; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_EXPRESSION_CAT); 


        initialize_rule(&r1, token_list, token_list_len, starting_token);
    }

    Rule r2;
    {
        Token r2_token; //initial
        initialize_token(&r2_token, NULL, NON_TERMINAL_EXPRESSION_CAT); 


        int token_list_len = 3; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_EXPRESSION_CAT); 

        char* plus_str = (char*)malloc(sizeof(char) * 2); 
        strcpy(plus_str, "+"); 
        initialize_token(&token_list[1], plus_str, NON_TERMINAL_TERM_CAT); 

        initialize_token(&token_list[2], NULL, NON_TERMINAL_TERM_CAT); 


        initialize_rule(&r2, token_list, token_list_len, r2_token);
    }


    Rule r3;
    {
        Token r3_token; //initial
        initialize_token(&r3_token, NULL, NON_TERMINAL_EXPRESSION_CAT); 


        int token_list_len = 1; 
        Token* token_list = (Token*)malloc(sizeof(Token) * token_list_len); 

        initialize_token(&token_list[0], NULL, NON_TERMINAL_TERM_CAT); 


        initialize_rule(&r3, token_list, token_list_len, r3_token);
    }




















}

























// P3_PARSER_GD_PRODRULES_H

#endif