//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSMOVE_H
#define CHESSMOVE_H

using namespace std;

class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece * piece;   // you can change the position of the chess piece with this pointer.

    //constructor
    ChessMove(int fX, int fY, int tX, int tY, ChessPiece *p) : from_x(fX), from_y(fY), to_x(tX), to_y(tY), piece(p) {}
};

#endif //CHESSMOVE_H