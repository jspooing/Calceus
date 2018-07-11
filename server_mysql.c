#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"/usr/include/mysql/mysql.h"

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "calceus"
#define CHOP(x) x[strlen(x)-1] = NULL


typedef struct _Matchtable{
	char user[15];
	char designer[15];
	int size,num;
	char wide[5];
	char color[15];
	char detail[200];
	char sex;
}Match;

int DBinsert(char* table , char data[][200], int nData){

	MYSQL *connection = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	char query[255];
	int i;

	mysql_init(&conn);
	connection= mysql_real_connect(&conn,DB_HOST,DB_USER,DB_PASS,DB_NAME,
			3306,(char *)NULL, 0 );

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s",mysql_error(&conn));
		return -1;
	}

	sprintf(query,"insert into %s values(",table );
	for(i=0; i<nData; i++){
		sprintf(query,"%s\'%s\',",query,data[i]);
	}

	CHOP(query);

	sprintf(query,"%s)",query);
	
	printf("DBinset : ");
	printf("%s\n",query);


	fflush(stdout);
	query_stat = mysql_query(connection,query);


	mysql_close(connection);
	return 1;

}


int checkLogin(char id[15],char pw[15])
{
	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];
	int type;

	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}


	sprintf(query, "select * from USER where id = '%s'", id);

	query_stat = mysql_query(connection, query);

	if(query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);


	sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL)return 0;

	sprintf(correct,"%s",sql_row[2]);
	type = (int)sql_row[5];

	mysql_free_result(sql_result); 
	mysql_close(connection);
	

	type = atoi(type);

	if(!strcmp(pw,correct)){
		printf("login sucess \n");
		return type;
	}
	else{
		printf("worng pw \n");
		return 0;
	}


}

int DBcheck(char * table, char * column, char * value){

	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];

	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query,"select * from %s where %s  = '%s'",table,column,value);

	query_stat = mysql_query(connection,query);

	if(query_stat != 0)
	{

		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);


	sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL)return 0;
	else return 1;


}
int DBcheck_designer(char * value){
	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];

	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query,"select * from S_ORDER where d_id != '' and u_id = '%s'",value);

	query_stat = mysql_query(connection,query);

	if(query_stat != 0)
	{

		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);


	sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL)return 0;
	else return 1;


}



int DBselect_match(char * buf,char* table ,char *column ,char* value, int dnum){
	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];
	int i;


	printf("DB_select : ");
	fflush(stdout);
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query,"select * from %s where %s = '%s'",table,column,value);

	printf("%s\n",query);
	fflush(stdout);

	query_stat = mysql_query(connection,query);

	if(query_stat != 0)
	{

		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);


	while((	sql_row = mysql_fetch_row(sql_result))!=NULL){

		for(i=0; i < dnum; i++)
			sprintf(buf,"%s%s#",buf,sql_row[i]);
		CHOP(buf);
		sprintf(buf,"%s/",buf);
		



		fflush(stdout);
	}
	CHOP(buf);
	sprintf(buf,"%s\n",buf);	
	printf("%s",buf);
	return 0;
}


int DBselect_user(char* buf,char* value){
	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];
	int i;


	printf("DB_select : ");
	fflush(stdout);
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query,"select * from S_ORDER join USER on u_id = id  where d_id = '%s'",value);

	printf("%s\n",query);
	fflush(stdout);

	query_stat = mysql_query(connection,query);

	if(query_stat != 0)
	{

		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);


	while((	sql_row = mysql_fetch_row(sql_result))!=NULL){


		sprintf(buf,"%s#%s#%s#%s#%s#%s#%s#",sql_row[1],sql_row[7],sql_row[13],sql_row[3],sql_row[4],sql_row[5],sql_row[6]);
		CHOP(buf);
		sprintf(buf,"%s/",buf);
	}
	CHOP(buf);
	sprintf(buf,"%s\n",buf);	
	printf("%s",buf);
	return 0;

}

int DBselect_designer(char* buf,char* value){
	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];
	int i;


	printf("DB_select : ");
	fflush(stdout);
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query,"select D.id,D.Mnum,R.r_date,D.id,D.aff,D.career,D.intro from  D_DESIGNER as D, S_ORDER as O,REQUST as R where O.d_id = D.id and O.d_id = R.d_id and O.u_id ='%s'",value);

	printf("%s\n",query);
	fflush(stdout);

	query_stat = mysql_query(connection,query);

	if(query_stat != 0)
	{

		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);

	while((	sql_row = mysql_fetch_row(sql_result))!=NULL){

		for(i=0; i < 7; i++)
			sprintf(buf,"%s%s#",buf,sql_row[i]);
		CHOP(buf);
		sprintf(buf,"%s/",buf);
		



		fflush(stdout);
	}
	CHOP(buf);
	sprintf(buf,"%s\n",buf);	
	printf("%s",buf);
	return 0;

}

int DBselect_olist(char* buf){
	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];
	int i;


	printf("DB_select : ");
	fflush(stdout);
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query,"select u_id from S_ORDER where d_id = ''");

	printf("%s\n",query);
	fflush(stdout);

	query_stat = mysql_query(connection,query);

	if(query_stat != 0)
	{

		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);

	memset(buf,0x00,sizeof(buf));
	while((	sql_row = mysql_fetch_row(sql_result))!=NULL){

		sprintf(buf,"%s%s#",buf,sql_row[0]);
	}
	CHOP(buf);
	sprintf(buf,"%s\n",buf);	
	printf("%s",buf);
	return 0;



}

int getMAX(char * table ,char * col){

	MYSQL *connection  = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	int stat =0;
	char query[255];
	char correct[15];

	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return -1;
	}


	sprintf(query, "select max(%s) from %s", col,table);

	query_stat = mysql_query(connection, query);

	if(query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return -1;
	}



	sql_result = mysql_store_result(connection);


	sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL)return 0;

	sprintf(correct,"%s",sql_row[0]);
	return atoi(correct);

	mysql_free_result(sql_result); 
	mysql_close(connection);

}

int sbuy(char* num,char * id){

	MYSQL *connection = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	char query[255];
	int i;

	mysql_init(&conn);
	connection= mysql_real_connect(&conn,DB_HOST,DB_USER,DB_PASS,DB_NAME,
			3306,(char *)NULL, 0 );

	if(connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s",mysql_error(&conn));
		return -1;
	}

	sprintf(query,"update S_ORDER set d_id = '%s' where u_id = %s",id,num );


	printf("%s",query);


	fflush(stdout);
	query_stat = mysql_query(connection,query);


	mysql_close(connection);
	return 1;


}
