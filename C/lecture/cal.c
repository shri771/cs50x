#include<cs50.h>
#include<stdio.h>

int add(int a, int b);

int main(void)
{
    int x=get_int("x= ");
    int y=get_int("y= ");
    {
        printf("sum=%f\n", add( x, y));
    }
}

float add(int a, int b)
{

    return a/b;
}
