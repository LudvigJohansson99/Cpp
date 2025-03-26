//
// DD1388 - Lab 4: Losing Chess
//

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"
class Queen : public virtual ChessPiece, public Rook, public Bishop {
    public:
    // Override virtual methods from ChessPiece here
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;
    using ChessPiece::ChessPiece;
    Queen(int x, int y, bool is_white, ChessBoard* board);
};


#endif //QUEEN_H