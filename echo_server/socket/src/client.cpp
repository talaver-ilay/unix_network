#include  <iostream>
#include "client.h"
#include <csignal>

    Client::Client(const char* addr, const uint16_t& port)     :Socket(addr,port){connect_socket();}

    Client::Client(const in_addr_t& addr, const uint16_t& port):Socket(addr,port){connect_socket();}
    
    Client::~Client(){}

    void Client::close_connect(const int &){
        shutdown(sSockfd, SHUT_RDWR);
        close(sSockfd);
    }

    ssize_t Client::write(const char *buffer, const int &){
        return send(sSockfd,buffer,MAXLINE,MSG_WAITALL);
    }

    void Client::readn(char* buffer, const int &){
        read(sSockfd, buffer, sizeof(buffer));
    }

    
    void Client::connect_socket()const{
        if(connect(sSockfd, (struct sockaddr*)&sSockaddr,sizeof(sSockaddr)) < 0) err_sys("Connect: ERROR");
        else std::cout<<"Connect: OK"<<std::endl;
    }