#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int frobcmp(char const *a, char const *b);
int compare(const void *a, const void *b);
void checkForInputError();
void checkForOutputError();
void checkForMemoryError(void *ptr);
int main(void)
{
    char *currentWord;
    currentWord = (char *)malloc(sizeof(char));
    int currentLetter = 0;
    char **wordArray;
    wordArray = (char **)malloc(sizeof(char *));
    int currentWordPos = 0;
    char currentChar = getchar();
    checkForInputError();
    while (currentChar == ' ')
    {
        currentChar = getchar();
        checkForInputError();
    }
    char nextChar = getchar();
    checkForInputError();
    int notInc = 0;
    while (!feof(stdin))
    {
        notInc = 0;
        currentWord[currentLetter] = currentChar;
        char *wordWithMoreSpace = realloc(currentWord, (currentLetter + 2) * sizeof(char));
        checkForMemoryError(wordWithMoreSpace);
        currentWord = wordWithMoreSpace;
        if (currentChar == ' ')
        {
            wordArray[currentWordPos] = currentWord;
            char **wordsWithMoreSpace = realloc(wordArray, (currentWordPos + 2) * sizeof(char *));
            checkForMemoryError(wordsWithMoreSpace);
            wordArray = wordsWithMoreSpace;
            currentWordPos++;
            currentLetter = 0;
            notInc = 1;
            currentWord = NULL;
            currentWord = (char *)malloc(sizeof(char));

            if (nextChar == ' ')
            {
                while (nextChar == ' ')
                {
                    nextChar = getchar();
                    checkForInputError();
                }
            }
        }
        if (notInc == 0)
            currentLetter++;
        currentChar = nextChar;
        nextChar = getchar();
        checkForInputError();
    }
    if (currentLetter > 0 && currentWord[currentLetter - 1] != ' ')
    {
        currentWord[currentLetter] = currentChar;
        currentLetter++;

        if (currentChar != ' ')
        {
            currentWord[currentLetter] = ' ';
        }
        wordArray[currentWordPos] = currentWord;
        currentWordPos++;
    }
    int (*functionPtr)(const void *, const void *) = &compare;
    qsort(wordArray, currentWordPos, sizeof(char *), functionPtr);
    for (int i = 0; i < currentWordPos; i++)
    {
        size_t j = 0;
        while (1)
        {
            putchar(wordArray[i][j]);
            checkForOutputError();
            if (wordArray[i][j] == ' ')
                break;
            j++;
        }
    }
    int wordIndex;
    for (wordIndex = 0; wordIndex < currentWordPos; wordIndex++)
    {
        free(wordArray[wordIndex]);
    }

    free(wordArray);
    return 0;
}

int frobcmp(char const *a, char const *b)
{
    while (*a != ' ' && *b != ' ')
    {
        if (*a == ' ')
            return -1;
        if (*b == ' ')
            return 1;

        char frobA = *a ^ 42;
        char frobB = *b ^ 42;

        if (frobA < frobB)
            return -1;
        if (frobA > frobB)
            return 1;

        a++;
        b++;
    }
    return 0;
}

int compare(const void *a, const void *b)
{
    return frobcmp(*(const char **)a, *(const char **)b);
}

void checkForInputError()
{
    if (ferror(stdin) != 0)
    {
        fprintf(stderr, "Error reading input.");
        exit(1);
    }
}
void checkForOutputError()
{
    if (ferror(stdin) != 0)
    {
        fprintf(stderr, "Error writing output.");
        exit(1);
    }
}
void checkForMemoryError(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Error with memory allocation.");
        exit(1);
    }
}
