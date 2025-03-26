//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"

// Implement method definitions here
Bishop::Bishop(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {
    //std::shared_ptr<ChessPiece> bishop_ptr = std::shared_ptr<Bishop>(this);
    //board->setState(bishop_ptr, x, y);
    //board->setState(this, x, y);
    board->addPiece(this);
}

int Bishop::validMove(int to_x, int to_y) {
    int deltaX = to_x - m_x;
    int deltaY = to_y - m_y;

    // Kollar att move är diagonalt
    if (abs(deltaX) != abs(deltaY)) {
        return 0;
    }
    int xDirection = 0;
    int yDirection = 0;
    // Se vilket håll den rör sig
    if(deltaX > 0){
        xDirection = 1;
    }
    else{
        xDirection = -1;
    }
    if(deltaY > 0){
        yDirection = 1;
    }
    else{
        yDirection = -1;
    }

    // Kollar pjäsar i vägen
    for (int i = 1; i < abs(deltaX); i++) {
        shared_ptr<ChessPiece> piece = m_board->getState(m_x + i * xDirection, m_y + i * yDirection);
        if (piece != nullptr) {
            return 0; // En pjäs blockerar
        }
    }

    // kollar målrutan
    shared_ptr<ChessPiece> piece = m_board->getState(to_x, to_y);
    if (piece != nullptr) {
        if (piece->getColor() != m_is_white) {
            return 2; // capture
        }
        else {
            return 0; // egen pjäs
        }
    }
    else {
        return 1; // non-capture
    }
}

char32_t Bishop::utfRepresentation() {
    // Return the Unicode code point for the bishop piece
    if (m_is_white) {
        return U'\u2657';
    } else {
        return U'\u265D';
    }
}

char Bishop::latin1Representation() {
    // Return the Latin-1 character code for the bishop piece
    if (m_is_white) {
        return 'B';
    }
    else {
        return 'b';
    }
}