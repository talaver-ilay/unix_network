#pragma once
#include "socket.h"

class Client: public Socket{
    public:
        Client(const char* addr, const uint16_t& port);

        Client(const in_addr_t& addr, const uint16_t& port);

        ~Client();

        void close_connect(const int& descriptor = 0)override;

        ssize_t write(const char *buffer, const int &descriptor = 0)override;
        
        ssize_t readn(const int &descriptor)override;

    private:
        void connect_socket()const;
};