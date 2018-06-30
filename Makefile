CC = gcc
CFLAGS = -pthread
TARGET = server.exe 

server : server.o 
	$(CC) -o $(TARGET) $^ $(CFLAGS)
	rm $^
debug : server.c
	$(CC) -D_DEBUG -o $(TARGET) $^ $(CFLAGS)
	
server.o : server.c
	$(CC) -c $^

clean : 
	rm $(TARGET)  
