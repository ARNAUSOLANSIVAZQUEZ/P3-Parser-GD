#ifndef DATASTRUCT_HEADER
#define DATASTRUCT_HEADER

#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "monads.h"








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

    Stack stack; 

    int num_rules; 
    Rule* rules; 

} RSA;

typedef struct struct_token{
    char* identifier;
    int id_length;
    int category;
} Token;
// functions

//TOKEN: 
/*
    Initializes the token with the given identifier and the category it belongs. 
*/
void initialize_token(Token* t, char* _identifier, int _categoty); 

/*
    Frees the identifier inside token. 
*/
void free_token(Token* t); 

//Stack
/* Initializes*/
void initialize_stack(Stack* stack); 

/*peeks*/
Token* peek_stack(Stack* stack); 

/*pop*/
Token* pop_stack(Stack* stack); 

/*Push*/
void push_stack(Stack* stack, Token* new_token); 

/*Frees EVERYTHING inside*/
void free_stack(Stack* stack); 

//RULE
/*Initializes*/
void initialize_rule(Rule* rule, Token** body, int body_length, Token element); 

/*Returns true iff the list of rule_candidates follows the rule*/
bool follows_rule(Rule* rule, Token* rule_candidates, int candidate_len); 

/*Frees*/
void free_rule(Rule* rule); 

//RSA
/*Initialize the rsa*/
void initialize_rsa(RSA* rsa); 

/*Adds a rule. The order matters. */
void add_rule(RSA* rsa, Rule rule); 

/*
    Advances the rsa with the next token. It will shift the rsa with the token and then 
    reduce until it fails to do so. 
    
*/
void advance_rsa(RSA* rsa, Token* token); 

/*Adds token to ths stack inside the rsa*/
void shift_rsa(RSA* rsa, Token* token); 

/*
    Tries to aply the rules in order until it can aply one. Once aplied, 
    returns true. If no rule can be aplied, returns false. 
*/
bool reduce_rsa(RSA* rsa); 

/*Returns true if there is only 1 token in the stack and that one is the starting token*/
bool is_starting_token(RSA* rsa); 









#endif