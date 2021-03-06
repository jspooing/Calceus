#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include"calceus.h"

#define NUM_DATA 5
#define STREAM_PATH "/home/chc/calceus/datastream/stream.txt"
#define STREAM_CON "/home/chc/calceus/datastream/content.txt"
#define STREAM_VAL "/home/chc/calceus/value.txt"
#define CHPN(x) x[strlen(x)] = '\n'
#define CHOP(x) x[strlen(x)-1] = NULL

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

	close(fd);
	return len;

}


void sendresult(int sock){
	FILE *fp;
	int lval[5];
	int rval[5];
	char temp[100];
	char buf[1024];
	int i;


	printf("Backend running...\n");

	
	while(1){	
		if(access(STREAM_CON,F_OK)==0)
			break;
	}

	fp= fopen(STREAM_CON,"r");

	memset(buf,0x00,1024);

	while(fgets(temp,100,fp) != NULL){
		CHOP(temp);
		sprintf(buf,"%s%s#",buf,temp);
	}
	CHOP(buf);
	CHPN(buf);

	printf("%s",buf);

	write(sock,buf,sizeof(buf));

	return;

}

void* t_testBackend(void *data){

	char* id = (char *)data;

	FILE *fp;
	int lval[5];
	int rval[5];
	char ilist[12][200];
	char buf[100];
	int i;


	printf("Backend running...\n");

	system("echo '1234' |sudo -S python /home/chc/calceus/analysis.py");

	
	while(1){	
		if(access(STREAM_VAL,F_OK)==0)
			break;
	}

	printf("wait end\n");
	fflush(stdout);

	system("sed -i 's/ //g' /home/chc/calceus/value.txt");

	fp= fopen(STREAM_VAL,"r");


	
	fscanf(fp,"[%d,%d,%d,%d,%d]",&lval[0],&lval[1],&lval[2],&lval[3],&lval[4]);
	fscanf(fp,"[%d,%d,%d,%d,%d]",&rval[0],&rval[1],&rval[2],&rval[3],&rval[4]);



	sprintf(ilist[0],"%s",id);


		for(i=0; i<5; i ++){
			sprintf(ilist[i+1],"%d",lval[i]);
		}


		for(i=0; i < 5 ; i ++){
			sprintf(ilist[i+6],"%d",rval[i]);
		}

	if(DBcheck("TEST","id",id))
		DBdelete("TEST","id",id);

	DBinsert("TEST",ilist,11);
	system("rm /home/chc/calceus/value.txt");
//	system("rm /home/chc/calceus/datastream/stream.txt");
//	system("rm /home/chc/calceus/datastream/content.txt");

	return;

}




int getImg(int sock,char* buf,int buf_size){

	char chkbuf;
	int fd;
	int str_len;
	int i ;


	fd = open("/home/chc/calceus/datastream/result.bmp",O_RDONLY);
	if(fd == -1)
		printf("File Open err .. \n");
	while(read(fd,buf,buf_size)){
		str_len = strlen(buf);
		write(sock,buf,str_len);
		printf("%s",buf);
	}
	close(fd);

	return 0;
}
