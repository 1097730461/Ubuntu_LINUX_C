

#include "procces.h"

int procces_init(void){
//创建子进程，父子进程分别进行鼠标和键盘的读取工作
//两个文件IO都是阻塞的
int ret = -1;
int fd = -1;
char buf[200];

ret = fork();
if(ret<0){
    perror("fork:");
    return -1;
}

if(ret == 0){
    //子进程
    //处理鼠标
    fd = open("/dev/input/mouse0", O_RDONLY); //此处要用阻塞式
    if(fd<0){
        perror("open:");
        return -1;
    }
    while(1){
    memset(buf , 0, sizeof(buf));
    read(fd, buf, 100);
    printf("鼠标读出的内容是： [%s].\n", buf); 
    }
}

if(ret > 0){
    //父进程
    //处理键盘(主任务)
    while(1){
    memset(buf , 0, sizeof(buf));
    read(0, buf, 5);
    printf("读出的内容是： [%s].\n", buf); 
    }
}
    return 0;
}