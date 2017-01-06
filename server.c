#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <sys/unistd.h>

#define SERVER_IP   "192.168.1.100"
#define SERVER_PORT 4096
#define BACK_LOG    10

#define BUFFER_SIZE 100

char rcv_buff[BUFFER_SIZE];

int main()
{
    int sockfd,new_fd;

    struct sockaddr_in server_addr;

    struct sockaddr_in client_addr;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket create failed!\n");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
 //   server_addr.sin_addr.s_addr = SERVER_IP;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    printf("Socket created!\n");

    if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("Bind error!\n");
        exit(1);
    }

    printf("Bind IP....\n");
    printf("Listen IP...\n");

    if(listen(sockfd,BACK_LOG) == -1)
    {
        perror("Listen error!\n");
        exit(1);
    }



    socklen_t len = sizeof(struct sockaddr_in);
    int newSock;

    printf("Wait client connect...\n");

    int bytes_sent;
    int strlength;
    char *msg = "Server: You have connected to server!\n";

    strlength = strlen(msg);
    int rsvbytessize;

    while(1)
    {
        if((newSock = accept(sockfd,(struct sockaddr *)&client_addr,&len)) == -1)
        {
            printf("%d",newSock);
            perror("Accept error!\n");

            continue;
        }

        bytes_sent = send(newSock, msg, strlength, 0);
        printf("Server:Got connection from %s\n",inet_ntoa(client_addr.sin_addr));

        while(1)
        {
            rsvbytessize = recv(newSock, rcv_buff, BUFFER_SIZE, 0);

            printf("%s", rcv_buff);





            printf("%d bytes has been sent\n",bytes_sent);

 //         close(newSock);
        }



    }

    close(sockfd);
    return 0;
}
