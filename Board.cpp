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
    delete[] panel;
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
        return wKingMoves(spot);
        break;
    case 2:
        return wQueenMoves(spot);
        break;
    case 3:
        return wBishopMoves(spot);
        break;
    case 4:
        return wKnightMoves(spot);
        break;
    case 5:
        return wRookMoves(spot);
        break;
    case 6:
        return wPawnMoves(spot);
        break;
    case -1:
        return bKingMoves(spot);
        break;
    case -2:
        return bQueenMoves(spot);
        break;
    case -3:
        return bBishopMoves(spot);
        break;
    case -4:
        return bKnightMoves(spot);
        break;
    case -5:
        return bRookMoves(spot);
        break;
    case -6:
        return bPawnMoves(spot);
        break;
    default:
        cout << "Bad info for moving piece" << endl;
        break;
    }
    return vector<int>();
}

vector<int> Board::wPawnMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    
    //moving forward
    int tempSpot = returnSpot(x, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);

            //if its a pawn's first move it can move 2 squares
            //if pawn is not on pawns starting positions(48-55) its not his first move
            // since pawn can only go forward
            if(spot > 47 && spot < 56) {
                tempSpot = returnSpot(x, y - 200);
                if(tempSpot != -1 ) {
                    if(panel[tempSpot].occpuiedBy == 0) {
                        moves.push_back(tempSpot);
                    } 
                }
            }
        }
    }
    
    //attacking diagonaly left
    tempSpot = returnSpot(x - 100, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
            moves.push_back(tempSpot);
        }
    }

    //attacking diagonaly right
    tempSpot = returnSpot(x + 100, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
            moves.push_back(tempSpot);
        }
    }
    return moves;
}

vector<int> Board::wRookMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;
    //moving forward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving backward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving left
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x - (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving right
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x + (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return moves;
}



vector<int> Board::wKnightMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //upright move
    tempSpot = returnSpot(x + 100, y - 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //upleft move
    tempSpot = returnSpot(x - 100, y - 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //downleft move 
    tempSpot = returnSpot(x - 100, y + 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //downright move 
    tempSpot = returnSpot(x + 100, y + 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //leftup move
    tempSpot = returnSpot(x - 200, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //leftdown move
    tempSpot = returnSpot(x - 200, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //rightup move
    tempSpot = returnSpot(x + 200, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    //rightdown move
    tempSpot = returnSpot(x + 200, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7)) {
            moves.push_back(tempSpot);
        }
    }

    return moves;
}

vector<int> Board::wBishopMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //upperright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //upperleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }
    
    //downright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //downleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return moves;
}

vector<int> Board::wQueenMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //moving forward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving backward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving left
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x - (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving right
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x + (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //upperright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //upperleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //downright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //downleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    break;
                }
                else {
                    moves.push_back(tempSpot);
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return moves;
}

vector<int> Board::wKingMoves(int spot) {
    //ADD restriction to moving on a checkmate square///////////////////////////////////////////////////////////////
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //upmove
    tempSpot = returnSpot(x, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //move back 
    tempSpot = returnSpot(x, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //move left
    tempSpot = returnSpot(x - 100, y);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //move right 
    tempSpot = returnSpot(x + 100, y);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //upperright move 
    tempSpot = returnSpot(x + 100, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //upperleft move 
    tempSpot = returnSpot(x - 100, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //downright move 
    tempSpot = returnSpot(x + 100, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    //downleft move
    tempSpot = returnSpot(x - 100, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                moves.push_back(tempSpot);
            }
        }
    }

    return moves;
}

vector<int> Board::bPawnMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    
    //moving forward
    int tempSpot = returnSpot(x, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);

            //if its a pawn's first move it can move 2 squares
            //if pawn is not on pawns starting positions (8-15) its not his first move
            //since pawn can only go forward
            if(spot > 7 && spot < 16) { 
                tempSpot = returnSpot(x, y + 200);
                if(tempSpot != -1 ) {
                    if(panel[tempSpot].occpuiedBy == 0) {
                        moves.push_back(tempSpot);
                    } 
                }
            }
        }
    }
    
    //attacking diagonaly left
    tempSpot = returnSpot(x - 100, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
            moves.push_back(tempSpot);
        }
    }

    //attacking diagonaly right
    tempSpot = returnSpot(x + 100, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
            moves.push_back(tempSpot);
        }
    }
    return moves;
}

vector<int> Board::bRookMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;
    
    //moving backward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving forward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving left
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x - (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving right
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x + (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return moves;
}

vector<int> Board::bKnightMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //upright move
    tempSpot = returnSpot(x + 100, y - 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //upleft move
    tempSpot = returnSpot(x - 100, y - 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //downleft move 
    tempSpot = returnSpot(x - 100, y + 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //downright move 
    tempSpot = returnSpot(x + 100, y + 200);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //leftup move
    tempSpot = returnSpot(x - 200, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //leftdown move
    tempSpot = returnSpot(x - 200, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //rightup move
    tempSpot = returnSpot(x + 200, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    //rightdown move
    tempSpot = returnSpot(x + 200, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0 || (panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0)) {
            moves.push_back(tempSpot);
        }
    }

    return moves;
}
vector<int> Board::bBishopMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //upperright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //upperleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }
    
    //downright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //downleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return moves;
}
vector<int> Board::bQueenMoves(int spot) {
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //moving backward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving forward
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x, y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving left
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x - (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //moving right
    for(int i = 1; i < 8; i++)
    {
        tempSpot = returnSpot(x + (i * 100), y);
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {//if(panel[tempSpot].occpuiedBy < 0 && panel[tempSpot].occpuiedBy > -7) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //upperright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //upperleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y - (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //downright move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x + (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    //downleft move
    for(int i = 1; i < 8; i++) {
        tempSpot = returnSpot(x - (i * 100), y + (i * 100));
        if(tempSpot != -1) {
            if(panel[tempSpot].occpuiedBy == 0) {
                moves.push_back(tempSpot);
            }
            else {
                if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                    moves.push_back(tempSpot);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return moves;
}
vector<int> Board::bKingMoves(int spot) {
    //ADD restriction to moving on a check square///////////////////////////////////////////////////////////////
    vector<int> moves;
    int x = panel[spot].x;
    int y = panel[spot].y;
    int tempSpot;

    //upmove
    tempSpot = returnSpot(x, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //move back 
    tempSpot = returnSpot(x, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //move left
    tempSpot = returnSpot(x - 100, y);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //move right 
    tempSpot = returnSpot(x + 100, y);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //upperright move 
    tempSpot = returnSpot(x + 100, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //upperleft move 
    tempSpot = returnSpot(x - 100, y - 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //downright move 
    tempSpot = returnSpot(x + 100, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    //downleft move
    tempSpot = returnSpot(x - 100, y + 100);
    if(tempSpot != -1) {
        if(panel[tempSpot].occpuiedBy == 0) {
            moves.push_back(tempSpot);
        }
        else {
            if(panel[tempSpot].occpuiedBy < 7 && panel[tempSpot].occpuiedBy > 0) {
                moves.push_back(tempSpot);
            }
        }
    }

    return moves;
}