#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int is_alphabet(string text);
int repeats(string text);
string ciphertext(string plaintext, string key);

int main(int argc, string argv[])
{

    if (argc != 2)                                                             //checking if key is entered and argument is only 1
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    else if (strlen(argv[1]) != 26)                                            // checking if key has 26 chars
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else if (is_alphabet(argv[1]) == 0)                                        //made a function to check if  key only has alphabets
    {
        printf("Key must contain only alphabets.\n");
        return 1;
    }
    else if (repeats(argv[1]) == 0)                                            //another function to check if alphabet is repeating or not
    {
        printf("Key must contain each letter exactly once.\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext:  ");                           //if all conditions met than take input string from user

        printf("ciphertext: %s\n", ciphertext(plaintext, argv[1]));
    }

    return 0;
}

int is_alphabet(string text)
{

    for (int i = 0 ; text[i] != '\0' ; i++)                              //looping till null char and checking if it is an alphabet
    {

        if (isalpha(text[i]) == 0)
        {
            return 0;
        }
    }


    return 1;
}

int repeats(string text)
{

    for (int i = 0 ; text[i] != '\0' ; i++)
    {

        for (int j = i + 1 ; text[j] != '\0' ; j++)                  //loop till null char and check if any char is repeating
        {

            if (text[i] == text[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

string ciphertext(string text, string key)
{
    int asciicode;


    for (int i = 0 ; text[i] != '\0' ; i++)
    {
        if (isupper(text[i]) != 0)
        {
            asciicode = text[i];                                      //checking if uppercase or lowercase and coverting to vice versa
            text[i] = toupper(key[asciicode - 'A']);
        }
        else if (islower(text[i]) != 0)nd
        {
            asciicode = text[i];
            text[i] = tolower(key[asciicode - 'a']);
        }
    }

    return text;
}