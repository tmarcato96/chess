#include <memory>
#include <vector>
#include <raylib.h>
#include "board.h"

#ifndef GAME_H
#define GAME_H

class Game {
    private:
        
    public:
        std::vector<Texture2D> pieceSprites;
        std::unique_ptr<Board> board;
        Game();
        ~Game();
        void run();
        void loadPiecesSprites();
        int spriteToRender(int);
        void drawBoard();
};

#endif
