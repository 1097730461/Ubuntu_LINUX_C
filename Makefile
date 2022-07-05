#目标：依赖
main : main.o procces.o socket_server.o socket_client.o
#命令-指定依赖如何生成目标
	gcc main.o procces.o socket_server.o socket_client.o -o main        
#.o文件依赖与.c文件
#将.c文件生成.o文件
main.o : main.c                      
	gcc -c main.c -o main.o          
procces.o : procces.c
	gcc -c procces.c -o procces.o

socket_server.o : socket_server.c
	gcc -c socket_server.c -o socket_server.o

socket_client.o : socket_client.c
	gcc -c socket_client.c -o socket_client.o

#伪目标，避免出现符号clean与文件clean重名的情况，
#导致执行make clean清除操作失败
.PHONY:clean     

clean:
	rm *.o main 
