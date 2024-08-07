
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
    int socketdescr;
    struct sockaddr_in servaddr;
    public:
        Socket(const char* addr, const uint16_t& port):socketdescr(sock_tcp_in()){
            sockaddr_new(port);
            inet_aton(addr, (in_addr*)&servaddr.sin_addr.s_addr);
        }
        Socket(in_addr_t addr, const uint16_t& port):socketdescr(sock_tcp_in()){
            sockaddr_new(port);
            servaddr.sin_addr.s_addr = htonl(addr);
        }
        ~Socket(){}
        void listen_server(){
            bind_socket();
            listen_socket();
            while (true){
                int clientdescr = accept(socketdescr,(struct sockaddr*) NULL, NULL);
                char buff[100]{0};
                while (ssize_t n = read(clientdescr,buff) != 0){
                    std::cout<<n<<std::endl;
                    std::cout<<buff<<std::endl;
                }
                if(buff[0] == 'c') close_connect(clientdescr);
            }
        }
        ssize_t read(const int descriptor,char* buffer){
            return recv(descriptor, buffer, sizeof(buffer), MSG_WAITALL);
        }
        ssize_t read(char* buffer){
            return recv(socketdescr, buffer, sizeof(buffer), MSG_WAITALL);
        }
        ssize_t write(const int descriptor,char *buffer){
            return send(descriptor,buffer,sizeof(buffer),MSG_WAITALL);
        }
        ssize_t write(char *buffer){
            return send(socketdescr,buffer,sizeof(buffer),MSG_WAITALL);
        }
        void close_connect(){
            shutdown(socketdescr, SHUT_RDWR);
            close(socketdescr);
        }
        void close_connect(const int descriptor){
            shutdown(descriptor, SHUT_RDWR);
            close(descriptor);
        }
        void connect_socket()const{
            if(connect(socketdescr, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) err_sys("Connect: ERROR");
            else std::cout<<"Connect: OK"<<std::endl;
        }
    private:  
         
        int sock_tcp_in(){
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if(sock < 0) err_sys("Sock: ERROR");
            std::cout<<"Sock: OK"<<std::endl;
            return sock;
        }
        void sockaddr_new(uint16_t port){
            bzero(&servaddr,sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(port);
        }
        void bind_socket()const{
            if(bind(socketdescr,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) err_sys("Bind: ERROR");
            else std::cout<<"Bind: OK"<<std::endl;
        }
        void listen_socket()const{
            if(listen(socketdescr,SOMAXCONN) < 0) err_sys("Listen error");
            else std::cout<<"Listen: OK"<<std::endl;
        }
        

};