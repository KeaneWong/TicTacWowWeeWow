/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe P.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/03/13 Testing complete. Debugged fully.            */
/* 2021/03/13 Began testing. Added debug flags and valgrind					 	*/
/* 2021/03/12 Wrote fprint function for the board		 	*/
/* 2021/03/11 Wrote takeback and remove last move functions	 	*/
/* 2021/03/10 Finished gameboard and set. Finished debugging		*/
/* 2021/03/09 Added beginnings of takeback support. wrote printboard function 	*/
/* 2021/03/09 wrote accessor functions and set functions	 					*/
/* 2021/03/08 Wrote 'MakeBoard' and SetBoard		 					*/
/* 2021/03/08 began file						 					*/
/**/
/**/
/**/
#include "GameBoard.h"
#include <time.h>



BOARD *MakeBoard(int size, char icon1, char icon2){

	char **table;
    table = malloc(size* sizeof(*table));
    for (int i = 0; i < size; i++) {
  	table[i] = malloc(size * sizeof(table[0]));
	}
	for(int j =0;j<size;j++)//allocating memory and initializing to ' '  in all squares
    {   
        for(int k=0;k<size;k++)
        {   
            table[j][k]=' ';
        }
    }
    BOARD *myBoard = (BOARD*)malloc(sizeof(BOARD));//allocating board memory for struct.
 
    PLAYER *myplay1 = (PLAYER*)malloc(sizeof(PLAYER));//allocating players
    PLAYER *myplay2 = (PLAYER*)malloc(sizeof(PLAYER));
    myplay1->playNum = 1;//default settings. Note that size technically takes more than 3 but some features of this program (basically just savereplay) requires exactly size 3
    myplay2->playNum = 2;
    myplay1->icon = 'X';
    myplay2->icon = 'O';
    myplay1->color = 0;
    myplay2->color=0;

    myBoard->Table = table;
    myBoard->size = size;
    myBoard->p1 = myplay1;
    myBoard->p2 = myplay2;
    myBoard->curTurn = 1;
    myBoard->p1Move = NULL;//empty move list is NULL to signify the head
    myBoard->p2Move=NULL;
    return myBoard;
}



int gameBoard(BOARD *myBoard,char input[2])//takes input in for of [rowletter][colnumber]
{
    int inputRow;
	int boardSize = myBoard->size;
    if((input[0]<'z' && input[0]>='a') || (input[0]<'Z' && input[0]>='A') )//converting letters into row number
    {
        if(input[0]<'z'&& input[0]>='a')//checking if lower case
        {
            inputRow = input[0]-'a';
        }
        else
        {
            inputRow = input[0]-'A';
        }
    }
    else
    {
        printf("Invalid Row\n");
        return 0;
    }
    if(inputRow>=boardSize||inputRow<0)//checking if the row is in bounds
    {

        printf("Row out of bounds\n");
        return 0;
    }

    int inputCol = input[1]-'1'; //turning the char into an integer that can be used for column index
    if (inputCol>=boardSize || inputCol <0)//checking to be in bounds
    {
        printf("Error. Invalid column\n");
        return 0;
    }


    setBoard(myBoard,inputRow, inputCol);
    int temp = checkWin(myBoard,inputRow, inputCol);
    if(temp == 2)//checking for win conditions
    {
    	int turn = getCurTurn(myBoard);
    	turn = (turn==1) ? 2:1;
    	printf("Winner is player %d!\n",turn);//prints current winner
    	return 2;
    }
    if(temp == 0)
    {
    	printf("ERROR: INVALID INPUT\n");
    }
return 1;//if there are no errors and no winners return 1
}



int checkWin(BOARD *myboard, int inputRow, int inputCol)//0 indicates error, 1 indicates no winner, 2 indicates win
{
	

    int turn;//check last move
    if(myboard->curTurn ==1)//checking most recent turn for win condition.
    {
    	turn = 2;
    }
    if(myboard->curTurn ==2)
    {
    	turn =1;
    }
    int boardSize = myboard->size;
    int icon1 = myboard->p1->icon;
    int icon2 = myboard->p2->icon;
    if(turn == 1)
    {
    int horiz=0;
    int vert=0;
    int diag=0;
    int diag2=0;
        for(int i =0;i<boardSize;i++)//checks all rows and columns centered about the most recent moveand relevant diagonals.
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
        if(diag2==boardSize||diag==boardSize||horiz==boardSize||vert==boardSize)//Checks win condition based on any of the possibilities.
        {
        	printf("Winner!\n");
        	return 2;//signals a win
        }
        else 
        {
		#ifdef DEBUG
        	printf("Good move\n");
        #endif
			return 1;//signals no win
        }
    }
    if(turn == 2)
    {
    int horiz=0;
    int vert=0;
    int diag=0;
    int diag2=0;
        for(int i =0;i<boardSize;i++)//checks all rows and columns centered about the most recent moveand relevant diagonals.
        {
            if(getSquare(myboard,inputRow,i)==icon2)
            {
                horiz++;
            }
            if(getSquare(myboard,i,inputCol)==icon2)
            {
                vert++;
            }
            if(getSquare(myboard,i,i)==icon2)
            {
                diag++;
            }
            if(getSquare(myboard,i,boardSize-1-i)==icon2)
            {
                diag2++;
            }
        }
        if(diag2==boardSize||diag==boardSize||horiz==boardSize||vert==boardSize)
        {
        printf("Winner!\n");
        return 2;//signals a win
        }
        else
        {
		#ifdef DEBUG
        	printf("Good move\n");
        #endif
		return 1;//signals no win

        }
    }
    printf("Invalid turn\n");
    return 0;
}





int setBoard(BOARD *myboard, int inputRow, int inputCol)//sets square at coordinate input and increments to next turn. return 0 for failure due to occupied space, return 1 for success
{


    //setting board square
	if(myboard->curTurn == 1)//player 1
	{
		if(getSquare(myboard,inputRow,inputCol)!=' ')//return 0 and dont increment to next turn if unsuccessful set
		{
			return 0;//error, occupied space
		}
		myboard->Table[inputRow][inputCol] = myboard->p1->icon;
		myboard->curTurn = 2;
		addMove(myboard,1, inputRow, inputCol);
		return 1;//successful set
	}
	else			//player 2
	{
		if(getSquare(myboard,inputRow,inputCol)!=' ')
		{
			return 0;
		}
		myboard->Table[inputRow][inputCol] = myboard->p2->icon;
		myboard->curTurn = 1;
		addMove(myboard,2, inputRow, inputCol);
		return 1;//successful set
	}
}

char getSquare(BOARD *myboard, int inputRow, int inputCol)
{
	
				//self explanatory function
    return myboard->Table[inputRow][inputCol];
}


void printBoard(BOARD *myboard)
{
	int boardSize = myboard->size;
	int defaultColor1 = myboard->p1->color;
	int defaultColor2 = myboard->p2->color;
	char icon1 = myboard->p1->icon;
	char icon2 = myboard->p2->icon;


    int charIndex = boardSize+'A'-1;	//The outside labeling on the side of the board, corresponding to Row
    int size=boardSize;
    int colorIcon = 0;
    if(getSquare(myboard,boardSize-1,0)==icon1)//checking which icon it is so we know which color to use
    {
        colorIcon=defaultColor1;
    }
    else if (getSquare(myboard,boardSize-1,0)==icon2)
    {
        colorIcon=defaultColor2;
    }
    printf("%c \x1b[%dm%c\x1b[0m",(char)charIndex,colorIcon,getSquare(myboard,boardSize-1,0));//Stateemnt to set color and immediately reset with ansi codes

    for(int u = 1; u < boardSize; u++)//because the tictactoe thing is typically starts with out an '----' row we need to add this first loop for the first column
    {
        //colorIcon = 0;
        if(getSquare(myboard,boardSize-1,u)==icon1)
        {
            colorIcon=defaultColor1;
        }
        else if (getSquare(myboard,boardSize-1,u)==icon2)
        {
            colorIcon=defaultColor2;
        }
        printf("|\x1b[%dm%c\x1b[0m",colorIcon,getSquare(myboard,boardSize-1,u));
    }
    printf("\n  ");
    size--;
    for(int i =1; i < boardSize; i++)	//main loop body
    {
        for(int j = 0; j<boardSize*2-1;j++)	//Board separator
        {
            printf("-");
        }
        printf("\n");
        //colorIcon=0;
        if(getSquare(myboard,size-i,0)==icon1)
        {
            colorIcon=defaultColor1;		//color escape sequences again
        }
        else if (getSquare(myboard,size-i,0)==icon2)
        {
            colorIcon=defaultColor2;
        }
        printf("%c \x1b[%dm%c\x1b[0m",(char)(--charIndex),colorIcon,getSquare(myboard,size-i,0));
for(int k = 1; k < boardSize;k++)
        {
            //colorIcon=0;
        if(getSquare(myboard,size-i,k)==icon1)
        {
            colorIcon=defaultColor1;
        }
        else if (getSquare(myboard,size-i,k)==icon2)
        {
            colorIcon=defaultColor2;
        }   
            printf("|\x1b[%dm%c\x1b[0m",colorIcon,getSquare(myboard,size-i,k));
        }
        printf("\n  ");

    }
    for(int e = 1; e<=boardSize;e++)//loop to print out column markers
    {
        printf("%d ",e);
    }
    printf("\n");
    //printf("C %c|%c|%c\n",table[2][0],table[0][1],table[0][2]);
    //printf("  -----\n");
    //printf("B %c|%c|%c\n",table[1][0],table[1][1],table[1][2]);
    //printf("  -----\n");
    //printf("A %c|%c|%c\n",table[0][0],table[2][1],table[2][2]);
    //printf("  1 2 3\n");
}




void clearBoard(BOARD *myboard)
{
	//int boardSize = myboard->size;
	/*for(int i =0;i<boardSize;i++)
	{
		for(int j = 0; j < boardSize;j++)
		{
			myboard->Table[i][j] = ' ';
			myboard->curTurn = 1;

		}
	}
	Move *pp1 = myboard->p1Move;
	Move *pp2 = myboard->p2Move;
	while(pp1!=NULL)
	{
		printf("removing1\n");
		Move *temp = pp1->prev;
		//temp->next = NULL;
		free(pp1);
		pp1 = temp;//should leave us with just null
	}
	while(pp2!=NULL)
	{
		printf("removing2\n");
		Move *temp = pp2->prev;
		//temp->next = NULL;//set this pointer to null
		free(pp2);
		pp2 = temp;//should leave us with just null
	}*/
	int temp1=1;
	while(temp1!=0)	//simply removes the last move over and over until it is empty
	{
		temp1 = removeLastMove(myboard,1);
	}
	int temp2=1;
	while(temp2!=0)
	{
		temp2 = removeLastMove(myboard,2);
	}
	myboard->curTurn=1;

}

void deleteBoard(BOARD *myboard)
{

	int boardSize = myboard->size;
	for (int i = 0; i < boardSize; i++) //Starts by freeing the table columns, then the table itself
	{
  	free(myboard->Table[i]);
	}
	free(myboard->Table);
	myboard->Table = NULL;
	Move *pp1 = myboard->p1Move;			//Sets the move list and frees each move one by one until it is cleared out
	Move *pp2 = myboard->p2Move;
	while(pp1!=NULL)
	{
		Move *temp = pp1->prev;
		//temp->next = NULL;
		free(pp1);
		pp1 = temp;//should leave us with just null
	}
	while(pp2!=NULL)
	{
		Move *temp = pp2->prev;
		//temp->next = NULL;//set this pointer to null
		free(pp2);
		pp2 = temp;//should leave us with just null
	}
	myboard->p1Move = NULL;
	myboard->p2Move = NULL;
	free(myboard->p1);//deleting associated players
	free(myboard->p2);
	free(myboard);  //finally deleting board
	myboard=NULL;//setting to NULL
}


int getCurTurn(BOARD *myboard)
{
	return myboard->curTurn;
}

char getIcon(BOARD *myboard, int p)//function that gets icon of player p
{
	if(p==1)
	{
		return myboard->p1->icon;
	}
	else
	{
		return myboard->p2->icon;
	}
}

int getColor(BOARD *myboard, int p)//function that gets icon of player p
{
	if(p==1)
	{
		return myboard->p1->color;
	}
	else
	{
		return myboard->p2->color;
	}
}


void addMove(BOARD *myboard,int playernum, int inputRow, int inputCol)
{
	Move *newMove = (Move *) malloc(sizeof(Move));
	newMove->moveR = inputRow;
	newMove->moveC = inputCol;
	newMove->next = NULL;
	if(playernum ==1)
	{
		if(myboard->p1Move == NULL)//if no moves in the list
		{
			newMove->prev = NULL;
			myboard->p1Move = newMove;
		}
		else//set new p1move and set the prev and next pointers
		{
			myboard->p1Move->next = newMove;
			newMove->prev = myboard->p1Move;
			myboard->p1Move = newMove;
		}
		printf("Adding move %d %d\n",inputRow,inputCol);
	}
	if(playernum ==2)
	{
		if(myboard->p2Move == NULL)//if no moves in the list
		{
			newMove->prev = NULL;
			myboard->p2Move = newMove;
		}
		else//set new p1move and set the prev and next pointers
		{
			myboard->p2Move->next = newMove;
			newMove->prev = myboard->p2Move;
			myboard->p2Move = newMove;
		}
		#ifdef DEBUG
		printf("Adding move %d %d\n",inputRow,inputCol);
		#endif 
	}

}

int removeLastMove(BOARD *myboard,int playernum)//return 0 if empty p1moves and 1 if successful
{
	int roww;
	int coll;

	if(playernum == 1)
	{
		if(myboard->p1Move == NULL)
		{	
			#ifdef DEBUG
			printf("Empty move list, exiting\n");
			#endif
			return 0;//return 0 if empty
		}
		roww = myboard->p1Move->moveR;
		coll = myboard->p1Move->moveC;
		myboard->Table[roww][coll] = ' ';
		if(myboard->p1Move->prev == NULL)
		{
			#ifdef DEBUG
			printf("%d %d\n",myboard->p1Move->moveR, myboard->p1Move->moveC);
			#endif
			free(myboard->p1Move);
			myboard->p1Move=NULL;
			#ifdef DEBUG
			printf("Move list now empty, exiting\n");
			#endif
			return 0;//p1Move is now empty so return 0
		}
		else
		{	
			#ifdef DEBUG
			printf("%d %d\n",myboard->p1Move->moveR, myboard->p1Move->moveC);
			#endif
			Move *temp;
			temp = myboard->p1Move->prev;
			myboard->p1Move->prev = NULL;
			temp->next = NULL;
			free(myboard->p1Move);
			myboard->p1Move = temp;
			#ifdef DEBUG
			printf("Removing last move\n");
			#endif
			return 1;
		}
	}
	if(playernum == 2)
	{
		if(myboard->p2Move == NULL)
		{
			#ifdef DEBUG
			printf("Empty move list, exiting\n");
			#endif
			return 0;//return 0 if empty
		}
		roww = myboard->p2Move->moveR;
		coll = myboard->p2Move->moveC;
		myboard->Table[roww][coll] = ' ';
		if(myboard->p2Move->prev == NULL)
		{	
			#ifdef DEBUG
			printf("%d %d\n",myboard->p2Move->moveR, myboard->p2Move->moveC);
			#endif
			free(myboard->p2Move);
			myboard->p2Move=NULL;
			#ifdef DEBUG
			printf("Move list now empty, exiting\n");
			#endif
			return 0;//p2Move is now empty so return 0
		}
		else
		{
			#ifdef DEBUG
			printf("%d %d\n",myboard->p2Move->moveR, myboard->p2Move->moveC);
			#endif
			Move *temp;
			temp = myboard->p2Move->prev;
			myboard->p2Move->prev = NULL;
			temp->next = NULL;
			free(myboard->p2Move);
			myboard->p2Move = temp;
			#ifdef DEBUG
			printf("Removing last move\n");
			#endif
			return 1;
		}
	}
	printf("Something went wrong, playernum invalid\n");
	return 0;
}

int getSize(BOARD *myboard)
{
	return myboard->size;
}

void saveReplay(BOARD *myboard, char *filename, int play1, int play2, int winner)
{
	Move *curMove1;
	Move *curMove2;
	int count1=1;
	int count2=1;
	int firstOne;  //marks which player went first
	curMove1 = myboard->p1Move;
	curMove2 = myboard->p2Move;
	while(curMove1->prev!=NULL)//going to beginning of move list
	{
		curMove1=curMove1->prev;
		count1++;
	}
	while(curMove2->prev!=NULL)
	{
		curMove2=curMove2->prev;
		count2++;
	}
	if(count1>count2)//checks who went first
	{
		firstOne=1;
	}
	else
	{
		firstOne=2;
	}
	FILE *fp;
	fp = fopen(filename, "w");
	fprintf(fp, "#TicTacWowWeeWow\n");
	fprintf(fp, "Version 1.0\n");
	fprintf(fp, "Filename: %s\n",filename);
	char text[100];//code to get the time and date and print into f
	time_t now = time(NULL);
	struct tm *t = localtime(&now);


	strftime(text, sizeof(text)-1, "%d %m %Y %H:%M", t);
	fprintf(fp, "Date: %s\n\n", text);

	fprintf(fp, "#Settings\n");
	char icon1 = getIcon(myboard,1);
	char icon2 = getIcon(myboard,2);
	switch(play1)//a switch statement that corresponds an input into some hardcoded options. Humans or AI
	{
		case 0:
		{
			fprintf(fp, "Player 1 (Human): \'%c\' ",icon1);
			break;
		}
		case 1:
		{
			fprintf(fp, "Player 1 (Inky): \'%c\' ",icon1);
			break;
		}
		case 2:
		{
			fprintf(fp, "Player 1 (Blinky): \'%c\' ",icon1);
			break;
		}
		case 3:
		{
			fprintf(fp, "Player 1 (Pinky): \'%c\' ",icon1);
			break;
		}
		case 4:
		{
			fprintf(fp, "Player 1 (Clyde): \'%c\' ",icon1);
			break;
		}
	}
	fprintcolor(getColor(myboard,1),fp);
	fprintf(fp,"\n");
	switch(play2)
	{
		case 0:
		{
			fprintf(fp, "Player 2 (Human): \'%c\'' ",icon2);
			break;
		}
		case 1:
		{
			fprintf(fp, "Player 2 (Inky): \'%c\'  ",icon2);
			break;
		}
		case 2:
		{
			fprintf(fp, "Player 2 (Blinky): \'%c\' ",icon2);
			break;
		}
		case 3:
		{
			fprintf(fp, "Player 2 (Pinky): \'%c\' ",icon2);
			break;
		}
		case 4:
		{
			fprintf(fp, "Player 2 (Clyde): \'%c\' ",icon2);
			break;
		}
	}
	fprintcolor(getColor(myboard,2),fp);
	fprintf(fp,"\n");
	if(winner==1||winner==2)
	{
		fprintf(fp,"#Winner: Player %d\n\n",winner);
	}
	else
	{
		fprintf(fp,"#Winner: Draw\n\n");
	}
	fprintf(fp,"#MovesList\n");
	Move *temp1 = curMove1;//temp variables used in move outputs
	Move *temp2 = curMove2;
	int done1=0;
	int done2=0;
	while(done1==0 || done2==0)//while the move list for either is not empty, output the moves
	{
		
		if(curMove1 != NULL)
		{
			fprintf(fp,"Player 1: %c%c\n",curMove1->moveR+'A',curMove1->moveC+'1');
			curMove1=curMove1->next;
		}
		else
		{
			//printf("Done1\n");
			done1=1;
		}


		if(curMove2 != NULL)
		{
			fprintf(fp,"Player 2: %c%c\n",curMove2->moveR+'A',curMove2->moveC+'1');
			curMove2=curMove2->next;
		}
		else
		{
			//printf("Done2\n");
			done2=1;
		}
	}
	char table[DEFAULTSIZE][DEFAULTSIZE];//temp array used for a replay
	for(int i =0;i<DEFAULTSIZE;i++)//intiialize to ' ' characters
	{
		for(int j =0 ; j < DEFAULTSIZE;j++)
		{
			table[i][j] = ' ';
		}
	}
	int dane1 = 0;
	int dane2 = 0;
	fprintf(fp,"\n\n#Replay \n");
	while(dane1==0 || dane2==0)//flags to see if done. This loop prints out the grids move by move
	{
		
		if((temp1) != NULL)
		{
			fprintf(fp,"Player 1 chooses %c %c\n",temp1->moveR+'A', temp1->moveC+'1');
			table[temp1->moveR][temp1->moveC] = icon1;
			fprintBoard(myboard, fp, table);
			temp1=temp1->next;
		}
		else
		{
			printf("Done1\n");
			dane1=1;
		}


		if(temp2 != NULL)
		{
			fprintf(fp,"Player 2 chooses %c %c\n",temp2->moveR+'A', temp2->moveC+'1');
			table[temp2->moveR][temp2->moveC] = icon2;
			fprintBoard(myboard,fp,table);
			temp2=temp2->next;
		}
		else
		{
			printf("Done2\n");
			dane2=1;
		}
	}
	if(winner==1||winner==2)
	{
		fprintf(fp, "Player %d wins!\n\n",winner);
	}
	else
	{
		fprintf(fp, "No contest!\n\n");
	}
	fprintf(fp, "#EOF");

}


void fprintBoard(BOARD *myboard, FILE *fp, char table[DEFAULTSIZE][DEFAULTSIZE])
{
	//repeated code from printboard but without the colors and it takes in table as an input
	int boardSize = myboard->size;
	int defaultColor1 = myboard->p1->color;
	int defaultColor2 = myboard->p2->color;
	char icon1 = myboard->p1->icon;
	char icon2 = myboard->p2->icon;


    int charIndex = boardSize+'A'-1;
    int size=boardSize;
    //int colorIcon = 0;
    if(table[boardSize-1][0]==icon1)
    {
        //colorIcon=defaultColor1;
    }
    else if (table[boardSize-1][0]==icon2)
    {
        //colorIcon=defaultColor2;
    }
    fprintf(fp,"%c %c",(char)charIndex,table[boardSize-1][0]);

    for(int u = 1; u < boardSize; u++)
    {
        //colorIcon = 0;
        if(table[boardSize-1][u]==icon1)
        {
            //colorIcon=defaultColor1;
        }
        else if (table[boardSize-1][u]==icon2)
        {
            //colorIcon=defaultColor2;
        }
        fprintf(fp,"|%c",table[boardSize-1][u]);
    }
    fprintf(fp,"\n  ");
    size--;
    for(int i =1; i < boardSize; i++)
    {
        for(int j = 0; j<boardSize*2-1;j++)
        {
            fprintf(fp,"-");
        }
        fprintf(fp,"\n");
        //colorIcon=0;
        if(table[size-i][0]==icon1)
        {
            //colorIcon=defaultColor1;
        }
        else if (table[size-i][0]==icon2)
        {
            //colorIcon=defaultColor2;
        }
        fprintf(fp,"%c %c",(char)(--charIndex),table[size-i][0]);
for(int k = 1; k < boardSize;k++)
        {
            //colorIcon=0;
        if(table[size-i][k]==icon1)
        {
            //colorIcon=defaultColor1;
        }
        else if (table[size-i][k]==icon2)
        {
            //colorIcon=defaultColor2;
        }   
            fprintf(fp,"|%c",table[size-i][k]);
        }
        fprintf(fp,"\n  ");

    }
    for(int e = 1; e<=boardSize;e++)
    {
        fprintf(fp,"%d ",e);
    }
    fprintf(fp,"\n\n");
    defaultColor1++;
    defaultColor2++;
    //fprintf(fp,"C %c|%c|%c\n",table[2][0],table[0][1],table[0][2]);
    //fprintf(fp,"  -----\n");
    //fprintf(fp,"B %c|%c|%c\n",table[1][0],table[1][1],table[1][2]);
    //fprintf(fp,"  -----\n");
    //fprintf(fp,"A %c|%c|%c\n",table[0][0],table[2][1],table[2][2]);
    //fprintf(fp,"  1 2 3\n");
}

void fprintcolor(int colorCode,FILE *fp)
{
	switch(colorCode)
	{
		case 0:
		{
			fprintf(fp,"\'Default Color\'");
			break;
		}
		case 30:
		{
			fprintf(fp,"\'Black\'");
			break;
		}
		case 31:
		{
			fprintf(fp,"\'Red\'");
			break;
		}
		case 32:
		{
			fprintf(fp,"\'Green\'");
			break;
		}
		case 33:
		{
			fprintf(fp,"\'Yellow\'");
			break;
		}
		case 34:
		{
			fprintf(fp,"\'Blue\'");
			break;
		}case 35:
		{
			fprintf(fp,"\'Magenta\'");
			break;
		}
		case 36:
		{
			fprintf(fp,"\'Cyan'\'");
			break;
		}
		case 37:
		{
			fprintf(fp,"\'White\'");
			break;
		}




	}
}














