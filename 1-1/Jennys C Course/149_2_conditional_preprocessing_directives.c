/************conditional preprocessing directives,PreProcessor Comands***************/
/*  
#if #elif #else  
#ifdef #else #ifndef (if not defined)

The #if, #elif, and #else directives are used to conditionally include or exclude blocks of code based on the value of VERSION.
The #ifdef directive checks whether DEBUG is defined.
The #ifndef directive checks whether RELEASE is not defined
.*/
/***********************************************************************************************************************************************/
#include <stdio.h>
int main()
{
/*******************************************************************************************************************************/    
#define VERSION_1 2 // Yes, you can use #define directives within the main() function or any other function in C and C++.
                    // However, the scope of these macros will be limited to the block in which they are defined.
#define RELEASE_1 3

#if VERSION_1 == 1
    printf("Using version_1 1\n");
#elif VERSION_1 == 2
    printf("Using version_1 2\n");
#else
    printf("Unknown version_1\n");
#endif

#ifdef DEBUG_1
    printf("Debug_1 mode is enabled\n");
#else
    printf("Debug_1 mode is disabled\n");
#endif

#ifndef RELEASE_1
    printf("This is not a release_1 build\n");
#endif

    printf("\n\n");
/***********************************************************************************************************************************************/
#define VERSION_2 1
#define DEBUG_2 3

#if VERSION_2 == 1
    printf("Using version_2 1\n");
#elif VERSION_2 == 2
    printf("Using version_2 2\n");
#else
    printf("Unknown version_2\n");
#endif

#ifdef DEBUG_2
    printf("Debug_2 mode is enabled\n");
#else
    printf("Debug_2 mode is disabled\n");
#endif

#ifndef RELEASE_2
    printf("This is not a release_2 build\n");
#endif
    /*************************************************************************************************************************/
    /*
    instead of writing two different VERSION, we can change the value of these VERSION, or define them while compiling by this:
    gcc -DVERSION=1 my_program.c -o my_program

    -DVERSION=1 is a compiler flag used in C (and C++) to define a macro named VERSION with a value of 1.

    When you compile a C program, you can pass various options to the compiler to control how the code is processed. One common set of options is used to define preprocessor macros. The -D option followed by a macro definition is used to define a macro with a specific value.

    So, when you compile a program with -DVERSION=1, it's equivalent to having a #define VERSION 1 line at the beginning of your source code. The compiler treats occurrences of VERSION in the code as if they were replaced by 1 before compiling.

    For example, if you have #if VERSION == 1, with -DVERSION=1, it's as if you had #if 1 == 1 after preprocessing, which is a true condition.


    You can use the -D option with the compiler to define macros, which can replace the need for #define directives in your source code.

    For instance, instead of putting #define VERSION 1 at the beginning of your source file, you can use -DVERSION=1 when invoking the compiler:
    gcc -DVERSION=1 my_program.c -o my_program
    This command tells the compiler to define the macro VERSION with the value 1 during the compilation of my_program.c.

    Using -D with the compiler can be convenient, especially when you want to define macros dynamically based on build configurations or external factors, such as through build scripts or makefiles. It allows you to control macro definitions without modifying the source code directly.
    */
    /**************************************************************************************************************************/

    return 0;
}