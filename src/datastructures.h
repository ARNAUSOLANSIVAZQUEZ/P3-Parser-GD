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
void initialize_token(Token* t, char* _identifier, int _categoty); 

void free_token(Token* t); 

//Stack
void initialize_stack(Stack* stack); 

Token* peek_stack(Stack* stack); 

Token* pop_stack(Stack* stack); 

void push_stack(Stack* stack, Token* new_token); 

void free_stack(Stack* stack); 

//RULE
void initialize_rule(Rule* rule, Token** body, int body_length, Token element); 

bool follows_rule(Rule* rule, Token* rule_candidates, int candidate_len); 

void free_rule(Rule* rule); 

//RSA
void initialize_rsa(RSA* rsa); 

void add_rule(RSA* rsa, Rule rule); 

void advance_rsa(RSA* rsa, Token* token); 

void shift_rsa(RSA* rsa, Token* token); 

bool reduce_rsa(RSA* rsa); 

bool is_starting_token(RSA* rsa); 









#endif