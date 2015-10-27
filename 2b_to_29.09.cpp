#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*test test test
 */

int main()
{
    int status, n, i = 0;
    scanf("%d", &n);
    while (i < n)
    {
        pid_t pid = fork();
        i++;
        if ((i == n) && (pid == 0))         //last child mustn't print 'status'
            exit(0);
        if (pid > 0)
            break;
    }
    wait(&status);
    printf("\n%d", status);
    return 0;
}
