#ifndef MONADS_HEADER
#define MONADS_HEADER


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



#define UNWRAP_ERROR_MESSAGE "Tried to unwrap a None option. \n"
#define UNWRAP_OK_ERROR_CODE "Tried to unwrap as Ok an Err Result. \n"
#define UNWRAP_ERR_ERROR_CODE "Tried to unwrap as Err an Ok Result. \n"
#define UNWRAP_ERROR_CODE 142
#define EXPECT_ERROR_CODE 143
// 142 and  143 don't have any special meaning


/*
    Option monad: 

For detailed information, check Rust's definition (https://doc.rust-lang.org/std/option/). 

Small introduction: 
It can have two (2) variants: 

    Some(T)
    None()

Where T is a generic type. In other words: this variable can have 2 "forms" having a value 
(some) or not having any value (none). Some holds a generic value; to get it you need to use 
the corresponding methods. Note that trying to unwrap a None will result in an error (this 
is by design). It is recommended to use expect_some() for a custom error message. 

*/
typedef struct { 
    void* value; 
    unsigned int value_size_bytes; 
    bool has_value;
} Option;



/*
    Result monad: 

For detailed information, check Rust's definition (https://doc.rust-lang.org/std/result/). 

Small introduction: 
It can have two (2) variants: 

    Ok(T)
    Err(E)

Where T and E are generic types. This monad is intended to be a return of a function than 
can have an error, for example accessing a file (where the permissions can deny it). In 
this example we can succesfully retrive the contents or fail to do so. To return a proper 
return value Result is optimal since we can just return Ok(contents) if it is succesful or
Error(my_custom_error_message) in case of error. 

In other words: this variable can have 2 "forms": Ok, that holds a succeeed value, or 
Err, that holds an error value. 

Please use the corresponding methods for interacting with result. Use is_ok() to determinare 
if the value is ok and expect() to get the value or unwrap_err to get the error. 

*/

typedef struct {
    void* ok; 
    void* error; 
    unsigned int value_size_bytes; 
    int is_ok;
} Result;


//      Option Methods: 

/*
    Generate an option with the Some variant and the given value. 
    _value_size_bytes is the size of value in bytes. This may be helpfull to the one
    that retrives the information. 
*/
Option* Some(void* value, int _value_size_bytes); 

/*
    Ctrates an option of the variant None. It does NOT hold any value. 
*/
Option* None(); 

/*
    returns true iff opt contains a value (is the variant some)
*/
bool is_some(Option* opt); 

/*
    Returns the value inside the Option. If there is no value, it will print 
    an error and will abort the process. 
*/
void* unwrap(Option* opt); 

/*
    Same as unwrap but with a custom error message. It's more usefull because it allows 
    you to write what are you expecting in the error message to improve legivility. 
    Usage example: 

    int ret = *(int*)expect_some(my_option, "Expecting index of the element 0. "). 

    If you are certain that a function should return a value you could use this direcly 
    without checking the contents first. 
*/
void* expect_some(Option* res, char* error_message); 

/*
    Frees the option. Does NOT free the contents inside, they are responsability of the calee. 
*/
void free_option(Option* opt); 


//      Result Methods: 

/*
    Generate a result with the Ok variant and the given value. Represents that 
    the operation was succesfull. 

    _value_size_bytes is the size of value in bytes. This may be helpfull to the one
    that retrives the information. 
*/
Result* Ok(void* value, int _value_size_bytes); 

/*
    Generate a result with the Err variant and the given value. Represents thet there 
    was an error in the function. 
    
    _value_size_bytes is the size of value in bytes. This may be helpfull to the one
    that retrives the information. 
*/
Result* Err(void* error, int _value_size_bytes); 

/*
    Returns true iff res is the variant Ok. 
*/
bool is_ok(Result* res); 

/*
    Returns true iff res is the variant Err. 
*/
bool is_err(Result* res); 

/*
    Returns the Ok value inside the Result. If res is Err, it will print 
    an error and will abort the process. 
*/
void* unwrap_ok(Result* res); 

/*
    Returns the Err value inside the Result. If res is Ok, it will print 
    an error and will abort the process. 
*/
void* unwrap_err(Result* res); 

/*
    Same as unwrap_ok but with a custom error message. It's more usefull because it allows 
    you to write what are you expecting in the error message to improve legivility. 
    Usage example: 

    char* ret = (char*)expect(my_result, "Expecting the contents of a file. "). 

    If you are certain that a function should return Ok, you could use this direcly 
    without checking the contents first. 
*/
void* expect(Result* res, char* error_message); 

/*
    Frees the result. Does NOT free the contents inside, they are responsability of the calee. 
*/
void free_result(Result* res); 


















#endif