#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdlib.h>
#include "http.h"

int main(int argc, char *argv[]){
    int server_sock = -1; //服务器socket
    int port = 4000; //port
    int client_sock = -1; //客户端socket
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);
    
    server_sock = start_up(&port);  //封装的socket()
    printf("http is runing... port: %d\n", port);
    while(1){
        client_sock = accept(&server_sock,
                (struct sockaddr *)&client_name,
                 &client_name);
        if(client_sock == -1)
            error_die("accept error");
    }
    close(server_sock);
    return 0;
}
