#include <vector>
#include <iostream>
#include <memory>
#include "move.h"
#include "board.h"
#include "piece.h" 

const std::vector<int> directionOffsets = {8, -8, -1, 1, 7, -7, 9, -9};

MoveGenerator::MoveGenerator(const std::unique_ptr<Board>& board) : board{board} {};

void MoveGenerator::generateSlidingMoves(int piece, int startSquare) {

    int startDirection = (Piece::isType(piece, Piece::Bishop)) ? 4 : 0;
    int endDirection = (Piece::isType(piece, Piece::Rook)) ? 4 : 8;

    for (int direction = startDirection; direction < endDirection; ++direction) {
        for (int n = 0; n < board->numToEdge[startSquare].at(direction); ++n) {
            int targetSquare = startSquare + directionOffsets[direction] * (n + 1);
            int pieceOnTargetSquare = board->square[targetSquare];

            if (Piece::isColor(pieceOnTargetSquare, board->colorToMove)) break;

            Move move = {startSquare, targetSquare};
            moves.push_back(move);

            int opponentColor = (board->colorToMove == Piece::White) ? Piece::Black : Piece::White;
            if (Piece::isColor(pieceOnTargetSquare, opponentColor)) break;
        }
    }
}

void MoveGenerator::generateMoves() {

    for (int startSquare = 0; startSquare < 64; ++startSquare) {
        int piece = board->square[startSquare];
        if (Piece::isColor(piece, board->colorToMove)) {
            if (Piece::isSlidingPiece(piece)) {
                generateSlidingMoves(piece, startSquare);
            }
        }
    }

};