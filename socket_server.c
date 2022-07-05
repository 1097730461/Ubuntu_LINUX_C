/*————————————————————————————————————————————————————————
                    网络编程
                    
                    version:0.1
—————————————————————————————————————————————————————————*/
/*
编写服务器应用程序的流程如下： 
①、调用 socket()函数打开套接字，得到套接字描述符；
②、调用 bind()函数将套接字与 IP 地址、端口号进行绑定；
③、调用 listen()函数让服务器进程进入监听状态；
④、调用 accept()函数获取客户端的连接请求并建立连接；
⑤、调用 read/recv、write/send 与客户端进行通信；
⑥、调用 close()关闭套接字。
//各个函数原型
int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
*/

#include "socket_server.h"
/*
  +——————————————————————————————————————————————————
  |  1.服务器部分
  +——————————————————————————————————————————————————
*/

int server_init(void) {
 struct sockaddr_in server_addr = {0};
 struct sockaddr_in client_addr = {0};
 char ip_str[20] = {0};
 int sockfd, connfd;
 int addrlen = sizeof(client_addr);
 char recvbuf[512];
 int ret;
 /* 打开套接字，得到套接字描述符 */
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (0 > sockfd) {
 perror("socket error");
 exit(EXIT_FAILURE);
 }
 /* 将套接字与指定端口号进行绑定 */
 server_addr.sin_family = AF_INET;
 server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 server_addr.sin_port = htons(SERVER_PORT);
 ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
 if (0 > ret) {
 perror("bind error");
 close(sockfd);
 exit(EXIT_FAILURE);
 }
 /* 使服务器进入监听状态 */
 ret = listen(sockfd, 50);
 if (0 > ret) {
 perror("listen error");
 close(sockfd);
 exit(EXIT_FAILURE);
 }
 /* 阻塞等待客户端连接 */
 connfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
 if (0 > connfd) {
 perror("accept error");
 close(sockfd);
 exit(EXIT_FAILURE);
 }
 printf("有客户端接入...\n");
 inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip_str, sizeof(ip_str));
 printf("客户端主机的 IP 地址: %s\n", ip_str);
 printf("客户端进程的端口号: %d\n", client_addr.sin_port);
 /* 接收客户端发送过来的数据 */
 for ( ; ; ) {
     // 接收缓冲区清零
 memset(recvbuf, 0x0, sizeof(recvbuf));
 // 读数据
 ret = recv(connfd, recvbuf, sizeof(recvbuf), 0);
 if(0 >= ret) {
 perror("recv error");
 close(connfd);
 break;
 }
 // 将读取到的数据以字符串形式打印出来
 printf("from client: %s\n", recvbuf);
 // 如果读取到"exit"则关闭套接字退出程序
 if (0 == strncmp("exit", recvbuf, 4)) {
 printf("server exit...\n");
 close(connfd);
 break;
 }
 }
 /* 关闭套接字 */
 close(sockfd);
 exit(EXIT_SUCCESS);
}





