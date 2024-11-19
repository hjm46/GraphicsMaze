#include <stdbool.h>

typedef struct{
    bool north;
    bool south;
    bool east;
    bool west;
} post;

typedef struct{
    int x;
    int y;
    int parent_index;
} cell;

post** gen_maze(int, int);
void gen_maze_re(int, int, post**);
void print_maze(int, int, post**);
cell* shortest_path(int, int, post**);
bool collision(int, int, int, post**);
