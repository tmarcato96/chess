#include <iostream>
#include <memory>
#include <raylib.h>
#include "board.h"
#include "piece.h"

#define SQUARE_SIZE 75
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

std::unique_ptr<Texture2D[]> pieceSprites(new Texture2D[12]);

void loadPieceSprites() {
    pieceSprites[0] = LoadTexture("sprites/king_w.png");
    pieceSprites[1] = LoadTexture("sprites/pawn_w.png");
    pieceSprites[2] = LoadTexture("sprites/knight_w.png");
    pieceSprites[3] = LoadTexture("sprites/bishop_w.png");
    pieceSprites[4] = LoadTexture("sprites/rook_w.png");
    pieceSprites[5] = LoadTexture("sprites/queen_w.png");

    pieceSprites[6] = LoadTexture("sprites/king_b.png");
    pieceSprites[7] = LoadTexture("sprites/pawn_b.png");
    pieceSprites[8] = LoadTexture("sprites/knight_b.png");
    pieceSprites[9] = LoadTexture("sprites/bishop_b.png");
    pieceSprites[10] = LoadTexture("sprites/rook_b.png");
    pieceSprites[11] = LoadTexture("sprites/queen_b.png");

    for (size_t i=0; i<12; ++i) {
        SetTextureWrap(pieceSprites[i], TEXTURE_WRAP_MIRROR_CLAMP);
    }
}

void CreateBoard() {
    Board* board = new Board();

    Vector2 squareSize = {SQUARE_SIZE, SQUARE_SIZE};
    Color darkColor = {169, 122, 101, 255};
    Color lightColor = {241, 217, 192, 255};

    
    const Vector2 spriteOrigin = {0.0f, 0.0f};
    for (size_t file = 0; file < 8; ++file) {
        for (size_t rank = 0; rank < 8; ++rank) {
            bool isLightSquare = (file + rank) % 2 != 0;

            Color squareColor = isLightSquare ? WHITE: darkColor;
            Vector2 squarePos = {SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + file * SQUARE_SIZE, 
                                 SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + rank * SQUARE_SIZE};
            
            DrawRectangleV(squarePos, squareSize, squareColor);

            Rectangle dstRect = {SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + file * SQUARE_SIZE, 
                         SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + rank * SQUARE_SIZE,
                         (float)SQUARE_SIZE, 
                         (float)SQUARE_SIZE};
            int square = board->square[8 * rank + file];
            int spriteIndex;
            if (square != Piece::None) {
                switch (square)
                {
                case (Piece::White | Piece::King):
                spriteIndex = 0;
                break;

                case (Piece::White | Piece::Pawn):
                    spriteIndex = 1;
                    break;

                case (Piece::White | Piece::Knight):
                    spriteIndex = 2;
                    break;

                case (Piece::White | Piece::Bishop):
                    spriteIndex = 3;
                    break;
                
                case (Piece::White | Piece::Rook):
                    spriteIndex = 4;
                    break;

                case (Piece::White | Piece::Queen):
                    spriteIndex = 5;
                    break;
                case (Piece::Black | Piece::King):
                    spriteIndex = 6;
                    break;

                case (Piece::Black | Piece::Pawn):
                    spriteIndex = 7;
                    break;

                case (Piece::Black | Piece::Knight):
                    spriteIndex = 8;
                    break;

                case (Piece::Black | Piece::Bishop):
                    spriteIndex = 9;
                    break;
                
                case (Piece::Black | Piece::Rook):
                    spriteIndex = 10;
                    break;

                case (Piece::Black | Piece::Queen):
                    spriteIndex = 11;
                    break;
                default:
                    break;
                }
                Rectangle srcRect = {0.0f, 0.0f, 
                                     (float)pieceSprites[spriteIndex].width, 
                                     (float)pieceSprites[spriteIndex].height};
                DrawTexturePro(pieceSprites[spriteIndex], 
                               srcRect, dstRect, spriteOrigin, 0.0f, WHITE);
            }
        }
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
    loadPieceSprites();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        CreateBoard();
        EndDrawing();
    }
    CloseWindow();

}