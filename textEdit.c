/*
    Name: Abdallah Elsayed Ahmed
    Descritpion: Edit text (find and replace, delete, insert);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WordStruct.h"

void transTextToList(char text[], Word **first_word);
void showText(Word *first_word);
void freeText(Word *first_word);

void main()
{
    char text[1000];
    printf("Enter a Text: ");
    gets(text);

    Word *first_word;

    transTextToList(text, &first_word);
    showText(first_word);
    freeText(first_word);
}

/* Linked List */
// Initiate the linkedlist
void initText(Word **first_word)
{
    *first_word = (Word *) malloc(sizeof(Word));
    (*first_word)->nextWord = NULL;
}

// Add new word in the end of the text
Word *addWord(char word[])
{
    Word *new_word = (Word *) malloc(sizeof(Word));
    strcpy(new_word->word, word);
    new_word->nextWord = NULL;
    return new_word;
}

// Print the text
void showText(Word *first_word)
{
    for (Word *i = first_word; i != NULL;)
    {
        Word *temp = i->nextWord;
        printf("%s ", i->word);
        i = temp;
    }
}

// Free the linkedlist in the end of the program
void freeText(Word *first_word)
{
    for (Word *i = first_word; i != NULL;)
    {
        Word *temp = i->nextWord;
        free(i);
        i = temp;
    }
}

/* Text processing */
void transTextToList(char text[], Word **first_word)
{
    initText(first_word);
    
    Word *last_word = *first_word;

    // Split text in each space
    char *token = strtok(text, " ");
    strcpy((*first_word)->word, token);

    token = strtok(NULL, " ");
    while( token != NULL ) 
    {
        showText(*first_word);
        
        last_word->nextWord = addWord(token);
        last_word = last_word->nextWord;

        if ((*first_word)->nextWord == NULL)
            (*first_word)->nextWord = last_word;
        token = strtok(NULL, " ");
    }
}