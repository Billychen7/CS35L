#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int frobcmp(char const *a, char const *b);
int compare(const void *a, const void *b);
void InputError();
void OutputError();
void MemoryError();
void FoptionError();
int fcall = 0;

int main(int argc, char* argv[])
{
    int isRegularFile = 0;
    char *currentWord;
    int notInc = 0;
    if (argc == 2)
    {
        char* flagParameter = "-f";
        if (strcmp(argv[1], flagParameter) == 0)
        {
            fcall = 1;
        }
        else //invalid parameter
        {
            FoptionError();
        }
    }
    else if (argc > 2)
    {
        FoptionError();
    }
    struct stat fileInfo;
    int fstatStatus = fstat(0, &fileInfo);
    if (fstatStatus < 0)
    {
        FoptionError();
    }
    if (S_ISREG(fileInfo.st_mode))
    {
        isRegularFile = 1;
    }
    size_t fileSize = fileInfo.st_size;
    //use a pointer to a pointer as an array of strings
    char **wordArray;
    wordArray = (char **)malloc(sizeof(char *));
    int currentWordPos = 0;
    char* fileInput;
    if (isRegularFile == 1)
    {
        fileInput = (char *) malloc(fileSize * sizeof(char));
        ssize_t bytesRead = read(0, fileInput, fileSize + 1);
        if (bytesRead < 0)
        {
            InputError();
        }
        int charCount = 0;
        for (size_t i = 0; i < fileSize; i++)
        {
            //for the beginning of the word
            if (i == 0)
            {
                if (fileInput[0] != ' ')
                {
                    charCount++;
                }
            }
            //end with a space
            if (i == fileSize - 1 && fileInput[i] != ' ')
            {
                char* temp = realloc(fileInput, (fileSize + 2) * sizeof(char));
                if (temp == NULL)
                {
                    MemoryError();
                }
                fileInput = temp;
                fileSize++;
                fileInput[fileSize - 1] = ' ';
                break;
            }
            if (fileInput[i] == ' ')
            {
                while (fileInput[i] == ' ' && i < fileSize)
                {
                    i++;
                }
                if (i < fileSize)
                {
                    charCount++;
                }
            }
        }
        wordArray = (char **) malloc(charCount * sizeof(char*));
        int addedToArray = 0;
        for (size_t i = 0; i < fileSize; i++)
        {
            if (addedToArray == 0 && fileInput[i] != ' ')
            {
                wordArray[currentWordPos] = &fileInput[i];
                addedToArray = 1;
                currentWordPos++;
            }
            else if (addedToArray == 1 && fileInput[i] == ' ')
            {
                addedToArray = 0;
            }
        }
    }
    ssize_t currentBytesRead;
    ssize_t nextBytesRead;
    char * currentChar = (char *) malloc(sizeof(char));
    currentBytesRead = read(0, currentChar, 1);
    if (currentBytesRead < 0)
    {
        InputError();
    }
    if (currentBytesRead > 0)
    {
        while (*currentChar == ' ')
        {
            currentChar = NULL;
            currentChar = (char *) malloc(sizeof(char));
            currentBytesRead = read(0, currentChar, 1);
            
            if (currentBytesRead < 0)
            {
                InputError();
            }
        }
    }
    char * nextChar = (char *) malloc(sizeof(char));
    nextBytesRead = read(0, nextChar, 1);
    if (nextBytesRead < 0)
    {
        InputError();
    }
    currentWord = (char *)malloc(sizeof(char));
    int currentLetter = 0;
    while (!feof(stdin) && currentBytesRead >0)
    {
        notInc = 0;
        currentWord[currentLetter] = *currentChar;
        char *wordWithMoreSpace = realloc(currentWord, (currentLetter + 2) * sizeof(char));
        if (wordWithMoreSpace == NULL)
        {
            free(currentWord);
            MemoryError();
        }
        currentWord = wordWithMoreSpace;
        if (*currentChar == ' ')
        {
            wordArray[currentWordPos] = currentWord;
            char **wordsWithMoreSpace = realloc(wordArray, (currentWordPos + 2) * sizeof(char *));
            if (wordWithMoreSpace == NULL)
            {
                free(wordArray);
                MemoryError();
            }
            wordArray = wordsWithMoreSpace;
            currentWordPos++;
            currentLetter = 0;
            notInc = 1;
            currentWord = NULL;
            currentWord = (char *)malloc(sizeof(char));

            if (*nextChar == ' ')
            {
                while (*nextChar == ' ')
                {
                    nextChar = NULL;
                    nextChar = (char *) malloc(sizeof(char));
                    nextBytesRead = read(0, nextChar, 1);
                    
                    if (nextBytesRead < 0)
                    {
                        InputError();
                    }
                }
            }
        }
        if (notInc == 0)
            currentLetter++;
        *currentChar = *nextChar;
        nextChar = NULL;
        nextChar = (char *) malloc(sizeof(char));
        nextBytesRead = read(0, nextChar, 1);
        
        if (nextBytesRead < 0)
        {
            InputError();
        }
        
        //empty input
        if (nextBytesRead == 0)
        {
            break;
        }
    }
    if (currentLetter > 0 && currentWord[currentLetter - 1] != ' ')
    {
        currentWord[currentLetter] = *currentChar;
        currentLetter++;
        if (*currentChar != ' ')
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
        long wordLength = 0;
        while (1)
        {
            if (j == strlen(wordArray[i]))
            {
                break;
            }
            wordLength++;
            char charToOutput = wordArray[i][j];
            if (charToOutput == ' ')
            {
                break;
            }
            j++;
        }
        ssize_t bytesWritten = write(1, wordArray[i], wordLength);
        if (bytesWritten <= 0)
        {
            OutputError();
        }
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
        if (fcall == 1)
        {
            frobA = toupper((unsigned char) frobA);
            frobB = toupper((unsigned char) frobB);
        }
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

void InputError()
{
    char* errorMsg = "Input Error";
    write(2, errorMsg, strlen(errorMsg));
            exit(1);
}
void OutputError()
{
    char* errorMsg = "Output Error";
    write(2, errorMsg, strlen(errorMsg));
            exit(1);
}
void MemoryError()
{
    char* errorMsg = "Memory Error";
    write(2, errorMsg, strlen(errorMsg));
            exit(1);
}
void FoptionError()
{
    char* errorMsg = "-f Error";
    write(2, errorMsg, strlen(errorMsg));
            exit(1);
}
