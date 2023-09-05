#include <list>
#include <iostream>
#include "mazeTravel.h"

travelMap travel;

inline bool isTheCellDestination(int x, int y) {
    for(int i=0; i<maze.numOfTreasure+2; i++) {
        if(maze.treasures[i].first == x && maze.treasures[i].second == y) {
            return true;
        }
    }
    return false;
}

inline int getIndexOfTreasureByCoordinate(Coordinate coordinate) {
    for(int i=0; i<maze.numOfTreasure+2; i++) {
        if(maze.treasures[i].first == coordinate.first && maze.treasures[i].second == coordinate.second) {
            return i;
        }
    }
    return -1;
}

inline Coordinate getCoordinateOfTreasureByIndex(int index) {
    return maze.treasures[index];
}

// 获取从某个点出发，到其他各个点的最短距离，flag是用于标记visited的编号，每次调用都必须不同
void getShortestPathToEveryPoint(int enterIndex, int flag) {
    Coordinate enter = getCoordinateOfTreasureByIndex(enterIndex); // 查找enter的坐标
    // first: 上一个节点, second: 当前节点
    vector<pair<int, Coordinate>> bfsVector;   // 注意，first记录的是上一个节点在bfsVector中的index，而不是上一个节点的坐标

    bfsVector.emplace_back(0, enter);   // first是0，这是起点的标志
    for(int i=0; i<bfsVector.size(); i++) {
        // 取出最前面的元素，并获得x和y坐标
        Coordinate current = bfsVector[i].second;
        int x = current.first;
        int y = current.second;

        // 如果已经访问过，则不再访问，直接丢弃
        if(maze.cells[x][y].visited == flag) {
            continue;
        }

        // 标记为已经访问
        maze.cells[x][y].visited = flag;

        // 找到一个宝藏，回溯路径（注意宝藏不能是本身）
        if (isTheCellDestination(x, y) && current != enter) {
            // 回溯路径
            list<Coordinate> path;
            auto recallIt = i;
            while (recallIt != 0) {   // 起点不用记录在链表中
                path.push_front(bfsVector[recallIt].second);  // 前插，回溯
                recallIt = bfsVector[recallIt].first;
            }
            travel.roads[enterIndex][getIndexOfTreasureByCoordinate(path.back())] = path;  // 记录路径
        }

        // 走下一步
        MazeCell cell = maze.cells[x][y];
        if (cell.up) {
            bfsVector.emplace_back(i, Coordinate{x, y - 1});
        }
        if (cell.down) {
            bfsVector.emplace_back(i, Coordinate{x, y + 1});
        }
        if (cell.left) {
            bfsVector.emplace_back(i, Coordinate{x - 1, y});
        }
        if (cell.right) {
            bfsVector.emplace_back(i, Coordinate{x + 1, y});
        }
    }
}

// 基于Maze初始化travelMap
void initTravelMap() {
    // 从起点和终点出发遍历迷宫，记录路径
    for (int i = 0; i < maze.numOfTreasure + 2; i++) {
        getShortestPathToEveryPoint(i, i);
    }
    travel.minPath[0] = 0;
    travel.minPath[maze.numOfTreasure + 1] = maze.numOfTreasure + 1;
}

void getShortestVisitOrder() {
    // 初始化travelMap
    initTravelMap();

    // 接下来都只是对travel做操作了
    // 暴力搜索，每次都从起点出发，从终点结束，找到最短的访问次序
    int per[MAX_NUM_OF_TREASURE + 1];   // 用于辅助排列组合, 有效范围为1 ~ numOfTreasure
    for (int i = 1; i <= maze.numOfTreasure; i++) {
        per[i] = i;
    }
    for (int i = 0; i <= (1 << maze.numOfTreasure) + 1; i++) {
//        for(int j=1; j<=maze.numOfTreasure; j++) {
//            cout << per[j] << " ";
//        }
//        cout << endl;

        int distance = travel.roads[0][per[1]].size();  // 起点到第一个宝藏的距离
        for (int j = 1; j <= maze.numOfTreasure-1; j++) {  // 计算路径长度
            distance += travel.roads[per[j]][per[j+1]].size();  // 两个宝藏之间的距离
        }
        distance += travel.roads[per[maze.numOfTreasure]][maze.numOfTreasure+1].size();  // 最后一个宝藏到终点的距离
        if(distance < travel.minDistance) {
            travel.minDistance = distance;
            for(int k=1; k<=maze.numOfTreasure; k++) {
                travel.minPath[k] = per[k];
            }
        }

        next_permutation(per+1, per + maze.numOfTreasure+1);    // 生成下一个排列
    }
}

