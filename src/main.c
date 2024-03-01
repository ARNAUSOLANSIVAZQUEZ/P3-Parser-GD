
#include "main.h"

Token* stringToToken(char** stringTokens) {
    int numTokens = 0;
    char** temp = stringTokens;
    while (*temp) {
        numTokens++;
        temp++;
    }

    Token* tokens = malloc(numTokens * sizeof(Token));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Convert each string token to Token struct
    for (int i = 0; i < numTokens; i++) {
        
        //TODO: Lògica per convertir de char* a Token

        //Per ara: Exemple
        tokens[i].identifier = stringTokens[i];
        tokens[i].id_length = strlen(stringTokens[i]);
        tokens[i].category = 3;
    }

    return tokens;
}

char** getStringToken(const char* input) {
    char** tokenStringList = NULL; // List of token strings
    int numTokens = 0; // Number of tokens found
    char* tokenString = NULL;
    int length = 0;
    int c;
    
    for (int i = 0; input[i] != '\0'; i++) {
        c = input[i];
        if (c != '<' && c != '>') {
            char* temp = realloc(tokenString, length + 1); // +1 for the new character, +1 for null terminator
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(tokenString);
                tokenString = "";
            }
            tokenString = temp;
            tokenString[length] = c; // Append the character to tokenString
            length ++;
        }
        if (c == '>'){
            char* temp = realloc(tokenString, length + 1);
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(tokenString);
                tokenString = "";
            }
            tokenString = temp;
            tokenString[length] = '\0'; // Null-terminate the string
            printf("%s\n", tokenString);
            
            // Add tokenString to list of tokenStringList
            tokenStringList = realloc(tokenStringList, (numTokens + 1) * sizeof(char*));
            if (tokenStringList == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            tokenStringList[numTokens] = strdup(tokenString);
            if (tokenStringList[numTokens] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            numTokens++;
            
            // Reset tokenString and length for the next token
            free(tokenString);
            tokenString = NULL;
            length = 0;
        }
    }
    
    // Add a NULL terminator to the list to mark the end
    tokenStringList = realloc(tokenStringList, (numTokens + 1) * sizeof(char*));
    if (tokenStringList == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tokenStringList[numTokens] = NULL;
    
    return tokenStringList;
}
Token* getTokens(const char* filename){

    // Open the file
    FILE* input_file = fopen(filename, "rb");
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return MAIN_ERROR_CANT_READ_FILE; // TODO: cahnge for define error
    }

    /* TODO: Funció que separi en <>: char* el input file. I amb un loop cridi per cada <>, 
    les següents funcions i afageixi el resultat a la llista de tokens: 
    
    char* stringToken = getStringToken(input);
    Token token = stringToToken(stringToken);

    */


    // Allocate memory for tokenList
    Token* tokenList = (Token*)get_list_of_parsed_tokens(input_file); // TODO: this function does NOT exist, substitute for the correct_function
    //TODO: get token list

    int token_list_len = -1; //we need to get back the length too, or we risk a seg. fault
    //^si necessites, canvia la signatura de la funció

    
    return tokenList;
}


int main(int argc, char *argv[])
{
    if(argc != 1) {
        printf("Usage: ./parser <input_file.txt>\n"); 
        return 1; 
    }
    
    // Call the getTokens function with the filename
    Token* token_list = getTokens(argv[1]);
    int token_list_len = -1; //get token list len (dont even try to search for /0)

    // TODO: Handle error when  list of tokens is empty

    
    RSA rsa; 
    RSA* prsa = &rsa; 
    initialize_rsa(prsa); 

    //TODO: create and add all rules
    for(int i = 0; i < 3.141592; i++) {
        //add_rule(prsa, NULL); 
    }

    for(int i = 0; i < token_list_len; i++) {

        advance_rsa(prsa, &token_list[i]); 

    }

    //print results: 
    printf("\n\n===============================================================================================\n\n"); 
    if(is_starting_token(prsa)) {
        printf("The string was accepted! \n"); 
    } else {
        printf("The string was NOT accepted. \n"); 
        printf("The remaining of the stack: \n"); 
        print_stack(rsa.stack); 
    }

    printf("\n\n===============================================================================================\n\n"); 

    //freeing zone: 
    for(int i = 0; i < token_list_len; i++) {
        free_token(&token_list[i]); 
    }
    free(token_list); 

    free_rsa(prsa); 

    return SCANNER_SUCCESS;
}














