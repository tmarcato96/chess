#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <raylib.h>
#include "board.h"
#include "piece.h"
#include "move.h"

class Game {
    private:
        
    public:
        std::vector<Texture2D> pieceSprites;
        std::unique_ptr<Board> board;
        std::unique_ptr<MoveGenerator> moveGenerator;
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
