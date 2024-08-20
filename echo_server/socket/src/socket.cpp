#include "socket.h"
#include <csignal>

Socket::Socket(const char* addr, const uint16_t& port):sSocketdescr(sock_tcp_in()){
    sockaddr_new(port);
    inet_aton(addr, (in_addr*)&sSockaddr.sin_addr.s_addr);
}

Socket::Socket(in_addr_t addr, const uint16_t& port):sSocketdescr(sock_tcp_in()){
    sockaddr_new(port);
    sSockaddr.sin_addr.s_addr = htonl(addr);
}

int Socket::sock_tcp_in(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) err_sys("Sock: ERROR");
    std::cout<<"Sock: OK"<<std::endl;
    return sock;
}

void Socket::sockaddr_new(const uint16_t& port){
    bzero(&sSockaddr,sizeof(sSockaddr));
    sSockaddr.sin_family = AF_INET;
    sSockaddr.sin_port = htons(port);
}