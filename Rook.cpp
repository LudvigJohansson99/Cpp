//
// DD1388 - Lab 4: Losing Chess
//
#include "Rook.h"
//constructor
Rook::Rook(int x, int y, bool is_white, ChessBoard *board)
    : ChessPiece(x, y, is_white, board) {
        //std::shared_ptr<ChessPiece> rook_ptr = std::shared_ptr<Rook>(this);
        //board->setState(rook_ptr, x, y);
        board->addPiece(this);
}

int Rook::validMove(int to_x, int to_y) {
    int deltaX = to_x - m_x;
    int deltaY = to_y - m_y;

    //används för att kolla riktningen och därmed kolla om några and pjäser är i vägen i den riktningen
    int xDirection = 0;
    int yDirection = 0;

    //deltaX eller deltaY måste vara 0
    if(deltaX == 0 || deltaY == 0){
        //Vilken riktning går den?
        if(deltaX > 0){
            xDirection = 1;
        }
        else if(deltaX < 0){
            xDirection = -1;
        }
        else if(deltaY > 0){
            yDirection = 1;
        }
        else if(deltaY < 0){
            yDirection = -1;
        }
        //Kollar riktningen
        for (int i = 1; i < max(abs(deltaX), abs(deltaY)); i++) {
            //kollar varje ruta i riktningen mellan m_x och to_x
            shared_ptr<ChessPiece> piece = m_board->getState(m_x + i*xDirection, m_y + i*yDirection);
            if (piece != nullptr) {
                return 0; // en pjäs i vägen
            }
        }

        // Check if there is a piece at the destination square
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
    else{
        //deltaX eller deltaY måste vara 0
        return 0;
    }
}

// Implement method definitions here
char32_t Rook::utfRepresentation() {
    if (m_is_white) {
        return U'\u2656';
    } else {
        return U'\u265C';
    }
}

char Rook::latin1Representation() {
    if (m_is_white) {
        return 'R';
    } else {
        return 'r';
    }
}