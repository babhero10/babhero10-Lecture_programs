#include <stdio.h>

#define NUMBER_OF_OPTIONS 4

unsigned char selectControll()
{
    unsigned char selected = 0;
    while (selected > NUMBER_OF_OPTIONS || selected < 1)
    {
        printf("Enter your choose: ");
        scanf("%d", &selected);
    }
    
    switch (selected)
    {
        case 3:
            printf("Text Edit c program programmed by Abdallah Elsayed.\n");
            return 3;
            break;
        case 4:
            printf("Thank you!\n");
            return 0;
            break;
        
        default:
            return selected;
    }

}

void startMenu()
{
    printf("-- Welcome to Text Edit --\n");
    printf("1 - Open file.\n");
    printf("2 - Enter text.\n");
    printf("3 - About.\n");
    printf("4 - Exit.\n");
}