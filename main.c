

#include "procces.h"
#include "socket_server.h"
#include "socket_client.h"

int main(void){
    printf("all is well!\n");
    printf("change\n");
    
    //父进程运行服务器打印客户端的消息，子进程做客户端。
    int ret = -1;
    char buf[512];

    ret = fork();
    if(ret<0){
        perror("fork:");
        return -1;
    }

    if(ret == 0){
        printf("son_procces\n");
        client_init();
    }

    if(ret > 0){
        printf("father_procces\n");
        server_init();
    }

    return 0;
}

//gcc *.c -o main   统一编译
//或者用Makefile     一键make

//su root 168558    进入root
//su xwave          回到普通模式