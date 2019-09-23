/*
Name: David Bruno
Date: 09/20/2019
File: substitution.c
Design and implement a program, substitution, that encrypts messages using a substitution cipher.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// #include <cs50.h> // cs50

const int keylen = 26;
const int maxlen = 100;
const int specialCheck = 2019;


char *isValid(char *str)
{
    if (str == NULL|| strlen(str) != keylen)
    {
        return false;
    }

    //checks for duplicate letters
    int alpha[keylen];
    str = tolower(str);

    for (int i = 0;  i < keylen;  i++)
    {
        if (!isalpha(str[i]))
        {
            return false;
        }
        
        if (islower(str[i]))
        {
            if (alpha[str[i] - 'a'] ==  specialCheck)
            {
                return false;
            }
            else{
                alpha[str[i] - 'a'] = specialCheck;
            }
        }
    }
    return true;
}

  // Your program must output ciphertext:
    // (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical
    // character in the plaintext substituted for the corresponding character in the ciphertext;
    // non-alphabetical characters should be outputted unchanged.
char *encrpyt(char *str, char *key)
{
    char *result = malloc(strlen(str));
    for (int i = 0; i < strlen(str); ++i)
    {
        // If it is a lowercase letter, substitute it, preserving case, then print out the rotated character
        if (islower(str[i]))
        {
            result[i] = tolower(key[((int)str[i] - 'a')]);
        }
        
        // If it is an uppercase letter, substitute it, preserving case, then print out the rotated character
        else if (isupper(str[i]))
        {
            result[i] = toupper(key[((int)str[i] - 'A')]);
        }

        // If it is neither, print out the character as is
        else
        {
            result[i] = str[i];
        }
    }
    return result;
}

int main(int argc, char *argv[])
{    
    //Your program must accept a single command-line argument, the key to use for the substitution.
    if (argc != 2)
    {
        // If your program is executed without
        // any command-line arguments or with more than one command-line argument, your program should 
        // print an error message of your choice (with printf) and return from main a value of 1 (which
        // tends to signify an error) immediately.
        fprintf(stderr,"Usage: %s key\n",argv[0]);
        return 1;
    }
    char *key = argv[1];

    if (!isValid(argv[1]))
    {
        // If the key is invalid (as by not containing 26 characters,
        // containing any character that is not an alphabetic character, or not containing each letter
        // exactly once), your program should print an error message of your choice (with printf) and return
        // from main a value of 1 immediately.
        fprintf(stderr,"Key must contain %d characters.\n",keylen);
        return 1;
    }

    //The key itself should be case-insensitive, so whether any character in the key is uppercase or
    //lowercase should not affect the behavior of your program.
    printf("%s\n", isValid(argv[1]));
    printf("%s\n",  argv[1]);

    // Your program must output plaintext: (without a newline) and
    // then prompt the user for a string of plaintext (using get_string).
    char *txt = malloc(maxlen);
    // Prompt user for plaintext
    printf("plaintext: ");
    fgets(txt, maxlen, stdin);

    // string txt =  get_string("plaintext: "); //CS50

    printf("ciphertext: %s\n", encrpyt(txt, argv[1]));

    // Your program should then exit by returning 0 from main.
    return 0;

}