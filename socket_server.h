#ifndef _SOCKET_SERVER_H
#define _SOCKET_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//服务器端口号
#define SERVER_PORT 9999 
//端口号不能发生冲突,不常用的端口号通常大于 5000

int server_init(void);

#endif