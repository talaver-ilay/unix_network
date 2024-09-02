#include "socket.h"
#include <csignal>

namespace unix_sock{

    template<class T>
    Socket::Socket(T addr, const uint16_t& port):sSockfd(sock_tcp_in()){
        bzero(&sSockaddr,sizeof(sSockaddr));
        sSockaddr.sin_family = AF_INET;
        sSockaddr.sin_port = htons(port);
        if(std::is_same<T,const char*>()){ inet_aton(addr, (in_addr*)&sSockaddr.sin_addr.s_addr);}
        else sSockaddr.sin_addr.s_addr = htonl(addr);
    }

    int Socket::sock_tcp_in(){
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0) err_sys("Sock: ERROR");
        return sock; 
    }
}
