//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"
//Constructor
King::King(int x, int y, bool is_white, ChessBoard *board)
    : ChessPiece(x, y, is_white, board) {
        //std::shared_ptr<ChessPiece> king_ptr = std::shared_ptr<King>(this);
        //board->setState(king_ptr, x, y);
        //board->setState(this, x, y);
        board->addPiece(this);
}

int King::validMove(int to_x, int to_y){
    int deltaX = abs(to_x - m_x);
    int deltaY = abs(to_y - m_y);
    // Kungen kan gå ett steg i alla riktningar
    if (deltaX * deltaY == 1 || deltaX + deltaY == 1) {

        //Att kungen inte rör sig är inte validMove
        if (to_x == m_x && to_y == m_y) {
            return 0;
        }

        // Check if there is a piece at the destination square
        shared_ptr<ChessPiece> piece = m_board->getState(to_x, to_y);
        //ChessPiece pieceObject = *piece;
        if (piece != nullptr) {
            if(piece->getColor() != m_is_white){
                return 2; // capture move
            }

            else{
                return 0; // Står en piece av samma färg alltså inte valid
            }
        } 
        
        else {
            return 1; // valid non-capture move
        }
    }
    else {
        return 0; // invalid move
    }
}

char32_t King::utfRepresentation() {
    // Return the Unicode code point for the pawn piece
    if (m_is_white) {
        return U'\u2654';
    } 
    else {
        return U'\u265A';
    }
}

char King::latin1Representation(){
    // Return the Latin-1 character code for the king piece
    if(this->m_is_white == true){
        return 'K';
    }
    else{
        return 'k';
    }
}
// Implement method definitions here