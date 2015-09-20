#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* astring, char* delimiters, char*** tokens, int* tokensCount)
{
    char * wordPointer;
    int i = 0;
    wordPointer = strtok(astring, delimiters);
  /*
   * FIXIT: форматирование: пробелы вокруг бинарных операций.
   * —тарайтесь называть переменные более осмысленно: если вместо char* p; можно написать char* token;
   */
    while (wordPointer != NULL)
    {
        (*tokens)[i] = wordPointer;
        i++;
        wordPointer = strtok(NULL, delimiters);
    }
    *tokensCount = i;
}

int main()
{
    char s[] = "asdasd     asdahsd         asduyiasd           dfghfgh          jhhjjh";
    char delim[] = " ";
    int tokensCount;
  /*
   * «ачем это кручение-верчение указателей: уберите все лишние переменные.
   * int tokensCount;
   * char** tokens;
   * tokens = (char**)malloc...
   * Split(s, delims, &tokens, &tokensCount);
   */
    char ** tokens;
  /*
   * 1. ” вас в некоторых местах отступы сделаны пробелами, а где-то символами табул€ции.
   * ” мен€ форматирование поехало из-за этого.
   * 2. ѕам€ть надо выдел€ть в том же месте, где вы еЄ освобождаете. “.к. внутри ф-и split вы еЄ освободить не можете, то и выделить еЄ надо в main`е.
   * 3. tokk - плохое, не внос€щие никакой €сности название. будто пон€тные слова кончились.
   * 4. надо освободить пам€ть.
   */
    tokens = (char**)malloc(100 * sizeof(char*));
    Split(s, delim, &tokens, &tokensCount);
    for (int i = 0; i < tokensCount; i++)
        printf("%s\n", tokens[i]);
    printf("String contains %d word(s).", tokensCount);
    free(tokens);
    return 0;
}


