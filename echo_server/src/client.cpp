#include  <iostream>
#include "my_socket.h"
#include <csignal>

int main(int argc, char **argv){
    if( argc != 2){err_quit("usage : <IPaddress>"); }
    Client client(argv[1],12345);
    
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

