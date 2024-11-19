#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include <stdbool.h>

//maze matrix represents the middle of the maze,
// ie all posts have a valid north/south/east/west value and no posts
// are on the border
//the border around the maze is constant
// 0 means theres no wall
// 1 means there is a wall

// confirmed all walls are constant between posts

//enter bottom left exit top right

int length;
int width;

// prints maze
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
            if(row!=0)
                maze[row-1][col].south = 0;
        }
        else
        {
            int remove = rand()%(lenN+1);
            maze[row-remove][col].north = 0;
            if(row-remove != 0)
                maze[row-remove-1][col].south = 0;
        }
    }
    
    // remove south wall
    if(wall!=1)
    {
        if(lenS == 0)
        {
            maze[row][col].south = 0;
            if(row!=length-1)
                maze[row+1][col].north = 0;
        }
        else
        {
            int remove = rand()%(lenS+1);
            maze[row+remove][col].south = 0;
            if(row+remove != length-1)
                maze[row+remove+1][col].north = 0;
        }
    }

    // remove east wall
    if(wall!=2)
    {
        if(lenE == 0)
        {
            maze[row][col].east = 0;
            if(col!=width-1)
                maze[row][col+1].west = 0;
        }
        else
        {
            int remove = rand()%(lenE+1);
            maze[row][col+remove].east = 0;
            if(col+remove != width-1)
                maze[row][col+remove+1].west = 0;
        }
    }

    // remove west wall
    if(wall!=3)
    {
        if(lenW == 0)
        {
            maze[row][col].west = 0;
            if(col!=0)
                maze[row][col-1].east = 0;
        }
        else
        {
            int remove = rand()%(lenW+1);
            maze[row][col-remove].west = 0;
            if(col-remove != 0)
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


// takes size of maze and returns maze data structure
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

// takes index of player position and maze data structure
// returns a array of cell structs which have the x,y coordinates of which cells to traverse
cell* shortest_path(int start_row, int start_col, post** maze)
{
    bool visited[length+1][width+1];
    for(int i=0; i<length+1; i+=1)
    {
        for(int j=0; j<width+1; j+=1)
        {
            visited[i][j] = 0;
        }
    }

    visited[start_row][start_col] = 1;
    cell *queue = (cell*)malloc((length+1)*(width+1)*sizeof(cell));
    int front=0;
    int back=0;
    queue[back] = (cell){start_row, start_col, -1};

    //because there is always a path to the end
    while(visited[length][0]==0)
    {
        int row = queue[front].x;
        int col = queue[front].y;

        //only two ways to get into and out of a corner
        //top right corner
        if(row==0 && col==width)
        {
            // go south
            if(maze[0][col-1].east==0 && visited[row+1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row+1, col, front};
                visited[row+1][col] = 1;
                // printf("South: %d, %d\n", row+1, col);
            }

            // go west
            if(maze[0][col-1].north==0 && visited[row][col-1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col-1, front};
                visited[row][col-1] = 1;
                // printf("West: %d, %d\n", row, col-1);
            }
            front+=1;
        }

        // top left corner
        else if(row==0 && col==0)
        {
            // can go east
            if(maze[0][0].north==0 && visited[row][col+1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col+1, front};
                visited[row][col+1] = 1;
                // printf("ahh\n");
            }

            // can go south
            if(maze[0][0].west==0 && visited[row+1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row+1, col, front};
                visited[row+1][col] = 1;
                // printf("hi\n");
            }
            front+=1;
        }

        // bottom right corner
        else if(row==length && col==width)
        {
            if(maze[length-1][width-1].south==0 && visited[row][col-1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col-1, front};
                visited[row][col-1] = 1;
                // printf("bottom rigth s: %d, %d\n", row, col-1);
            }

            if(maze[length-1][width-1].east==0 && visited[row-1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row-1, col, front};
                visited[row-1][col] = 1;
                // printf("bottom right e: %d, %d\n", row-1, col);
            }
            front+=1;
        }

        // first col edge case
        else if(col==0)
        {
            // can go east
            if(maze[row][col].north==0 && visited[row][col+1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col+1, front};
                visited[row][col+1] = 1;
                // printf("a: %d, %d\n", row, col+1);
            }

            // can go south
            if(maze[row][col].west==0 && visited[row+1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row+1, col, front};
                visited[row+1][col] = 1;
                // printf("b: %d, %d\n", row+1, col);
            }

            // can go north
            if(maze[row-1][col].west==0 && visited[row-1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row-1, col, front};
                visited[row-1][col] = 1;
                // printf("c: %d, %d\n", row-1, col);
            }
            front+=1;
        }

        // top row edge case
        else if(row==0)
        {
            // can go east
            if(maze[row][col].north==0 && visited[row][col+1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col+1, front};
                visited[row][col+1] = 1;
                // printf("d: %d, %d\n", row, col+1);
            }

            // can go south
            if(maze[row][col].west==0 && visited[row+1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row+1, col, front};
                visited[row+1][col] = 1;
                // printf("e: %d, %d\n", row+1, col);
            }

            // can go east
            if(maze[row][col-1].north==0 && visited[row][col-1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col-1, front};
                visited[row][col-1] = 1;
                // printf("f: %d, %d\n", row, col-1);
            }
            front+=1;
        }

        // last column edge case
        else if(col==width)
        {
            // can go west
            if(maze[row][col-1].north==0 && visited[row][col-1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col-1, front};
                visited[row][col-1] = 1;
                // printf("g: %d, %d\n", row, col-1);
            }

            // can go south
            if(maze[row][col-1].east==0 && visited[row+1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row+1, col, front};
                visited[row+1][col] = 1;
                // printf("h: %d, %d\n", row+1, col);
            }

            // can go north
            if(maze[row-1][col-1].east==0 && visited[row-1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row-1, col, front};
                visited[row-1][col] = 1;
                // printf("i: %d, %d\n", row-1, col);
            }
            front+=1;
        }

        // bottom row edge case
        else if(row==length)
        {
            // can go east
            if(maze[row-1][col].south==0 && visited[row][col+1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col+1, front};
                visited[row][col+1] = 1;
                // printf("j: %d, %d\n", row, col+1);
            }

            // can go north
            if(maze[row-1][col].west==0 && visited[row-1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row-1, col, front};
                visited[row-1][col] = 1;
                // printf("k: %d, %d\n", row-1, col);
            }

            // can go west
            if(maze[row-1][col-1].south==0 && visited[row][col-1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col-1, front};
                visited[row][col-1] = 1;
                // printf("l: %d, %d\n", row, col-1);
            }
            front+=1;
        }

        // interior
        else
        {
            // can move east
            if(maze[row][col].north==0 && visited[row][col+1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col+1, front};
                visited[row][col+1] = 1;
                // printf("m: %d, %d\n", row, col+1);
            }

            // can move south
            if(maze[row][col].west==0 && visited[row+1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row+1, col, front};
                visited[row+1][col] = 1;
                // printf("n: %d, %d\n", row+1, col);
            }

            // // can move north
            if(maze[row-1][col-1].east==0 && visited[row-1][col]==0)
            {
                back+=1;
                queue[back] = (cell){row-1, col, front};
                visited[row-1][col] = 1;
                // printf("o: %d, %d\n", row-1, col);
            }

            // // can move west
            if(maze[row-1][col-1].south==0 && visited[row][col-1]==0)
            {
                back+=1;
                queue[back] = (cell){row, col-1, front};
                visited[row][col-1] = 1;
                // printf("p: %d, %d\n", row, col-1);
            }
            front+=1;
        }
    }

    // printf("\n");
    // printf("%d, %d, Length: %d\n", queue[back].x, queue[back].y, length);
    while(queue[back].x != length && queue[back].y != width)
    {
        // printf("why\n");
        // printf("%d, %d\n", queue[back].x, queue[back].y);
        back-=1;
    }

    cell *temp = (cell*)malloc((back+1)*sizeof(cell));
    
    int index=back;
    int i=back;
    while(i>-1)
    {
        temp[index] = (cell){queue[i].x, queue[i].y, -1};
        index-=1;
        i = queue[i].parent_index;
    }
    index+=2;
    int size = back-index+1;
    cell *path = (cell*)malloc(size*sizeof(cell));
    // printf("\n");
    for(int i=0; i<size; i+=1)
    {
        path[i] = temp[index];
        index+=1;
        // printf("%d, %d\n", path[i].x, path[i].y);
    }

    free(temp);
    free(queue);
    
    return path;
}

bool collision(int row, int col, int direction, post** maze)
{
    if(row>length || col>width || row<0 || col<0)
        return false;
    // bottom left corner
    else if(row == length && col == 0)
    {
        if(direction == 0)
            return false;
        else if(direction == 3)
            return true;
        else if(direction == 1)
        {
            if(maze[row-1][col].west == 1)
                return true;
            else
                return false;
        }   
        
        else if(direction == 2)
        {
            if(maze[row-1][col].south == 1)
                return true;
            else
                return false;
        } 
    }

    // top right corner
    else if(row == 0 && col == width)
    {
        if(direction == 1)
            return false;
        else if(direction == 2)
            return true;
        else if(direction == 0)
        {
            if(maze[row][col-1].east == 1)
                return true;
            else
                return false;
        }   
        
        else if(direction == 3)
        {
            if(maze[row][col-1].north == 1)
                return true;
            else
                return false;
        } 
    }

    // top left corner
    else if(row == 0 && col == 0)
    {
        if(direction == 1)
            return true;
        else if(direction == 3)
            return true;
        else if(direction == 0)
        {
            if(maze[row][col].west == 1)
                return true;
            else
                return false;
        }

        else if(direction == 2)
        {
            if(maze[row][col].north == 1)
                return true;
            else
                return false;
        }
    }

    // bottom right corner
    else if(row == length && col == width)
    {
        if(direction == 0)
            return true;
        else if(direction == 2)
            return true;
        else if(direction == 1)
        {
            if(maze[row-1][col-1].east == 1)
                return true;
            else
                return false;
        }

        else if(direction == 3)
        {
            if(maze[row-1][col-1].south == 1)
                return true;
            else
                return false;
        }
    }

    // first row
    else if(row == 0)
    {
        // move south
        if(direction == 1)
            return true;
        if(direction == 0)
        {
            if(maze[row][col-1].east == 1)
                return true;
            else
                return false;
        }

        if(direction == 3)
        {
            if(maze[row][col-1].north == 1)
                return true;
            else
                return false;
        }

        if(direction == 2)
        {
            if(maze[row][col].north == 1)
                return true;
            else
                return false;
        }

    }

    // last row
    else if(row == length)
    {
        // move north
        if(direction == 0)
            return true;
        if(direction == 1)
        {
            if(maze[row-1][col].east == 1)
                return true;
            else
                return false;
        }
        if(direction == 3)
        {
            if(maze[row-1][col-1].south == 1)
                return true;
            else
                return false;
        }
        if(direction == 2)
        {
            if(maze[row-1][col].south == 1)
                return true;
            else
                return false;
        }
    }

    // first column
    else if(col == 0)
    {
        if(direction == 3)
            return true;
        if(direction == 0)
        {
            if(maze[row][col].west == 1)
                return true;
            else
                return false;
        }
        if(direction == 1)
        {
            if(maze[row-1][col].west == 1)
                return true;
            else
                return false;
        }
        if(direction == 2)
        {
            if(maze[row-1][col].south == 1)
                return true;
            else
                return false;
        }
    }

    // last column
    else if (col == width)
    {
        if(direction == 2)
            return true;
        if(direction == 1)
        {
            if(maze[row-1][col-1].east == 1)
                return true;
            else
                return false;
        }
        if(direction == 0)
        {
            if(maze[row][col-1].east == 1)
                return true;
            else
                return false;
        }
        if(direction == 3)
        {
            if(maze[row-1][col-1].south == 1)
                return true;
            else
                return false;
        }
    }

    // interior
    else
    {
        if(direction == 0)
        {
            if(maze[row][col].west == 1)
                return true;
            else
                return false;
        }
        if(direction == 1)
        {
            if(maze[row-1][col].west == 1)
                return true;
            else
                return false;
        }
        if(direction == 3)
        {
            if(maze[row][col-1].north == 1)
                return true;
            else
                return false;
        }
        if(direction == 2)
        {
            if(maze[row][col].north == 1)
                return true;
            else
                return false;
        }
    }

    return false;
}

// int main(int argc, char **argv)
// {
//     post** maze = gen_maze(4, 4);
//     print_maze(length, width, maze);
//     printf("Start: %d, %d\n", length, 1);
//     // shortest_path(0,width,maze);
//     printf("%d\n", collision(2,3,0,maze));
//     return 0;
// }