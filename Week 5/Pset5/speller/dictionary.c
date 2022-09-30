// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *point = table[index];       //accessing linked list at index in hash table
    while (point != NULL)
    {
        if(strcasecmp(point -> word, word) == 0)     //comparing two strings,, transversing the linked list
    {
        return true;
    }
    point = point->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
   unsigned int value = 0;
    unsigned int string_length= strlen(word);           //crating an int with value 0 and other int in which storing the length of string
    for (int i = 0; i < string_length; i++)
    {
        value += toupper(word[i]);
    }
    value = value % N;        // taking mod to make sure value will not be greater than N
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
  int size_count = 0;
bool load(const char *dictionary)
{
    // TODO
    //open dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }
    // read string from file
    char Word[LENGTH + 1];
    while (fscanf(dictionary_file, "%s", Word) != EOF)
    {
        // create new node for words
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
         //copying word into new new_node
        strcpy(new_node->word, Word);
        new_node->next = NULL;

        // obtaining hash values using hash function
        int index = hash(Word);
        if (table[index] == NULL)      //hashtable from line 20
        {
             // inserting node into hash table at location
            table[index] = new_node;
        }
        else
        {
            new_node -> next = table[index];
            table[index] = new_node;
        }
         size_count++;           //from size function
    }
    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return size_count;
}

// Unloads dictionary from memory, returning true if successful, else false

//freeing up the memory allocated in any process
bool unload(void)
{
    // TODO
    for (int i=0; i< N; i++)    //iterating through the linked list
    while (table[i] != NULL)
    {
        //creating temp node which is pointing to next node
        node *temp = table[i]->next;
        free(table[i]);
        table[i] = temp;
    }
    return true;
    }
