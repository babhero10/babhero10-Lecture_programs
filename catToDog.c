/*
    Name: Abdallah Elsayed Ahmed
    ID/Group: 7459 G2
    Descritpion: Find and replace every cat with dog
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int catToDog(char text[])
{
    char *nextCat = text;
    int counter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        nextCat = strstr(nextCat, "cat");
        
        if (nextCat == NULL)
            break;
        
        *nextCat += 1;
        *(nextCat + 1) += 14;
        *(nextCat + 2) -= 13;

        counter++;
    }

    return counter;  
}