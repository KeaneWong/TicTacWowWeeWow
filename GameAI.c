/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe P.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/03/13 Added comments and accessors						    */
/* 2021/03/13 completed program. Testing done					 	*/
/* 2021/03/12 debugging. testing features						 	*/
/* 2021/03/11 Debguged pinky. Fixed 3 in a row detection		 	*/
/* 2021/03/09 wrote Pinky. outlined function	 					*/
/* 2021/03/08 Inky and Blinky		 								*/
/* 2021/03/08 began file						 					*/
/**/
/**/
/**/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "GameAI.h"

int Inky(BOARD *myboard)
{
	int size = getSize(myboard);
	for(int i =0;i<size;i++)
	{
		for(int j = 0; j <size; j++)
		{
			if(getSquare(myboard,i,j)  == ' ')
			{
				return i*size + j;
			}
		}
	}
	printf("Error in INKY: no available space\n");
	return -1;
}

int Blinky(BOARD *myboard)
{
	int size = getSize(myboard);
	int found = 0;
	time_t te;
	srand((unsigned) time(&te));//rng tic tac toe 'AI'
	int inRow;
	int inCol;
	int count=0;
	while(!found)
	{
		inRow = rand()%size;
		inCol = rand()%size;
		if(getSquare(myboard,inRow,inCol) == ' ')
		{
			found = 1;
		}
		if(count>120)//probabilistically will hit an available space before getting 120 unless no available spaces.
		{
			return -1;
		}
		count++;
	}
	return (inRow*size+inCol);
}

int Pinky(BOARD *myboard, int p)//the number p is what player pinky is
{
	int size = getSize(myboard);
	//int horiz=0;
    //int vert=0;
    //int diag=0;
    //int diag2=0;
        /*for(int i =0;i<boardSize;i++)//checks all rows and columns centered about the most recent moveand relevant diagonals.
        {
            if(getSquare(myboard,inputRow,i)==icon1)
            {
                horiz++;
            }
            if(getSquare(myboard,i,inputCol)==icon1)
            {
                vert++;
            }
            if(getSquare(myboard,i,i)==icon1)
            {
                diag++;
            }
            if(getSquare(myboard,i,boardSize-1-i)==icon1)
            {
                diag2++;
            }
        }
        if(diag2==boardSize||diag==boardSize||horiz==boardSize||vert==boardSize)
        {
        	
        }*/
	char icon;

	if(p==1)
	{
		icon= getIcon(myboard,2);//getting icon of opponent
	}
	else if(p==2)
	{
		icon = getIcon(myboard,1);//getting icon of p1 if pinky is p2
	}
	else
	{
		printf("Invalid AI playernumber \n");
		icon = 'X';
	}
	printf("ICON IS %c\n",icon);
	

    for(int i =0;i<size;i++)
    {
    	int vert = 0;
    	int horiz = 0;//counter for numbers of icons
    	for(int j=0;j<size;j++)
    	{
    		if(getSquare(myboard,i,j)==icon)
    		{
    			horiz++;
    		}
    		if(getSquare(myboard,j,i)==icon)
    		{
    			vert++;
    		}

    	}
    	if(horiz == size-1)//implies about to get a 3 in a row for that row
    	{
    		for(int q = 0; q < size; q++)
    		{
    			if(getSquare(myboard,i,q)==' ')//return first available space
    			{
    				return (i*size+q);
    			}
    		}
    	}
    	if(vert == size-1)
    	{
    		for(int q = 0; q < size; q++)
    		{
    			if(getSquare(myboard,q,i)==' ')
    			{
    				return (q*size+i);
    			}
    		}

    	}
    }
    int diag=0;
    int diag2=0;
    for(int l = 0; l < size;l++)
    {
    	if(getSquare(myboard,l,l) == icon)
    	{
    		diag++;
    	}
    	if(getSquare(myboard,l,size-1-l)==icon)
    	{
    		diag2++;
    	}
    }
    if(diag == size-1)
    {
	    for(int l = 0; l < size;l++)
	    {
	    	if(getSquare(myboard,l,l) ==' ')
	    	{
	    		return l*size+l;
	    	}
	    }
    }
    if(diag2 == size-1)
    {
	    for(int l = 0; l < size;l++)
	    {
	    	if(getSquare(myboard,l,size-1-l) ==' ')
	    	{
	    		return l*size+(size-1-l);
	    	}
	    }
    }

    //if it made it to this point then theres no 3 in a row about to happen. Default to random/blinky
    printf("Using random\n");
    return Blinky(myboard);

}

int Clyde(BOARD *myboard)
{
	return 1;
}


char getRow(BOARD *myboard, int in)//equation to get row from output
{
	int size = myboard->size;
	return ('a'+(in/size));
}
char getCol(BOARD *myboard,int in)//equation to get col from output
{
	int size = myboard->size;
	return (in%size + '1');
}









