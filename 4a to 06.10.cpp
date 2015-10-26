#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int n, msize, m1[100][100], m2[100][100], result[100][100];

void* func(void* x)
{
    int startpoint = *((int*)x);
    for (int k = 0; k < msize / n; k++)
        for (int e = 0; e < msize; e++)
            for (int t = 0; t < msize; t++)
            {
                result[startpoint + k][e] += m1[startpoint + k][t] * m2[t][e];
            }
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &n);
    printf("Enter matrix size: ");
    scanf("%d", &msize);
    srand(time(0));
    for (int i = 0; i < msize; i++)
        for (int j = 0; j < msize; j++)
        {
            result[i][j] = 0;
            m1[i][j] = rand() % 100;
            m2[i][j] = rand() % 100;
        }
    pthread_t* thrid;
    thrid = (pthread_t*)malloc(n * sizeof(pthread_t));
    int thrnum[100];
    thrnum[0] = 0;
    for (int i = 0; i < n; i++)
    {
        pthread_create(&thrid[i], 0, func, &(thrnum[i]));
        thrnum[i + 1] = thrnum[i] + msize / n;
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(thrid[i], 0);
    }
    for (int i = 0; i < msize; i++)
    {
        printf("\n");
        for (int j = 0; j < msize; j++)
            printf(" %10d", result[i][j]);
    }
    free(thrid);
    return 0;
}
