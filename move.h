#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <memory>
#include "board.h"


struct Position {
    size_t file, rank;
};

struct Move
{
    int startSquare, targetSquare;
};

class MoveGenerator {
    public:
        std::vector<Move> moves;
        const std::unique_ptr<Board>& board;

        MoveGenerator(const std::unique_ptr<Board>&);

        // We need to be careful about clearing the moves every time;
        void generateMoves();
        void generateSlidingMoves(int, int);
        void generateKnightMoves(int, int);
        Position index2Position(int);
};

#endif