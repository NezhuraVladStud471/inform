#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* astring, char* delimiters, char*** tokens, int* tokensCount)
{
	char *p;
	int i = 0;
	p = strtok(astring, delimiters);
  /*
   * FIXIT: форматирование: пробелы вокруг бинарных операций.
   * Старайтесь называть переменные более осмысленно: если вместо char* p; можно написать char* token;
   */
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
	char s[] = "asdasd     asdahsd         asduyiasd           dfghfgh          jhhjjh";
	char *p;
	char delim[] = " ";
	int *tcount, a, i;
  /*
   * Зачем это кручение-верчение указателей: уберите все лишние переменные.
   * int tokensCount;
   * char** tokens;
   * tokens = (char**)malloc...
   * Split(s, delims, &tokens, &tokensCount);
   */
	tcount = &a;
	char *** tok;
  /*
   * 1. У вас в некоторых местах отступы сделаны пробелами, а где-то символами табуляции.
   * У меня форматирование поехало из-за этого. 
   * 2. Память надо выделять в том же месте, где вы её освобождаете. Т.к. внутри ф-и split вы её освободить не можете, то и выделить её надо в main`е.
   * 3. tokk - плохое, не вносящие никакой ясности название. будто понятные слова кончились.
   * 4. надо освободить память.
   */
    char ** tokk;
    tok = &tokk;
    Split(s, delim, tok, tcount);
    for (i = 0; i < a; i++)
        printf("%s\n", tokk[i]);
	return 0;
}


