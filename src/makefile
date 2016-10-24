INC = ../inc
OBJS = main_v2.o main_classes_v2.o auxillary.o ui_v2.o
CC = g++
CFLAGS = -Wall -c 
LFLAGS = -Wall

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main_v2.o : main_v2.cpp $(INC)/main_classes_v2.h $(INC)/auxillary.h $(INC)/ui.h
	$(CC) -I$(INC) $(CFLAGS) main_v2.cpp

ui_v2.o : ui_v2.cpp $(INC)/ui.h $(INC)/main_classes_v2.h $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) ui_v2.cpp

main_classes_v2.o : main_classes_v2.cpp $(INC)/main_classes_v2.h $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) main_classes_v2.cpp

auxillary.o : auxillary.cpp $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) auxillary.cpp
