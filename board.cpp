#include <vector>
#include <string>
#include <map>
#include <cctype>
#include "board.h"
#include "piece.h"

Board::Board(): square(64, 0) {

    loadFromFen(startFen);

}

void Board::loadFromFen(std::string fenString) {
    std::map<char, int> fenSymbToPiece({{'k', Piece::King},
                                        {'p', Piece::Pawn},
                                        {'n', Piece::Knight},
                                        {'b', Piece::Bishop},
                                        {'r', Piece::Rook},
                                        {'q', Piece::Queen}});

    size_t rank = 7, file = 0;
    size_t posSecondField = fenString.find_first_of(' ');
    for (size_t i=0; i<posSecondField; ++i) {
        if (fenString[i] == '/') {
            --rank;
            file = 0;
        }
        else {
            if (isdigit(fenString[i])) file += fenString[i] - '0';
            else {
                int pieceColor = (islower(fenString[i])) ? Piece::White : Piece::Black;
                int pieceType = fenSymbToPiece[tolower(fenString[i])];
                square[rank * 8 + file] = pieceColor | pieceType;
                ++file;
            }
        }

        
    }
}