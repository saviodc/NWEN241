/**
 * Skeleton file for server.c
 * 
 * You are free to modify this file to implement the server specifications
 * as detailed in Assignment 3 handout.
 * 
 * As a matter of good programming habit, you should break up your imple-
 * mentation into functions. All these functions should be contained in this
 * file as you are only allowed to submit this file.
 */ 

#include <stdio.h>
#include <ctype.h>
// Include necessary header files

/**
 * The main function should be able to accept a command-line argument
 * argv[0]: program name
 * argv[1]: port number
 * 
 * Read the assignment handout for more details about the server program
 * design specifications.
 */ 
int main(int argc, char *argv[])
{


    if(!isdigit(argv[1]) || argc != 2){
        printf("Error");
        return -1;
    }


    return 0;
}

