#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

//maze matrix represents the middle of the maze,
// ie all posts have a valid north/south/east/west value and no posts
// are on the border
//the border around the maze is constant
// 0 means theres no wall
// 1 means there is a wall

//enter bottom left exit top right

int length;
int width;

void print_maze(int len, int wid, post** maze)
{
    //top border
    printf("+");
    for(int j=0; j<wid; j+=1)
    {
        printf("---+");
    }
    printf("   +\n|");

    for(int j=0; j<wid; j+=1)
    {
        printf("   ");
        if(maze[0][j].north == 1)
            printf("|");
        else
            printf(" ");
    }
    printf("   |\n");

    //interior
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
    printf("+   +");
    for(int j=1; j<wid+1; j+=1)
    {
        printf("---+");
    }
    printf("\n\n");
}

void gen_maze_re(int row, int col, post** maze)
{
    //length of each walls with crosshair as origin
    int lenN = 0;
    int lenS = 0;
    int lenE = 0;
    int lenW = 0;

    //crosshair
    maze[row][col] = (post){1,1,1,1};
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

    //north walls
    for(int i=row-1; i>=0; i-=1)
    {
        maze[i][col].south = 1;
        if(maze[i][col].east==1 || maze[i][col].west==1)
            break;
        maze[i][col].north = 1;
        lenN+=1;
    }

    //south walls
    for(int i=row+1; i<length; i+=1)
    {
        maze[i][col].north = 1;
        if(maze[i][col].east==1 || maze[i][col].west==1)
            break;
        maze[i][col].south = 1;
        lenS+=1;
    }

    //west walls
    for(int i=col-1; i>=0; i-=1)
    {
        maze[row][i].east = 1;
        if(maze[row][i].north==1 || maze[row][i].south==1)
            break;
        maze[row][i].west = 1;
        lenW+=1;
    }

    //east walls
    for(int i=col+1; i<width; i+=1)
    {
        maze[row][i].west = 1;
        if(maze[row][i].north==1 || maze[row][i].south==1)
            break;
        maze[row][i].east = 1;
        lenE+=1;
    }

    // North=0, South=1, East=2, West=3
    int wall = rand()%4;

    // remove north wall
    if(wall!=0)
    {
        if(lenN == 0)
        {
            maze[row][col].north = 0;
        }
        else
        {
            int remove = rand()%(lenN+1);
            maze[row-remove][col].north = 0;
            if(remove != lenN)
                maze[row-remove-1][col].south = 0;
        }
    }
    
    // remove south wall
    if(wall!=1)
    {
        if(lenS == 0)
        {
            maze[row][col].south = 0;
        }
        else
        {
            int remove = rand()%(lenS+1);
            maze[row+remove][col].south = 0;
            if(remove != lenS)
                maze[row+remove+1][col].north = 0;
        }
    }

    // remove east wall
    if(wall!=2)
    {
        if(lenE == 0)
        {
            maze[row][col].east = 0;
        }
        else
        {
            int remove = rand()%(lenE+1);
            maze[row][col+remove].east = 0;
            if(remove != lenE)
                maze[row][col+remove+1].west = 0;
        }
    }

    // remove west wall
    if(wall!=3)
    {
        if(lenW == 0)
        {
            maze[row][col].west = 0;
        }
        else
        {
            int remove = rand()%(lenW+1);
            maze[row][col-remove].west = 0;
            if(remove != lenW)
                maze[row][col-remove-1].east = 0;
        }
    }

    //getting ranges for next crosshair
    int minX = row-lenN;
    int maxX = row+lenS;
    int minY = col-lenW;
    int maxY = col+lenE;

    //top right corner
    if(lenN!=0 && lenE!=0)
    {
        int x = rand()%(row-minX)+minX;
        int y = rand()%(maxY-col)+col+1;
        gen_maze_re(x, y, maze);
    }

    //bottom right corner
    if(lenS!=0 && lenE!=0)
    {
        int x = rand()%(maxX-row)+row+1;
        int y = rand()%(maxY-col)+col+1;
        gen_maze_re(x, y, maze);
    }

    //top left corner
    if(lenN!=0 && lenW!=0)
    {
        int x = rand()%(row-minX)+minX;
        int y = rand()%(col-minY)+minY;
        gen_maze_re(x, y, maze);
    }

    //bottom left corner
    if(lenS!=0 && lenW!=0)
    {
        int x = rand()%(maxX-row)+row+1;
        int y = rand()%(col-minY)+minY;
        gen_maze_re(x, y, maze);
    }

    return;
}



post** gen_maze(int len, int wid)
{
    srand(time(0));
    length = len-1;
    width = wid-1;
    post **maze = (post**)malloc(length*sizeof(post*));
    for(int i=0; i<length; i+=1)
    {
        maze[i] = (post*)malloc(width*sizeof(post));
    }

    for(int i=0; i<length; i+=1)
    {
        for(int j=0; j<width; j+=1)
        {
            maze[i][j] = (post){0,0,0,0};
        }
    }


    int row = rand()%(length);
    int col = rand()%(width);
    gen_maze_re(row, col, maze);
    return maze;
}

int main(int argc, char **argv)
{
    post** maze = gen_maze(15, 15);
    print_maze(length, width, maze);
    return 0;
}