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
char *POSSIBLE_CHARS= "ABCDEFGHIJKLMNOOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char* strslice(char* str, int numBites){
    if(str == NULL || numBites < 0) return NULL;

    char* result = malloc(numBites);

    for(int i = 0; i < numBites; ++i){
        result[i] += str[i]; 
    }

    return result;
}


char* decrypt(char* str){
    char *pass = malloc(MAXPASSLEN+1), *temp;
    pass[0] = '\0';pass[1] = '\0';pass[2] = '\0';pass[3] = '\0';pass[4] = '\0';pass[5] = '\0';
    int i = 0, j = 0, k = 0, l = 0, m = 0;
    
    int counter = 0;
    //brute force attempt for every possible combination
    for( i = 0; i < 52; ++i){        
        for( j = 0; j < 52; ++j){
            for( k = 0; k < 52; ++k){
                for( l = 0; l < 52; ++l){
                    for( m = 0; m < 52; ++m){
                        pass[0] = POSSIBLE_CHARS[m];

                        temp = crypt(pass, strslice(str,2));
                        // printf("%s\n",pass);
                        // printf("%s\n",temp);
                        // printf("%s\n",str);
                        // printf("%d\n", strcmp(temp , str));
                        // printf("%d\n",strcmp(crypt(pass, "50"), str));
                        // counter++;
                        // if(counter == 10 ) return NULL;
                        
                        
                        //if the current password combination matches the hashed password
                        if( strcmp(temp , str) == 0){
                            return pass;
                        }

                        // if(strcmp(pass,"a") == 0){
                        //     printf("%s\n", temp);
                        //     // printf("%d\n",strcmp(, str));
                        //     printf("%s\n", str);
                        //     return pass;
                        //     // return crypt(pass, "50");
                        // }
                        
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

    // const char* ans = crypt("rofl", "50");
    // printf("%s\n",ans);

    printf("%s\n", decrypt(argv[1]));

    return 0;
}

//abc - 50PaJ4.RO0YUo
//a - 50OqznXGVcOJU

//rofl - 50fkUxYHbnXGw
//roftl - 50Q9152hEw3Wk