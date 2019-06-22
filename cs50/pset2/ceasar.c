#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <cs50.h> cs50

char* encrpyt( char* str, int key){

    char* result = malloc( strlen(str) );
    for(int i = 0; i < strlen(str); ++i){
        if(islower(str[i])){
            result[i] = (char)(((int)str[i] - 'a' + key )%26 + 'a');
        }
        else if(isupper(str[i]))
            result[i] = (char)(((int)str[i] - 'A' + key )%26 + 'A');
        else
            result[i] = str[i];
        
    }

    return result;
}


int main ( int argc, char *argv[] ){
    if ( argc != 2 ) //checking that their are only two inputs
    {
        printf( "Usage: %s k \n", argv[0] );
        return 1;
    }
    
    char* txt = malloc(100);
    printf("plaintext: ");
    fgets(txt, 100, stdin);
    printf("cipertext: %s\n", encrpyt(txt, atoi(argv[1])));


    return 0;
}