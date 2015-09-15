#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* astring, char* delimiters, char*** tokens, int* tokensCount)
{
	char *p;
	int i = 0;
	p = strtok(astring, delimiters);
	*tokens = (char**)malloc(100*sizeof(char*));
	while (p != NULL)
	{
		(*tokens)[i] = p;
		i++;
		p = strtok(NULL, delimiters);
	}
	*tokensCount = i;
}

int main()
{
	char s[] = "asdasd asdahsd asduyiasd dfghfgh jhhjjh";
	char *p;
	char delim[] = " ";
	int *tcount, a, i;
	tcount = &a;
	char *** tok;
    char ** tokk;
    tok = &tokk;
    Split(s, delim, tok, tcount);
    for (i = 0; i < a; i++)
        printf("%s\n", tokk[i]);
	return 0;
}


