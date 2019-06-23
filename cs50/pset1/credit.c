#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool isNumeric(char* str){
    if( str == NULL || strlen(str) <= 0) return false;

    int i = 0;
    while( i < strlen(str)){
        if( !isdigit(str[i]) ) return false;
        ++i;
    }

    return true;
}

int digitSum(int n){
    int sum = 0;
    while(n > 0){
        sum += n%10;
        n/=10;
    }
    return sum;
}

/*
Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
Add the sum to the sum of the digits that weren’t multiplied by 2.
If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
 */
bool isSyntax(char* str){
    if( str == NULL || strlen(str) <= 0) return false;

    int i, sum=0;
    for(i = strlen(str)-1; i >= 0; --i){
        //multiply every other number by two
        if((i%2==0 && strlen(str)%2==0) || ((i%2==1 && strlen(str)%2==1))) { //not 100% sure i need to check the lengths
            sum += digitSum((int)(str[i]-'0')*2);
        }
        //add the sum of the digits that weren't multiplied by 2
        else{
            sum += digitSum((int)(str[i]-'0'));
        }
    }
    return sum%10 == 0 ? true : false;
}


/*
 American Express numbers all start with 34 or 37;
 MasterCard numbers start with 51, 52, 53, 54, or 55;
 Visa numbers all start with 4.
*/

char* cardCheck(char* str){
    
    if(!isSyntax(str)){
        return "INVALID";
    }
    // American Express uses 15-digit numbers.
    if( (strlen(str) == 15) && (strncmp(str, "34", 2)==0 || strncmp(str, "37", 2)==0)){
        return "AMEX";
    }
    //MasterCard uses 16-digit numbers.
    else if((strlen(str) == 16) && (strncmp(str, "51", 2)==0 || strncmp(str, "52", 2)==0 ||strncmp(str, "53", 2)==0 || strncmp(str, "54", 2)==0 || strncmp(str, "55", 2)==0)){
        return "MASTERCARD";
    }
    //Visa uses 13- and 16-digit numbers
    else if((strlen(str) == 13 || strlen(str) == 16)&& strncmp(str, "4", 1)==0){
        return "VISA";
    }
    else{
        return "INVALID";
    }
}

int main (void){

    char* input = malloc(sizeof(char*));
    do{
        printf("Number: ");
        scanf("%s",input);

    } while(!isNumeric(input));

    printf("%s\n", cardCheck(input));
    return 0;
}