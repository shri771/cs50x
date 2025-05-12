// include
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// function declration
int Coleman_index(int no_letters, int no_words, int no_sentences);
void print_grade(int grade);

// manin function
int main(void)
{
    // promot user for text
    string text = get_string("Text: ");

    int no_letters = 0, no_words = 0, no_sentences = 0;

    // count number of letters and words
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            no_letters++;
        }
        else if (isblank(text[i]))
        {
            no_words++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            no_sentences++;
        }
    }
    no_words++;

    // variables
    int grade = Coleman_index(no_letters, no_words, no_sentences);

    // funcitons
    print_grade(grade);
}

// function to compute the value's in Coleman-Liau indes
int Coleman_index(int no_letters, int no_words, int no_sentences)
{
    float l = ((float) no_letters / (float) no_words) * 100;
    float s = ((float) no_sentences / (float) no_words) * 100;
    float index = 0.0588 * l - 0.296 * s - 15.8;
    return round(index);
}

// function to print grade
void print_grade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i", grade);
        printf("\n");
    }
}
