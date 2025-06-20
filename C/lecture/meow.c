#include<cs50.h>
#include<stdio.h>

int main(void)


{
    //Promt user for frequncey of meow between "1 and 7"
    int n;
    do
    {
      n =get_int("meow times?\n");
    }
     while ( n<1 || n>1000);

    //To make loop
    for (int i = 0; i < n ; i++)
    {
      printf("meow\n");

    }


}

