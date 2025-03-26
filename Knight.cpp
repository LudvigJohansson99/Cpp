//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"
// Implement method definitions here
// Constructor
Knight::Knight(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {
        //std::shared_ptr<ChessPiece> knight_ptr = std::shared_ptr<Knight>(this);
        //board->setState(knight_ptr, x, y);
        //board->setState(this, x, y);
        board->addPiece(this);
    }

// Implement validMove() function
int Knight::validMove(int to_x, int to_y) {
    int deltaX = abs(to_x - m_x);
    int deltaY = abs(to_y - m_y);

    // De två alternativen för att röra knight
    if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1)) {

        // Kolla om den är tom eller ej
        shared_ptr<ChessPiece> piece = m_board->getState(to_x, to_y);
        if (piece != nullptr) {
            //kolla om den kan göra capture
            if (piece->getColor() != m_is_white) {
                return 2;
            } 
            
            else {
                return 0; //ruta upptagen av egen pjäs
            }
        } 
        
        else {
            return 1; //tom ruta
        }
    }
    
    else {
        return 0; // kan ej röra sig utanför
    }
}

// Override
char32_t Knight::utfRepresentation() {
    // Returna Unicode
    if (m_is_white) {
        return U'\u2658';
    } else {
        return U'\u265E';
    }
}

// Override
char Knight::latin1Representation() {
    // Returna Latin-1
    if (m_is_white) {
        return 'N';
    } else {
        return 'n';
    }
}