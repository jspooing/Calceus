#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

#define NUM_DATA 5
#define STREAM_PATH "/home/chc/calceus/datastream/stream.txt"

#define CHPN(x) x[strlen(x)] = '\n'

int inputStream(int* data,int num){
	
	int fd;
	char buf[100];
	int i;
	int len;
	
	memset(buf,0x00,sizeof(buf));

	fd = open(STREAM_PATH,O_APPEND|O_WRONLY|O_CREAT,0666);
	
	if(fd == -1)
		printf("File open err..\n");
	
	sprintf(buf,"%d",data[0]);
	for(i=1; i < num; i++)
		sprintf(buf,"%s %d",buf,data[i]);

	
	CHPN(buf);
	printf("%s",buf);

	len = strlen(buf);
	write(fd,buf,len);

	return len;

}
