#include <iostream>
#include "server.h"

    Server::Server(const char* addr, const uint16_t& port)     :Socket(addr,port){bind_socket();}
    
    Server::Server(const in_addr_t& addr, const uint16_t& port):Socket(addr,port){bind_socket();}

    void Server::close_connect(const int& descriptor){
        shutdown(descriptor, SHUT_RDWR);
        close(descriptor);
    }

    ssize_t Server::write(const char *buffer, const int &descriptor){
        return send(descriptor,buffer,sizeof(buffer),MSG_WAITALL);
    }

    ssize_t Server::readn(const int& descriptor){
        ssize_t n = 0;
        char buffer[MAXLINE];
        // while (1)
        // {
           if((n = read(descriptor, buffer, MAXLINE))>0){ return -1;}
            std::cout<<buffer<<std::endl;   
        // }
    }

    void Server::listen_server(){
        listen_socket();
        while (true){
            int clientdescr = accept(sSocketdescr,(struct sockaddr*) NULL, NULL);
            // char buff[MAXLINE]{0};
            readn(clientdescr);
            // if(buff[0] == 'c') close_connect(clientdescr);
        }
    }

    void Server::bind_socket()const{
            if(bind(sSocketdescr,(struct sockaddr*) &sSockaddr,sizeof(sSockaddr)) < 0) err_sys("Bind: ERROR"); 
            else std::cout<<"Bind: OK"<<std::endl;
    }

    void Server::listen_socket()const{
        if(listen(sSocketdescr,SOMAXCONN) < 0) err_sys("Listen error");
        else std::cout<<"Listen: OK"<<std::endl;
    }