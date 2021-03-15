/****************************************************/
/* TicTacWhoa.c: Variation on Tic Tac Toe.   						*/
/* authors: Keane Wong 							  					*/	
/*																  	*/
/* modifications:									  				*/
/* 2021/01/15 Adjujusted for non x and o icons. totally complete    */
/* 2021/01/12 completed program. Testing done					 	*/
/* 2021/01/12 debugging. testing features						 	*/
/* 2021/01/10 finished extra credit and game settings			 	*/
/* 2021/01/08 wrote extra credit option. started color codes		*/
/* 2021/01/08 outlined main variables. wrote printboard function 	*/
/* 2021/01/07 wrote gameboard function			 					*/
/* 2021/01/06 wrote main switch statement		 					*/
/* 2021/01/06 began file						 					*/
/**/
/**/
/**/

#include <stdio.h>
#include <stdlib.h>
#include "GameBoard.h"
#include "GameAI.h"
#include "Settings.h"
//#include 
int main()
{
	BOARD *myBoard = MakeBoard(3,'X','O');
	while(1){
	    //deleteBoardSize=gameBoardSize;
	    printf("Welcome to TicTacWhoa. To begin, please enter a valid option from below:\n");
	    printf("1. Start a new game (Human vs Human)\n");
	    printf("2. Start a new game (Human vs Robot)\n");
	    printf("3. Game settings\n");
	    printf("4. Exit game\n");
	    printf("Enter code:");
	    int commandCode;
	    int validopt=0;
	    int numTurns1 = 0;
	    while(!validopt)//valid input loop
	    {   
	        if(scanf("%d",&commandCode)!=1)
	        {   
	            printf("Please enter a valid integer:");
	        }
	        else if (commandCode>4 || commandCode<1)
	        {   
	            printf("Please enter an integer between 1 and 4:");
	        }
	        else
	        {   
	            validopt=1;
	        
	        }
	        while((getchar())!='\n');//flushing input buffer
	    }

	    
	    switch(commandCode)
	    {
	    case 1:
	    {
	    int won =0;
	    char makeYourMove[2];//input of current player
	    int numTurns=0;
	    printBoard(myBoard);
	    while(!won && numTurns<9)
	    {

	        char curIcon = getIcon(myBoard, getCurTurn(myBoard));
	        printf("Player %c make your move: ",curIcon);
	        scanf("%s",makeYourMove);
	        int temp = gameBoard(myBoard,makeYourMove);
	        if(temp == 2)
	        {
	        	won = 1;
	        }
	        if(temp == 1 && numTurns>=8)
	        {
	        	printf("Draw. No winners\n");
	        }
	        if(temp!=0)
	        {
	        	numTurns++;
	        }
	        printBoard(myBoard);
	    }
 		while((getchar())!='\n'){};

	    printf("Save replay?(y/n):");
	    char ew;
	    scanf("%c",&ew);
	    if(ew=='y')
	    {
	    	int winner;
	    	if(won==1)
	    	{
	    		winner = getCurTurn(myBoard);
	    		winner = ((winner==1) ? 2:1);//flip them because curturn always turns it around
	    	}
	    	else
	    	{
	    		winner = -1;//signals a draw
	    	}

	    	printf("Enter the name of the save filename (include .txt at end please): ");
	    	char inp[256];
	    	scanf("%s",inp);
	    	saveReplay(myBoard,inp,0,0,winner);
	    }
	    else
	    {
	    	printf("Ok. Replay not saved\n");
	    }
	    
	    break;
	    }
	    case 2:
	    {
	    	int AIModel;
			printf("1.Inky\n");
			printf("2.Blinky\n");
			printf("3.Pinky\n");
			printf("4.Clyde (Incomplete)\n");

	    	printf("Which AI version would you like to face off against?\n");
	    	scanf("%d",&AIModel);

	    	printf("Would you like to be player 1 or player 2? (1/2)\n");
	    	int inp;
	    	scanf("%d",&inp);
	    	int won=0;
	    	int winnner;
	    	char makeYourMove[2];
	    	char makeAIMove[2];
	    	int AITurn;
	    	if(inp == 1)
	    	{
	    		AITurn = 2;
	    	}
	    	else
	    	{
	    		AITurn = 1;
	    	}
	    	if(inp == 2)//implies ai goes first so we do an extra turn
	    	{
	    		printBoard(myBoard);
	    		switch(AIModel)
	    		{
	    			int mmove;
	    			case 1:
	    			{
	    				mmove = Inky(myBoard);
	    				makeAIMove[0] = getRow(myBoard,mmove);
	    				makeAIMove[1] = getCol(myBoard,mmove);
	    				gameBoard(myBoard,makeAIMove);
	    				break;
	    			}
	    			case 2:
	   				{
						mmove = Blinky(myBoard);
	    				makeAIMove[0] = getRow(myBoard,mmove);
	    				makeAIMove[1] = getCol(myBoard,mmove);
	    				gameBoard(myBoard,makeAIMove);
	    				break;
	   				}
	   				case 3:
	   				{
						mmove = Pinky(myBoard,AITurn);
	    				makeAIMove[0] = getRow(myBoard,mmove);
	    				makeAIMove[1] = getCol(myBoard,mmove);
	    				gameBoard(myBoard,makeAIMove);
	    				break;
	   				}
	   				case 4:
	   				{
	   					mmove = Clyde(myBoard);
	    				makeAIMove[0] = getRow(myBoard,mmove);
	    				makeAIMove[1] = getCol(myBoard,mmove);
	    				gameBoard(myBoard,makeAIMove);
	    				break;
	   				}


	    		}
	    		printf("%d turns\n",numTurns1);
	    		numTurns1++;
	    	}
	    	 printBoard(myBoard);
	    	 int status;
	    	while(!won && numTurns1<9)
	    	{

	    		

	    		printf("Player human make your move ('zz' to undo): ");
	        	scanf("%s",makeYourMove);
	        	if(makeYourMove[0] == 'z' && makeYourMove[1] == 'z')
	        	{
	        		removeLastMove(myBoard,1);
	        		removeLastMove(myBoard,2);
	        		numTurns1 = numTurns1-2;
	        		printBoard(myBoard);
	        	}
	        	else
	        	{
		        	status = gameBoard(myBoard,makeYourMove);
		        	if(status == 2)
			        {
			        	won = 1;
			        	printf("Winner -\n");
			        	winnner = inp; //if input 1 then the human was player 1 and therefore player 1 was winner. if input = 2 then human was player 2 and won
			        	break;
			        }
			        if(status == 1 && numTurns1 >= 8)
			        {
			        	winnner = -1;//implies draw
			        	printf("Draw. No winners\n");
			        	break;
			        }
					
			        if(status!=0)
			        {
						#ifdef DEBUG
			  			printf("%d turns\n",numTurns1);
			        	#endif
						numTurns1++;
			        }
			         
					 printBoard(myBoard);
		    		switch(AIModel)
		    		{
		    			int mmove;
		    			case 1:
		    			{
		    				mmove = Inky(myBoard);
		    				makeAIMove[0] = getRow(myBoard,mmove);
		    				makeAIMove[1] = getCol(myBoard,mmove);
		    				status = gameBoard(myBoard,makeAIMove);
		    				break;
		    			}
		    			case 2:
		   				{
							mmove = Blinky(myBoard);
		    				makeAIMove[0] = getRow(myBoard,mmove);
		    				makeAIMove[1] = getCol(myBoard,mmove);
		    				status = gameBoard(myBoard,makeAIMove);
		    				break;
		   				}
		   				case 3:
		   				{
							mmove = Pinky(myBoard,AITurn);
		    				makeAIMove[0] = getRow(myBoard,mmove);
		    				makeAIMove[1] = getCol(myBoard,mmove);
		    				status = gameBoard(myBoard,makeAIMove);
		    				break;
		   				}
		   				case 4:
		   				{
		   					mmove = Clyde(myBoard);
		    				makeAIMove[0] = getRow(myBoard,mmove);
		    				makeAIMove[1] = getCol(myBoard,mmove);
		    				status = gameBoard(myBoard,makeAIMove);
		    				break;
		   				}


		    		}
			    	if(status == 2)
			        {
			        	won = 1;
			        	printf("Winner\n");
			        	printf("Undo last move? (y/n)\n");
			        	char cc;
			        	scanf("%s",&cc);
			        	while ((getchar()) != '\n');//flush input
			        	if(cc=='y')
			        	{
			        		removeLastMove(myBoard,2);
			        		removeLastMove(myBoard,1);
			        		numTurns1 = numTurns1-2;
			        		won = 0;
			        		printBoard(myBoard);
			        		continue;
			        	}
			        	winnner = (inp==1 ? 2 : 1);
			        	break;
			        }
			        if(status == 1 && numTurns1>=8)
			        {
			        	winnner = -1;
			        	printf("Draw. No winners\n");
			        	break;
			        }
			        if(status!=0)
			        {
					#ifdef DEBUG
			        	printf("%d turns\n",numTurns1);
			        #endif
						numTurns1++;
			        }
			         printBoard(myBoard);
			    }
		   }
	    	printBoard(myBoard);
	    	while((getchar())!='\n');

	    	printf("Save replay?(y/n):");
		    char ew2;
		    scanf("%c",&ew2);
		    if(ew2=='y')
		    {

		    	printf("Enter the name of the save filename (include .txt at end please): ");
		    	char inp2[256];
		    	scanf("%s",inp2);
		    	if(inp == 1)
		    	{
		    		saveReplay(myBoard,inp2,0,AIModel,winnner);
		    	}
		    	else
		    	{
		    		saveReplay(myBoard,inp2,AIModel,0,winnner);
		    	}
		    }
		    else
		    {
		    	printf("Ok. Replay not saved\n");
		    }
	    	break;	
	    }
	    case 3:
	    {
	    	//printf("Removing last move\n");//testing remove last moves
	    	//removeLastMove(myBoard,1);

	        printf("Welcome to game settings.\nCurrent Settings:\n\tPlayer 1: %c\n\tPlayer 2: %c\n\tBoardSize: %d\n",getIcon(myBoard,1),getIcon(myBoard,2),getSize(myBoard));
	        printf("Which setting would you like to change?\n\t1. Change player 1 color\n\t2.Change player 2 color\n\t3.Change player icons\n\t5.Quit\n");
	        char option;
	        scanf("%c",&option);
	        switch(option)
	        {
	            case '1':
	            {
	                int inme;
	                printf("\t1.Black\n");
	                printf("\t2.Red\n");
	                printf("\t3.Green\n");
	                printf("\t4.Yellow\n");
	                printf("\t5.Blue\n");
	                printf("\t6.Magenta\n");
	                printf("\t7.Cyan\n");
	                printf("\t8.White\n");
	                printf("\t9.Reset\n");
	                printf("Choose from the options below (Enter 1-9):\n");
	                scanf("%d",&inme);
	                if(inme == 9)
	                {
	                	changeColor(myBoard,0,1);
	                }
	                else
	                {
	                	changeColor(myBoard,inme,1);
	                }
	                break;
	            }
	            case '2':
	            {
	                int inme2;
	                printf("\t1.Black\n");
	                printf("\t2.Red\n");
	                printf("\t3.Green\n");
	                printf("\t4.Yellow\n");
	                printf("\t5.Blue\n");
	                printf("\t6.Magenta\n");
	                printf("\t7.Cyan\n");
	                printf("\t8.White\n");
	                printf("\t9.Reset\n");
	                printf("\t0.Something fun :) (Not supported on all versions)\n");
	                printf("Choose from the options below (Enter 1-9):\n");
	                scanf("%d",&inme2);
	               	if(inme2 == 9)
	                {
	                	changeColor(myBoard,0,2);
	                }
	                else
	                {
	                	changeColor(myBoard,inme2,2);
	                }
	                break;
	            }
	            case '3':
	            {
	                int innn;
	                printf("Which player's icon do you want changed?\n");
	                scanf("%d",&innn);
	                if(innn==1)
	                {
	                    char newIcon;
	                    while((getchar())!='\n');
	                    printf("What do you want the new icon to be?\n");
	                    scanf("%c",&newIcon);
	                    changeIcon(myBoard,newIcon,1);
	                    printf("Changing new icon to be %c\n",newIcon);

	                }
	                else
	                {
	                    char newIcon;
	                    while((getchar())!='\n');
	                    printf("What do you want the new icon to be?\n");
	                    scanf("%c",&newIcon);
	                    changeIcon(myBoard,newIcon,2);
	                    printf("Changing new icon to be %c\n",newIcon);
	                }
	                break;
	            }
	            case '5':
	            {
	                printf("Quitting. Returning to main menu\n");
	                break;
	            }
	            default:
	            {
	                printf("Invalid option. Returning to main menu\n");
	                break;
	            }

	        }
		
	    break;
	    }
	    case 4:
	    {
	        printf("Thank you. Have a wonderful day\n");
	        deleteBoard(myBoard);
	        return 0;
	        break;
	    }
	    while((getchar())!='\n');//flushing input buffer

	    }
	    
	    //deleteBoard(table,deleteBoardSize);//function to prevent memory leaks between iterations
	    clearBoard(myBoard);
	}
	return 0;
}




/* EOF */
