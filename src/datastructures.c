
#include "datastructures.h"




//TOKEN: 
void initialize_token(Token* t, char* _identifier, int _categoty) {
    //TODO: 
    t->identifier = strdup(_identifier);
    t->id_length = strlen(_identifier);  
    t->category = _categoty;   
}

Token* clone_token(Token* original_token) {
    //TODO: 
    Token* clone = (Token*)malloc(sizeof(Token));
    clone->identifier = strdup(original_token->identifier);
    clone->id_length = original_token->id_length;
    clone->category = original_token->category;
    return clone;
}

void print_token(Token* token) {
    //TODO: 
    printf("\tToken: _________________________\n");
    printf("Identifier: %s\n", token->identifier);
    printf("Length: %d\n", token->id_length);
    printf("Category: %d\n", token->category);
    printf("\t_________________________________\n");
}

void free_token(Token* t) {
    //TODO: 
    free(t->identifier);
}

//Stack
void initialize_stack(Stack* stack) {
    //TODO: 
    stack->element_length = 0;
    stack->element_capacity = ARRAY_BASE_CAPACITY;
    stack->elements = (Token*)malloc(stack->element_capacity * sizeof(Token));
}

Option* peek_stack(Stack* stack) {
    if (stack->element_length > 0) {
        return Some(&(stack->elements[stack->element_length - 1]), sizeof(Token));
    } else {
        return None(); // Stack is empty
    }
}

Option* pop_stack(Stack* stack) {

    if (stack->element_length > 0) {
        Token* top_element_ptr = (Token*)malloc(sizeof(Token) * 1); 
        *top_element_ptr = stack->elements[stack->element_length - 1]; 
        stack->element_length--;
        return Some(top_element_ptr, sizeof(Token));
    } else { 
        return None(); // Stack is empty
    }
}

void push_stack(Stack* stack, Token* new_token) {

    if (stack->element_length >= stack->element_capacity) {
        // If the stack is full, reallocate memory to increase capacity
        stack->element_capacity = (int)(stack->element_capacity * ARRAY_GROWTH_FACOTR);
        stack->elements = realloc(stack->elements, stack->element_capacity * sizeof(Token));
    }
    // Add the new token to the top of the stack
    stack->elements[stack->element_length] = *new_token;
    stack->element_length++; // Increment element length 

    free(new_token); //the information has been copied, but we must free the memory since its our responsability now. 

}

void print_stack(Stack* stack) {
    printf("\tStack: _________________________\n"); 
    for(int i = 0; i < stack->element_length; i++) {
        print_token(&stack->elements[i]); 
    }
    printf("_______________________________\n"); 
}


void free_stack(Stack* stack) {
    for(int i = 0; i < stack->element_length; i++) {
        free_token(&stack->elements[i]); //free the contents of the token
    }

    free(stack->elements); // Free the memory allocated for elements
    //no need to assing everything to 0, this memory is now unvalid and should not be used. It is not our responsability to warn anyone
}

//RULE
void initialize_rule(Rule* rule, Token** body, int body_length, Token element) {
    //TODO: 

}

bool follows_rule(Rule* rule, Token* rule_candidates, int candidate_len) {
    //TODO: 
    return false; 
}

void print_rule(Rule* rule) {
    //TODO: 

    //maybe wanna use: ?
    // print_token(Token* token)
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
    Token* cloned = clone_token(token); 
    push_stack(rsa->stack, cloned); 
}

bool reduce_rsa(RSA* rsa) {
    
    for(int i = 0; i < rsa->num_rules; i++) {
        Rule* current_rule = &rsa->rules[i]; 
        int num_of_elements_to_take = 1; 
        Token* corresponding_tokens = &rsa->stack->elements[rsa->stack->element_length - num_of_elements_to_take]; 
        bool follows_the_current_rule = follows_rule(current_rule, corresponding_tokens, num_of_elements_to_take); 
        if(follows_the_current_rule) { 

            printf("Aplying the rule: \n"); 
            print_rule(current_rule); 
            printf("\n\n"); 

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


void free_rsa(RSA* rsa) {
    //TODO


}




























