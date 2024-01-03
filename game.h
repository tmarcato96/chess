#include <memory>
#include <vector>
#include <raylib.h>
#include "board.h"
#include "piece.h"

#ifndef GAME_H
#define GAME_H

struct Position {
    size_t file, rank;
};

class Game {
    private:
        
    public:
        std::vector<Texture2D> pieceSprites;
        std::unique_ptr<Board> board;
        bool isPieceSelected;
        int selectedPieceIndex = 8, selectedPiece = 8;
        size_t srcFile, srcRank;
        
        Game();
        void run();
        void loadPiecesSprites();
        int spriteToRender(int);
        void drawBoard();
        bool isMouseOnPiece(Vector2, size_t&, size_t&);
        Position getSquarePosition(Vector2);
        void checkUserInput();
};

#endif
