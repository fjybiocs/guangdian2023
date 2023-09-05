#ifndef _MAZE_TRAVEL_H_
#define _MAZE_TRAVEL_H_

#include <queue>
#include "list"
#include "maze.h"

using namespace std;

typedef list<Coordinate> Road;  // 路径，用list存储，因为不需要随机访问，且头插方便回溯

struct travelMap {
    Road roads[MAX_NUM_OF_TREASURE + 2][MAX_NUM_OF_TREASURE + 2];    // 记录宝藏间的路径
    int visited[MAX_NUM_OF_TREASURE + 2];  // 节点的访问记录，不用bool，因为要遍历多次，每次用不同的标记
    int minDistance = INT_MAX;  // 记录每个宝藏到终点的最短距离
    int minPath[MAX_NUM_OF_TREASURE + 2];  // 记录每个宝藏到终点的最短路径，记录的是宝藏的下标
};

void initTravelMap();
void getShortestVisitOrder();

extern travelMap travel;

#endif //_MAZE_TRAVEL_H_


