#include    <iostream>
#include "my_socket.h"
#include <csignal>

int main(int argc, char **argv){
    char recvline[MAXLINE + 1];
    if( argc != 2){err_quit("usage : <IPaddress>"); }
    Socket client(argv[1],12345);
    client.client_connect();
    
    int n;
    while(true){
        std::cout<<"\n";
        std::cin>>recvline;
        client.write_client(recvline);
        bzero(recvline, sizeof(recvline));
        n = client.read_client(recvline);
        recvline[n] = 0; // завершающий нуль
        if(fputs(recvline,stdout) == EOF) err_sys("fputs error");
        bzero(recvline,sizeof(recvline));

    }
    
    exit(0);
}

