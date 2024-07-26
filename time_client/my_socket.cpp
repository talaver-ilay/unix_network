#include "my_socket.h"

void time_send(int clientSocket){
            char buffer[MAXLINE];
            // while (true){
                time_t ticks = time( NULL);
                snprintf(buffer,sizeof(buffer),"%.24s\er\en",ctime(&ticks));
                sleep(120);
                write(clientSocket, buffer,strlen(buffer));
                close (clientSocket);
                std::cout<<"Close thread"<<std::endl;
            // }
        } 