#include <sys/types.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

/*
  Для общения нитей подойдёт как глобальная переменная (указатель на массив переменных, выделенных в куче, т.е. malloc`ом).
  Общение через разделяемую память в данном случае совсем не обязательно. 
  Если вы просто решили потренироваться, то пусть будет так.
  
  Вы уже довольно уверенно пишите работающие программы. Старайтесь теперь писать код, называя переменные как можно более ясно, не использовать 
  магические числа, вроде ваших 5, 101, 999, 1000, 49999 и т.п.
  Также разбивать код на небольшие ф-и: это делает код самодокументируемым.
 */

void * newuser(void * x)
{
    int shmid = *(int*)x;
    int * usersptr = (int*)shmat(shmid, 0, 0);
    int * newsockfd = (int*)(usersptr + 1);
    int currentuser = (*usersptr) - 1;
    char line[1000];
    bzero(line, 1000);
    while(1)
    {
        read(newsockfd[currentuser], line, 999);
        for (int i = 0; i < (*usersptr); i++)
        {
            if (i != currentuser) write(newsockfd[i], line, strlen(line) + 1);
        }
    }
}

int main()
{
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    int * usersptr, * newsockfd;
    int fd = open("connection", O_CREAT);
    close(fd);
    key_t key = ftok("connection", 0);
    int shmid = shmget(key, (101 * sizeof(int)), 0666 | IPC_CREAT);
    usersptr = (int*)shmat(shmid, 0, 0);
    newsockfd = (int*)(usersptr + 1);
    (*usersptr) = 0;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(49999);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
      perror("can`t bind:");
      exit(1);
    }
    if (listen(sockfd, 5) != 0)
    {
      perror("listen:");
      exit(0);
    }
    unsigned int clilen = sizeof(cliaddr);
    while (1)
    {
        newsockfd[*usersptr] = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        (*usersptr)++;
        pthread_t thrid;
        pthread_create(&thrid, 0, newuser, &shmid);
    }
}
