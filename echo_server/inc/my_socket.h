
#pragma once
#include <iostream>
#include <time.h>
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>
#include "error.h"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>

class Socket{
    int sSocketdescr;
    struct sockaddr_in sSockaddr;

    public:
        Socket(const char* addr, const uint16_t& port):sSocketdescr(sock_tcp_in()){
            sockaddr_new(port);
            inet_aton(addr, (in_addr*)&sSockaddr.sin_addr.s_addr);
        }
        Socket(in_addr_t addr, const uint16_t& port):sSocketdescr(sock_tcp_in()){
            sockaddr_new(port);
            sSockaddr.sin_addr.s_addr = htonl(addr);
        }
        ~Socket(){}

        ssize_t read(const int descriptor,char* buffer){
            return recv(descriptor, buffer, sizeof(buffer), MSG_WAITALL);
        }
        ssize_t read(char* buffer){
            return recv(sSocketdescr, buffer, sizeof(buffer), MSG_WAITALL);
        }
        
        ssize_t write(const char *buffer){
            return send(sSocketdescr,buffer,sizeof(buffer),MSG_WAITALL);
        }
        void close_connect(){
            shutdown(sSocketdescr, SHUT_RDWR);
            close(sSocketdescr);
        }
        void connect_socket()const{
            if(connect(sSocketdescr, (struct sockaddr*)&sSockaddr,sizeof(sSockaddr)) < 0) err_sys("Connect: ERROR");
            else std::cout<<"Connect: OK"<<std::endl;
        }
        int get_socketdescr()const{
            return sSocketdescr;
        }
        sockaddr_in get_sockaddr(){
            return sSockaddr;
        }
    private:  
        int sock_tcp_in(){
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if(sock < 0) err_sys("Sock: ERROR");
            std::cout<<"Sock: OK"<<std::endl;
            return sock;
        }
        void sockaddr_new(uint16_t port){
            bzero(&sSockaddr,sizeof(sSockaddr));
            sSockaddr.sin_family = AF_INET;
            sSockaddr.sin_port = htons(port);
        }
};

class Server: public Socket{
    public:
        Server(const char* addr, const uint16_t& port)     :Socket(addr,port){}
        Server(const in_addr_t& addr, const uint16_t& port):Socket(addr,port){}

    void close_connect(const int descriptor){
        shutdown(descriptor, SHUT_RDWR);
        close(descriptor);
    }
    ssize_t write(const int descriptor,char *buffer){
        return send(descriptor,buffer,sizeof(buffer),MSG_WAITALL);
    }
    void listen_server(){
        bind_socket();
        listen_socket();
        while (true){
            int clientdescr = accept(get_socketdescr(),(struct sockaddr*) NULL, NULL);
            char buff[100]{0};
            while (ssize_t n = read(clientdescr,buff) != 0){
                std::cout<<n<<std::endl;
                std::cout<<buff<<std::endl;
            }
            if(buff[0] == 'c') close_connect(clientdescr);
        }
    }
    void bind_socket()const{
            if(bind(get_socketdescr(),(struct sockaddr*) &get_sockaddr(),sizeof(get_sockaddr())) < 0) err_sys("Bind: ERROR"); 
            else std::cout<<"Bind: OK"<<std::endl;
    }
    void listen_socket()const{
        if(listen(get_socketdescr(),SOMAXCONN) < 0) err_sys("Listen error");
        else std::cout<<"Listen: OK"<<std::endl;
    }
    
};