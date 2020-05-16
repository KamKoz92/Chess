#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
    int a;
    


public:
    Board();
    ~Board();
    void setData();
    
    //Special struct for storing each spot information
    struct boardData {
        int x; 
        int y;
        bool occupied;
        int occpuiedBy;

        boardData(){
            x = 0;
            y = 0;
            occupied = 0;
            occpuiedBy = 0;
        }
    };
    boardData *panel;
};



#endif /* BOARD_H_ */