//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

 int ChessPiece::getRow(){
    return m_y;
 }
int ChessPiece::getColumn(){
    return m_x;
}

char ChessPiece::getLatinRep(){
    return latin1Representation();
}
char32_t ChessPiece::getUtfRepresentation(){
    return utfRepresentation();
}
bool ChessPiece::getColor(){
    return m_is_white;
}

int ChessPiece::validMove(int to_x, int to_y){
    return 0;
}
int ChessPiece::getValidMove(int to_x, int to_y){
    return validMove(to_x, to_y);
}

/*char32_t ChessPiece::utfRepresentation() {
    // Implementation goes here
}

char ChessPiece::latin1Representation() {
    // Implementation goes here
}*/

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
/*:  Initialize members here */ {
    m_x = x;
    m_y = y;
    m_is_white = is_white;
    m_board = board;
    // or here ...
}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    // Implementation goes here
    int result = validMove(to_x, to_y);
    if (result == 2) {
        return true;
    }
    else{
        return false;
    }
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    // Kollar om det är valid move
    int result = validMove(to_x, to_y);
    if (result == 1) {
        return true;
    }
    else{
        return false;
    }

}

vector<ChessMove> ChessPiece::capturingMoves() {
    // Implementation goes here
    vector<ChessMove> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (capturingMove(i, j)) {
                moves.push_back(ChessMove(m_x, m_y, i, j, this));
            }
        }
    }
    return moves;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    // Implementation goes here
    vector<ChessMove> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (nonCapturingMove(i, j)) {
                moves.push_back(ChessMove(m_x, m_y, i, j, this));
            }
        }
    }
    return moves;
}