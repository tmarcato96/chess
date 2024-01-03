#include <vector>
#include <map>
#include <string>

#ifndef BOARD_H
#define BOARD_H

class Board {
    public:
        const std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        std::vector<int> square;
        std::map<int, std::vector<int>> numToEdge;
        int colorToMove;

        Board();

        void loadFromFen(std::string);
        void precomputeNumToEdge();
};

#endif
