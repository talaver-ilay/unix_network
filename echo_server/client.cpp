#include    <iostream>
#include "my_socket.h"
#include <csignal>

int main(int argc, char **argv){
    // char recvline[MAXLINE + 1];
    if( argc != 2){err_quit("usage : <IPaddress>"); }
    Socket client(argv[1],12345);
    client.connect_socket();
    
    while(true){
        std::string input;
        getline(std::cin, input);
        if(input == "&exit"){
            client.close_connect();
            break;
        }
        client.write(input.data());
    }
}

