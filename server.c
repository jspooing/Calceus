#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "time.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "pthread.h"

#define BUFSIZE 1024 //버퍼 사이즈 
#define PORT 7163 //서버 포트 
#define MAX_CLIENT 5 //클라이언트 최대 

void error_handling(char* message); //예외처리 함수 
void* clnt_connection(void* arg);  //클라이언트 서비스 스레드 함수 
void* t_wLog(void* arg);
int findEmpty(int indicator, int *slot, int s_size);

int cntNum=0;  //현재 서비스중인 클라이언트 수 

int clnt_sock[MAX_CLIENT]; //클라이언트 소켓
int clnt_con[MAX_CLIENT] = {0};       //클라이언트 접속 정보
int clnt_indicator = 0;  //클라이언트 교통정리용 


int main(int argc, char ** argv)
{
	int serv_sock; // 서버  소켓 
	struct sockaddr_in serv_addr;   //서버,클라이언트  소켓 주소 구조체 
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;  // 클라이언트 소켓 구조체 사이즈 
	pthread_t t_clnt[MAX_CLIENT]; // 스레드 구조체 배열 



	if((serv_sock = socket(AF_INET, SOCK_STREAM, 0))<0)  //서버 소켓 생성 
	{
		perror("socket() error: ");
	}


	memset(&serv_addr, 0x00 , sizeof(serv_addr));  

	serv_addr.sin_family = AF_INET;   //tcp 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serv_addr.sin_port = htons(PORT);  //서버 포트번호 설정 

	if(bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
		error_handling("bind() error");


	if(listen(serv_sock,5)<0)
		error_handling("listen() error");

	printf("Waiting for client...\n");

	clnt_addr_size = sizeof(clnt_addr);

	while(1){

		//클라이언트 접속 슬롯 결정 
		clnt_indicator = findEmpty(clnt_indicator,clnt_con,MAX_CLIENT);
		if(clnt_indicator == -1){
			printf("Server is full\n");
			sleep(5);
			clnt_indicator++;
		}
		else{
			//클라이언트 연결 
			clnt_sock[clnt_indicator] = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
			if(clnt_sock[clnt_indicator] < 0)
				error_handling("accept() error");
			printf("Client%d connected !\n",clnt_indicator);

			if(pthread_create(&t_clnt[clnt_indicator],NULL, clnt_connection, (void *)&clnt_sock[clnt_indicator])<0)
				printf("Thread Error!\n");

			clnt_con[clnt_indicator] = 1;
			cntNum++;
		}

	}
	close(serv_sock);
	return 0;
}

void error_handling(char* message){
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}

int findEmpty(int indicator, int *slot, int s_size){
	int i= indicator;
	while(slot[i]){
		i++;
		if(i == s_size){
			i =0 ;
		}
		if(i == indicator)
			return -1;
	}
	return i;
}


void *clnt_connection(void* arg){
	int* pSock = (int*) arg;
	int sock = *pSock;
	char* command[20];
	char* ptr;
	int str_len;
	char message[BUFSIZE];
	char buf[BUFSIZE];
	int i;

	memset(message,0x00, sizeof(message));
	while(str_len = recv(sock,message,BUFSIZE,0)>0){
		str_len = strlen(message);
		
		ptr = strtok(message, " ");
		i=0;
		while(ptr != NULL){
			command[i] = ptr;
			ptr = strtok(NULL, " ");
			i++;
			if(i > 20)break;
		}

		str_len = strlen(command[0]);
		memset(buf,0x00,sizeof(buf));	
		
		//서버 명령어 처리 

		//로그인 
		if(!strcmp(command[0],"login")){
			printf("login %s/%s\n",command[1],command[2]);

			//로그인 정보 조회

			sprintf(buf,"1");// test form : 모든 로그인 시도 성공 	
			str_len = strlen(buf);
			write(sock,buf,str_len);
			printf("server send c%d:%s\n",sock,buf);
		}

		else if(!strcmp(command[0],"siu")){
			//DB 입력 
		}
	
		else if(!strcmp(command[0],"sid")){
			if(!strcmp(command[5],"zzzz"))   //D_aff null값 처리 
				sprintf(command[5],"");    
			//DB 입력 

		}



		else 

			write(sock,"Undefined commnad!",sizeof("Undefined command!"));		

		memset(message,0x00,sizeof(message));
	}


	for(i=0;i<MAX_CLIENT;i++){
		if(sock == clnt_sock[i]){
#ifdef _DEBUG 
			printf("Client %d is disconnected.\n",i);
#endif
			clnt_con[i] = 0;
			break;
		}
	}

	cntNum--;
#ifdef _DEBUG
	printf("******Replace Clients*********\n Sector : Socket\n");
	for(i=0;i < MAX_CLIENT; i++)
		printf("%d : %d\n",i,clnt_con[i]);
#endif	


	close(sock);	

	return 0;
}

