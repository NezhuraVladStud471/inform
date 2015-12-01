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
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 2);
    unsigned int clilen = sizeof(cliaddr);
    while (1)
    {
        newsockfd[*usersptr] = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        (*usersptr)++;
        pid_t pid = fork();
        if (pid > 0)
        {
            usersptr = (int*)shmat(shmid, 0, 0);
            newsockfd = (int*)(usersptr + 1);
            int currentuser = (*usersptr) - 1;
            while(1)
            {
                read(newsockfd[currentuser], line, 999);
                for (int i = 0; i < (*usersptr); i++)
                {
                    write(newsockfd[i], line, strlen(line) + 1);
                }
            }
        }
    }
}
