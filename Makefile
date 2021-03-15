#Makefile: TicTacWowWeeWow
#03/11/21

CC = gcc
DEBUG = -g -DDEBUG
#DEBUG =  -O2  -DNDEBUG
CFLAGS = -Wall -ansi -std=c99 -c
LFLAGS = -Wall
CFLAGSD = -Wall -ansi -std=c99 $(DEBUG) -c
LFLAGSD = -Wall $(DEBUG)
all: TicTacWowWeeWow

clean:
	rm -f *.o
	rm -f TicTacWowWeeWow
	rm -f *.a

GameBoard.o: GameBoard.h GameBoard.c
	$(CC) $(CFLAGS) GameBoard.c -o GameBoard.o

GameAI.o: GameBoard.h GameAI.h GameAI.c
	$(CC) $(CFLAGS) GameAI.c -o GameAI.o

Settings.o: Settings.c Settings.h GameBoard.h
	$(CC) $(CFLAGS) Settings.c -o Settings.o

TicTacWowWeeWow.o: TicTacWowWeeWow.c 
	$(CC) $(CFLAGS) TicTacWowWeeWow.c -o TicTacWowWeeWow.o

TicTacWowWeeWow: libGameFunctions.a TicTacWowWeeWow.o
	$(CC) $(LFLAGS)  TicTacWowWeeWow.o -o TicTacWowWeeWow -L. -lGameFunctions

libGameFunctions.a: GameBoard.o GameAI.o Settings.o
	ar rcs libGameFunctions.a GameBoard.o GameAI.o Settings.o

libs: libGameFunctions.a
