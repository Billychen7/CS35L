#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkInput();
void checkOutput();

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "ERROR: incorrect number of arguments, there should be 2.");
        exit(1);
    }
    
    const char* from = argv[1];
    const char* to = argv[2];
    
    if (strlen(from) != strlen(to))
    {
        fprintf(stderr, "ERROR: The input for to and from must be the same length");
        exit(1);
    }

    for (int i = 0; i < strlen(from); i++)
    {
        const char curr = from[i];
        
        for (int j = i + 1; j < strlen(from); j++)
        {
            if (curr == from[j])
            {
                fprintf(stderr, "ERROR: 'from' parameter can not have duplicate bytes.");
                exit(1);
            }
        }
    }
    
    int curr = getchar();
    checkInput();
    
    while(!feof(stdin))
    {
        char charToOutput = curr;
        for (int i = 0; i < strlen(from); i++)
        {
            if (curr == from[i])
            {
                charToOutput = to[i];
                break;
            }
        }
        putchar(charToOutput);
        checkOutput();
        curr = getchar();
        checkInput();
    }
}

void checkInput()
{
    if (ferror(stdin) != 0)
    {
        fprintf(stderr, "Input Error");
        exit(1);
    }
}

void checkOutput()
{
    if (ferror(stdout) != 0)
    {
        fprintf(stderr, "Output Error");
        exit(1);
    }
}
