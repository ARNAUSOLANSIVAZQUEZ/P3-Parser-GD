
#include "datastructures.h"




//TOKEN: 
void initialize_token(Token* t, char* _identifier, int _categoty) {
    if(_identifier != NULL) {
        t->identifier = strdup(_identifier);
        t->id_length = strlen(_identifier);  
    } else {
        t->identifier = NULL; 
        t->id_length = 0; 
    }
    t->category = _categoty;   
}

Token* clone_token(Token* original_token) {
    Token* clone = (Token*)malloc(sizeof(Token));
    if(original_token->identifier != NULL) {
        clone->identifier = strdup(original_token->identifier);
    } else {
        clone->identifier = NULL; 
    }
    clone->id_length = original_token->id_length;
    clone->category = original_token->category;
    return clone;
}

void print_token(Token* token) {
    //printf("\tToken: _________________________\n");


    char category_string[50] = ""; 
    switch (token->category){
    case NUMERIC_NUMBER_CAT: 
        strcpy(category_string, "NUMBER"); 
        break;
    case NUMERIC_OPERAND_CAT: 
        strcpy(category_string, "OPERAND"); 
        break;
    case NUMERIC_SPECIALCHAR_CAT: 
        strcpy(category_string, "SPECIALCHAR"); 
        break;
    case NON_TERMINAL_STARTING_CAT: 
        strcpy(category_string, "NT_STARTING"); 
        break;
    case NON_TERMINAL_EXPRESSION_CAT: 
        strcpy(category_string, "NT_EXPRESSION"); 
        break;
    case NON_TERMINAL_TERM_CAT: 
        strcpy(category_string, "NT_TERM"); 
        break;
    case NON_TERMINAL_FACTOR_CAT: 
        strcpy(category_string, "NT_FACTOR"); 
        break;

    default: 
        printf("NON-VALID CATEGORY. /////////////////////////////////////////////////////////////////////////////////\n"); 
        return; 
        break;
    }


    if(token->identifier != NULL) {
        printf("[%s | (%d) %s ]", category_string, token->id_length, token->identifier); 
    } else {
        printf("[%s]", category_string); 
    }

    /*
    printf("Identifier: %s\n", token->identifier);
    printf("Length: %d\n", token->id_length);
    printf("Category: %d\n", token->category);
    printf("\t_________________________________\n");*/
}

void filter_token(Token* token_list, int* len) {

    /*
    There are 2 indexes, reading and writing. The reading reads the token and if it is valid
    (category is good), copies all the contents in the wrinting index position. 
    Otherwise, it frees the token and proceeds. 
    
    */

    int current_index = 0; 

    int current_token_category = 0; //auxiliar variable
    for(int i = 0; i < *len; i++) {

        current_token_category = token_list[i].category; 
        if(NUMERIC_NUMBER_CAT == current_token_category || NUMERIC_OPERAND_CAT == current_token_category || NUMERIC_SPECIALCHAR_CAT == current_token_category) {
            
            //Valid categories are only NUMERIC_NUMBER_CAT, NUMERIC_OPERAND_CAT and NUMERIC_SPECIALCHAR_CAT
            // this could be generalized

            token_list[current_index].identifier = token_list[i].identifier; 
            token_list[current_index].id_length = token_list[i].id_length; 
            token_list[current_index].category = token_list[i].category; 
            current_index++; 

        } else {
            free_token(&token_list[i]); 
        }

    }

    *len = current_index; 

}

void free_token(Token* token) {
    if(token->identifier != NULL) {
        free(token->identifier);
    }
}

//Stack
void initialize_stack(Stack* stack) {
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

    if(stack->element_length <= 0) {
        return None(); // Stack is empty
    }

    /*
    Token* top_element_ptr = (Token*)malloc(sizeof(Token) * 1); 
    *top_element_ptr = stack->elements[stack->element_length - 1]; 
    stack->element_length += -1; */

    Token* top_element_ptr_clone = clone_token(&stack->elements[stack->element_length - 1]); 
    free_token(&stack->elements[stack->element_length - 1]); 
    stack->element_length += -1;


    return Some(top_element_ptr_clone, sizeof(Token));
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
        printf("\n%d: \t", i + 1);
        print_token(&stack->elements[i]); 
    }
    printf("\n_______________________________\n"); 
}

void free_stack(Stack* stack) {
    for(int i = 0; i < stack->element_length; i++) {
        free_token(&stack->elements[i]); //free the contents of the token
    }

    free(stack->elements); // Free the memory allocated for elements
    //no need to assing everything to 0, this memory is now unvalid and should not be used. It is not our responsability to warn anyone
}

//RULE
void initialize_rule(Rule* rule, Token* body, int body_length, Token element) {
    rule->body = (Token*)malloc(body_length * sizeof(Token));

    for (int i = 0; i < body_length; i++) {
        rule->body[i] = body[i];
    }

    rule->body_length = body_length;
    rule->element = element;
    free(body); 
}

bool follows_rule(Rule* rule, Token* rule_candidates, int candidate_len) {
    // We check if the body_length matches the candidate_len
    if (rule->body_length != candidate_len) {
        return false;
    }

    // Compare token categories instead of literals
    for (int i = 0; i < rule->body_length; i++) {
        if (rule->body[i].category != rule_candidates[i].category) {
            return false;
        }
    }

    return true;
}

void print_rule(Rule* rule) {
    printf("\tRule: _________________________\n");

    printf("Element: ");
    print_token(&rule->element); 
    printf("\nBody: ");
    for (int i = 0; i < rule->body_length; i++) {
        //printf("%s ", rule->body[i].identifier);
        print_token(&rule->body[i]); 
        printf("\t");
    }

    //printf("Element: %s\n", rule->element.identifier);
    printf("\n");
    //printf("\t_________________________________\n");
}

void free_rule(Rule* rule) {
    // Free the tokens in rule->body
    for (int i = 0; i < rule->body_length; i++) {
        free_token(&rule->body[i]);
    }

    // Free rule->body itself
    free(rule->body);

    // Free the element
    free_token(&rule->element);
}
//RSA
void initialize_rsa(RSA* rsa) {
    rsa->num_rules = 0; 
    rsa->capacity_rules = ARRAY_BASE_CAPACITY; 
    rsa->rules = (Rule*)malloc(ARRAY_BASE_CAPACITY * sizeof(Rule)); 
    rsa->stack = (Stack*)malloc(sizeof(Stack)); 
    initialize_stack(rsa->stack);

}

void add_rule(RSA* rsa, Rule rule) {

    if(rsa->num_rules == rsa->capacity_rules) {
        //add capacity
        rsa->capacity_rules = (int)(rsa->capacity_rules * ARRAY_GROWTH_FACOTR); 
        rsa->rules = (Rule*)realloc(rsa->rules, rsa->capacity_rules * sizeof(Rule)); 
    
    } 

    rsa->rules[rsa->num_rules] = rule; //copy all the contents, the rsa takes ownership of the rule
    rsa->num_rules += 1; 

}

void advance_rsa(RSA* rsa, Token* token) {

    printf("Shift: \t"); 
    print_token(token); 
    printf("\n"); 

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
        Rule* current_rule_ptr = &rsa->rules[i]; 
        int num_affected_tokens = current_rule_ptr->body_length; 
        Token* affected_tokens = &rsa->stack->elements[rsa->stack->element_length - num_affected_tokens]; 
        bool follows_the_current_rule = follows_rule(current_rule_ptr, affected_tokens, num_affected_tokens); 
        
        if(follows_the_current_rule) { 

            printf("Aplying the rule: \n"); 
            print_rule(current_rule_ptr); 
            printf("\n\n"); 

            //remove the substituted elements
            for(int j = 0; j < num_affected_tokens; j++) { 
                Option* poped_token_opt = pop_stack(rsa->stack); 
                Token* poped_token = (Token*)expect_some(poped_token_opt, "A token. Should always succeed because the rule test suceded. \n"); 
                
                free_option(poped_token_opt); 
                free_token(poped_token); 
                free(poped_token); 
            }

            //add new token
            Token* substituter_token = clone_token(&(current_rule_ptr->element)); 

            push_stack(rsa->stack, substituter_token); 

            return true; 

        }

    }

    return false; 

}

bool is_starting_token(RSA* rsa) {

    bool ret = rsa->stack->element_length == 1; 
    if(!ret) return false; 

    Option* first_token_opt= peek_stack(rsa->stack); 
    if(first_token_opt->has_value) {
        Token* first_token = unwrap(first_token_opt); 
        ret = first_token->category == NON_TERMINAL_STARTING_CAT; 
    } else ret = false; 
    free_option(first_token_opt); 
    return ret; 

    /*
    bool ret = rsa->stack->element_length == 1; 
    if(ret) { 
        ret = rsa->stack->elements[0].category == NON_TERMINAL_STARTING_CAT; 
    }
    return ret; */
}

void print_rsa(RSA* rsa) {

    for(int i = 0; i < rsa->num_rules; i++) print_rule(&(rsa->rules[i])); 

    print_stack(rsa->stack); 

}


void free_rsa(RSA* rsa) {
    //rsa->rules
    for(int i = 0; i < rsa->num_rules; i++) {
        free_rule(&rsa->rules[i]); 
    }
    free(rsa->rules); 
    free_stack(rsa->stack); 
    
}


