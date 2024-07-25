#include    <iostream>
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>
#include    "error.h"
#include	<unistd.h>
#include	<string.h>
#include    <arpa/inet.h>	

int main(int argc, char **argv){
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if( argc != 2){err_quit("usage : a.out <IPaddress>"); }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){err_sys("sock error");}
    else std::cout<<"Sock : OK"<<std::endl;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    inet_aton(argv[1], (in_addr*)&servaddr.sin_addr.s_addr);

    if(connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) err_sys("connect error");
    else std::cout<<"connect : OK"<<std::endl;

    while((n = read(sockfd,recvline, MAXLINE)) > 0){
        recvline[n] = 0; // завершающий нуль
        if(fputs(recvline,stdout) == EOF) err_sys("fputs error");
        else std::cout<<"fputs : OK"<<std::endl;
        
    }
    if(n < 0) err_sys("read error");
    else std::cout<<"read : OK"<<std::endl;


    exit(0);
}

