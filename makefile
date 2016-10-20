INC = ./inc
OBJS = main.o main_classes.o auxillary.o
CC = g++
CFLAGS = -Wall -c 
LFLAGS = -Wall

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o : main.cpp $(INC)/main_classes.h $(INC)/auxillary.h $(INC)/userinterface.h
	$(CC) -I$(INC) $(CFLAGS) main.cpp

main_classes.o : main_classes.cpp $(INC)/main_classes.h $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) main_classes.cpp

auxillary.o : auxillary.cpp $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) auxillary.cpp
