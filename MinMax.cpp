#include "MinMax.h"


using namespace std;


MinMax::MinMax() {

}

MinMax::~MinMax() {

}

int MinMax::nextMove() {

}

int MinMax::minimax(int pos, int depth, bool maximizingPlayer) {
    if (depth == 0 || false ) { // game over 

    }


    if(maximizingPlayer) {
        int maxEval = -inf;
        for() {
            int eval = minimax(child, depth - 1, false);
            maxEval = max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = +inf;
        for() {
            int eval = minimax(child, depth - 1, true);
            minEval = min(minEval, eval);
        }
        return minEval;
    }
}


