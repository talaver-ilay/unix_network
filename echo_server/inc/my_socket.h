
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

class Socket{
    protected:
        int sSocketdescr;
        struct sockaddr_in sSockaddr;

    public:
        Socket(const char* addr, const uint16_t& port):sSocketdescr(sock_tcp_in()){
            sockaddr_new(port);
            inet_aton(addr, (in_addr*)&sSockaddr.sin_addr.s_addr);
        }
        Socket(in_addr_t addr, const uint16_t& port):sSocketdescr(sock_tcp_in()){
            sockaddr_new(port);
            sSockaddr.sin_addr.s_addr = htonl(addr);
        }
        virtual ~Socket(){}

        virtual ssize_t read(char *, const int &) = 0;
        
        virtual ssize_t write(const char *, const int &) = 0;
    
        virtual void close_connect(const int&) = 0;

        
    private:  
        int sock_tcp_in(){
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if(sock < 0) err_sys("Sock: ERROR");
            std::cout<<"Sock: OK"<<std::endl;
            return sock;
        }
        void sockaddr_new(const uint16_t& port){
            bzero(&sSockaddr,sizeof(sSockaddr));
            sSockaddr.sin_family = AF_INET;
            sSockaddr.sin_port = htons(port);
        }
};

class Server: public Socket{
    public:
        Server(const char* addr, const uint16_t& port)     :Socket(addr,port){bind_socket();}
        Server(const in_addr_t& addr, const uint16_t& port):Socket(addr,port){bind_socket();}
        ~Server(){}

    void close_connect(const int& descriptor)override{
        shutdown(descriptor, SHUT_RDWR);
        close(descriptor);
    }

    ssize_t write(const char *buffer, const int &descriptor) override{
        return send(descriptor,buffer,sizeof(buffer),MSG_WAITALL);
    }

    ssize_t read(char* buffer, const int& descriptor)override{
        return recv(descriptor, buffer, sizeof(buffer), MSG_WAITALL);
    }

    void listen_server(){
        listen_socket();
        while (true){
            int clientdescr = accept(sSocketdescr,(struct sockaddr*) NULL, NULL);
            char buff[100]{0};
            while (ssize_t n = read(buff, clientdescr) != 0){
                std::cout<<n<<std::endl;
                std::cout<<buff<<std::endl;
            }
            if(buff[0] == 'c') close_connect(clientdescr);
        }
    }
    void bind_socket()const{
            if(bind(sSocketdescr,(struct sockaddr*) &sSockaddr,sizeof(sSockaddr)) < 0) err_sys("Bind: ERROR"); 
            else std::cout<<"Bind: OK"<<std::endl;
    }
    void listen_socket()const{
        if(listen(sSocketdescr,SOMAXCONN) < 0) err_sys("Listen error");
        else std::cout<<"Listen: OK"<<std::endl;
    }
    
};

class Client: public Socket{
    public:
        Client(const char* addr, const uint16_t& port)     :Socket(addr,port){connect_socket();}
        Client(const in_addr_t& addr, const uint16_t& port):Socket(addr,port){connect_socket();}
        ~Client(){close_connect();}

        void close_connect(const int& descriptor = 0)override{
            shutdown(sSocketdescr, SHUT_RDWR);
            close(sSocketdescr);
        }

        ssize_t write(const char *buffer, const int &descriptor = 0)override{
            return send(sSocketdescr,buffer,sizeof(buffer),MSG_WAITALL);
        }

        ssize_t read(char *buffer, const int &descriptor = 0)override{
            return recv(sSocketdescr, buffer, sizeof(buffer), MSG_WAITALL);
        }

    private:
        void connect_socket()const{
            if(connect(sSocketdescr, (struct sockaddr*)&sSockaddr,sizeof(sSockaddr)) < 0) err_sys("Connect: ERROR");
            else std::cout<<"Connect: OK"<<std::endl;
        }
};