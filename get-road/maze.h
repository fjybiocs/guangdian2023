#ifndef _MAZE_H_
#define _MAZE_H_

const int X_LEN = 10;
const int Y_LEN = 10;

#define MAX_NUM_OF_TREASURE 4

typedef std::pair<int, int> Coordinate;  // first: x坐标; second: y坐标

struct MazeCell {
    // 每个迷宫格子，记录上下左右是否可以走，可以走为true，走不通为false
    // 都初始化为true，因为我们记录迷宫的方法是插入墙板，十字路口没有墙板
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
    // 记录是否访问过
    int visited = -1;   // 不用bool，要访问多次，每次用不同的flag
};

struct Maze {
    MazeCell cells[X_LEN][Y_LEN];   // 储存每个格子，第一个维度为x，第二个维度为y
    int numOfXCell = 0;
    int numOfYCell = 0;
    int numOfTreasure = 4;
    Coordinate treasures[MAX_NUM_OF_TREASURE + 2]{};  // 记录宝藏、起点终点的位置，起点位于0，终点位于末尾，中间的宝藏按照顺序排列
    Coordinate enterPoint;
    Coordinate exitPoint;
};

extern Maze maze;  // 创建一个迷宫

void initMaze(int, int);
void insertMazeWall(Coordinate a, Coordinate b);

#endif //_MAZE_H_
