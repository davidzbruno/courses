#include <stdio.h>

int main(void)
{
    int i, j, k;

    do{
        printf("Height: ");
        scanf("%d", &k);
    }while( !(0 <= k && k < 24) );

    
    for(i = 0; i < k; i++)
    {
        for(j = 0; j < k-i+2; ++j)
        {
            printf(" ");
        }
        for(j = 0; j < i+2; ++j)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}