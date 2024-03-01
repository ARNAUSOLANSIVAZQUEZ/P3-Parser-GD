
#include "main.h"

int numerateCategory(char* category){
    
    if (strstr(category, "CAT_NUMBER") != NULL) {
        return 1;   //TODO: Change for defined variables, NO NUMBERS!!!
    }
    if (strstr(category, "CAT_OPERAND") != NULL) {
        return 2;       //TODO: Change for defined variables, NO NUMBERS!!!
    }
    if (strstr(category, "CAT_SPECIALCHAR") != NULL) {
        return 3;       //TODO: Change for defined variables, NO NUMBERS!!!
    }else {
        return -1;  //Case CAT_NONRECOGNIZED
    }
}

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
    int validTokens = 0; // Track the number of valid tokens
    for (int i = 0; i < numTokens; i++) {
        
        char* identifier;
        char* category;
        
        // Manual parsing to extract identifier and category from string token
        char* token = stringTokens[i];
        char* comma = strchr(token, ',');
        if (comma == NULL) {
            fprintf(stderr, "Invalid token format: %s\n", token);
            exit(EXIT_FAILURE);
        }
        *comma = '\0'; // Replace comma with null terminator to split the token
        identifier = token;
        category = comma + 1; // Category starts after the comma
        int numberCategory = numerateCategory(category);
        
        if(numberCategory != -1){
            // Assign values to Token struct
            tokens[validTokens].identifier = identifier;
            tokens[validTokens].id_length = strlen(identifier);
            tokens[validTokens].category = numberCategory;
            validTokens++; // Increment the number of valid tokens
        }
    }

    // Resize the tokens array to contain only valid tokens
    tokens = realloc(tokens, validTokens * sizeof(Token));
    if (tokens == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
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

// Function to get content of a file as a string
char* getFileContent(const char* filename) {
    // Open the file
    FILE *input_file = fopen(filename, "r");
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }
    
    // Determine the file size
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    // Allocate memory to store file content
    char* content = malloc(file_size + 1);
    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return NULL;
    }

    // Read file content into string
    size_t bytes_read = fread(content, 1, file_size, input_file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        fclose(input_file);
        free(content);
        return NULL;
    }
    content[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(input_file);

    return content;
}

int calculateTokenListLength(Token *tokenList) {
    int length = 0;
    while (tokenList[length].identifier != NULL) {
        length++;
    }
    return length;
}

Token* getTokens(const char* filename){

    const char* input = getFileContent(filename);
    if (input == NULL) {
        fprintf(stderr, "Error getting file content from: %s\n", filename);
        return NULL;
    }

    char** stringtokens = getStringToken(input);
    
    Token* tokenList = stringToToken(stringtokens);
    
    int length = calculateTokenListLength(tokenList);
    printf("Length of tokenList: %d\n", length);

    for (int i=0; i<length; i++){
        printf("Id: %s\n", tokenList[i].identifier);
        printf("Id length: %d\n", tokenList[i].id_length);
        printf("Category: %d\n", tokenList[i].category);
    }

    // Free allocated memory
    for (int i = 0; stringtokens[i] != NULL; i++) {
        free(stringtokens[i]);
    }

    int token_list_len = -1; //we need to get back the length too, or we risk a seg. fault
    //^si necessites, canvia la signatura de la funció

    
    return tokenList;
}


int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage: ./parser <input_file.txt>\n"); 
        return 1; 
    }
    
    // Call the getTokens function with the filename
    Token* token_list = getTokens(argv[1]);
    int token_list_len = -1; //get token list len (dont even try to search for /0)

    // TODO: Handle error when  list of tokens is empty

    
    /* RSA rsa; 
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
    free_rsa(prsa);  */

    return SCANNER_SUCCESS;
}














