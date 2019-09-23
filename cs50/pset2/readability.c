/*
Name: David Bruno
Date: 09/17/2019
File: readability.c
*/

#include <stdlib.h>
#include <stdio.h>
// #include <cs50.h> //cs50
#include <string.h>
#include <ctype.h>
#include <math.h>
/*
If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number. If the index number is less than 1, your program should output "Before Grade 1".
*/
#define maxLen 1000

double colemanLiau(int letters, int words, int sentences);

int main(void){
    //Your program must prompt the user for a string of text (using get_string).
    char* txt = malloc(maxLen);
    printf("Text: ");
    fgets(txt, maxLen, stdin);

    // string txt = get_string("Text: "); // CS50
    int i = 0, j = 0, letters = 0, words = 0, sentences = 0;

    /*Your program should count the number of letters, words, and sentences in the text. You may assume that any sequence of characters separated
    by spaces should count as a word, and that any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.*/
    for(i = 0,  j  = strlen(txt); i < j; i++){

        if(isalpha(txt[i])){ // counts only alphabetic
            letters++;
        }else if(isspace(txt[i])){ //spaces should count as a word
            words++;
        }else if(txt[i] ==  '.' || txt[i] ==  '!' || txt[i] ==  '?'){ //period, exclamation point, or quesetion mark is the end of a sentence
            sentences++;
        }

    }

    // printf("l:  %d w:  %d s:  %d\n", letters,words,sentences);
    double index = colemanLiau(letters, words, sentences);

    //If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number.
    if( index >= 16 )
    {
        printf("Grade 16+\n");
    }
    // If the index number is less than 1, your program should output "Before Grade 1".
    else if( index < 1 )
    {
        printf("Before Grade 1\n");
    }
    //Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
    else{
        printf("Grade %.0f\n",  round(colemanLiau(letters, words, sentences)));
    }

}

double colemanLiau(int letters, int words, int sentences){

    // Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    // Do we count letters or characters? in the
    double L = 0 , S = 0;

    L = ((float)letters/words) * 100;
    S = ((float)sentences/words) * 100;

    // index = 0.0588 * L - 0.296 * S - 15.8
    double index = (0.0588  * L - 0.296 * S -  15.8);

    return index;
}