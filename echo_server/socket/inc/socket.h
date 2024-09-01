
#pragma once
#include <iostream>
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>
#include "error.h"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

class Socket{
    protected:
        int sSockfd;
        struct sockaddr_in sSockaddr;

    public:
        Socket(const char* addr, const uint16_t& port);
        Socket(in_addr_t addr, const uint16_t& port);

        virtual ~Socket(){}

        virtual void readn(char*, const int &) = 0;
        
        virtual ssize_t write(const char *, const int &) = 0;
    
        virtual void close_connect(const int&) = 0;
        
    private:  
        int sock_tcp_in();
        void sockaddr_new(const uint16_t& port);
};



