#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* astring, char* delimiters, char*** tokens, int* tokensCount)
{
    char * wordPointer;
    int i = 0;
    wordPointer = strtok(astring, delimiters);
  /*
   * FIXIT: ��������������: ������� ������ �������� ��������.
   * ���������� �������� ���������� ����� ����������: ���� ������ char* p; ����� �������� char* token;
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
   * ����� ��� ��������-�������� ����������: ������� ��� ������ ����������.
   * int tokensCount;
   * char** tokens;
   * tokens = (char**)malloc...
   * Split(s, delims, &tokens, &tokensCount);
   */
    char ** tokens;
  /*
   * 1. � ��� � ��������� ������ ������� ������� ���������, � ���-�� ��������� ���������.
   * � ���� �������������� ������� ��-�� �����.
   * 2. ������ ���� �������� � ��� �� �����, ��� �� � ������������. �.�. ������ �-� split �� � ���������� �� ������, �� � �������� � ���� � main`�.
   * 3. tokk - ������, �� �������� ������� ������� ��������. ����� �������� ����� ���������.
   * 4. ���� ���������� ������.
   */
    tokens = (char**)malloc(100 * sizeof(char*));
    Split(s, delim, &tokens, &tokensCount);
    for (int i = 0; i < tokensCount; i++)
        printf("%s\n", tokens[i]);
    printf("String contains %d word(s).", tokensCount);
    free(tokens);
    return 0;
}


