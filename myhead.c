#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //intptr_t
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h> //bzero
#include "myhead.h"



void error_die(const char *c){
    perror(c);
    exit(1);
}


int startup(u_short* port){

    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;
    httpd = socket(AF_INET, SOCK_STREAM, 0);

    if(httpd == -1){
        error_die("socket");
    }
    bzero(&name, sizeof(&name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    //SO_REUSEADDR :设置地址复用 on是函数的输入参数
    //允许同一port上启动同一服务器的多个实例(多个进程) 但每个实例绑定的IP地址是不能相同的
    //这里的应用场景是多线程下处理用户请求，主线程负责监听，子线程负责交互处理请求
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0){
        error_die("setsockopt failed");
    }
    if(bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0){
        error_die("bind");
    }
    if(*port == 0){
        socklen_t namelen = sizeof(name);
        if(getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1){
            error_die("getsockname");
        }
        *port = ntohs(name.sin_port);
    }
    if(listen(httpd, 5) < 0) error_die("listen");
    return httpd;
}

void accept_request(void* arg){
    
    return;
}

int get_line(int sock, char* buf, int size){
    int i = 0;
    int n;
    char c = '\0';
    while((i < size - 1) && (c != '\n')){
        //一次仅仅接受一个字节
        n = recv(sock, &c, 1, 0);
        if(n > 0){
            if(c == '\r'){
                n = recv(sock, &c, 1, MSG_PEEK);
                if((n > 0) && (c =='\n')) recv(sock, &c, 1, 0);
                else c = '\n';
            }
            buf[i] = c;
            i++;
        }else{
            c = '\n'; //END
        }
        buf[i] = '\0';

    }
    return i;
}















