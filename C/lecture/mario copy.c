
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get size of grid between "1 to 8"
    int n;


    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);


    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j < n; j++)
     {
        printf(" ");

     }
        {
           for (int j = 1; j <= i; j++)
           {
            printf("#");
           }
        }

        printf("\n");
         }
}
