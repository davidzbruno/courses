/*
    Design and implement a program, crack, that cracks passwords.

    Otherwise, your program must proceed to crack the given password, ideally as quickly as possible, ultimately printing the password in the clear followed by \n, nothing more, nothing less, with main returning 0.

    Assume that each password has been hashed with C’s DES-based (not MD5-based) crypt function.

    Assume that each password is no longer than five (5) characters. Gasp!

    Assume that each password is composed entirely of alphabetical characters (uppercase and/or lowercase).

 */

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XOPEN_SOURCE
#include <unistd.h>

char *POSSIBLE_CHARS= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// char* decrypt(char* str){
//     char *pass = {'','\0','','',''};

//     for(){
//         if( strcmp(crpyt(pass), str) == 0){
//             return crpyt(pass);
//         }
//     }
// }


int main(int argc, char *argv[]){
    
    if(argc != 2){
        fprintf(stderr, "Usage: %s [hashed-password]", argv[0]);
        return 1;
    }

    printf("%s\n",crypt(argv[1],"50"));
    // printf("%s", decrypt(argv[1]));

    return 0;
}