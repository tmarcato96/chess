#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>
#include "board.h"
#include "piece.h"

Board::Board() : 
    square(64, 0),
    colorToMove{Piece::White}
 {
    loadFromFen(startFen);
    precomputeNumToEdge();
}

void Board::precomputeNumToEdge() {
    for (int file = 0; file<8; ++file) {
        for (int rank = 0; rank < 8; ++rank) {
            int numNorth = 7 - rank;
            int numSouth = rank;
            int numWest = file;
            int numEast = 7 - file;

            int squareIndex = 8 * rank + file;
            std::vector<int> numsToEdge = {numNorth,
                                           numSouth,
                                           numWest,
                                           numEast,
                                           std::min(numNorth, numWest),
                                           std::min(numSouth, numEast),
                                           std::min(numNorth, numEast),
                                           std::min(numSouth, numWest)};
            numToEdge[squareIndex] = numsToEdge;
        }
    }
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