CC = g++
INCLUDES = -I/usr/include/mysql
LIBS = -lmysqlclient

all:main

main.o: main.cpp
	$(CC) -g -c $(INCLUDES) main.cpp

main: main.o
	$(CC) -g -o main main.o $(LIBS)

clean:
	rm -rf main.o main *~