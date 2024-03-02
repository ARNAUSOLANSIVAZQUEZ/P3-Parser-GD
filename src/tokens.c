#include "tokens.h"

int numerateCategory(char* category){
    
    if (strstr(category, "CAT_NUMBER") != NULL) {
        return NUMERIC_NUMBER_CAT;   //TODO: Change for defined variables, NO NUMBERS!!!
    }
    if (strstr(category, "CAT_OPERAND") != NULL) {
        return NUMERIC_OPERAND_CAT;       //TODO: Change for defined variables, NO NUMBERS!!!
    }
    if (strstr(category, "CAT_SPECIALCHAR") != NULL) {
        return NUMERIC_SPECIALCHAR_CAT;       //TODO: Change for defined variables, NO NUMBERS!!!
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
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        return NULL;
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
            fprintf(stderr, "Error: %s%s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED, token);
            return NULL;
        }
        *comma = '\0'; // Replace comma with null terminator to split the token
        identifier = token;
        category = comma + 1; // Category starts after the comma
        
        // Assign values to Token struct
        tokens[validTokens].identifier = identifier;
        tokens[validTokens].id_length = strlen(identifier);
        tokens[validTokens].category = numerateCategory(category);
        validTokens++; // Increment the number of valid tokens
        
    }

    // Resize the tokens array to contain only valid tokens
    tokens = realloc(tokens, validTokens * sizeof(Token));
    if (tokens == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        return NULL;
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
                fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
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
                fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
                free(tokenString);
                tokenString = "";
            }
            tokenString = temp;
            tokenString[length] = '\0'; // Null-terminate the string
            
            // Add tokenString to list of tokenStringList
            tokenStringList = realloc(tokenStringList, (numTokens + 1) * sizeof(char*));
            if (tokenStringList == NULL) {
                fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
                return NULL;
            }
            tokenStringList[numTokens] = strdup(tokenString);
            if (tokenStringList[numTokens] == NULL) {
                fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
                return NULL;
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
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }
    tokenStringList[numTokens] = NULL;
    
    return tokenStringList;
}

char* getFileContent(const char* filename) {
    // Open the file
    FILE *input_file = fopen(filename, "r");
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_CANT_OPEN_FILE);
        return NULL;
    }
    
    // Determine the file size
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    // Allocate memory to store file content
    char* content = malloc(file_size + 1);
    if (content == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        fclose(input_file);
        return NULL;
    }

    // Read file content into string
    size_t bytes_read = fread(content, 1, file_size, input_file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_CANT_READ_FILE);
        fclose(input_file);
        free(content);
        return NULL;
    }
    content[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(input_file);

    return content;
}

int calculateTokenListLength(Token* tokenList) {
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
    if (stringtokens == NULL) {
        // Handle error, maybe free input here if necessary
        return NULL;
    }
    
    // Calculate the size of stringTokens
    int stringTokensSize = 0;
    while (stringtokens[stringTokensSize] != NULL) {
        stringTokensSize++;
    }

    // Allocate memory for tokenList based on the size of stringTokens
    Token* tokenList = malloc(stringTokensSize * sizeof(Token));
    if (tokenList == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        // Free allocated memory for stringtokens before returning
        for (int i = 0; stringtokens[i] != NULL; i++) {
            free(stringtokens[i]);
        }
        free(stringtokens);
        return NULL;
    }

    // Populate tokenList with tokens
    tokenList = stringToToken(stringtokens);

    return tokenList;
}