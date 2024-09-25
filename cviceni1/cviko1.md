1. Complete the following table by entering the number of bits and the numeric range for the selected data types defined in C.

   | **Data type** | **Number of bits** | **Range** | **Description** |
   | :-: | :-: | :-: | :-- |
   | `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
   | `int8_t`   | 8 | -128, -127, ..., 126, 127 | Signed 8-bit integer |
   | `uint16_t` | 16 | 0, 1, ..., 65 535 |  Unsigned 16-bit integer |
   | `int16_t`  | 16 | −32 768, ..., +32 767 | Signed 16-bit integer |
   | `float`    | 32 | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
   | `void`     | -- | -- | Depending on the context, it means *no type*, *no value* or *no parameters* |

<a name="part1"></a>



2. #include <stdio.h>    // Standard C input/output library
#include <stdint.h>   // Standard C integer library

uint8_t factorial(uint8_t value)

{
    uint32_t result = 1;
 
    
    while(value> 1 ) {
       result *= value;
       value--;
        
    }
    
    return result;
}

int main(void)        // Main function with no input parameters
{                     // Beginning of function body
    int8_t  a = 200;  // Definition of two local variables
    uint8_t b = 5;  // Unsigned 8-bit integer variable

    printf("Factorial b = %d", factorial(b));
    
    return 0;         // Main function returns 0 indicating successful execution
}                     // End of function body
