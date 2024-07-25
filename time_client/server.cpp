#include <iostream>
#include <time.h>
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>
#include    "error.h"
#include	<unistd.h>
#include	<string.h>
#include    <arpa/inet.h>

#define	LISTENQ		1024

// strace execute_name посмотреть системные вызовы
// telnet 127.0.0.0 12345 подключиться к серверу
// fuser -k 12345/tcp закрыть все соединения на порт
// ps aux | fgrep server
// lsof -p PID
// gdb -p PID

int main(int argc, char **argv){
    int listenfd, connfd;
    char buff[MAXLINE];
    time_t ticks;
    struct sockaddr_in servaddr;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){err_sys("sock error");}
    else std::cout<<"Sock : OK"<<std::endl;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);

    while(true){
        connfd = accept(listenfd,(struct sockaddr*) NULL, NULL);

        ticks = time( NULL);
        snprintf(buff,sizeof(buff),"%.24s\er\en",ctime(&ticks));
        write(connfd, buff,strlen(buff));
        close (connfd);
    }
    return 0;
}