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

/*
 * Если часто перезапускать программу, то на вызове bind будет ошибка.
 * Нужно подождать секунд 10 и можно заново запускать.
 * Мне кажется вы уже близки к рабочему варианту.
 * Какая-то проблема с разделяемой памятью. Поразбирайтесь.
 */

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
    char line[1000];
    bzero(line, 1000);
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
	printf("step1\n");
        newsockfd[*usersptr] = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
	printf("step2\n");
        (*usersptr)++;
        pid_t pid = fork();
        if (pid > 0)
        {
	    printf("step3\n");
            usersptr = (int*)shmat(shmid, 0, 0);
            newsockfd = (int*)(usersptr + 1);
            int currentuser = (*usersptr) - 1;
	    printf("currentuser %d; usersCount %d\n", currentuser, usersptr[0]);
            while(1)
            {
                read(newsockfd[currentuser], line, 999);
                for (int i = 0; i < (*usersptr); i++)
                {
		    printf("client socket addr %d\n", newsockfd[i]);
                    write(newsockfd[i], line, strlen(line) + 1);
                }
            }
        }
    }
}
