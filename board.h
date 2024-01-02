#include <vector>
#include <string>

#ifndef BOARD_H
#define BOARD_H

class Board {
    public:
        Board();
        void loadFromFen(std::string);
        std::vector<int> square;
        const std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
};

#endif
