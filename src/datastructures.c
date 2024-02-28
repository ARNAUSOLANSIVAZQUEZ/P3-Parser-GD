
#include "datastructures.h"




//TOKEN: 
void initialize_token(Token* t, char* _identifier, int _categoty) {
    //TODO: 
}

void free_token(Token* t) {
    //TODO: 
}

//Stack
void initialize_stack(Stack* stack) {
    //TODO: 

}

Token* peek_stack(Stack* stack) {
    //TODO: 

}

Token* pop_stack(Stack* stack) {
    //TODO: 

}

void push_stack(Stack* stack, Token* new_token) {
    //TODO: 

}

void free_stack(Stack* stack) {
    //TODO: 

}

//RULE
void initialize_rule(Rule* rule, Token** body, int body_length, Token element) {
    //TODO: 

}

bool follows_rule(Rule* rule, Token* rule_candidates, int candidate_len) {
    //TODO: 
    return false; 
}

void free_rule(Rule* rule) {
    //TODO: 

}

//RSA
void initialize_rsa(RSA* rsa) {
    rsa->num_rules = 0; 
    rsa->capacity_rules = ARRAY_BASE_CAPACITY; 
    rsa->rules = (Rule*)malloc(rsa->capacity_rules * sizeof(Rule)); 
    rsa->stack = (Stack*)malloc(sizeof(Stack)); 
    initialize_stack(rsa->stack);

}

/*Adds a rule. The order matters. */
void add_rule(RSA* rsa, Rule rule) {

    if(rsa->num_rules = rsa->capacity_rules) {
        //add capacity
        rsa->capacity_rules = (int)(rsa->capacity_rules * ARRAY_GROWTH_FACOTR); 
    } 

    rsa->rules[rsa->num_rules] = rule; //copy all the contents, the rsa takes ownership of the rule
    rsa->num_rules += 1; 


}

/*
    Advances the rsa with the next token. It will shift the rsa with the token and then 
    reduce until it fails to do so. 
    
*/
void advance_rsa(RSA* rsa, Token* token) {
    //TODO: 

}

/*Adds token to ths stack inside the rsa*/
void shift_rsa(RSA* rsa, Token* token); 

/*
    Tries to aply the rules in order until it can aply one. Once aplied, 
    returns true. If no rule can be aplied, returns false. 
*/
bool reduce_rsa(RSA* rsa); 

/*Returns true if there is only 1 token in the stack and that one is the starting token*/
bool is_starting_token(RSA* rsa); 





























