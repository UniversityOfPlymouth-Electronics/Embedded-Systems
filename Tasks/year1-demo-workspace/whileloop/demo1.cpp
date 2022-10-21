#include <stdio.h>

int main()
{
    int counter = 10;

    while (counter >= 0)
    {
        printf("Counter is equal to %u\n", counter);
        counter--;
    }

    puts("While Loop Done!");

    for (int n = 10; n>=0; n--) 
    {
        printf("n is equal to %u\n", n);
        if ((n % 2) == 0) {
            continue;
        }
        puts("---------------------");
    }
    puts("For Loop Done!");


    // Nested Loop
    for (unsigned int row = 0; row <= 12 ; row++)
    {
        for (unsigned int col = 0; col <= 12; col++) 
        {
            printf("[%u,%u] ", row, col);
            if (row*col == 9) {
                printf("These are a pair of factors for 9!");
                break;
            }
        }
        puts("\n---------------------");
    }

    return 0;
}