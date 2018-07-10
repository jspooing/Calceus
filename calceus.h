#include"/usr/include/mysql/mysql.h"
int DBinsert(char *, char[][100], int);
int inputStream(int* data, int num);
void* t_testBackend(void* data);
int checkLogin(char*, char*);
int DBcheck(char *, char *, char *);
int getImg(int ,char *, int );
int DBselect_match(char * buf ,char * table,char *,char*,int);
int sqltest();
int getMAX(char * ,char *);
int sbuy(char *, char *);
void sendresult(int);


