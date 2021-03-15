/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe P.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/03/13 Finished program. Added comments					    */
/* 2021/03/13 Modified existing structs. Testing done			 	*/
/* 2021/03/09 Outlined main variables. wrote function outlines 		*/
/**/
/**/
/**/
#ifndef SETTINGS_H
#define SETTINGS_H
#include "GameBoard.h"

void changeIcon(BOARD *myboard, char c, int p);			//Changes the icon of player p to char c.

void changeColor(BOARD *myboard, int colo, int p);		//Changes color code of player p icon to integer colo

void changeNumber(BOARD *myboard,int p);				//changes the number of player 1 to player 2 and vice versa. Largely unused








#endif
