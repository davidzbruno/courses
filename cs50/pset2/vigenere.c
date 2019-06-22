#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define maxlen 100
#define a 97
#define A 65
#define maxletters 26

// returns 0 (false) if the str contains any non-alphabetical character(s)
// returns 1 (true) if the str only contains alphabetical characters
bool isAlpha( char* str ){
    for(int i = 0; i < strlen(str); ++i){
        if(!isalpha(str[i])) return false;
    }
    return true;
}

char* encrpyt( char* str, char* key){

    char* result = malloc(strlen(str));
    int i= 0, j=0;
    while(i < strlen(str)){
        // printf("plain: %c key: %c ",str[i],key[j]);

        if(islower(str[i])){
            result[i] = (char)(((int)str[i] + (tolower(key[j])-a) - a)%maxletters + a);
            j++;
        }
        else if(isupper(str[i])){
            result[i] = (char)(((int)str[i] - A + (toupper(key[j])-A) )%maxletters + A);
            j++;
        }
        else
            result[i] = str[i];


        if(j >= strlen(key)) j = 0;
        // printf("ciph: %c\n", result[i]);
        i++;
    }

    return result;
}

int main(int argc, char *argv[] ){

    if(argc != 2 || !isAlpha(argv[1])){
        printf("Usage: %s k",argv[0]);
        return 1;
    }

    char* txt = malloc(maxlen);
    printf("plaintext: ");
    fgets(txt, maxlen, stdin);
    printf("ciphertext: %s\n", encrpyt(txt, argv[1]));

    return 0;
}