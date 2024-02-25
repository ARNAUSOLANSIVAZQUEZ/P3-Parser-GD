#include "monads.h"


// Option Methods: ////////////////////////////////////////////////////////////////

// Some utility functions for Option


Option* Some(void* value, int _value_size_bytes) {
    Option* opt = (Option*)malloc(sizeof(Option));
    if (opt != NULL) {
        opt->value = value; 
        opt->value_size_bytes = _value_size_bytes; 
        opt->has_value = true;
    }
    return opt;
}


Option* None() {
    Option* opt = (Option*)malloc(sizeof(Option));
    if (opt != NULL) {
        opt->value = NULL;
        opt->value_size_bytes = 0; 
        opt->has_value = false; 
    }
    return opt;
} 


bool is_some(Option* opt) {
    return opt->has_value; 
}


void* unwrap(Option* opt) {

    if(opt->has_value) {
        return opt->value; 
    }

    printf(UNWRAP_ERROR_MESSAGE); 
    exit(UNWRAP_ERROR_CODE); 
}


void* expect_some(Option* opt, char* error_message) {

    if(opt->has_value) {
        return opt->value; 
    }
    printf("%s", error_message); 
    exit(EXPECT_ERROR_CODE); 


}


void free_option(Option* opt) {
    //free(opt->value); 
    free(opt);
}



// Result Methods: ////////////////////////////////////////////////////////////////



Result* Ok(void* value, int _value_size_bytes) {
    Result* res = (Result*)malloc(sizeof(Result));
    if (res != NULL) {
        res->ok = value; 
        res->error = NULL; 
        res->value_size_bytes = _value_size_bytes; 
        res->is_ok = 1;
    }
    return res;
}


Result* Err(void* error, int _value_size_bytes) {
    Result* res = (Result*)malloc(sizeof(Result));
    if (res != NULL) {
        res->ok = NULL;
        res->error = error;
        res->value_size_bytes = _value_size_bytes; 
        res->is_ok = 0;
    }
    return res;
}


bool is_ok(Result* res) {
    return res->is_ok; 
}


bool is_err(Result* res) {
    return !res->is_ok; 
}


void* expect(Result* res, char* error_message) {
    if(res->is_ok) {
        return res->ok; 
    }
    printf("%s", error_message); 
    exit(EXPECT_ERROR_CODE); 

}  


void* unwrap_ok(Result* res) {
    if(res->is_ok) {
        return res->ok; 
    }
    printf("%s", UNWRAP_OK_ERROR_CODE); 
    exit(EXPECT_ERROR_CODE); 

} 


void* unwrap_err(Result* res) {
    if(!res->is_ok) {
        return res->error; 
    }
    printf("%s", UNWRAP_ERR_ERROR_CODE); 
    exit(EXPECT_ERROR_CODE); 

} 


void free_result(Result* res) { 
    /*
    if(res->is_ok) {
        free(res->ok); 
    } else {
        free(res->error); 
    }*/
    free(res);
}







