#include <stdio.h>

int main(void)
{
    // create variables
    int i, j, k;

    do
    {
        // asks user for height for input
        printf("Height: ");
        scanf("%d", &k);
    }
    while (!(0 < k && k <= 8));

    
    for (i = 0; i < k; i++)
    {
        // prints spaces
        for (j = 0; j < k - i - 1; ++j)
        {
            printf(" ");
        }
        
        //prints hashes
        for (j = 0; j < i + 1; ++j)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}

