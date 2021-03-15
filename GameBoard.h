/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe P.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/03/13 Organized code and polished comments    */
/* 2021/03/13 completed program. Testing done					 	*/
/* 2021/03/12 debugging. testing features						 	*/
/* 2021/03/11 Added replay support						 			*/
/* 2021/03/10 Finished Move takeback support						*/
/* 2021/03/09 outlined necessary accessor functions. outlined settings variables 	*/
/* 2021/03/09 Outlined structure for takeback support			 					*/
/* 2021/03/08 created structs for player and game board		 					*/
/* 2021/03/08 began file						 					*/
/**/
/**/
/**/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <stdio.h>
#include <stdlib.h>
#define DEFAULTSIZE 3

typedef struct Move //a node in a dll used to track moves.
{
	struct Move* next;
	struct Move* prev;
	int moveR;
	int moveC;
} Move;

typedef struct{
	char icon;
	int playNum;
	int color;//a color code that corresponds to a color from the ansi escape sequences labeled from 1-8, and 0 signifies default color


} PLAYER;

typedef struct 
{
	char **Table;
	int size;
	Move *p1Move;//movelist
	Move *p2Move;//movelist of p2
	PLAYER *p1;
	PLAYER *p2;
	int curTurn;//tracks which player did last move. 1 for player 1, 2 for player 2

} BOARD;

int setBoard(BOARD *myboard, int inputRow, int inputCol);//sets square at coordinate input and increments to next turn automaitcally. Takes inputs [rowletter][colnumber] such as 'A2' or 'C3'
//returns 0 for error, 1 for no winner or incomplete game, or 2 for a winner. 


char getSquare(BOARD *myboard, int row, int col);		//accessor function that returns the icon at location row,col. Does not modify board

int getSize(BOARD *myboard);										//Returns size of board


int checkWin(BOARD *myboard, int inputRow, int inputCol);			//Checks board for win conditions. 0 indicates error, 1 indicates no winner, 2 indicates win

int getColor(BOARD *myboard, int p);								//returns color code. 0 is default and 1-8 correspond to a ansi color code. Only input 0-8 for input p


//makes a new gameboard and returns it. INitializes board icons to a default X and O for player 1 and 2 respectively. Many features of this program work with variable size HOWEVER the SAVE REPLAY function is 3x3 ONLY. Can otherwise be easily expanded to accomodate indefinite size. 
BOARD *MakeBoard(int size, char icon1, char icon2);


int gameBoard(BOARD *myboard,char input[2]);//tracks game, returns a 2 for a victory, 0 if invalid input, and a 1 if a draw. CHANGES CURTURN TO NEXT TURN AUTOMATICALLY.

//void goBack(BOARD *myboard);//undoes last move. Unimplemented in favor of RemoveLastMove


//void ResetGameBoard(BOARD *myboard);//resets gameboard. Turns all squares to ' ' and empties move list. Unused

void printBoard(BOARD *myboard);							//prints board to console

int getCurTurn(BOARD *myboard);								//gets the current turn, 1 or 2.

char getIcon(BOARD *myboard, int p);						//returns icon of player p. used as accessor

void clearBoard(BOARD *myboard);							//clears game board.Turns alls quares to ' ' and empties move list

void deleteBoard(BOARD *myboard); 							//frees game board, associated players, and all game data and move list.

void addMove(BOARD *myboard,int playernum, int inputRow, int inputCol);		//Adds a move to the move list. Inputrow and inputcol are numbers starting from 0

//char getLastMove(myboard, int playernum);//unused function

int removeLastMove(BOARD *myboard, int playernum);	//removes last move from pmove and removes from the board. Returns 0 if the movelist of that player is empty, i.e null

void saveReplay(BOARD *myboard,char *filename, int play1, int play2, int winner);	//play1 and play 2 are for the players. 0 indicates human, 1-4 is an AI. Winner is who won. Prints a replay and save data to a file, filename. 
void fprintBoard(BOARD *myboard, FILE *fp, char table[DEFAULTSIZE][DEFAULTSIZE]);	//prints table (not board) to the file. The myboard input is only there to access variables like size and icon and such. This is a private function designed only to be used in saveReplay

void fprintcolor(int colorCode,FILE *fp);//private function designed exlusively to print a color string, in quotations, to file fp based on an input code. That is all.

#endif
