#include"/usr/include/mysql/mysql.h"
int DBinsert(char *, char[][100], int);
int inputStream(int* data, int num);
void* t_testBackend(void* data);
int checkLogin(char*, char*);
int DBcheck(char *, char *, char *);
int getImg(int ,char *, int );
int DBselect_match(char * buf ,char *,char*,int);
int sqltest();
