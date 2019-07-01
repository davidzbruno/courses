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

#define MAXPASSLEN 5
// const char *POSSIBLE_CHARS= "\0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

const char *POSSIBLE_CHARS= "abcdefghijklmnopqrstuvwxyz\0";

// char* strslice(char* str, int index)


char* decrypt(char* str){
    char pass[MAXPASSLEN+1];
    pass[5] = '\0';
    int i = 0, j = 0, k = 0, l = 0, m = 0;
    int counter = 0;
    
    //brute force attempt for every possible combination
    for( i = 0; i < 26; ++i){
        pass[0] = POSSIBLE_CHARS[i];
        
        for( j = 0; j < 27; ++j){
            pass[1] = POSSIBLE_CHARS[j];

            if(pass[1] != '\0'){
                for( k = 0; k < 27; ++k){
                    pass[2] = POSSIBLE_CHARS[k];
                    
                    if(pass[2] != '\0'){
                        for( l = 0; l < 27; ++l){
                            pass[3] = POSSIBLE_CHARS[l];
                            if(pass[3] == '\0') continue;
                            for( m = 0; m < 27; ++m){
                                pass[4] = POSSIBLE_CHARS[m];
                                printf("%s\n",pass);

                                // counter++;
                                // if(counter == 1000) return NULL;
                                if(strcmp(pass,"mal") == 0) return NULL;
                                // //if the current passowrd combination matches the hashed password
                                // if( strcmp(crypt(pass, "50"), str) == 0){
                                //     return crypt(pass, "50");
                                // }
                            }
                        }
                    }
                }
            }
        }
    }

    return NULL;
}
/*

a0000
aa000
aaa00
aaaa0
aaaaa
b0000
ba000
 */

int main(int argc, char *argv[]){
    
    if(argc != 2){
        fprintf(stderr, "Usage: %s [hashed-password]\n", argv[0]);
        return 1;
    }

    printf("%s\n",crypt(argv[1],"50"));
    printf("%s\n", decrypt(argv[1]));

    return 0;
}