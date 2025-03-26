
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <istream>
#include <memory>
#include "ChessMove.h"
#include "Matrix.h"
// Use the "-I ../02" flag to let the compiler find Matrix.h

using namespace std;

class ChessPiece;

class ChessBoard {
    //friend class Chesspiece;
    // add additional members or functions of your choice

private:
    //håller shared pointers till chesspiece objekt
    Matrix<shared_ptr<ChessPiece>> m_state; // Matrix from lab 2

    vector<ChessPiece *> m_white_pieces;
    vector<ChessPiece *> m_black_pieces;
    //Chess board har ett state som säger 


public:
    ChessBoard();
    ChessBoard(int boardSize);
    void movePiece(ChessMove chess_move);
    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);
    std::shared_ptr<ChessPiece> getState(int x, int y);
    void setState(shared_ptr<ChessPiece> piece, int x, int y);
    // Adderar pjäs till vektor
    void addPiece(ChessPiece* piece);
    // raderar pjäs från vektor
    void removePiece(ChessPiece* piece);
    //accessors
    vector<ChessPiece*>& getWhitePieces();
    vector<ChessPiece*>& getBlackPieces();
    void clearBoard();
    void clearVectors();
};

ChessBoard & operator>>(istream & is, ChessBoard & cb);
ChessBoard & operator<<(ostream & os, ChessBoard & cb);

#endif //CHESSBOARD_H