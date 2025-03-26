//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public virtual ChessPiece {
    public:
    // Override virtual methods from ChessPiece here
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;
    using ChessPiece::ChessPiece;
    Bishop(int x, int y, bool is_white, ChessBoard* board);
};


#endif //BISHOP_H