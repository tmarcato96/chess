#ifndef PIECE_H
#define PIECE_H

namespace Piece {
    enum : int {
        None,
        King,
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        White = 8,
        Black = 16 
    };

    bool isColor(int, int);
    bool isSlidingPiece(int);
}

#endif