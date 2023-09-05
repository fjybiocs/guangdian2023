#include <iostream>
#include "mazeTravel.h"

using namespace std;

int main() {
    initMaze(10, 10);
    int x1, y1, x2, y2;
    while (true) {
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1) {
            break;
        }
        insertMazeWall({x1, y1}, {x2, y2});
    }

    getShortestVisitOrder();

    cout << "Done.";
}
