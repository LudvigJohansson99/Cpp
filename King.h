//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
public:
    // Override virtual methods from ChessPiece here
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;
    using ChessPiece::ChessPiece;
    King(int x, int y, bool is_white, ChessBoard* board);
};


#endif //KING_H