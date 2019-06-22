#include <stdio.h>
// #include <cs50.h> cs50
#include <math.h>



#define COINS 4
int coins[COINS] = {1, 5, 10, 25}; 

int cashOut(int cash){
    int result = 0, i;
    for (i = COINS - 1; i >= 0; --i) { 
        while ((cash-coins[i]) >= 0) { 
            cash -= coins[i]; 
            result++;
        }
    }
    
    return result;
}


int main(void){
    float changeInput;
   
    // CS50 solution
    // do
    // {
    //     changeInput = get_float("Change owed: ");
    // }
    // while (changeInput < 0);

    do{
        printf("Change owed: ");
        scanf("%f",&changeInput);
    }while(changeInput < 0);

    changeInput = round(changeInput * 100);
    
    printf("%d\n",cashOut(changeInput));
}
