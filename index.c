#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char board[3][3];
int player1Wins = 0;
int player2Wins = 0;
int computerWins = 0;
int draws = 0;
void resetBoard()
{
    char ch = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ch++;
        }
    }
}

void displayBoard()
{
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c ",
               board[i][0],
               board[i][1],
               board[i][2]);

        if (i < 2)
            printf("\n---|---|---\n");
    }

    printf("\n");
}

int placeMove(int pos, char mark)
{
    if (pos < 1 || pos > 9)
        return 0;

    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (board[row][col] == 'X' ||
        board[row][col] == 'O')
        return 0;

    board[row][col] = mark;
    return 1;
}

char checkWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return board[i][0];
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return board[0][i];
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return ' ';
}

int isDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' &&
                board[i][j] != 'O')
                return 0;
        }
    }

    return 1;
}

void playerVsPlayer()
{
    int player;
    int pos;
    char mark;
    char playAgain;

    do
    {
        resetBoard();
        player = 1;

        while (1)
        {
            displayBoard();

            if (player == 1)
                mark = 'X';
            else
                mark = 'O';

            printf("\nPlayer %d (%c), Enter Position (1-9): ",
                   player, mark);

            scanf("%d", &pos);

            if (!placeMove(pos, mark))
            {
                printf("Invalid Move! Try Again.\n");
                continue;
            }

            char winner = checkWinner();
if(winner == 'X' || winner == 'O')
{
    if(player == 1)
        player1Wins++;
    else
        player2Wins++;

    displayBoard();
    printf("\nPlayer %d Wins!\n", player);
    break;
}
           
            if (isDraw())
            {
                displayBoard();
                draws++;
                printf("\nMatch Draw!\n");
                break;
            }

            if (player == 1)
                player = 2;
            else
                player = 1;
        }

        printf("\nPlay Again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');
}
int computerMove()
{
    int pos;

    while (1)
    {
        pos = rand() % 9 + 1;

        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;

        if (board[row][col] != 'X' &&
            board[row][col] != 'O')
        {
            return pos;
        }
    }
}
void playerVsComputer()
{
    int pos;
    resetBoard();

    while (1)
    {
        displayBoard();

        printf("\nYour Turn (X): ");
        scanf("%d", &pos);

        if (!placeMove(pos, 'X'))
        {
            printf("Invalid Move!\n");
            continue;
        }

       if(checkWinner()=='X')
{
    player1Wins++;

    displayBoard();
    printf("\nYou Win!\n");
    break;
}

        if (isDraw())
        {
            displayBoard();
            draws++;
            printf("\nMatch Draw!\n");
            break;
        }

        int botPos = computerMove();

        placeMove(botPos, 'O');

        printf("\nComputer chose %d\n", botPos);

        if (checkWinner() == 'O')
        {
            displayBoard();
            computerWins++;
            printf("\nComputer Wins!\n");
            break;
        }

        if (isDraw())
        {
            displayBoard();
            draws++;
            printf("\nMatch Draw!\n");
            break;
        }
    }
}
void showScoreboard()
{
    printf("\n====================\n");
    printf("     SCOREBOARD\n");
    printf("====================\n");

    printf("Player 1 Wins : %d\n", player1Wins);
    printf("Player 2 Wins : %d\n", player2Wins);
    printf("Computer Wins : %d\n", computerWins);
    printf("Draws         : %d\n", draws);
}
void resetScoreboard()
{
    player1Wins = 0;
    player2Wins = 0;
    computerWins = 0;
    draws = 0;

    printf("\nScoreboard Reset Successfully!\n");
}
int main()
{
    int choice;
    srand(time(NULL));
    while (1)
    {
        printf("\n********************************\n");
        printf("*      TIC TAC TOE GAME        *\n");
        printf("*       By Lokesh             *\n");
        printf("*      PPS Project       *\n");
        printf("********************************\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer\n");
        printf("3. Scoreboard\n");
        printf("4. Reset Scoreboard\n");
        printf("5. Exit\n");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            playerVsPlayer();
            break;

        case 2:

            playerVsComputer();
            break;

        case 3:
            showScoreboard();
            break;

        case 4:
            resetScoreboard();
            break;

        case 5:
            printf("\nThanks For Playing!\n");
            return 0;
        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}