#ifndef _SOCKET_CLIENT_H
#define _SOCKET_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 9999 //服务器的端口号
#define SERVER_IP "192.168.1.10" //服务器的 IP 地址

int client_init(void);

#endif