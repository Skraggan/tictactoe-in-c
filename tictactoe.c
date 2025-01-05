#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printScreen(char board[3][3], int *turn)
{
    printf("\n");
    printf("Axels superkomplicerade TicTacToe-spel\n");
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            printf("-------------\n");
        }
        printf("| %c | %c | %c |\n", board[0][i], board[1][i], board[2][i]);
        printf("-------------\n");
    }
    printf("\n");
    if (*turn == 1)
    {
        printf("It is Player 1's turn!");
    }
    else if (*turn == -1)
    {
        printf("It is Player 2's turn!");
    }
    printf("\n");
}

char handleStrictChoiceInput()
{
    int validInput = 0;
    char givenInput;
    while (validInput == 0)
    {
        scanf("%c", &givenInput);
        if (givenInput == 'y' || givenInput == 'n')
        {
            validInput = 1;
            break;
        }
        else
        {
            printf("Invalid input! Try again.\n");
        }
    }
    return givenInput;
}

int handleStrictIntInput(int min, int max)
{
    int validInput = 0;
    int givenInput;
    while (validInput == 0)
    {
        scanf("%d", &givenInput);
        if (givenInput >= min && givenInput <= max)
        {
            validInput = 1;
            break;
        }
        else
        {
            printf("Invalid input!\nTry again:\n");
        }
    }
    return givenInput;
}

void handleMove(int (*pCurrentMove)[2], char (*pBoard)[3][3], char *pCurrentPlayer)
{
    int col, row;
    int validInput = 0;
    do
    {
        printf("Enter Column (1-3): ");
        col = handleStrictIntInput(1, 3) - 1;
        printf("Enter Row (1-3): ");
        row = handleStrictIntInput(1, 3) - 1;

        if ((*pBoard)[col][row] != '-')
        {
            printf("Slot already occupied!\n");
        }
        else
        {
            validInput = 1;
            break;
        }
    } while (validInput == 0);

    (*pCurrentMove)[0] = col;
    (*pCurrentMove)[1] = row;

    (*pBoard)[col][row] = *pCurrentPlayer;
}

int checkGameState(int (*pCurrentMove)[2], char (*pBoard)[3][3], char *pCurrentPlayer)
{
    int placedCol = (*pCurrentMove)[0];
    int placedRow = (*pCurrentMove)[1];

    // Vertical check
    if ((*pBoard)[placedCol][0] == *pCurrentPlayer && (*pBoard)[placedCol][1] == *pCurrentPlayer && (*pBoard)[placedCol][2] == *pCurrentPlayer)
    {
        return 1;
    }

    // Horizontal check
    if ((*pBoard)[0][placedRow] == *pCurrentPlayer && (*pBoard)[1][placedRow] == *pCurrentPlayer && (*pBoard)[2][placedRow] == *pCurrentPlayer)
    {
        return 1;
    }

    // Diagonal up-right check
    if ((placedCol == 0 && placedRow == 2) || (placedCol == 1 && placedRow == 1) || (placedCol == 2 && placedRow == 0))
    {
        if ((*pBoard)[0][2] == *pCurrentPlayer && (*pBoard)[1][1] == *pCurrentPlayer && (*pBoard)[2][0] == *pCurrentPlayer)
        {
            return 1;
        }
    }

    // Diagonal up-left check
    if ((placedCol == 2 && placedRow == 2) || (placedCol == 1 && placedRow == 1) || (placedCol == 0 && placedRow == 0))
    {
        if ((*pBoard)[0][0] == *pCurrentPlayer && (*pBoard)[1][1] == *pCurrentPlayer && (*pBoard)[2][2] == *pCurrentPlayer)
        {
            return 1;
        }
    }

    return 0;
}

void gameOver(char *pCurrentPlayer, char (*pBoard)[3][3], int *pTurn, char (*player1name)[], char (*player2name)[])
{
    char winnerName[10];
    if (*pCurrentPlayer == 'X')
    {
        printf("Game Over! %s has won the game!\n", *player1name);
    }
    else
    {
        printf("Game Over! %s has won the game!\n", *player2name);
    }
    printf("Would you like to play again? (y/n)\n");
    char choice = handleStrictChoiceInput();
    if (choice == 'n')
    {
        return;
    }
    else
    {
        if (*pCurrentPlayer == 'X')
        {
            *pTurn = 1;
        }
        else
        {
            *pTurn = -1;
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                (*pBoard)[i][j] = '-';
            }
        }
    }
}

int main()
{
    char board[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}};
    char(*pBoard)[3][3] = (&board);
    char player1 = 'X';
    char player1name[] = "Player 1";
    char player2 = 'O';
    char player2name[] = "Player 2";
    char *pCurrentPlayer = &player1;
    int turn = 1;
    int currentMove[2];
    int(*pCurrentMove)[2] = &currentMove;
    int gameState = 0;

    while (turn != 0)
    {
        system("cls");
        printScreen(board, &turn);
        handleMove(pCurrentMove, pBoard, pCurrentPlayer);
        gameState = checkGameState(pCurrentMove, pBoard, pCurrentPlayer);
        if (gameState == 0)
        {
            turn = turn * -1;
            if (turn == 1)
            {
                pCurrentPlayer = &player1;
            }
            else
            {
                pCurrentPlayer = &player2;
            }
        }
        else
        {
            turn = 0;
            system("cls");
            printScreen(board, &turn);
            gameOver(pCurrentPlayer, pBoard, &turn, &player1name, &player2name);
        }
    }

    return 0;
}