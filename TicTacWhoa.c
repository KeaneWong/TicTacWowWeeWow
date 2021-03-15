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
#include <ctype.h>
#include <time.h>
int gameBoard(char **table,char input[2],int turn, int boardSize, char icon1, char icon2);//Function that modifies an array. Returns 0 for errors, 1 for no errors, 2 for a victor. Represents a 'change' in the gameboard
//Takes argument table, which has the gameboard, the input array representing the next move, an integer that corresponds to whose turn it is either 0 for x and 1 for O, and the size of the board on a side
void printBoard(char **table, int boardSize,int color1, int color2, char icon1, char icon2);//prints board. This is where the color codes are used
void deleteBoard(char **table,int boardSize);//memory leak preventing
//char* colorSetting(int colorNum); useless function, unused
int main()
{

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

    //intiialize gameboard
    switch(commandCode)
    {
    case 1:
    {
    int numGames=0;//used to track how many turns have passed. If it exceeds the board size and no victor, it is a draw
    int won=0;//variable used to track if someone has won
    char makeYourMove[2];//input of current player
    int curTurn=defaultTurn;
    while(!won)
    {

        
        printf("Player %c make your move: ",curIcon);
        scanf("%s",makeYourMove);
        
    }

    break;
    }
    case 2:
    {
    int curTurn=defaultTurn;//if x or o goes first
    int numTurns=0;//elapsed numbers of turns
    printf("Would you like to be player 1 or player 2?[1/2]\n");
    int playe=1;
    scanf("%d",&playe);
    if(playe!=1 && playe !=2)//just error catching
    {
        printf("Not a valid option\n");
        break;
    }

    char *table1[gameBoardSize];//initializing the AI's table
    //this table is used to check for valid moves before doing it
	for(int i=0;i<gameBoardSize;i++)
    {
    table1[i] = (char*)malloc(gameBoardSize*sizeof(char));
    }
    for(int j =0;j<gameBoardSize;j++)
    {
        for(int k=0;k<gameBoardSize;k++)
        {
            table1[j][k]=' ';
        }
    }

    time_t te;
    srand((unsigned) time(&te));//rng tic tac toe 'AI'
    char robotsMove[2];
    if(playe==2)//run an extra turn if the computer goes first i.e user chose player 2
    {
        
            int inRow = rand()%gameBoardSize;
            int randCol = rand()%gameBoardSize;
            robotsMove[0] = (char)('A'+inRow);
            robotsMove[1] = (char)('1'+randCol);
            table1[inRow][randCol] = 'p';//placeholder to indicate that spot is filled. Doesnt matter if the place is an x or an O
        gameBoard(table,robotsMove,curTurn,gameBoardSize, icon1, icon2);//game baord is used to run a second 'game' for the AI that is used to check valid moves only
        if(curTurn == 0)
        {
            curTurn=1;
        }
        else
        {
            curTurn=0;
        }

        numTurns++;//increment numbter of turns if robot goes first
    }
    printBoard(table,gameBoardSize,defaultColor1,defaultColor2, icon1, icon2);
    printf("Human player, your turn\n");
    int won=0;
    char userIn[2];
    while(!won)//basically we run a simulation of the AI with a separate table before putting it in to the real one
    {
        if(numTurns>=(gameBoardSize*gameBoardSize) )
        {
            printf("Draw. Play again?\n");                        
            deleteBoard(table1,gameBoardSize);//freeing memory
            break;
        }
        scanf("%s",userIn);
        int success = gameBoard(table,userIn,curTurn,gameBoardSize, icon1, icon2);
        printf("%d\n",success);
        if(success == 1)//if the input is valid
        {
            numTurns++;
            if(curTurn==1)
            {
                curTurn=0;
            }
            else
            {
                curTurn=1;
            }//if success goes out to 0 then we repeat loop without changing turns
            printBoard(table,gameBoardSize,defaultColor1,defaultColor2, icon1, icon2);
            if(numTurns>=gameBoardSize*gameBoardSize)//we only take the robots turn if the human's is successful
            {
                printf("Draw. Play again?\n");
                deleteBoard(table1,gameBoardSize);
                break;

            }
            int rowy = userIn[0]-'A';//converting user input so we can plug it into the AI simulation
            int coly = userIn[1]-'1';
            table1[rowy][coly] = 'p';

            int validRobotInput=0;
            printf("Robots turn\n");
            int succes;
            while(!validRobotInput)//trying some robot inputs before putting it in
            {
                int rowt = rand()%gameBoardSize;
                int colt = rand()%gameBoardSize;
                robotsMove[0] = rowt+'A';
                robotsMove[1]=colt+'1';
                if(table1[rowt][colt]==' ')
                {
                    table1[rowt][colt]='p';//setting that part as filled
                    succes = gameBoard(table,robotsMove,curTurn,gameBoardSize, icon1, icon2);
                    validRobotInput=1;
                    numTurns++;
                    if(curTurn==1)
                    {
                        curTurn=0;
                    }
                    else
                    {
                        curTurn=1;
                    }
                    printBoard(table,gameBoardSize,defaultColor1,defaultColor2, icon1, icon2);
                    if(succes==2)
                    {
                        printf("ROBOT WINS \n");
                        deleteBoard(table1,gameBoardSize);
                        break;
                    }
                }

            }
            if(succes==2)
            {
                break;
            }
            printf("Your turn Human\n");
        }
        if(success == 2)
        {
            printBoard(table,gameBoardSize,defaultColor1,defaultColor2, icon1, icon2);
            printf("Human wins!\n");
            deleteBoard(table1,gameBoardSize);
            break;
        }

    }

    break;
    }
    case 3:
    {
	
        //default turn switch from 0 to 1. Turn player 1 x or player 1 o
        //change game board size
        char p1;
        char p2;
        if(defaultTurn == 0)//player '1' is determined by who goes first
        {
            p1=icon1;
            p2=icon2;
        }
        else
        {
            p1=icon2;
            p2=icon1;
        }

        printf("Welcome to game settings.\nCurrent Settings:\n\tPlayer 1: %c\n\tPlayer 2: %c\n\tBoardSize: %d\n",p1,p2,gameBoardSize);
        printf("Which setting would you like to change?\n\t1. Change player 1 color\n\t2.Change player 2 color\n\t3.Change player icons\n\t4.Change board size (up to 10, min 3)\n\t5.Quit\n");
        char option;
        scanf("%c",&option);
		srand(time(NULL));
		int funColor=rand()%8+40;//some number between 40 and 47 in case user picks option 0 :)
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
                printf("\t0.Something Fun :) (Not supported on all versions)\n");
                printf("Choose from the options below (Enter 1-9):\n");
                scanf("%d",&inme);
                if(defaultTurn==0)//implies player 1 is x
                {
                    if(inme==0)
                    {
										
                        defaultColor1=funColor;//makes player 1 a randomly generated background color
                    }
                    if(inme==9)
                    {
                        defaultColor1=0;//resets colors back to default
                    }
                    else
                    {
                    defaultColor1=inme+29;//shifts default color to ansi color code
                    }
                }
                else//implies player 1 is O
                {
                    if(inme==0)
                    {
                        defaultColor2=funColor;
                    }
                    if(inme==9)
                    {
                        defaultColor2=0;
                    }
                    else
                    {
                    defaultColor2=inme+29;
                    }
                    //defaultColor2=inme+29;
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
                if(defaultTurn==1)//implies player 2 is x
                {
                    if(inme2==0)
                    {
                        defaultColor1=funColor;
                    }
                    if(inme2==9)
                    {
                        defaultColor1=0;
                    }
                    else
                    {
                    defaultColor1=inme2+29;
                    }
                    //defaultColor1=inme2-1;
                }
                else//implies player 2 is O
                {
                    if(inme2==0)
                    {
                        defaultColor2=funColor;
                    }
                    if(inme2==9)
                    {
                        defaultColor2=0;
                    }
                    else
                    {
                    defaultColor2=inme2+29;
                    }
                    //defaultColor2=inme2-1;
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
                    icon1=newIcon;
                    printf("Changing new icon to be %c\n",icon1);

                }
                else
                {
                    char newIcon;
                    while((getchar())!='\n');
                    printf("What do you want the new icon to be?\n");
                    scanf("%c",&newIcon);
                    icon2=newIcon;
                    printf("Changing new icon to be %c\n",icon2);
                }
                break;
            }
            case '4'://extra credit option
            {
                printf("What would you like the new board size to be?\n");
                while ((getchar()) != '\n');//mini function to clear input buffer. 
  
                int newSize;
                if(!scanf("%d",&newSize))
                {
                    printf("Invalid Size. Keeping current size\n");
                    break;
                }
                while ((getchar()) != '\n');//mini function to clear input buffer. 

                if(newSize<3||newSize>10)
                {
                    printf("Invalid Size. Keeping current size %d\n",gameBoardSize);
                }
                else
                {
                    gameBoardSize = (newSize);
                    printf("Affirmative. New game board size to %d\n",gameBoardSize);
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
        deleteBoard(table,gameBoardSize);
        return 0;
    }
    while((getchar())!='\n');//flushing input buffer

    }
    
    deleteBoard(table,deleteBoardSize);//function to prevent memory leaks between iterations
}
return 0;
}





/* EOF */
