//
// DD1388 - Lab 4: Losing Chess
//

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    // Override virtual methods from ChessPiece here
    int validMove(int to_x, int to_y) override;
    //char32_t utfRepresentation() override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;
    using ChessPiece::ChessPiece;
    Pawn(int x, int y, bool is_white, ChessBoard* board);
};


#endif //PAWN_H