#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <cs50.h> cs50

#define maxLen 100
char *encrpyt(char *str, int key);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s k \n", argv[0]);
        return 1;
    }

    char *txt = malloc(maxLen);
    // Prompt user for plaintext
    printf("plaintext: ");
    fgets(txt, maxLen, stdin);

    // Convert that command-line argument from a string to an int
    printf("ciphertext: %s\n", encrpyt(txt, atoi(argv[1])));

    return 0;
}

char *encrpyt(char *str, int key)
{
    char *result = malloc(strlen(str));
    for (int i = 0; i < strlen(str); ++i)
    {
        // If it is a lowercase letter, rotate it, preserving case, then print out the rotated character
        if (islower(str[i]))
        {
            result[i] = (char)(((int)str[i] - 'a' + key) % 26 + 'a');
        }
        // If it is an uppercase letter, rotate it, preserving case, then print out the rotated character
        else if (isupper(str[i]))
        {
            result[i] = (char)(((int)str[i] - 'A' + key) % 26 + 'A');
        }
        // If it is neither, print out the character as is
        else
        {
            result[i] = str[i];
        }
    }
    return result;

}
