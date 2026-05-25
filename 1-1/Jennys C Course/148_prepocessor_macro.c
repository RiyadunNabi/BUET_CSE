#include <stdio.h>
#define A 10   //no semicolon here
               //whenever we will use A in our program,
               //A will be replaced with 10 before compiling in the preprocessor phase
               //preprocessor comes before compilation,
               //it's a step in compilation
               //It's called Macro
               
               //Yes, you can use #define directives within the main() function or any other function in C and C++. 
               //However, the scope of these macros will be limited to the block in which they are defined.
#define PI 3.1416 // PI is macro name, 3.1416 is character sequence
                  //character sequence can be any value, int float or even string

#define DCH "This is Riyad, from BOET"

//it can  be used like a function also, it will work faster than function

//multiplication
#define MULTIPLICATION(a,b) a*b           //((a)*(b)) best practice
#define MULTIPLICATION_best_practice(a,b) ((a)*(b))

//max num
#define MAX_1(a,b) (if(a>b) a; else b;) //always use bracket
/*using if and else statements, which are control flow constructs, not expressions. 
Macros in C and C++ should expand to expressions. //Here if else statement is returning something, which is not possible in macro
Also, there's a semicolon at the end of your macro, which might lead to unexpected behavior when you use the macro in your code.*/
#define MAX_IFELSE(a,b) if(a>b) \
                        a; \
                        else b;

#define MAX_TERNARY(a,b) (a>b ? a : b) //The corrected version uses the ternary conditional operator ? : 
                                       //to form an expression that evaluates to the maximum of a and b.
                                       // Additionally, it's enclosed in parentheses to ensure proper evaluation when used in more complex expressions.


//these will execute correctly because it's an expression of printing, not returning anything
#define MAX_IFELSE_print(a,b) if(a>b) \
                        printf("MAX_IFELSE_print(%d,%d) = %d\n",a,b,a); \
                        else \
                        printf("MAX_IFELSE_print(%d,%d) = %d\n",a,b,b);
//by ChatGPT                        
#define MAX_IFELSE_print_ChatGPT(a, b) do { \
                                if ((a) > (b)) \
                                    printf("MAX_IFELSE_print(%f,%f) = %f\n", (a), (b), (a)); \
                                else \
                                    printf("MAX_IFELSE_print(%f,%f) = %f\n", (a), (b), (b)); \
                                } while(0)      //by chatGPT       
                                                /*In this version, I've wrapped the entire block of code within a do { ... } while(0) loop. 
                                                This construct allows multiple statements to be treated as a single statement, 
                                                which is necessary for use in a macro. 
                                                The do { ... } while(0) loop ensures that the macro can be safely used in contexts where a single statement is expected, 
                                                such as after an if or else statement.*/          
int main()
{
    printf("\n");

    int x=A;  //A will be replaced with 10 before compiling
    printf("x = %d\n",x);

    printf("Area of a circle with radius %d is = %f\n\n", x, PI*x*x);

    printf("%s\n\n",DCH);

    printf("MULTIPLICATION(3,4) = %d\n",MULTIPLICATION(3,4));
    printf("MULTIPLICATION(5-2,1+3) = %d  // 5 -2*1 + 3\n",MULTIPLICATION(5-2,1+3));
    printf("MULTIPLICATION(5-2,1+3) = %d  // (5 -2)*(1 + 3)\n",MULTIPLICATION((5-2),(1+3)));
    printf("MULTIPLICATION_best_practice(5-2,1+3) = %d  // 5 -2*1 + 3\n\n",MULTIPLICATION_best_practice(5-2,1+3));

    //printf("MAX(3,4) = %d\n",MAX_1(3,4));              //will not execute
    //printf("MAX_IFELSE(3,4) = %d\n",MAX_IFELSE(3,4));  //will not execute also
    printf("MAX_TERNARY(3,4) = %d\n",MAX_TERNARY(3,4));

    MAX_IFELSE_print(9,5); //will work because it's an expression

    MAX_IFELSE_print_ChatGPT(3.5,4.0);  //will execute
    MAX_IFELSE_print_ChatGPT(3.5,4);  //won't execute correctly, will treat 4 as 0.000000, as b should be float
    
    //undefining macro
    #undef A   // if we use A after undefining, then it'll show us error;

    printf("\n");
    return 0;
}