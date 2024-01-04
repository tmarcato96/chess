#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include "move.h"
#include "board.h"
#include "piece.h" 

const std::vector<int> directionOffsets = {8, -8, -1, 1, 7, -7, 9, -9};
const std::vector<int> directionOffsetsKnight = {-10, -17, -15, -6, 6, 15, 17, 10};

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

Position MoveGenerator::index2Position(int index) {
    for (size_t file = 0; file < 8; ++file) {
        for (size_t rank = 0; rank < 8; ++rank) {
            if (8 * rank + file == index) {
                Position position = {file, rank};
                return position;
            }
        }
    }
}

void MoveGenerator::generateKnightMoves(int piece, int startSquare) {
    for (auto offset: directionOffsetsKnight) {
        int targetSquare = startSquare + offset;
        int pieceOnTargetSquare = board->square[targetSquare];
        if (targetSquare < 0 || targetSquare > 63) continue;

        // modify here to avoid wrapping on the other side of the board
        Position targetPosition = index2Position(targetSquare);
        Position startPosition = index2Position(startSquare);
        if (!(std::abs((int)startPosition.file - (int)targetPosition.file) == 1 || 
            std::abs((int)startPosition.rank - (int)targetPosition.rank) == 1)) continue;

        if (Piece::isColor(pieceOnTargetSquare, board->colorToMove)) continue;

        Move move = {startSquare, targetSquare};
        moves.push_back(move);
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