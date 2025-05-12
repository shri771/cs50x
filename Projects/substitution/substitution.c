// includes
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function declaration
const int key_len = 26;
string convert_to_ciphertext(char key[], string plaintext);

// main function
int main(int argc, string argv[])
{
    // check if user has enter key,key lenght is 26 and there only alpha
    if (argc != 2)
    {
        printf("Enter Key\n");
        return 1;
    }
    // varialbe
    else if (key_len != 26)
    {
        printf("Enter Valid key\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < key_len; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Enter Valid key\n");
                return 1;
            }
        }
    }

    // check for repeated alpha
    char key[26];
    int counter = 0;
     // populate the key array and convert all the key to capital
    for (int i = 0; i < key_len; i++)
    {
        key[i] = toupper(argv[1][i]);

    }

      // check for repeated alpha
    for (int i = 0; i < key_len; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (key[j] == argv[1][i])
            {
                counter++;
                if (counter == 2)
                {
                    printf("Enter Valid key\n");
                    return 1;
                }
            }
        }
        counter = 0;
    }

    // ask user for plaintext
    string plaintext = get_string("plaintext: ");

    //  print ciphertext
    printf("%s\n", convert_to_ciphertext(key, plaintext));
    return 0;


}

// function to convert to ciphertext
string convert_to_ciphertext(char key[], string plaintext)
{
    int postion = 0;
    string ciphertext =  malloc(strlen(plaintext) + 1);
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            postion = toupper(plaintext[i]) - 'A';
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(key[postion]);
            }
            else
            {
                ciphertext[i] = tolower(key[postion]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;

}
