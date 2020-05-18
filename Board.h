#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
    int a;
    


public:
    Board();
    ~Board();
    void setData();
    int returnSpot(int x, int y);
    
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