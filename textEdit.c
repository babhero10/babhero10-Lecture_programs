/*
    Name: Abdallah Elsayed Ahmed
    Descritpion: Edit text (find and replace, delete, insert);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH_OF_WORD 46

typedef struct Word
{
    char word[LENGTH_OF_WORD];
    struct Word *nextWord;
} Word;

void startMenu(Word **first_word);
void editMenu(Word **first_word);
unsigned char initFile(char filename[], Word **first_word);

void main(int argc, char *argv[])
{
    Word *first_word;
        
    if (argc == 2)
    {
        if (!initFile(argv[1], &first_word))
            startMenu(&first_word);
        else
            editMenu(&first_word);
    }
    else
    {
        startMenu(&first_word);
    }
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

        // if ((*first_word)->nextWord == NULL)
        //     (*first_word)->nextWord = last_word;
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

// Returns number of words deleted
int deleteWord(Word **first_word, char *word)
{
    int counter = 0;
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
                break;
            }
            else 
            {
                prevWord->nextWord = i->nextWord;
                free(i);
                i = prevWord->nextWord;
            }
            counter++;
        }
        else 
        {
            prevWord = i;
            i = prevWord->nextWord;
        }
    }
    return counter;
}

// Returns number of words added (before(b) or after(a))
int addWordPos(Word **first_word, char toFind[], char word[], unsigned char pos)
{
    pos = tolower(pos);
    int counter = 0;
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
            counter++;
        }

        prevWord = i;
        i = prevWord->nextWord;
    }

    return counter;
}

/* Files */
unsigned char initFile(char filename[], Word **first_word)
{
    initText(first_word);
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("\nCan't find the file.\n\n");
        return 0;  
    }

    Word *last_word = *first_word;
    char word[LENGTH_OF_WORD];

    fscanf(file, " %1023s", word);

    strcpy((*first_word)->word, word);

    while (fscanf(file, " %1023s", word) == 1)
    {
        last_word->nextWord = addWord(word);
        last_word = last_word->nextWord;
    }
    fclose(file);

    return 1;
}

void saveFile(Word *first_word, char filename[])
{
    FILE *file;
    file = fopen(filename, "w");
    for (Word *i = first_word; i != NULL;)
    {
        Word *temp = i->nextWord;
        fputs(i->word, file);
        fputs(" ", file);
        i = temp;
    }
    fclose(file);
    printf("\nFile Saved!\n\n");
}

/* Menu */
void fileMenu(Word **first_word)
{
    char fileLocation[50];
    printf("-- Open file --\n");
    printf("Enter file location (e to exit): ");
    scanf("%s", fileLocation);
    
    if (strcmp(fileLocation, "e") == 0 || strcmp(fileLocation, "E") == 0)
    {
        startMenu(first_word);
        return;
    }

    if (!initFile(fileLocation, first_word))
    {
        startMenu(first_word);
        return;
    }

    editMenu(first_word);
}

void enterTextMenu(Word **first_word)
{
    char text[1000];
    printf("-- Enter text --\n");
    printf("Enter the text (e to exit): ");
    getchar();
    gets(text);
    
    if (strcmp(text, "e") == 0 || strcmp(text, "E") == 0)
    {
        startMenu(first_word);
        return;
    }
    transTextToList(text, first_word);
    editMenu(first_word);
}

void findAndReplaceMenu(Word **first_word)
{
    char find[LENGTH_OF_WORD], replace[LENGTH_OF_WORD];
    printf("Enter word to find and then the word to replace with: ");
    scanf("%s%s", find, replace);
    printf("Number of words infected: %d\n", findAndReplace(*first_word, find, replace));
    
}

void addWordMenu(Word **first_word)
{
    char find[LENGTH_OF_WORD], word[LENGTH_OF_WORD], pos;
    printf("Enter word to find and then the word you want to add: ");
    scanf("%s%s", find, word);
    getchar();
    do 
    {
        printf("Enter a to add the word After or b to add the word before: ");
        scanf("%c", &pos);
    } while (toupper(pos) != 'A' && toupper(pos) != 'B');
    
    printf("Number of words infected: %d\n", addWordPos(first_word, find, word, pos));
}

void deleteMenu(Word **first_word)
{
    char word[LENGTH_OF_WORD];
    printf("Enter the word to delete: ");
    scanf("%s", word);
    printf("Number of words infected: %d\n", deleteWord(first_word, word));
}

void saveFileMenu(Word **first_word)
{
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    strcat(filename, ".txt");
    saveFile(*first_word, filename);
}

void editMenu(Word **first_word)
{
    printf("-- Edit menu --\n");
    printf("1 - Find and replace\n");
    printf("2 - Add word.\n");
    printf("3 - Delete word.\n");
    printf("4 - Save changes.\n");
    printf("5 - Show text.\n");
    printf("6 - Back.\n");

    unsigned char selected = 0;
    while (selected > 6 || selected < 1)
    {
        printf("Select: ");
        scanf("%d", &selected);
    }
    

    switch (selected)
    {
        case 1:
            findAndReplaceMenu(first_word);
            editMenu(first_word);
            break;
        
        case 2:
            addWordMenu(first_word);
            editMenu(first_word);
            break;
        
        case 3:
            deleteMenu(first_word);
            editMenu(first_word);
            break;
        
        case 4:
            saveFileMenu(first_word);
            editMenu(first_word);
            break;

        case 5:
            getchar();
            printf("\n");
            showText(*first_word);
            printf("\n");
            editMenu(first_word);
            break;
        case 6:
            startMenu(first_word);
            break;
        
        default:
            break;
    }
}

void selectControl(Word **first_word)
{
    unsigned char selected = 0;
    while (selected > 4 || selected < 1)
    {
        printf("Enter your choose: ");
        scanf("%d", &selected);
    }
    
    switch (selected)
    {
        case 1:
            fileMenu(first_word);
            break;
        case 2:
            enterTextMenu(first_word);
            break;
        case 3:
            printf("\nText Edit c program programmed by Abdallah Elsayed.\n\n");
            startMenu(first_word);
            break;
        case 4:
            printf("\nThank you!\n\n");
            freeText(first_word);
            exit(0);
            break;
    }

}

void startMenu(Word **first_word)
{
    printf("-- Welcome to Text Edit --\n");
    printf("1 - Open file.\n");
    printf("2 - Enter text.\n");
    printf("3 - About.\n");
    printf("4 - Exit.\n");

    selectControl(first_word);
}

