INC = ../inc
OBJS = main.o main_classes_v2.o auxillary.o ui.o
CC = g++
CFLAGS = -Wall -c 
LFLAGS = -Wall

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o : main.cpp $(INC)/main_classes_v2.h $(INC)/auxillary.h $(INC)/ui.h
	$(CC) -I$(INC) $(CFLAGS) main.cpp

ui.o : ui.cpp $(INC)/ui.h $(INC)/main_classes_v2.h $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) ui.cpp

main_classes_v2.o : main_classes.cpp $(INC)/main_classes_v2.h $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) main_classes_v2.cpp

auxillary.o : auxillary.cpp $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) auxillary.cpp
