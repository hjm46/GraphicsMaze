#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int north;
    int south;
    int east;
    int west;
} cell;

int length;
int width;

void print_maze(int len, int wid, cell maze[len][wid])
{
    //top border
    printf("+");
    for(int j=0; j<wid+1; j+=1)
    {
        printf("---+");
    }
    printf("\n|");

    for(int j=0; j<wid; j+=1)
    {
        printf("   ");
        if(maze[0][j].north == 1)
            printf("|");
        else
            printf(" ");
    }
    printf("   |\n");


    for(int i=0; i<len; i+=1)
    {
        printf("+");
        if(maze[i][0].west == 1)
            printf("---");
        else
            printf("   ");
        printf("+");

        for(int j=1; j<wid; j+=1)
        {
            if(maze[i][j].west == 1 && maze[i][j-1].east == 1)
                printf("---");
            else
                printf("   ");
            printf("+");
        }

        if(maze[i][wid-1].east == 1)
            printf("---");
        else
            printf("   ");
        printf("+");

        printf("\n|");
        for(int j=0; j<wid; j+=1)
        {
            printf("   ");
            if(i == length-1 && maze[i][j].south == 1)
                printf("|");
            else if(maze[i][j].south == 1 && maze[i+1][j].north == 1)
                printf("|");
            else
                printf(" ");
        }
        printf("   |");
        printf("\n");
    }

    //bottom border
    printf("+");
    for(int j=0; j<wid+1; j+=1)
    {
        printf("---+");
    }
    printf("\n");
}

void gen_maze_re(int row, int col, cell maze[length][width])
{
    // int hWall = rand()%(length-1);
    // int vWall = rand()%(width-1);
    // int a = rand()%(col);
    // int b = rand()%(width-col-1)+col;

    printf("%d, %d\n", row, col);

    // printf("%d, %d, %d, %d\n", x, y, a, b);

    int lenN = 0;
    int lenS = 0;
    int lenE = 0;
    int lenW = 0;

    maze[row][col] = (cell){1,1,1,1};
    if(col!=0)
    {
        maze[row][col-1].east = 1;
    }

    if(col<width-1)
    {
        maze[row][col+1].west = 1;
    }

    if(row!=0)
    {
        maze[row-1][col].south = 1;
    }

    if(row<length-1)
    {
        maze[row+1][col].north = 1;
    }

    printf("%d\n", col);

    //north walls
    // if(row==0)
    // {
    //     maze[row+1][col].north = 1;
    //     lenN+=1;
    // }

    // for(int i=row-1; i>=0; i-=1)
    // {
    //     // if(maze[i][col].east==1 && maze[i][col].west==1)
    //     // {
    //     //     maze[i][col].north = 1;
    //     //     lenN+=1;
    //     //     // maze[i][col].south = 1;
    //     //     break;
    //     // }

    //     maze[i][col].north = 1;
    //     maze[i][col].south = 1;
    //     lenN+=1;
    // }
    // lenN+=1;


    //south walls
    // if(row==length-1)
    // {
    //     maze[row][col].south = 1;
    //     // lenS+=1;
    // }

    // for(int i=row; i<length; i+=1)
    // {
    //     // if(maze[i][col].east==1 && maze[i][col].west==1)
    //     // {
    //     //     maze[i][col].north = 1;
    //     //     lenN+=1;
    //     //     // maze[i][col].south = 1;
    //     //     break;
    //     // }

    //     maze[i][col].north = 1;
    //     maze[i][col].south = 1;
    //     // lenS+=1;
    // }
    // lenS+=1;


    //east walls
    // for(int i=col; i>=0; i-=1)
    // {
    //     // if(maze[i][col].east==1 && maze[i][col].west==1)
    //     // {
    //     //     maze[i][col].north = 1;
    //     //     lenN+=1;
    //     //     // maze[i][col].south = 1;
    //     //     break;
    //     // }

    //     maze[row][i].east = 1;
    //     maze[row][i].west = 1;
    //     lenE+=1;
    // }
    // lenE+=1;


    // //west walls

    // for(int i=col+1; i<width; i+=1)
    // {
    //     // if(maze[i][col].east==1 && maze[i][col].west==1)
    //     // {
    //     //     maze[i][col].north = 1;
    //     //     lenN+=1;
    //     //     // maze[i][col].south = 1;
    //     //     break;
    //     // }

    //     maze[row][i].east = 1;
    //     maze[row][i].west = 1;
    //     lenW+=1;
    // }

    printf("%d, %d, %d, %d\n", lenN, lenS, lenE, lenW);

    // int wall = rand()%4;
    // printf("%d\n", wall);

    // if(wall!=0)
    // {
    //     if(lenN == 0)
    //     {
    //         maze[row][col].north = 0;
    //         maze[row-1][col].south = 0;
    //     }
    //     else
    //     {
    //         int remove = rand()%(lenN+1);
    //         printf("%d\n", remove);
    //         maze[row-remove][col].north = 0;
    //         maze[row-remove][col].south = 0;
    //     }
    // }
    // if(wall!=1 && row!=length-1)
    // {
    //     int remove = rand()%row;
    //     printf("%d\n", remove);
    //     if(remove == length-1)
    //         maze[remove+1][col].north = 0;
    //     else
    //     {
    //         maze[remove+1][col].north = 0;
    //         maze[remove-1][col].south = 0;
    //     }
    // }


    // if(row!=0 && col!=0)
    // {
    //     gen_maze_re(rand()%row, rand()%col, maze);
    // }
}



void gen_maze(int len, int wid)
{
    length = len-1;
    width = wid-1;
    cell maze[len][wid];
    for(int i=0; i<length; i+=1)
    {
        for(int j=0; j<width; j+=1)
        {
            maze[i][j] = (cell){0,0,0,0};
        }
    }

    int row = rand()%(length);
    int col = rand()%(width);
    gen_maze_re(row, col, maze);

    print_maze(length, width, maze);
    //four numbers: north, south, east, west
}

int main(int argc, char **argv)
{
    srand(time(0));
    gen_maze(5, 5);
    return 0;
}