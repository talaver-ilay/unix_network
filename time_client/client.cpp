#include    <iostream>
#include "my_socket.h"

int main(int argc, char **argv){
    char recvline[MAXLINE + 1];
    if( argc != 2){err_quit("usage : <IPaddress>"); }
    Socket client(argv[1],12345);
    client.client_connect();
    
    int n;
    while((n = client.read_client(recvline)) > 0){
        recvline[n] = 0; // завершающий нуль
        if(fputs(recvline,stdout) == EOF) err_sys("fputs error");
        else std::cout<<"\nfputs : OK"<<std::endl; 
    }
    if(n < 0) err_sys("read error");
    else std::cout<<"read : OK"<<std::endl;


    exit(0);
}

