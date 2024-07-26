#include <iostream>
#include "my_socket.h"

// strace execute_name посмотреть системные вызовы
// telnet 127.0.0.0 12345 подключиться к серверу
// fuser -k 12345/tcp закрыть все соединения на порт
// ps aux | fgrep server
// lsof -p PID
// gdb -p PID

int main(int argc, char **argv){
    Socket server(INADDR_ANY,12345);
    server.listen_server();
    return 0;
}
