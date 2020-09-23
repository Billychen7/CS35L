#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void InputError();
void OutputError();

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        char* errorMsg = "ERROR: incorrect number of arguments, there should be 2.";
        write(2, errorMsg, strlen(errorMsg));
        exit(1);
    }
    
    const char* from = argv[1];
    const char* to = argv[2];
    
    if (strlen(from) != strlen(to))
    {
        char* errorMsg = "ERROR: The input for to and from must be the same length";
        write(2, errorMsg, strlen(errorMsg));
        exit(1);
    }

    for (int i = 0; i < strlen(from); i++)
    {
        const char curr = from[i];
        
        for (int j = i + 1; j < strlen(from); j++)
        {
            if (curr == from[j])
            {
                char* errorMsg = "ERROR: 'from' parameter can not have duplicate bytes.";
                write(2, errorMsg, strlen(errorMsg));
                exit(1);
            }
        }
    }

while(1)
    {
        char* currChar = (char *) malloc(sizeof(char));
        ssize_t bytesRead = read(0, currChar, 1);
        if (bytesRead < 0)
        {
            InputError();
        }
        if (bytesRead == 0) break;
        char outputChar = *currChar;
        for (int i = 0; i < strlen(from); i++)
        {
            if (outputChar == from[i])
            {
                outputChar = to[i];
                break;
            }
        }
        ssize_t bytesWritten = write(1, &outputChar, 1);
        if (bytesWritten <= 0)
        {
            OutputError();
        }
    }
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
