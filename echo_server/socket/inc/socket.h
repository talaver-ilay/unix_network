
#pragma once
#include <iostream>
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>
#include "error.h"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

namespace unix_sock{
    
    class Socket{
        protected:
            int sSockfd;
            struct sockaddr_in sSockaddr;
            
        public:
            

            template<class T>
            explicit Socket(T addr, const uint16_t& port);
            
            virtual ~Socket(){}

            virtual void readn(char*, const int &) = 0;
            
            virtual ssize_t write(const char *, const int &) = 0;
        
            virtual void close_connect(const int&) = 0;
            
        private:  
            int sock_tcp_in();
    };
}


