#pragma once
#include "socket.h"

class Client: public unix_sock::Socket{
    public:
        template<class T>
        explicit Client(T addr, const uint16_t& port);

        ~Client();

        void close_connect(const int &)override;

        ssize_t write(const char *buffer, const int &)override;
        
        void readn(char*, const int &)override;

    private:
        void connect_socket()const;
};