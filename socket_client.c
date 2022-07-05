/*
  +——————————————————————————————————————————————————
  |  2.客户端部分
  +——————————————————————————————————————————————————
*/
#include "socket_client.h"
int client_init(void)
{
    struct sockaddr_in server_addr = {0};
    char buf[512];
    int sockfd;
    int ret;

    //打开套接字，得到套接字描述符
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (0 > sockfd) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    printf("sockfd = %d\n",sockfd);

    //调用connect连接远端服务器
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT); //端口号
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);//IP 地址

      printf("go to connect...\n");
    ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (0 > ret) {
        perror("connect error");
        close(sockfd);
        exit(EXIT_FAILURE);
     }

     printf("服务器连接成功...\n\n");

     //向服务器发送数据
     for ( ; ; ) {
     // 清理缓冲区
        memset(buf, 0x0, sizeof(buf));
     // 接收用户输入的字符串数据
        printf("Please enter a string: ");
        fgets(buf, sizeof(buf), stdin);
 
     // 将用户输入的数据发送给服务器
         ret = send(sockfd, buf, strlen(buf), 0);
         if(0 > ret){
         perror("send error");
         break;
         }
     //输入了"exit"，退出循环
         if(0 == strncmp(buf, "exit", 4))
         break;
     }
         close(sockfd);
         exit(EXIT_SUCCESS);
}