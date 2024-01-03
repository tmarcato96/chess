#include <vector>
#include "board.h"

#ifndef MOVE_H
#define MOVE_H

struct Move
{
    int startSquare, targetSquare;
};

class MoveGenerator {
    public:
        std::vector<Move> moves;
        Board* board;

        MoveGenerator(Board* board);

        // We need to be careful about clearing the moves every time;
        void generateMoves();
        void generateSlidingMoves(int, int);
};

#endif