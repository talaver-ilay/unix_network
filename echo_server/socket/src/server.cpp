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

    ssize_t Server::readn(char* buffer, const int& descriptor){
        ssize_t bytes_read = read(descriptor, buffer, sizeof(buffer) - 1);
        std::cout<<bytes_read<<std::endl;
        if (bytes_read == -1) {
            std::cerr << "Ошибка чтения из сокета" << std::endl;
            close_connect(descriptor);
            return 1;
        }else if(bytes_read == 0) {
            // Клиент закрыл соединение
            std::cout << "Клиент закрыл соединение" << std::endl;
            close_connect(descriptor);
            return 1;
        }
        buffer[bytes_read] = '\0';
        return 0;
    }

    void Server::listen_server(){
        listen_socket();
        
        char buffer[MAXLINE]{0};
        while (true){
            int clientdescr = accept(sSocketdescr,0, 0);
            if (clientdescr == -1) {
                std::cerr << "Ошибка принятия входящего подключения" << std::endl;
                close(sSocketdescr);
                return;
            }
            while(true){
                ssize_t n = read(clientdescr, buffer, sizeof(buffer) - 1); 
                std::cout << "Получено: " << buffer << " и "<<n<<" байт"<<std::endl;}
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