OBJS = main.o main_classes.o auxillary.o
CC = g++
CFLAGS = -Wall -c 
LFLAGS = -Wall

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o : main.cpp main_classes.h auxillary.h userinterface.h
	$(CC) $(CFLAGS) main.cpp

main_classes.o : main_classes.cpp main_classes.h auxillary.h
	$(CC) $(CFLAGS) main_classes.cpp

auxillary.o : auxillary.cpp auxillary.h
	$(CC) $(CFLAGS) auxillary.cpp
