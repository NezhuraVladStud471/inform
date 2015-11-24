#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    int users = 0;
    unsigned short userid[100];
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(49999);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    char line[1111];
    unsigned int clilen = sizeof(cliaddr);
    while (1)
    {
        recvfrom(sockfd, line, 1110, 0, (struct sockaddr*)&cliaddr, &clilen);
        for (int i = 0; i <= users; i++)
        {
            //printf("%d\n", userid[i]);
	    /*
	     * у вас users - число пользователей, и вы обращаетесь к элементу, которого заведомо нет +
	     * неплохо бы ещё и ip проверять
	     */
            if (userid[i] == cliaddr.sin_port) break;
            if (i == users)
            {   
                userid[users] = cliaddr.sin_port;
                users++;
                break;
            }
        }
        for (int i = 0; i < users; i++)
        {
	    /*
	     * Желательно отправлять всем, кроме автора сообщения.
	     */
            cliaddr.sin_port = userid[i];
            sendto(sockfd, line, strlen(line) + 1, 0, (struct sockaddr*)&cliaddr, clilen);
        }
    }
    return 0;
}
