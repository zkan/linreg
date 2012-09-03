#
#	Makefile for compiling all code in this directory.
#	Author: Kan Ouivirach
# 
CFLAGS = -g -Wall
CC = g++ $(CFLAGS)
PROG = linreg
all: $(PROG)

# program to test the function that gets the list of files under a specific folder
linreg.o: linreg.cc linreg.h
	$(CC) -c linreg.cc

linreg: main.o linreg.o
	$(CC) main.o linreg.o -o linreg

clean:
	rm *.o $(PROG)







