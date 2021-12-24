#define LENGTH_OF_WORD 46

typedef struct Word
{
    char word[LENGTH_OF_WORD];
    struct Word *nextWord;
} Word;