#include "my_socket.h"
#include <csignal>

void time_send(int clientSocket){
            char buffer[MAXLINE];
            while (true){
                time_t ticks = time( NULL);
                snprintf(buffer,sizeof(buffer),"%.24s\er\en",ctime(&ticks));
                // sleep(120);
                write(clientSocket, buffer,strlen(buffer));
                close (clientSocket);
                std::cout<<"Close thread"<<std::endl;
            }
        } 

void echo_send(int clientSocket){
            
            char buffer[MAXLINE];
            while (clientSocket){
                if(recv(clientSocket, buffer, sizeof(buffer), MSG_NOSIGNAL) < 0) break;
                if(write(clientSocket, buffer,strlen(buffer)) < 0) break;
            }
            close (clientSocket);
        } 