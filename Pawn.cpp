//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"
// Constructor
Pawn::Pawn(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {
    //std::shared_ptr<ChessPiece> pawn_ptr = std::shared_ptr<Pawn>(this);
    //board->setState(pawn_ptr, x, y);
    board->addPiece(this);
}

int Pawn::validMove(int to_x, int to_y) {
    int deltaX = (to_x - m_x);
    int deltaY = (to_y - m_y);
    //kolla ett steg fram för vit
    if(deltaY == 1 && deltaX == 0 && m_is_white == true){
        shared_ptr<ChessPiece> piece = m_board->getState(to_x, to_y);
        if(piece == nullptr){
            return 1;
        }
        else{
            return 0;
        }
    }
    //kolla ett steg för svart
    else if(deltaY == -1 && deltaX == 0 && m_is_white == false){
        shared_ptr<ChessPiece> piece = m_board->getState(to_x, to_y);
        if(piece == nullptr){
            return 1;
        }
        else{
            return 0;
        }
    }
    //kolla två steg för vit
    else if ((deltaX == 0) && (m_y-to_y) == -2 && m_is_white && m_y == 1) {
        shared_ptr<ChessPiece> piece = m_board->getState(to_x, to_y);
        if (piece != nullptr) {
            //rutan är blockerad
            return 0;
        }
        else {
            // kolla så att m_y+1 inte heller är blockad då den ej kan hoppa över en pjäs
            shared_ptr<ChessPiece> blockpiece = m_board->getState(to_x, to_y-1);
            //cout << to_x << " " << to_y-1 << endl;
            //cout << m_x << " " << m_y << endl;

            if(blockpiece != nullptr){
                return 0;
            }
            else{
                return 1;
            }
            
        }
    }

    //kolla två steg för svart
    else if ((deltaX == 0) && (m_y-to_y) == 2 && !m_is_white && m_y == 6) {
        shared_ptr<ChessPiece> piece2 = m_board->getState(to_x, to_y);
        if (piece2 != nullptr) {
            //rutan är blockerad
            return 0;
        }
        else {
            // kolla så att m_y-1 inte heller är blockad då den ej kan hoppa över en pjäs
            shared_ptr<ChessPiece> blockpiece2 = m_board->getState(to_x, to_y + 1);

            if(blockpiece2 != nullptr){
                return 0;
            }
            else{
                return 1;
            }
            
        }
    }

    //capture för vit
    else if ((abs(deltaX) == 1) && ((m_y-to_y) == -1 && m_is_white == true)){
        shared_ptr<ChessPiece> piece3 = m_board->getState(to_x, to_y);
        if (piece3 != nullptr) {
            // // Det finns en pjäs på (to_x, to_y)
            if (piece3->getColor() != m_is_white) {
                //pjäsen på (to_x, to_y) är en motståndarpjäs så den kan bli captured
                return 2;
            } 
            else{
                //pjäsen på (to_x, to_y) är en egen pjäs så den kan bli inte bli captured
                return 0;
            }
        }
        else {
            // kan ej röra sig hit utan capture
            return 0;
        }
    }

    else if(((abs(deltaX) == 1) && ((m_y-to_y) == 1 && m_is_white == false))){
        shared_ptr<ChessPiece> piece4 = m_board->getState(to_x, to_y);
        if (piece4 != nullptr) {
            // Det finns en pjäs på (to_x, to_y)
            if (piece4->getColor() != m_is_white) {
                //pjäsen på (to_x, to_y) är en motståndarpjäs så den kan bli captured
                return 2;
            } 
            else{
                //pjäsen på (to_x, to_y) är en egen pjäs så den kan bli inte bli captured
                return 0;
            }
        }
        else {
            // kan ej röra sig hit utan capture
            return 0;
        }
    }
    else {
        // kan ej röra sig hit
        return 0;
    }


}

/*char32_t Pawn::utfRepresentation() {
    // Return the Unicode code point for the pawn piece
    if (m_is_white) {
        return U'\u2659';
    } 
    else {
        return U'\u265F';
    }
}*/


char32_t Pawn::utfRepresentation() {
    if (m_is_white) {
        return U'\u2659';
    } else {
        return U'\u265F';
    }
}

char Pawn::latin1Representation(){
    // Return the Latin-1 character code for the king piece
    if(this->m_is_white == true){
        return 'P';
    }
    else{
        return 'p';
    }
}

// Implement method definitions here