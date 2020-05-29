#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

Board::Board() {
    panel = new boardData[64];

    //Setting each spot x,y position (left up corner)
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            panel[y*8 + x].x = x*100 + 20;
            panel[y*8 + x].y = y*100 + 20;
        }
    }
    //preocuppying starting spots
    for (int i = 0; i < 16; i++) {
        panel[i].occupied = true;
    }
    for (int i = 47; i < 64; i++) {
        panel[i].occupied = true;
    }
    //occupiedBy
    //0 - "none"
    //1 - white king
    //2 - white queen
    //3 - white bishop
    //4 - white knight
    //5 - while rook
    //6 - white pawn
    //black are the same but negative
    panel[0].occpuiedBy = -5;
    panel[1].occpuiedBy = -4;
    panel[2].occpuiedBy = -3;
    panel[3].occpuiedBy = -2;
    panel[4].occpuiedBy = -1;
    panel[5].occpuiedBy = -3;
    panel[6].occpuiedBy = -4;
    panel[7].occpuiedBy = -5;
    for (int i = 8; i < 16; i++) {
        panel[i].occpuiedBy = -6;
    }
    for (int i = 48; i < 56; i++) {
        panel[i].occpuiedBy = 6;
    }
    panel[56].occpuiedBy = 5;
    panel[57].occpuiedBy = 4;
    panel[58].occpuiedBy = 3;
    panel[59].occpuiedBy = 2;
    panel[60].occpuiedBy = 1;
    panel[61].occpuiedBy = 3;
    panel[62].occpuiedBy = 4;
    panel[63].occpuiedBy = 5;
}
Board::~Board() {
    cout << "destroying board data" << endl;
}
int Board::returnSpot(int x, int y)
{
    x -= 20;
    y -= 20;
    if(x < 0 || x > 799 || y < 0 || y > 799) {
        return -1;
    }
    else {
        return (y / 100)*8 + (x / 100);
    }
}

vector<int> Board::avaiableMoves(int spot, int pieceType) {

    switch (pieceType)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        return pawnMoves(spot);
        break;
    case -1:
        break;
    case -2:
        break;
    case -3:
        break;
    case -4:
        break;
    case -5:
        break;
    case -6:
        break;
    default:
        break;
    }
}

vector<int> Board::pawnMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    if(returnSpot(x, y - 100) != -1) {
        if(panel[returnSpot(x, y - 100)].occpuiedBy == 1) {

        }
    }
}