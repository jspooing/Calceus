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
#include "calceus.h"

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
	char data[12][200];
	char* ptr;
	int str_len;
	char message[BUFSIZE];
	char buf[BUFSIZE];
	int i,j,k;
	int pr_data[5];
	char uid[15];

	pthread_t t_tBend;

	memset(message,0x00, sizeof(message));
	while(str_len = recv(sock,message,BUFSIZE,0)>0){
		str_len = strlen(message);

		printf("message : %s\n",message);

		ptr = strtok(message, "^");
		i=0;
		while(ptr != NULL){
			command[i] = ptr;
			ptr = strtok(NULL, "^");
			i++;
			if(i > 20)break;
		}

		str_len = strlen(command[0]);
		memset(buf,0x00,sizeof(buf));	

		//서버 명령어 처리 

		//로그인 
		if(!strcmp(command[0],"login")){
			printf("login %s %s\n",command[1],command[2]);

			//로그인 정보 조회
			i = checkLogin(command[1],command[2]);

			sprintf(uid,"%s",command[1]);
			sprintf(buf,"%d",i);	
			str_len = strlen(buf);
			write(sock,buf,str_len);
			printf("server send c%d:%s\n",sock,buf);
		}


		// 유저 회원가입 
		else if(!strcmp(command[0],"siu")){
			//DB 입력
			
			
			for(i=0; i <6; i++){
				sprintf(data[i],"%s",command[i+1]);
			}
				DBinsert("USER",data,6);
	
			if(!strcmp(command[6],"2")){
		

				sprintf(data[0],"%s",command[1]);
			    sprintf(data[1],"%s",command[7]);
				sprintf(data[2],"%s",command[8]);
				
				if(!strcmp(data[1],"zzzz"))
				sprintf(data[1],"");
				
				if(!strcmp(data[2],"zzzz"))
				sprintf(data[2],"");


			
				DBinsert("D_DESIGNER",data,3);
			}

		}



		else if(!strcmp(command[0],"test")){
			//write(sock,"test start!",12);
			
			if(pthread_create(&t_tBend,NULL,t_testBackend,(void *)uid)<0){
				printf("t_testBackend err\n");
			}


			write(sock,buf,BUFSIZE);
		}

		else if(!strcmp(command[0],"img1")){
			system("convert /home/chc/calceus/datastream/result.png /home/chc/calceus/datastream/result.bmp");
			getImg(sock,buf,BUFSIZE);


		}
	
		else if(!strcmp(command[0],"designer")){
			

			
			memset(buf,0x00,sizeof(buf));


			if(!strcmp(uid,"js")){

				sprintf(buf,"no\n",4);
			}
			else 
			sprintf(buf,"d_name#99999#08-03,2018#aa#bb#cc#dd\n",sizeof(buf));
		
			write(sock,buf,sizeof(buf));


		}

		else if(!strcmp(command[0],"val")){
				
			sendresult(sock);
			
		}

		else if(!strcmp(command[0],"tst")){

//			for(i=0; i < 10;i++){
//				memset(message,0x00,sizeof(message));
//				str_len = recv(sock,message,BUFSIZE,0);	
//
//				printf("received : %s   ",message);
//
//
//				if(!strcmp(command[0],""))
//					str_len = strlen(message);
//
//				ptr = strtok(message, "^");
//				j=0;
//				while(ptr != NULL){
//					command[j] = ptr;
//					ptr = strtok(NULL, "^");
//					j++;
//					if(j > 20)break;
//				}
//				for(j=0;j<5;j++){
//					sscanf(command[j],"%d",&pr_data[j]);
//				}
//
//
//				inputStream(pr_data,5);
//
//
//
//			}
//



					system("python /home/chc/calceus/analysis.py");
			
			if(pthread_create(&t_tBend,NULL,t_testBackend,(void *)uid)<0){
				printf("t_testBackend err\n");
			}


			while(1){

				if(access("/home/chc/calceus/datastream/content.txt",F_OK)==0)
				break;
			}
			
	write(sock,"dbend\n",sizeof("dbend\n"));
			printf ("send: dbend\n");






		}

		else if (!strcmp(command[0],"order")){

			sprintf(data[0],"%d",getMAX("S_ORDER","o_num")+1);
			sprintf(data[1],"%s",uid);
			sprintf(data[2],"");

			for(i=1 ; i < 6; i ++)
				sprintf(data[i+2],"%s",command[i]);


			//주문에서 가격대를 설정하려면 여기를 바꾸면 됩니다. 

			sprintf(data[8],"0");
			sprintf(data[9],"0");
			


			//////////////////////////////////////////////



			DBinsert("S_ORDER",data,10);

		}

		else if(!strcmp(command[0],"user")){

			if(DBcheck("S_ORDER","d_id","")){

				DBselect_match(buf,"S_ORDER","d_id","",10);
				write(sock,buf,BUFSIZE);
			}

			else 
				write(sock,"no\n",4);


		}

		else if(!strcmp(command[0],"req")){

			sprintf(data[0],"%d",getMAX("REQUST","r_num")+1);
			printf("flag : %s",data[0]);

			for(i=1;i<5;i++)
				sprintf(data[i],"%s",command[i]);

			DBinsert("REQUST",data,5);
		}


		else if(!strcmp(command[0],"io")){
		
			DBselect_match(buf,"S_ORDER","u_id",uid,10);
			write(sock,buf,BUFSIZE);
		
		}
		else if(!strcmp(command[0],"ir")){
			
			
			DBselect_match(buf,"REQUST","o_num",command[1],5);
			write(sock,buf,500);
		
		}

		else if(!strcmp(command[0],"buy")){
			sbuy(command[1],command[2]);
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

		cntNum--;
#ifdef _DEBUG
		printf("******Replace Clients*********\n Sector : Socket\n");
		for(i=0;i < MAX_CLIENT; i++)
			printf("%d : %d\n",i,clnt_con[i]);
#endif	


		close(sock);	

		return 0;
	}

}
