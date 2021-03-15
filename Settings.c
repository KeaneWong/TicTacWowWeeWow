/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe P.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/03/13     */
/* 2021/03/13 Wrote change color and change icon functions. wrote change number	 	*/
/* 2021/03/12 debugging. testing features						 	*/
/* 2021/03/11 Wrote changeIcon function. Modified BOARD and PLAYER structs	*/
/* 2021/03/10 Began file													*/
/**/
/**/
/**/
#include <stdio.h>
#include <stdlib.h>
#include "Settings.h"

void changeIcon(BOARD *myboard,char c, int p)
{
	if(p==1)
	{
		printf("Icon changed to %c\n",c);
		myboard->p1->icon = c;
	}
	else if(p==2)
	{
		printf("Icon changed to %c\n",c);
		myboard->p2->icon = c;
	}
	else
	{
		printf("Invalid icon or player number\n");
	}
}

void changeColor(BOARD *myboard, int colo, int p)//colo is a number. 0 resets to default, 30-37 correspond to a color
{
	if(colo>8||colo<0)
	{
		printf("Invalid color\n");
		return;
	}
	if(p==1)
	{
		if(colo == 0)
		{
			myboard->p1->color = 0;
			return;
		}
		else
		{
			myboard->p1->color = 29+colo;
			return;
		}

	}
	else
	{
		if(colo == 0)
		{
			myboard->p2->color = 0;
			return;
		}
		else
		{
			myboard->p2->color = 29+colo;
			return;
		}

	}

}

void changeNumber(BOARD *myboard, int p)
{
	if(p==1)
	{
	myboard->p1->playNum = 2;
	}
	if(p==2)
	{
	myboard->p2->playNum = 1;
	}
	return;
	
}

