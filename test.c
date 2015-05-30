#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFER_SIZE 255
#define FIFO1 "xxxx1"
#define FIFO2 "xxxx2"
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
void main(){
	int readfd,writefd;
	char buf[BUFFER_SIZE];
	int len;
	if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno != EEXIST)){
		printf("����%sʧ��\n",FIFO1);
		return;
	}
	if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno != EEXIST)){
		unlink(FIFO1);
		printf("����%sʧ��\n",FIFO2);
		return;
	}
	writefd = open(FIFO1,O_WRONLY,0);
	readfd = open(FIFO2,O_RDONLY,0);
	strcpy(buf,"father_abcd");
	write(writefd,buf,strlen(buf)+1);
	sleep(2);
	bzero(buf,sizeof(buf));
	len = read(readfd,buf,BUFFER_SIZE);
	printf("father receive:%d\n",len);
	printf("father receive:%s\n",buf);
	close(readfd);
	close(writefd);
	/*��һ�����̹رձ�ɣ���Ȼ���Էŵ���Ľ���ȥ���ã�������Ҫ��mkfifo��ͬһ������*/
	unlink(FIFO1);
	unlink(FIFO2);
}
