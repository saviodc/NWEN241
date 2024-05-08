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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// Include necessary header files

/**
 * The main function should be able to accept a command-line argument
 * argv[0]: program name
 * argv[1]: port number
 * 
 * Read the assignment handout for more details about the server program
 * design specifications.
 */ 

int initiate(int);
int set_listen(int);
int main(int argc, char *argv[])
{


    if(argc != 2){
        printf("Error init %d",argc);
        return -1;
    }

    int port = atoi(argv[1]);
    if(port < 1024){
        printf("Invalid port - %d",port);
        return -1;
    }
    if(!initiate(port))return -1;

    return 0;
}

int initiate(int port){
    printf("Rwached port - %d\n", port);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        printf("Error - initiate at port %d", port);
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(fd, (struct sockaddr *)&addr, sizeof(addr))< 0){
        printf("Binding error");
        return 0;
    }

    printf("Successful bind @ %d\n\n", port);
    return fd;
}

