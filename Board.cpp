#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() {
    panel = new boardData[64];
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            panel[y*8 + x].x = x*100 + 20;
            panel[y*8 + x].y = y*100 + 20;
        }
    }

}
Board::~Board() {
    cout << "destroying board data" << endl;
}