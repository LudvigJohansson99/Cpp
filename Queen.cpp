//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"
Queen::Queen(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board), Rook(x, y, is_white, board), Bishop(x, y, is_white, board) {
    //std::shared_ptr<ChessPiece> queen_ptr = std::shared_ptr<Queen>(this);
    //board->setState(queen_ptr, x, y);
    board->addPiece(this);
    //board->addPiece(queen_ptr.get());
    //cout << "queen construct" << endl;
}


int Queen::validMove(int to_x, int to_y) {
    /*Rook rook(m_x, m_y, m_is_white, m_board);
    Bishop bishop(m_x, m_y, m_is_white, m_board);
    int rookResult = rook.validMove(to_x, to_y);
    int bishopResult = bishop.validMove(to_x, to_y);*/
    int rookResult = Rook::validMove(to_x, to_y);
    int bishopResult = Bishop::validMove(to_x, to_y);

    if (rookResult == 0 && bishopResult == 0) {
        return 0; // The move is invalid
    }
    else if (rookResult == 2 || bishopResult == 2) {
        return 2; // The move is a capture
    }
    else if (rookResult == 1 || bishopResult == 1) {
        return 1; // The move is valid but not a capture
    }
    else {
        return 0; // Something went wrong
    }
}

char32_t Queen::utfRepresentation() {
    // Return the Unicode code point for the bishop piece
    if (m_is_white) {
        return U'\u2655';
    } else {
        return U'\u265B';
    }
}

char Queen::latin1Representation() {

    // Return the Latin-1 character code for the bishop piece
    if (this->m_is_white==true) {
        return 'Q';
    }
    else {
        return 'q';
    }
}