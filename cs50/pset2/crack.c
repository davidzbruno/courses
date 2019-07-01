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

const char *POSSIBLE_CHARS= "abcdefghijklmnopqrstuvwxyz";

char* strslice(char* str, int numBites){
    if(str == NULL || numBites < 0) return NULL;

    char* result = malloc(numBites);

    for(int i = 0; i < numBites; ++i){
        result[i] += str[i]; 
    }

    return result;
}


const char* decrypt(const char* str){
    char *pass = malloc(MAXPASSLEN+1);
    pass[0] = '\0';pass[1] = '\0';pass[2] = '\0';pass[3] = '\0';pass[4] = '\0';pass[5] = '\0';
    int i = 0, j = 0, k = 0, l = 0, m = 0;
        
    int counter = 0;
    //brute force attempt for every possible combination
    for( i = 0; i < 26; ++i){        
        for( j = 0; j < 26; ++j){
            for( k = 0; k < 26; ++k){
                for( l = 0; l < 26; ++l){
                    for( m = 0; m < 26; ++m){
                        pass[0] = POSSIBLE_CHARS[m];

                        printf("%s\n",pass);
                        // printf("%s\n",crypt(pass, "50"));
                        printf("%s\n",str);
                        // printf("%d\n",strcmp(crypt(pass, "50"), str));

                        if(counter == 10 ) return NULL;
                        // //if the current password combination matches the hashed password
                        // if( strcmp(crypt(pass, "50") , str) == 0){
                        //     return pass;
                        // }

                        if(strcmp(pass,"jad") == 0){
                            printf("%s\n", str);
                            printf("%d\n",strcmp(crypt(pass, "50"), str));
                            printf("%s\n", str);
                            return pass;
                            // return crypt(pass, "50");
                        }
                        
                    }
                    pass[1] = POSSIBLE_CHARS[l];
                }
                pass[2] = POSSIBLE_CHARS[k];
            }
            pass[3] = POSSIBLE_CHARS[j];
        }
        pass[4] = POSSIBLE_CHARS[i];
    }

    return NULL;
}

int main(int argc, char *argv[]){
    
    if(argc != 2){
        fprintf(stderr, "Usage: %s [hashed-password]\n", argv[0]);
        return 1;
    }

    // printf("%s\n", decrypt(ans));

    return 0;
}