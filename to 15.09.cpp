#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MaxTokensCount = 100;

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
    char s[] = "asdasd     asdahsd         asduyiasd           dfghfgh          jhhjjh";
    char delim[] = " ";
    int tokensCount;
    char** tokens;
 
    tokens = (char**)malloc(MaxTokensCount * sizeof(char*));
    Split(s, delim, &tokens, &tokensCount);
    for (int i = 0; i < tokensCount; i++)
        printf("%s\n", tokens[i]);
    printf("String contains %d word(s).", tokensCount);

    free(tokens);
    return 0;
}


