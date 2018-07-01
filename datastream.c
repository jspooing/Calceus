#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_DATA 5
#define STREAM_PATH "/home/chc/calceus/datastream/stream.txt"

#define CHPN(x) x[strlen(x)] = '\n'


int inputStream(int* data,int num){
	
	int fd;
	char buf[100];
	int i;
	int len;


	fd = open(STREAM_PATH,O_APPEND|O_WRONLY|O_CREATE,0666);
	
	if(fd == -1)
		printf("File open err..\n");

	for(i=0; i < num; i++)
		sprintf(buf,"%s %d",buf,data[i]);

	
	CHPN(x);

	len = strlen(buf);
	write(fd,buf,len);

	return len;

}
