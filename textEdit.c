/*
    Name: Abdallah Elsayed Ahmed
    Descritpion: Edit text (find and replace, delete, insert);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "WordStruct.h"

void transTextToList(char text[], Word **first_word);
int findAndReplace(Word *first_word, char find[], char replace[]);
void showText(Word *first_word);
void freeText(Word *first_word);
void deleteWord(Word **first_word, char *word);
int addWordPos(Word **first_word, char toFind[], char word[], unsigned char pos);
// void initFile(FILE **file, char filename[], Word **first_word);

void main()
{
    char text[1000];
    printf("Enter a Text: ");
    gets(text);

    Word *first_word;
    // FILE *file;
    // initFile(&file, "text.txt", &first_word);
    // showText(first_word);
    transTextToList(text, &first_word);
    showText(first_word);
    addWordPos(&first_word, "hi", "bye", 'a');
    showText(first_word);
    addWordPos(&first_word, "bye2", "hi2", 'b');
    showText(first_word);
    findAndReplace(first_word, "hi", "bye");
    showText(first_word);
    deleteWord(&first_word, "bye");
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
    printf("\n");
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
        last_word->nextWord = addWord(token);
        last_word = last_word->nextWord;

        if ((*first_word)->nextWord == NULL)
            (*first_word)->nextWord = last_word;
        token = strtok(NULL, " ");
    }
}

/* Text Editing */
// Find and replace return number of edited words
int findAndReplace(Word *first_word, char find[], char replace[])
{
    int counter = 0;
    for (Word *i = first_word; i != NULL; i = i->nextWord)
    {
        if (strcmp(i->word, find) == 0)
        {
            strcpy(i->word, replace);
            counter++;
        }
    }

    return counter;
}

// Delete word
void deleteWord(Word **first_word, char *word)
{
    Word *prevWord = *first_word;
    for (Word *i = *first_word; i != NULL; )
    {
        if (strcmp(i->word, word) == 0)
        {
            if (i == *first_word)
            {
                Word *temp = (*first_word)->nextWord;
                free(*first_word);
                (*first_word) = temp;
                i = temp;
            }
            else if (i->nextWord == NULL)
            {
                free(i);
                prevWord->nextWord = NULL;
                return;
            }
            else 
            {
                prevWord->nextWord = i->nextWord;
                free(i);
                i = prevWord->nextWord;
            }
        }
        else 
        {
            prevWord = i;
            i = prevWord->nextWord;
        }
    }
}

// Returns number of words added (before(b) or after(a))
int addWordPos(Word **first_word, char toFind[], char word[], unsigned char pos)
{
    pos = tolower(pos);
    Word *prevWord = *first_word;
    for (Word *i = *first_word; i != NULL; )
    {
        if (strcmp(i->word, toFind) == 0)
        {
            if (pos == 'a')
            {
                Word *temp = i->nextWord;
                i->nextWord = addWord(word);
                i->nextWord->nextWord = temp;
                i = i->nextWord;
            }     
            else if (pos == 'b')
            {
                if (i == *first_word)
                {
                    Word *temp = *first_word;
                    *first_word = addWord(word);
                    (*first_word)->nextWord = temp;
                }
                else
                {
                    Word *temp = prevWord->nextWord;
                    prevWord->nextWord = addWord(word);
                    prevWord->nextWord->nextWord = temp;
                }
            }
        }

        prevWord = i;
        i = prevWord->nextWord;
    }
}

/* Files */
// void initFile(FILE **file, char filename[], Word **first_word)
// {
//     *file = fopen(filename, "r");

//     if (*file == NULL)
//     {
//         *file = fopen(filename, "w");
//         initText(first_word);
//         return;  
//     }

//     Word *last_word = *first_word;

//     fscanf(*file, " %1023s", (*first_word)->word);
//     char word[LENGTH_OF_WORD];
//     while (fscanf(*file, " %1023s", word) == 1)
//     {
//         last_word->nextWord = addWord(word);
//         last_word = last_word->nextWord;

//         if ((*first_word)->nextWord == NULL)
//             (*first_word)->nextWord = last_word;
//     }


// }