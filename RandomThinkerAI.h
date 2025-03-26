#ifndef RANDOMTHINKERAI_H
#define RANDOMTHINKERAI_H

#include <vector>
#include <memory>
#include "ChessPiece.h"
#include "ChessMove.h"

class RandomThinkerAI {
public:
    RandomThinkerAI(bool is_white);
    ChessMove chooseMove(vector<ChessPiece *> &my_pieces, ChessBoard& board);

private:
    bool m_is_white;
};

#endif // RANDOMTHINKERAI_H