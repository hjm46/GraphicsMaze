typedef struct{
    int north;
    int south;
    int east;
    int west;
} post;

post** gen_maze(int len, int wid);
void gen_maze_re(int row, int col, post** maze);
void print_maze(int len, int wid, post** maze);
