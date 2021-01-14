#ifndef MINMAX_H_
#define MINMAX_H_

#include <vector>

using namespace std;

class MinMax {

public:
    MinMax();
    ~MinMax();
    int nextMove();
    int minimax(int, int, bool);

};

#endif /* BOARD_H_ */