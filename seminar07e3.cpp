#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>

key_t key, semkey;
int msqid, n;
int semid;
pid_t pid;

/*
 * У вас в двух местах дублируется объявление структуры для пересылки.
 * Её можно вынести в отдельный файл mytypes.h
 * При этом и в клиенте и в сервере этот файл подключить #include "mytypes.h"
 * И при компиляии его также упомянуть:
 * g++ client.cpp mytypes.h -o client
 */

struct mesage{
long mtype;
    struct info {
        long pid;
        long x;
        long y;
    }inf;
}; 

struct sembuf mybuf;
    
int main()
{
    key = ftok("connection", 0);
    semkey = ftok("connection1", 0);
    msqid = msgget(key, 0666 | IPC_CREAT);
    printf("Enter max number of threads: ");
    scanf("%d", &n);
    /*
     * Перед запятой не нужен пробел.
     */
    semid = semget(key , 1 , 0666 | IPC_CREAT);
    mybuf.sem_op = n;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;
    semop(semid , &mybuf , 1);
    while (1)
    {
        mybuf.sem_op = -1;
        semop(semid , &mybuf , 1);
        pid = fork();
        if (pid > 0)
        { 
            mesage msg;
            msgrcv(msqid, &msg, sizeof(msg.inf), 1, 0);
            msg.inf.x = msg.inf.x * msg.inf.y;
            msg.mtype = msg.inf.pid;
            msgsnd(msqid, &msg, sizeof(msg.inf), 0);
            mybuf.sem_op = 1;
            semop(semid , &mybuf , 1);
            exit(0);
        }
    }
    return 0;
}

/*
 * В целом, все нормально. Засчитано.
 */
