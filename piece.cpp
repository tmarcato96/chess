#include "piece.h"

bool Piece::isColor(int piece, int pieceColor) {
    if ((piece & pieceColor) == pieceColor) return true;
    else return false;
}

bool Piece::isSlidingPiece(int piece) {
    piece = piece & 0b00111;
    if (piece == Piece::Bishop || piece == Piece::Queen || piece == Piece::Rook) return true;
    else return false;
}

bool Piece::isType(int pieceToTest, int piece) {
    pieceToTest = pieceToTest & 0b00111;
    piece = piece & 0b00111;
    if (pieceToTest == piece) return true;
    else return false;
} 