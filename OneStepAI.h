#ifndef ONE_STEP_AI_H
#define ONE_STEP_AI_H

#include "ChessBoard.h"
#include <vector>
#include <memory>

class OneStepAI {
public:
    OneStepAI(bool is_white);
    ChessMove chooseMove(vector<ChessPiece *> &my_pieces, ChessBoard& board);
    bool forceCapture(int x, int y, bool is_white, ChessBoard& board);
    int CaptureAfterPromotion(int x, int y, bool is_white, ChessBoard& board);

private:
    bool m_is_white;
};

#endif // ONE_STEP_AI_H