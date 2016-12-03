// Author: ANkur Sharma 2016225
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <time.h> 
#include <string.h>

#define PORT 5555



int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
   
    struct sockaddr_in serv_addr;
    char sendBuff[500];
    char recvBuff[500];


    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&serv_addr, '0', sizeof(serv_addr));

     

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //macros
    serv_addr.sin_port = htons(PORT); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 


    listen(listenfd, 5);



    printf("\nServer listening for connections!\n");
    
    pid_t pid;

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); //related to ./c <ip address>

        
        if ((pid=fork())==0)
        {
            close(listenfd); //so no other client can interrupt the established connection

            memset(recvBuff, '\0', sizeof(recvBuff)); 
            memset(sendBuff, '\0', sizeof(sendBuff));

            int readbytes = read(connfd,recvBuff,sizeof(recvBuff)); //read from client (recv buffer)
            if(readbytes < 0)
            {
                printf("\n Read error \n");
            }
    

            printf("MESSAGE FROM CLIENT: ");
 
            printf("%s\n",recvBuff ); //printing the received message
            printf("\nENTER YOUR REPLY: "); 
            
            fgets(sendBuff,sizeof(sendBuff),stdin); //server expecting you to reply with some message
        
            int n = write(connfd,sendBuff,sizeof(sendBuff)); //writes replyfrom server on client's terminal

            close(connfd);  //close client socket
            exit(0); //to succeessfully exit
        }
        
     }
}
