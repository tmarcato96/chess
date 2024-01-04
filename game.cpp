#include <iostream>
#include <vector>
#include <memory>
#include<string>
#include <raylib.h>
#include "board.h"
#include "piece.h"
#include "game.h"

#define SQUARE_SIZE 75
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800


Game::Game() : board(new Board()),
               isPieceSelected{false},
               moveGenerator(new MoveGenerator(board)) {
    pieceSprites = std::vector<Texture2D>(12);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
    loadPiecesSprites();

}

void Game::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        drawBoard();
        checkUserInput();
        EndDrawing();
    }
    CloseWindow();
}

bool Game::isMouseOnPiece(Vector2 pos, size_t& fPiece, size_t& rPiece) {
    for (size_t file=0; file<8; ++file) {
        for (size_t rank=0; rank<8; ++rank) {
            float x0 = SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + file * SQUARE_SIZE;
            float x1 = x0 + SQUARE_SIZE;
            float y0 = SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + rank * SQUARE_SIZE;
            float y1 = y0 + SQUARE_SIZE;
            int square = board->square[8 * rank + file];
            if (square != Piece::None && pos.x > x0 && pos.x < x1 && pos.y > y0 && pos.y < y1) {
                fPiece = file;
                rPiece = rank;
                return true;
            }
        }
    }
    return false;
}

Position Game::getSquarePosition(Vector2 pos) {
    for (size_t file=0; file<8; ++file) {
        for (size_t rank=0; rank<8; ++rank) {
            float x0 = SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + file * SQUARE_SIZE;
            float x1 = x0 + SQUARE_SIZE;
            float y0 = SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + rank * SQUARE_SIZE;
            float y1 = y0 + SQUARE_SIZE;
            if (pos.x > x0 && pos.x < x1 && pos.y > y0 && pos.y < y1) {
                Position squarePos = {file, rank};
                return squarePos;
            }
        }
    }
}


void Game::checkUserInput() {
    Vector2 mouseSrcPos = GetMousePosition();
    if (!isPieceSelected && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && 
        isMouseOnPiece(mouseSrcPos, srcFile, srcRank)) {
            isPieceSelected = true;
            selectedPiece = board->square[8 * srcRank + srcFile];
            selectedPieceIndex = Game::spriteToRender(selectedPiece);
            board->square[8 * srcRank + srcFile] = Piece::None;
            if (Piece::isSlidingPiece(selectedPiece)) {
                moveGenerator->moves.clear();
                moveGenerator->generateSlidingMoves(selectedPiece, 8 * srcRank + srcFile);
            }
            else if (Piece::isType(selectedPiece, Piece::Knight))
            {
                moveGenerator->moves.clear();
                moveGenerator->generateKnightMoves(selectedPiece, 8 * srcRank + srcFile);
            }
            
        }
    
    if (isPieceSelected) {
        Rectangle srcRect = {0.0f, 0.0f, 
                             (float)pieceSprites[selectedPieceIndex].width, 
                             (float)pieceSprites[selectedPieceIndex].height};
        Rectangle dstRect = {mouseSrcPos.x - SQUARE_SIZE/2, mouseSrcPos.y - SQUARE_SIZE/2,
                             (float)SQUARE_SIZE, (float)SQUARE_SIZE};
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(pieceSprites[selectedPieceIndex], srcRect, dstRect, origin, 0.0f, WHITE);

        // Highlight square to move 
        Color highlightColor = {255, 51, 51, 75};
        const Vector2 squareSize = {(float)SQUARE_SIZE, (float)SQUARE_SIZE};
        for (auto move: moveGenerator->moves) {
            Position positionToHighlight = moveGenerator->index2Position(move.targetSquare);
            Vector2 squarePosToHighlight = {SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + positionToHighlight.file * SQUARE_SIZE, 
                                            SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + positionToHighlight.rank * SQUARE_SIZE};
            
            DrawRectangleV(squarePosToHighlight, squareSize, highlightColor);
        }
        

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            mouseSrcPos = GetMousePosition();
            isPieceSelected = false;
            Position dstSquarePosition = getSquarePosition(mouseSrcPos);
            bool isdstSquareLegal = false;
            for (auto move: moveGenerator->moves) {
                if (move.targetSquare == 8 * dstSquarePosition.rank + dstSquarePosition.file) {
                    isdstSquareLegal = true;
                    break;
                }
            }

            if (isdstSquareLegal && dstSquarePosition.file < 8 && dstSquarePosition.rank < 8) {
                board->square[8 * dstSquarePosition.rank + dstSquarePosition.file] = selectedPiece;
            }
            else {
                board->square[8 * srcRank + srcFile] = selectedPiece;
            }
        }
    }
}

void Game::loadPiecesSprites() {
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

int Game::spriteToRender(int square) {
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
        }
        return spriteIndex;
    }
}

void Game::drawBoard() {
    Vector2 squareSize = {SQUARE_SIZE, SQUARE_SIZE};
    Color darkColor = {169, 122, 101, 255};
    Color lightColor = {241, 217, 192, 255};

    
    const Vector2 spriteOrigin = {0.0f, 0.0f};
    for (size_t file = 0; file < 8; ++file) {
        for (size_t rank = 0; rank < 8; ++rank) {
            bool isLightSquare = (file + rank) % 2 != 0;

            Color squareColor = isLightSquare ? lightColor: darkColor;
            Vector2 squarePos = {SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + file * SQUARE_SIZE, 
                                SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + rank * SQUARE_SIZE};
            
            DrawRectangleV(squarePos, squareSize, squareColor);

            Rectangle dstRect = {SCREEN_WIDTH / 2 - 4.0f*SQUARE_SIZE + file * SQUARE_SIZE, 
                        SCREEN_HEIGHT / 2 - 4.0f*SQUARE_SIZE + rank * SQUARE_SIZE,
                        (float)SQUARE_SIZE, 
                        (float)SQUARE_SIZE};
            int square = board->square[8 * rank + file];
            int spriteIndex = spriteToRender(square);
                Rectangle srcRect = {0.0f, 0.0f, 
                                    (float)pieceSprites[spriteIndex].width, 
                                    (float)pieceSprites[spriteIndex].height};
                DrawTexturePro(pieceSprites[spriteIndex], 
                            srcRect, dstRect, spriteOrigin, 0.0f, WHITE);
            DrawText(std::to_string(8 * rank + file).c_str(), (int)squarePos.x, (int)squarePos.y, 16, BLACK);
            }
        }
    }
