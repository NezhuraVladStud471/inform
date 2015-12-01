#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("IP address missing.");
        return 0;
    }
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(49999);
    if (inet_aton(argv[1], &servaddr.sin_addr) == 0)
    {   
        printf("invalid IP");
        close(sockfd);
        return 0;
    }
    char sendline[1000], recvline[1000], line[1000], nickname[1000];
    bzero(nickname, 1000);
    printf("Enter nickname:\n");
    fgets(nickname, 1000, stdin);
    nickname[strlen(nickname) - 1] = '\0';
    strcat(nickname, ":");
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == 0) printf("ok");
    pid_t pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            bzero(sendline, 1000);
            bzero(line, 1000);
            strncat(sendline, nickname, 1000);
            fgets(line, 1000, stdin);
            strncat(sendline, line, 1000);
            write(sockfd, sendline, strlen(sendline) + 1);
        }
    }
    if (pid > 0)
    {
        while(1)
        {
            bzero(recvline, 1000);
            if (read(sockfd, recvline, 999) < 0)
            {
                perror(0);
                close(sockfd);
                exit(1);
            }
            printf("%s\n", recvline);
        }
    }
}
