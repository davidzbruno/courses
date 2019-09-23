#include <stdio.h>

int main(void)
{
    int i, j, k;

    do
    {
        //Ask user for the height to print
        printf("Height: ");
        scanf("%d", &k);
    }
    while (!(1 <= k && k <= 8));

    
    for (i = 0; i < k; i++)
    {
        //print spaces on the left
        for (j = 0; j < k - i - 1; ++j)
        {
            printf(" ");
        }
        for (j = 0; j < i + 1; ++j)
        {
            printf("#");
        }

        printf("  "); // thn middle dividr
        
        //The hashes on the right
        for (j = 0; j < i + 1; ++j)
        {
            printf("#");
        }
        printf("\n");

    }

    return 0;
}


