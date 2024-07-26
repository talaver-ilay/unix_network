
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

#define	LISTENQ		1024

void time_send(int clientSocket);
void echo_send(int clientSocket);

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
            std::vector<std::thread> threads;
            while (true){
                struct sockaddr_in clientaddr;
                int clientdescr = accept(socketdescr,(struct sockaddr*) NULL, NULL);
                if(clientdescr < 0) err_sys("Client Sock: ERROR");
                // threads.emplace_back(time_send,clientdescr);
                threads.emplace_back(echo_send, clientdescr); 
            }
            for(auto& thread : threads ){
                thread.join();
            }
        }
        void client_connect()const{
            connect_socket();

        }
        ssize_t read_client(char* recvline){
            return read(socketdescr, recvline, MAXLINE);
        }
        ssize_t write_client(char *buffer){
            return write(socketdescr, buffer,strlen(buffer));
        }
        void close_connect(){
            shutdown(socketdescr, SHUT_RDWR);
            close(socketdescr);
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
            if(listen(socketdescr,LISTENQ) < 0) err_sys("Listen error");
            else std::cout<<"Listen: OK"<<std::endl;
        }
        void connect_socket()const{
            if(connect(socketdescr, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) err_sys("Connect: ERROR");
            else std::cout<<"Connect: OK"<<std::endl;
        }

};