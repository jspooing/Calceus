#include<stdio.h>
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

	mysql_free_result(sql_result); 
	mysql_close(connection);


	if(!strcmp(pw,correct)){
		printf("login sucess \n");
		return 1;
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

	sprintf(query,"update S_ORDER set d_id = '%s' where o_num = %s ",id,num );


	printf("%s",query);


	fflush(stdout);
	query_stat = mysql_query(connection,query);


	mysql_close(connection);
	return 1;


}
