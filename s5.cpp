#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MaxValue 100

int n, msize;
int ** m1, ** m2, ** result;

void* func(void* x)
{
    int startpoint = *((int*)x);
    for (int i = 0; i < msize / n; i++)
        for (int j = 0; j < msize; j++)
            for (int k = 0; k < msize; k++)
            {
                result[startpoint + i][j] += m1[startpoint + i][k] * m2[k][j];
            }
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &n);
    printf("Enter matrix size: ");
    scanf("%d", &msize);
    srand(time(0));
    m1 = (int**)malloc(msize * sizeof(int*));
    m2 = (int**)malloc(msize * sizeof(int*));
    result = (int**)malloc(msize * sizeof(int*));
    for (int i = 0; i < msize; i++)
    {    
        m1[i] = (int*)malloc(msize * sizeof(int));
        m2[i] = (int*)malloc(msize * sizeof(int));
        result[i] = (int*)malloc(msize * sizeof(int));
    }        
    for (int i = 0; i < msize; i++)
        for (int j = 0; j < msize; j++)
        {
            result[i][j] = 0;
            m1[i][j] = rand() % MaxValue;
            m2[i][j] = rand() % MaxValue;
        }
    pthread_t* thrid;
    /*
     * Странно, что вы веделили массив размером (100 * 4 байта) в куче, а двумерный массив из 10000 элементов - на стеке.
     * Его, вероятно, лучше тогда тоже было бы выделить в куче.
     */
    thrid = (pthread_t*)malloc(n * sizeof(pthread_t));
    int thrnum[100];
    thrnum[0] = 0;
    for (int i = 0; i < n; i++)
    {
        pthread_create(&thrid[i], 0, func, &thrnum[i]);
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
