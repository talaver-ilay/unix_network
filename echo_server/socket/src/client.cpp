#include  <iostream>
#include "client.h"
#include <csignal>

    Client::Client(const char* addr, const uint16_t& port)     :Socket(addr,port){connect_socket();}

    Client::Client(const in_addr_t& addr, const uint16_t& port):Socket(addr,port){connect_socket();}
    
    Client::~Client(){}

    void Client::close_connect(const int& descriptor = 0){
        shutdown(sSocketdescr, SHUT_RDWR);
        close(sSocketdescr);
    }

    ssize_t Client::write(const char *buffer, const int &descriptor = 0){
        return send(sSocketdescr,buffer,MAXLINE,MSG_WAITALL);
    }

    ssize_t Client::readn(const int &descriptor = 0){
        ssize_t n = 0;
        char buffer[MAXLINE];
        while (1){
            if((n = read(descriptor, buffer, MAXLINE))>0){ return -1;}
            std::cout<<buffer<<std::endl;   
        }
    }

    
    void Client::connect_socket()const{
        if(connect(sSocketdescr, (struct sockaddr*)&sSockaddr,sizeof(sSockaddr)) < 0) err_sys("Connect: ERROR");
        else std::cout<<"Connect: OK"<<std::endl;
    }