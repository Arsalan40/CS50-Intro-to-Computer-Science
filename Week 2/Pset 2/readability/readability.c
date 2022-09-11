#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int index_formula(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    int letter = count_letters(text);
    printf("%i letters\n", letter);

    int word = count_words(text);
    printf("%i words\n", word);

    int sentence = count_sentences(text);
    printf("%i sentences\n", sentence);


    int index = index_formula(letter, word, sentence);

    //   printf("Grade %i\n", index);
    
    if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return ++words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '?' || text[i] == '.' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}

int index_formula(int letters, int words, int sentences)
{

    float L = (letters / (float)words) * 100;
    float S = (sentences / (float)words) * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}
