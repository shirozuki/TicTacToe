#include <stdio.h>
#include <stdlib.h>

int b[3][3];

int chkWin()
{
    for(int i = 0; i < 3; i++)
    {
        if(b[i][0] && b[i][1] == b[i][0] && b[i][2] == b[i][0])
            return b[i][0];

        if(b[0][i] && b[1][i] == b[0][i] && b[2][i] == b[0][i])
            return b[0][i];
    }

    if(!b[1][1])
        return 0;

    if(b[1][1] == b[0][0] && b[2][2] == b[0][0])
        return b[0][0];
    if (b[1][1] == b[2][0] && b[0][2] == b[1][1])
        return b[1][1];

    return 0;
}

void drwBrd()
{
    char t[3] = "X O";
    printf("\n");

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(j == 1 || j == 2)
                printf("|");

            printf(" %c ", t[b[i][j] + 1]);
        }

        if(i == 0 || i == 1)
            printf("\n-----------");
        printf("\n");
    }

    printf("\n\n");
}

int best_i, best_j;
int minimax(int val, int depth)
{
    int score, best = -1, changed = 0;
    score = chkWin();

    if(score)
    {
        if(score == val)
            return 1;
        else
            return -1;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(b[i][j])
                continue;

            changed = b[i][j] = val;
            score = -minimax(-val, depth + 1);
            b[i][j] = 0;

            //printf("Try: %d, %d\n", i, j);
            //printf("Depth: %d, Score: %d\n", depth, score);

            if(score <= best)
                continue;

            if(!depth)
            {
                best_i = i;
                best_j = j;
            }

            best = score;
        }
    }

    if(changed)
        return best;
    else
        return 0;
}

void initBrd()
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            b[i][j] = 0;
}

int game(int turn)
{
    int i, j, k, move, win = 0;

    initBrd();

    for(k = 0; k < 9; k++)
    {
        if(turn)
        {
            do
            {
                printf("Ruch gracza >> ");
                scanf("%d", &move);
            }
            while(move < 1 || move > 9);

            move = move - 1;

            i = move / 3;
            j = move % 3;

            b[i][j] = 1;
        }

        if(!turn)
        {
            minimax(-1, 0);

            b[best_i][best_j] = -1;
            printf("Ruch CPU >> %d\n", best_i * 3 + best_j + 1);
        }

        drwBrd();

        win = chkWin();

        if((win != 0))
        {
            return win;
        }

        turn = !turn;
    }

    return 0;
}

int main()
{
    int turn = 1, win = 0;

    printf("Kto zaczyna?\n"
           "0: CPU\n"
           "1: Człowiek\n");

    while(1)
    {
        printf(">> ");
        scanf("%d", &turn);

        if(turn == 1 || turn == 0)
            break;
        else
            continue;
    }

    win = game(turn);

    if(win == 1)
        printf("Wygrywa gracz!\n");
    else if(win == -1)
        printf("Wygrygwa CPU!\n");
    else
        printf("Remis!\n");

    return 0;
}
