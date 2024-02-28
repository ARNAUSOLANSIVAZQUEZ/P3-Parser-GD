
#include "datastructures.h"




//TOKEN: 
void initialize_token(Token* t, char* _identifier, int _categoty) {
    //TODO: 
}

Token* clone_token(Token* original_token) {
    //TODO: 
}


void free_token(Token* t) {
    //TODO: 
}

//Stack
void initialize_stack(Stack* stack) {
    //TODO: 
    stack->elements = NULL;
    stack->element_length = 0;
    stack->element_capacity = 0;
}

Token* peek_stack(Stack* stack) {
    //TODO: 
    if (stack->element_length > 0) {
        return &(stack->elements[stack->element_length - 1]);
    } else {
        return NULL; // Stack is empty
    }
}

Token* pop_stack(Stack* stack) {
    //TODO: 
    if (stack->element_length > 0) {
        Token* top_element = &(stack->elements[stack->element_length - 1]);
        stack->element_length--;
        return top_element; // Return the pointer to the top element
    } else {
        return NULL; // Stack is empty
    }
}

void push_stack(Stack* stack, Token* new_token) {
    //TODO: 
    if (stack->element_length >= stack->element_capacity) {
        // If the stack is full, reallocate memory to increase capacity
        stack->element_capacity = (stack->element_capacity == 0) ? 1 : stack->element_capacity * 2;
        stack->elements = realloc(stack->elements, stack->element_capacity * sizeof(Token));
    }
    // Add the new token to the top of the stack
    stack->elements[stack->element_length] = *new_token;
    stack->element_length++; // Increment element length
}

void free_stack(Stack* stack) {
    //TODO: 
    free(stack->elements); // Free the memory allocated for elements
    stack->elements = NULL;
    stack->element_length = 0;
    stack->element_capacity = 0;
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
        rsa->rules = (Rule*)realloc(rsa->rules, rsa->capacity_rules * sizeof(Rule)); 
    
    } 

    rsa->rules[rsa->num_rules] = rule; //copy all the contents, the rsa takes ownership of the rule
    rsa->num_rules += 1; 

}

/*
    Advances the rsa with the next token. It will shift the rsa with the token and then 
    reduce until it fails to do so. 
    
*/
void advance_rsa(RSA* rsa, Token* token) {

    shift_rsa(rsa, token); 
    bool still_reducing = true; 
    while(still_reducing) {
        still_reducing = reduce_rsa(rsa); 
    }
}

void shift_rsa(RSA* rsa, Token* token) {
    push_stack(rsa->stack, token); 
}

bool reduce_rsa(RSA* rsa) {
    
    for(int i = 0; i < rsa->num_rules; i++) {
        Rule* current_rule = &rsa->rules[i]; 
        int num_of_elements_to_take = 1; 
        Token* corresponding_tokens = &rsa->stack->elements[rsa->stack->element_length - num_of_elements_to_take]; 
        bool follows_the_current_rule = follows_rule(current_rule, corresponding_tokens, num_of_elements_to_take); 
        if(follows_the_current_rule) {
            for(int j = 0; j < num_of_elements_to_take; j++) {
                Token* poped_token = pop_stack(rsa->stack); 
                free_token(poped_token); 
                free(poped_token); 
            }

            Token* substituter_token = clone_token(&(current_rule->element)); 

            push_stack(rsa->stack, substituter_token); 

            return true; 

        }

    }

    return false; 

}

bool is_starting_token(RSA* rsa) {
    printf("Comparason with starting token NOT implemented"); 
    return false; 
}





























