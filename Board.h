#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

using namespace std;

class Board {
private:

public:
    Board();
    ~Board();
    void setData();
    int returnSpot(int x, int y);
    vector<int> avaiableMoves(int spot, int pieceType);
    vector<int> wPawnMoves(int spot);
    vector<int> wRookMoves(int spot);
    vector<int> wKnightMoves(int spot);
    vector<int> wBishopMoves(int spot);
    vector<int> wQueenMoves(int spot);
    vector<int> wKingMoves(int spot);

    vector<int> bPawnMoves(int spot);
    vector<int> bRookMoves(int spot);
    vector<int> bKnightMoves(int spot);
    vector<int> bBishopMoves(int spot);
    vector<int> bQueenMoves(int spot);
    vector<int> bKingMoves(int spot);
    
    //Special struct for storing each spot information
    struct boardData {
        int x; 
        int y;
        bool occupied;
        int occpuiedBy;
        bool selected;
        boardData(){
            x = 0;
            y = 0;
            occupied = 0;
            occpuiedBy = 0;
            selected = false;
        }
    };
    boardData *panel;
};



#endif /* BOARD_H_ */