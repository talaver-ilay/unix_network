#pragma once
#include "socket.h"

class Server: public unix_sock::Socket{
    public:
        template<class T>
        explicit Server(T addr, const uint16_t& port); 

        ~Server(){}

        void close_connect(const int& descriptor)override;

        ssize_t write(const char *buffer, const int &descriptor) override;

        void readn(char *buffer,const int &descriptor)override;
        enum class server_state{BIND,LISTEN,ERROR};
    private:
        server_state bind_socket()const;
        void listen_server();
    
};