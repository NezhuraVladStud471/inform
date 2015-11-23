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
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, cliaddr;
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(0);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(49999);
    if (inet_aton(argv[1], &servaddr.sin_addr) == 0)
    {   
        printf("invalid IP");
        close(sockfd);
        return 0;
    }
    char sendline[1111], recvline[1111], line[1111];
    pid_t pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            printf("Enter nickname:\n");
            fgets(sendline, 1111, stdin);
            int l = strlen(sendline);
            strncpy(sendline, sendline, l - 2);         //i have no idea what to do with '\n' in the end of sendline
            strcat(sendline, ":");
            fgets(line, 1111, stdin);
            strncat(sendline, line, 1111);
            if (sendto(sockfd, sendline, strlen(sendline) + 1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
            {
                perror(0);
                close(sockfd);
                exit(1);
            }
        }
    }
    if (pid > 0)
    {
        while(1)
        {
            if (recvfrom(sockfd, recvline, 1111, 0, (struct sockaddr*)0, 0) < 0)
            {
                perror(0);
                close(sockfd);
                exit(1);
            }
            printf("%s\n", recvline);
        }
    }
}
