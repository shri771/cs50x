#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Prototype to get sum of alternative digit
int alternative_digit_sum(long credit_card);
int multiply_sum(int last_digit);
int num_digit(long credit_card);
int first_two(long credit_card, int n);

int main(void)
{
    long credit_card = get_long("credit num: ");
    int Luhns_Algorithm = alternative_digit_sum(credit_card);
    int last_digit = Luhns_Algorithm % 10;
    int n = num_digit(credit_card);
    int f = first_two(credit_card, n);

    if (last_digit == 0)
    {
        if (f == 37 || (f == 35 && n == 15))
        {
            printf("AMEX\n");
        }
        else if (f >= 51 && f <= 55 && n == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ( (f >= 40 && f <= 49 && n == 13) || (f >= 40 && f <= 49 && n == 16 ) )
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (last_digit != 0)
    {
        printf("INVALID\n");
    }
}

// First to add alternative number and add then remaing number (1)multiply by 2 (2)add the digits
int alternative_digit_sum(long credit_card)
{
    int sum = 0;
    bool alternative = false;

    while (credit_card > 0)
    {
        if (alternative == true)
        {
            int last_digit = credit_card % 10;
            int produt = multiply_sum(last_digit);
            sum = sum + produt;
        }
        else
        {
            int last_digit = credit_card % 10;
            sum = sum + last_digit;
        }
        alternative = !alternative;
        credit_card = credit_card / 10;
    }
    return sum;
}

// To multiply alternative number by 2 and adding the single digit("not the PRODUCT")
int multiply_sum(int last_digit)
{
    int multiply = last_digit * 2;
    int sum = 0;
    while (multiply > 0)
    {
        int last_digit_multiply = multiply % 10;
        sum = sum + last_digit_multiply;
        multiply = multiply / 10;
    }
    return sum;
}

// Sum of first two digit
int first_two(long credit_card, int n)
{
    int first_two_digit = credit_card / pow(10, n - 2);
    return first_two_digit;
}

// To count digit
int num_digit(long credit_card)
{
    int count = 0;
    while (credit_card > 0)
    {
        count += 1;
        credit_card /= 10;
    }
    return count;
}



























































































































