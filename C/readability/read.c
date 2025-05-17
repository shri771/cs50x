#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
float count_words(string text, int no_of_sentence);
int count_sentence(string text);
float average_letters(int no_of_letters, float no_of_words);
float average_sentence(int no_of_sentence, float no_of_words);
float coleman_index(float L, float S);


int main(void)
{
    // Promt user for text
    string text = get_string("Text: ");
    int no_of_letters = count_letters(text);
    int no_of_sentence = count_sentence(text);
    float no_of_words = count_words(text, no_of_sentence);
    float L = average_letters(no_of_letters, no_of_words);
    float S = average_sentence(no_of_sentence, no_of_words);
    float index = coleman_index(L, S);
    printf("%f,%i", no_of_words, no_of_sentence);
   //printf("%f", index);
}

// To assign and print Grade
//char grade_assign(double index)

   // if (index)


// Coleman-Liau index
float coleman_index(float L, float S)
{
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}

// No of letters
int count_letters(string text)
{
    int count = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// To count words
float count_words(string text, int no_of_sentence)
{

    int count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
       if (i > 0 && isalpha(text[i-1]) && !isalpha(text[i]) && (isspace(text[i+1]) || isalpha(text[i+1]) || ispunct(text[i+1])))
       {
         count++;
       }
    }

    return count;
}

// To count sentence
int count_sentence(string text)
{

    int count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
       if (i > 0 && isalpha(text[i-1]) && ispunct(text[i]) && isspace(text[i+1]) && isupper(text[i+2]))
       {
         count++;
       }
    }
    count++;
    return count;
}

 // Average number of letters per 100 words (=L)
float average_letters(int no_of_letters, float no_of_words)
{
    float L = 100*(no_of_letters / no_of_words);
    return L;
}

// Average number of sentence per 100 words (=S)
float average_sentence(int no_of_sentence, float no_of_words)
{
    float S = 100*(no_of_sentence / no_of_words);
    return S;
}

