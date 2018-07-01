CC = gcc
CFLAGS = -pthread -lmysqlclient
TARGET = server.exe 

server : server.o server_mysql.o datastream.o
	$(CC) -o $(TARGET) $^ $(CFLAGS)
	rm $^
debug : server.c
	$(CC) -D_DEBUG -o $(TARGET) $^ $(CFLAGS)

server_mysql.o: server_mysql.c
	$(CC) -c $^
	
server.o : server.c
	$(CC) -c $^

datastream.o : datastream.c
	$(CC) -c $^

clean : 
	rm $(TARGET)  
