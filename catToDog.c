/*
    Name: Abdallah Elsayed Ahmed
    ID/Group: 7459 G2
    Descritpion: Find and replace every cat with dog
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int catToDog(char text[]);

void main()
{
    char text[500];
    printf("Enter the text: ");
    gets(text);

    int count;
    count = catToDog(text);
    printf("Number of words edited: %i \nThe text: %s", count, text);
}

// Search for a word in a text returns the address of first letter of the word
char *search_for_word(char text[], char word[])
{
    const unsigned char length_of_word = strlen(word);
    char *first_char_adress = strstr(text, word);
    
    while (first_char_adress != NULL)
    {
        if (!isalpha(*(first_char_adress - 1)) &&
           (!isalpha(*(first_char_adress + length_of_word)) || *(first_char_adress + length_of_word) == '\0'))
        {
            return first_char_adress;
        }
        
        first_char_adress = strstr(first_char_adress + 1, word);
    }
    
    return NULL;
}

// Chagne all the word cat into dog
int catToDog(char text[])
{
    char *nextCat = text;
    int counter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        nextCat = search_for_word(nextCat, "cat");
    
        if (nextCat == NULL)
            break;
        
        *nextCat += 1;
        *(nextCat + 1) += 14;
        *(nextCat + 2) -= 13;

        counter++;
    }

    return counter;  
}