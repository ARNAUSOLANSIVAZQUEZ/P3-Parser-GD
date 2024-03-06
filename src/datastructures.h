#ifndef DATASTRUCT_HEADER
#define DATASTRUCT_HEADER

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "utils.h"
#include "monads.h"


// categories of tokens
#define NON_RECOGNIZED_CAT -1
#define NUMERIC_NUMBER_CAT 1
#define NUMERIC_OPERAND_CAT 2
#define NUMERIC_SPECIALCHAR_CAT 3

#define NON_TERMINAL_STARTING_CAT 4
#define NON_TERMINAL_EXPRESSION_CAT 5
#define NON_TERMINAL_TERM_CAT 6
#define NON_TERMINAL_FACTOR_CAT 7


typedef struct struct_token {
    char* identifier;
    int id_length;
    int category; 
} Token;


typedef struct struct_stack {
    Token* elements; 
    int element_length; 
    int element_capacity; 
} Stack; 

/*
    element -> body
*/
typedef struct struct_rule {
    Token* body; 
    int body_length; 
    Token element; 
} Rule; 


/* 
*/
typedef struct struct_rsa {

    Stack* stack; 

    Rule* rules; 
    int num_rules; 
    int capacity_rules; 

} RSA;


// functions

//TOKEN: 
/*
    Initializes the token with the given identifier and the category it belongs. 
*/
void initialize_token(Token* t, char* _identifier, int _categoty); 


/*prints, debug info. Does NOT take ownersip*/
void print_token(Token* token); 

/*duplicates the token*/
Token* clone_token(Token* original_token); 

/*
    Transforms the list and removes all unvalid tokens and frees them. 
    Len is updated. Does NOT take ownership of token_list. 
*/
void filter_token(Token* token_list, int* len); 

/*
    Frees the identifier inside token. 
*/
void free_token(Token* t); 

//Stack
/* Initializes*/
void initialize_stack(Stack* stack); 

/*
    peeks, does NOT give ownership
    Option<Token*>
*/
Option* peek_stack(Stack* stack); 

/*
    pop. gives ownership of the poped token. 
    Option<Token*>
*/
Option* pop_stack(Stack* stack); 

/*
    Push. Takes ownership of the new token. new_token must be heap-allocated. 
*/
void push_stack(Stack* stack, Token* new_token); 

/*prints*/
void print_stack(Stack* stack); 

/*Frees EVERYTHING inside*/
void free_stack(Stack* stack); 

//RULE
/*Initializes the rule with the parameters recieved, takes ownership of body and element*/
void initialize_rule(Rule* rule, Token* body, int body_length, Token element); 


/**
* The function looks if the list of rule_candidates follows the rule or not
 *
 * @param rule The rule that the rule_candidates follow or not
 * @param rule_candidates List of candidate rules that we will look if they follow the rule or not
 * @param candidate_len Lenght of the candidate rule.
 *
 * @return The function returns true if the list of rule_candidates follows the rule and false otherwise.
 */
bool follows_rule(Rule* rule, Token* rule_candidates, int candidate_len); 

/*Prints the rule's info. Does NOT take ownersip*/
void print_rule(Rule* rule); 

/*Frees the rule*/
void free_rule(Rule* rule); 

//RSA
/*Initialize the rsa*/
void initialize_rsa(RSA* rsa); 

/*Adds a rule. The order matters. */
void add_rule(RSA* rsa, Rule rule); 

/*
    Advances the rsa with the next token. It will shift the rsa with the token and then 
    reduce until it fails to do so. Does NOT take ownership of token
    
*/
void advance_rsa(RSA* rsa, Token* token); 

/*Adds clone of token to ths stack inside the rsa. Does NOT take ownership*/
void shift_rsa(RSA* rsa, Token* token); 

/*
    Tries to aply the rules in order until it can aply one. Once aplied, 
    returns true. If no rule can be aplied, returns false. 
*/
bool reduce_rsa(RSA* rsa); 

/*Returns true if there is only 1 token in the stack and that one is the starting token*/
bool is_starting_token(RSA* rsa); 

/*frees the contents of rsa*/
void free_rsa(RSA* rsa); 







#endif