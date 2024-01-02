#include <vector>
#include "board.h"
#include "piece.h"

Board::Board(): square(64, 0) {

    //square[0] = Piece::White | Piece::Rook;
    square[1] = Piece::White | Piece::Bishop;
    //square[2] = Piece::White | Piece::Knight;

}