#include <iostream>

#include "maze.h"


using namespace std;

Maze maze;

// 初始化迷宫，初始化迷宫尺寸，把边界上的格子往边界外走的方向都标记为不可行
void initMaze(int numOfXCell, int numOfYCell) {
    // 记录迷宫边长
    maze.numOfXCell = numOfXCell;
    maze.numOfYCell = numOfYCell;

    // 记录起点终点
    maze.enterPoint = {0, numOfYCell - 1};
    maze.exitPoint = {numOfXCell - 1, 0};

    maze.treasures[0] = maze.enterPoint;
    maze.treasures[MAX_NUM_OF_TREASURE+1] = maze.exitPoint;
    maze.treasures[1] = make_pair(1, 1);
    maze.treasures[2] = make_pair(7, 2);
    maze.treasures[3] = make_pair(1, 4);
    maze.treasures[4] = make_pair(8, 5);

    // 对迷宫格子进行初始化
    for (int i = 0; i < numOfXCell; i++) {
        // 上下边界，i为x，也就是初始化y为0和numOfCell-1的位置
        maze.cells[i][0].up = false;
        maze.cells[i][numOfYCell - 1].down = false;
        // 左右边界，i为y，也就是初始化x为0和numOfCell-1的位置
        maze.cells[0][i].left = false;
        maze.cells[numOfXCell - 1][i].right = false;
    }
}

// 在迷宫中插入墙壁，需要给出墙壁两侧的格子坐标
void insertMazeWall(Coordinate a, Coordinate b) {
    assert(a.first != b.first || a.second != b.second); // 断言：两个点的x和y坐标必须有一个不同
    assert(!(a.first == b.first && a.second == b.second));  // 断言：两个点的x和y坐标不同同时都相同

    // 先判断方向
    if (a.first - b.first == 0) {    // x坐标相同，也就是一个在上一个在下
        if (min(a.second, b.second) >= 0) {  // 如果小于零，那么就是边界线，不标记更小（-1）的那个
            maze.cells[a.first][min(a.second, b.second)].down = false;  // 把上面的down标记为false
        }
        maze.cells[a.first][max(a.second, b.second)].up = false;  // 把下面的up标记为false
    } else {    // y坐标相同，也就是一个在左一个在右
        if (min(a.first, b.first) >= 0) {  // 如果小于零，那么就是边界线，不标记更小（-1）的那个
            maze.cells[min(a.first, b.first)][a.second].right = false;  // 把左边的right标记为false
        }
        maze.cells[max(a.first, b.first)][a.second].left = false;  // 把右边的left标记为false
    }
}
