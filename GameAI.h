/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe P.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/03/13 Added accessor functions and comments   */
/* 2021/03/13 completed program. Testing done					 	*/
/* 2021/03/12 debugging. testing features						 	*/
/* 2021/03/10 Pinky outline. Changed parameters and arguments.		*/
/* 2021/03/09 outlined main variables. wrote Inky and Blinky function 	*/
/**/
/**/
/**/
#ifndef GAMEAI_H
#define GAMEAI_H

#include "GameBoard.h"


//All of the AI will return their turns in the form of an int, that signifies a square in a 3x3 grid (labeled 0-8). 
//This can be converted to an input row and col according to a formula, row = output/size+'a' and col = output%size+'1'

int Inky(BOARD *myboard); 		//AI that gets the simplest move

int Blinky(BOARD *myboard);		//AI that gets random move. Stops looking after 120 tries. Very unlikely itll hit no available spaces

int Pinky(BOARD *myboard, int p);	//AI that cuts off 3 in a row based on 2 in a row. p is which player pinky is. Defaults to blinky if no cutoff available

int Clyde(BOARD *myboard);		//unimplemented


char getRow(BOARD *myboard, int in);//equation to get row from output

char getCol(BOARD *myboard,int in);//equation to get col from output



#endif
