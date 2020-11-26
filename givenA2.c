#include "givenA2.h"

int main(){
    
    int userRow, userCol, computerRow, computerCol;
    int taken;
    int count = 1;
    int stepsWon = 0;
    
    char board[N][N];
    char winner = 'N';
    
    srand((int) time(0));
    
    printf ("This tic-tac-toe board is of size %d by %d\n", N, N);
    
    printf ("You are using symbol X and the computer program is using symbol O\n");
    
    printf ("Here is the board - spaces are indicated by a ?\n");
    
    createInitialBoard (board);
    
    while ((winner != 'Y') && !(isBoardFull(board)))
    {
        taken = 0;
        
        while (!(taken))
        {
            readUserMove(&userRow, &userCol, &stepsWon);
            printf("You chose row %d and column %d \n", userRow, userCol);
            
            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))
            {
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol, &stepsWon);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }
            
            if (board[userRow-1][userCol-1] == '?')
            {
                board[userRow-1][userCol-1] = 'X';
                taken = 1;
                count++;
                
            }
            else
            {
                taken = 0;
                printf("That spot is taken - please try another one\n");
            }
        }
        
        if (gameWon(board, 'X'))   //user won
        {
            printf("Congrats - you won against the computer :) in %d steps\n", stepsWon);
            winner = 'Y';
        }
        
        else  if (!(isBoardFull(board)))            //check computer's move if the board is not yet full
        {
            taken = 0;
            
            while (!(taken))
            {
                taken = getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1);
                
                if (taken) {
                    board[computerRow][computerCol] = 'O';
                    break;
                }
                
                getchar();
                
                if (board[computerRow][computerCol] == '?')
                {
                    board[computerRow][computerCol] = 'O';
                    taken = 1;
                    
                }
                else
                {
                    taken = 0;
                    //printf("That spot is taken - computer - try another one\n");
                }
            }
            printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
            if (gameWon(board, 'O'))
            {
                printf("Oh the computer won this time :(( think hard next time\n");
                winner = 'Y';
            }
        }
        
        printCurrentBoard (board);
        
        if (winner != 'Y') {
           printf("Enter to continue \n");
        }
        getchar();
        
    } //end of while
    
    if (winner != 'Y') {
       printf("Game was a tie - no winner!\n\n");
    }
    return 0;
}

/* In function getComputerMove , the computer tries to win the game first; if it cannot win, then
 
 1. for those who are not attempting the 10% additional functionality
     - the computer then decides to play randomly
 2. for those who are attempting the 10% additional functionality
     - the computer then tries to block the user's game
     - if it does not succeed in blocking, then it makes a random move
 */

int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
    
    int winningSpot = 0;
    int blocked;
    
    winningSpot = computerPlaysToWin(board, computerRow, computerCol);
    
    /*
     if the computer does not find a winning spot, then it either play randomly or blocks
     */
    
    if (!winningSpot)
    {
        // comment the next line if you are attempting the 2% functionality
        computerPlaysRandom(computerRow, computerCol);
        
        /* uncomment the next few  lines if you are attempting the 2% functionality
        int blocked = 0;*/

         
         blocked = computerPlaysToBlock(board, computerRow, computerCol);
         if (blocked == 0) { 
        computerPlaysRandom(computerRow, computerCol);
        return 0;
         }
         
         return blocked;
         
    }
    
    return winningSpot;
}
int gameWon (char board [N][N], char symbol)
{
    int sumR[N]={0};
    int sumC[N]={0};
    int sumLD=0;
    int sumRD = 0;

    for (int i = 0;i<N;i++)
    {
        for (int j = 0;j < N;j++)
        {
            if (board[i][j] == 'O')
                sumR[i]+=4;
            else if (board[i][j] == 'X')
                sumR[i] += 1;
            if (board[j][i] == 'O')
                sumC[i]+=4;
            else if (board[j][i] == 'X')
                sumC[i] += 1;
        }
    }
        for (int i = 0;i < 3;i++)
        {
            if (board[i][i] == 'O')
                sumLD += 4;
            else if(board[i][i]== 'X')
                sumLD +=1;
            if (board[2-i][i] == 'O')
                sumRD += 4;
            else if(board[2-i][i]== 'X')
                sumRD +=1;            
        }

    if (memberOf(3,sumR)||memberOf(3,sumC)||(sumLD==3)||(sumRD==3))
        {   
            if (symbol == 'X')
            return 1;
            else 
            return 0;
        }
    if (memberOf(12,sumR)||memberOf(12,sumC)||(sumLD==12)||(sumRD==12))
    {
        if (symbol == 'O')
            return 1;
        else 
            return 0;
    }  
    return 0;  
}
//Returns 1 if the computer wins in this step. This function is explained further on pages 3 and 4
int computerPlaysToWin (char board [N][N], int * cRow, int * cCol)
{
    int count=0;
    int returnif=0;
        for (int i=0;i < 3;i++)
        {   count = 0;
            returnif = 0;
            for (int j=0;j<3;j++)
            {
                if (board[i][j] == 'O')
                    count+=4;
                else if (board[i][j] == '?')
                {   
                    returnif = 1;
                    *cRow = i;
                    *cCol = j;
                }  
            }
            if (count == 8 && returnif == 1)
                return 1;
        }
        for (int  i=0;i < 3;i++)
        {   count = 0;
            returnif = 0;
            for (int j=0;j<3;j++)
            {
                if (board[j][i] == 'O')
                    count+=4;
                else if (board[j][i] == '?')
                {
                    returnif = 1;
                    *cRow = j;
                    *cCol = i;
                }  
            }
            if (count == 8 && returnif == 1)
                return 1;
        }
        count = 0;
        returnif = 0;
        for (int i=0; i<3;i++)
        {
            if (board[i][i] == 'O')
                    count+=4;
            else if (board[i][i] == '?')
            {
                returnif = 1;
                *cRow = i;
                *cCol = i;
            }  
        }
        if (count == 8 && returnif == 1)
            return 1;
        count = 0;
        returnif = 0;
        for (int i=0; i<3;i++)
        {
            if (board[2-i][i] == 'O')
                    count+=4;
            else if (board[2-i][i] == '?')
            {
                returnif = 1;
                *cRow = 2-i;
                *cCol = i;
            }  
        }
        if (count == 8 && returnif == 1)
            return 1;
    return 0;
}
/*Returns 1 if a value exists in the given array. For example, if someArray has the following values
[10,20,30], then memberOf (30, someArray) returns 1 but memberOf (3, someArray) returns 0.*/
int memberOf (int aNum, int someArray [N])
{   for (int i = 0;i<N;i++)
    {
        if (aNum == someArray[i])
            return 1;
    }
    return 0;
}
/*Returns 1 if the computer successfully blocks the players next winning move.
Returns a 0 if it doesn’t block.*/
int computerPlaysToBlock (char board [N][N], int * cRow, int * cCol)
{
    int count=0;
    int returnif=0;
        for (int i=0;i < 3;i++)
        {   count = 0;
            returnif = 0;
            for (int j=0;j<3;j++)
            {
                if (board[i][j] == 'X')
                    count+=4;
                else if (board[i][j] == '?')
                {   
                    returnif = 1;
                    *cRow = i;
                    *cCol = j;
                }  
            }
            if (count == 8 && returnif == 1)
                return 1;
        }
        for (int  i=0;i < 3;i++)
        {   count = 0;
            returnif = 0;
            for (int j=0;j<3;j++)
            {
                if (board[j][i] == 'X')
                    count+=4;
                else if (board[j][i] == '?')
                {
                    returnif = 1;
                    *cRow = j;
                    *cCol = i;
                }  
            }
            if (count == 8 && returnif == 1)
                return 1;
        }
        count = 0;
        returnif = 0;
        for (int i=0; i<3;i++)
        {
            if (board[i][i] == 'X')
                    count+=4;
            else if (board[i][i] == '?')
            {
                returnif = 1;
                *cRow = i;
                *cCol = i;
            }  
        }
        if (count == 8 && returnif == 1)
            return 1;
        count = 0;
        returnif = 0;
        for (int i=0; i<3;i++)
        {
            if (board[2-i][i] == 'X')
                    count+=4;
            else if (board[2-i][i] == '?')
            {
                returnif = 1;
                *cRow = 2-i;
                *cCol = i;
            }  
        }
        if (count == 8 && returnif == 1)
            return 1;
    return 0;
}
/*This is a utility function that can be used by other functions.
 It computes the sum of scores across all rows, columns, left diagonal and right diagonal.*/

void computerPlaysRandom (int * cRow, int * cCol)
{
    *cRow=rand()%N;
	*cCol=rand()%N;
}
int isInputValid (int entered, int minimum, int maximum )
{   
    for (int i=minimum; i<= maximum;i++)
    {
        if (entered == i)
            return 1;        
    }
    return 0;
}
//Returns 1 if there is no empty cell in the board; 0 otherwise
int isBoardFull (char board [N][N]) 
{
    for (int i = 0; i<3;i++)
    {
        for (int j=0; j<3 ;j++)
        {
            if (board[i][j]== '?')
                return 0;
        }
    }
    return 1;
}

/*Creates an empty board, which is a 2D array of size n X n – each cell on the board is assigned a ‘?’.
It also prints the board.*/
void createInitialBoard (char board[N][N])
{
    int i;
    for (i=0;i<3;i++)
    {
        for (int j=0; j<3 ;j++)
        {
            board [i][j] = '?';
        }

    }
}
/*Prompts the user to input row and column values to place symbol X on the board.
/!\ Note that your program must validate row and column values entered by the user – they must
be a number between 1 and 3 (both inclusive). You may use the helper function isInputValid to
validate.*/
void readUserMove (int * userRow, int * userCol, int * stepsWon)
{   
    printf("Your move - enter numbers between 1 and 3");
    printf("\nEnter row number:");
    scanf("%d",userRow);
    printf("\nEnter column number:");
    scanf("%d",userCol);   
    int Row=isInputValid(*userRow,1,3);
    int Col = isInputValid(*userCol, 1,3);
    if(Row&&Col)
        *stepsWon =*stepsWon+1;
}
/*Prints the current board.
/!\ Note that you must use a nested loop to print the board.*/
void printCurrentBoard (char board [N][N])
{
    for (int i=0;i<3;i++)
    {   printf("  %c",board[i][0]);
        for (int j=1;j<3;j++)
        {
            printf(" |  %c",board[i][j]);
        }
        printf("\n---------------\n");       
    }
}
