//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
    // Override virtual methods from ChessPiece here
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;
    using ChessPiece::ChessPiece;
    Knight(int x, int y, bool is_white, ChessBoard* board);
};


#endif //KNIGHT_H