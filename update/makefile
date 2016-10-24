##------------------------------------------------------------------
##Author: Jconstan
##makefile to generate executable 
##main_class_v2 and main_v2 to launch a tracker for CASH only expenses 
##uses the original ui and auxillary.cpp from src directory
##-------------------------------------------------------------------

INC = ../inc
SRC = ../src
OBJS = main_v2.o main_classes_v2.o auxillary.o ui.o
CC = g++
CFLAGS = -Wall -c 
LFLAGS = -Wall

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main_v2.o : main_v2.cpp main_classes_v2.h $(INC)/auxillary.h $(INC)/ui.h
	$(CC) -I$(INC) $(CFLAGS) main_v2.cpp

ui.o : $(SRC)/ui.cpp $(INC)/ui.h main_classes_v2.h $(INC)/auxillary.h
	$(CC) -I$(INC) -I. $(CFLAGS) $(SRC)/ui.cpp

main_classes_v2.o : main_classes_v2.cpp main_classes_v2.h $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) main_classes_v2.cpp

auxillary.o : $(SRC)/auxillary.cpp $(INC)/auxillary.h
	$(CC) -I$(INC) $(CFLAGS) $(SRC)/auxillary.cpp
