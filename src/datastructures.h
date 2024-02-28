#ifndef DATASTRUCT_HEADER
#define DATASTRUCT_HEADER

#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "monads.h"








typedef struct struct_stack {
    char* elements; 
    int element_length; 
    int element_capacity; 
} Stack;

/*
    element -> body
*/
typedef struct struct_rule {
    char* body; 
    int body_length; 
    char element; 
} Rule;


/* 
*/
typedef struct struct_rsa {

    Stack stack; 

    int num_rules; 
    Rule* rules; 

} RSA;

typedef struct token{
    char* identifier;
    int category;
    int id_length;
} Token;
// functions




















#endif