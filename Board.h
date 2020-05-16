#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
    int a;
    


public:
    Board();
    ~Board();
    void setData();
    
    struct boardData {
        int x;
        int y;
        bool occupied;
        int occpuiedType;

        boardData(){
            x = 0;
            y = 0;
            occupied = 0;
            occpuiedType = 0;
        }
    };
    boardData *panel;
};



#endif /* BOARD_H_ */