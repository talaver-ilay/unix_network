#pragma once
#include "socket.h"

class Server: public Socket{
    public:
        Server(const char* addr, const uint16_t& port); 

        Server(const in_addr_t& addr, const uint16_t& port);

        ~Server(){}

        void close_connect(const int& descriptor)override;

        ssize_t write(const char *buffer, const int &descriptor) override;

        void readn(char *buffer,const int &descriptor)override;

        void listen_server();
    
    private:
        void bind_socket()const;

        
        
        void listen_socket()const;
    
};