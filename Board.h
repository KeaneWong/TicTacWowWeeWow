#ifndef BOARD_H
#define BOARD_H
#include <stdlib.h>

typedef struct{
	char icon;
	int playNum;
	int color;

} PLAYER;


typedef struct 
{
	char **Table;
	PLAYER *p1;
	PLAYER *p2;
	int curTurn;
} BOARD

void setBoard(BOARD myboard, int row, int col)
{
	if(curTurn = 1)//player 1
	{
		myboard->Table[row][col] = myboard->p1->icon;
		myboard->curTurn = 2;
	}
	else
	{
		myboard->Table[row][col] = myboard->p2->icon;
		myboard->curTurn = 1;
	}
}
char getSquare(BOARD myboard, int row, int col)
{

}

#endif