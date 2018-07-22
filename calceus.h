#include"/usr/include/mysql/mysql.h"
int DBinsert(char *, char[][100], int);
int DBdelete(char*, char* , char *);
int inputStream(int* data, int num);
void* t_testBackend(void* data);
int checkLogin(char*, char*);
int DBcheck(char *, char *, char *);
int DBcheck_designer(char *value);
int getImg(int ,char *, int );
int DBselect_match(char * buf ,char * table,char *,char*,int);
int DBselect_user(char* buf, char* value);
int DBselect_userlist(char* buf, char* value);
int DBselect_usermain(char* buf, char* value);
int DBselect_designer(char* buf, char* value,int fn);
int DBselect_click(char* buf, char* id );
int sqltest();
int getMAX(char * ,char *);
int sbuy(char *, char *,int);

void sendresult(int);


