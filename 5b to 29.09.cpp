#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void Split(char* astring, char* delimiters, char*** tokens, int* tokensCount)
{
    char* word;
    int i = 0;
    word = strtok(astring, delimiters);

    while (word != NULL)
    {
        (*tokens)[i] = word;
        i++;
        word = strtok(NULL, delimiters);
    }
    *tokensCount = i;
}

int main()
{
    char input[100];
    fgets(input, 99, stdin);
    char delim[] = " \n";
    int tokensCount;
    char** tokens;
    tokens = (char**)malloc(6 * sizeof(char*));
    Split(input, delim, &tokens, &tokensCount);
    int time = atoi(tokens[4]);
    sleep(time);
    execlp(tokens[0], tokens[1], tokens[2], tokens[3]);
    free(tokens);
    return 0;
}
    
