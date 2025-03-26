//
// DD1388 - Lab 4: Losing Chess
//
#include "ChessBoard.h"
#include <fstream>
#include <iostream>
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

vector<ChessPiece*>& ChessBoard::getWhitePieces(){
    return m_white_pieces;
}

vector<ChessPiece*>& ChessBoard::getBlackPieces(){
    return m_black_pieces;
}


void ChessBoard::addPiece(ChessPiece* piece) {
    if (piece->getColor() == true) {
        if (std::find(m_white_pieces.begin(), m_white_pieces.end(), piece) == m_white_pieces.end()) {
            m_white_pieces.push_back(piece);
        }
    }
    else {
        if (std::find(m_black_pieces.begin(), m_black_pieces.end(), piece) == m_black_pieces.end()) {
            m_black_pieces.push_back(piece);
        }
    }
}

void ChessBoard::removePiece(ChessPiece* piece) {
    //itererar efter pjäsen
    //vit pjäs
    if (piece->getColor() == true) {
        auto it = std::find(m_white_pieces.begin(), m_white_pieces.end(), piece);
        if (it != m_white_pieces.end()) {
            this->m_white_pieces.erase(it);
        }
    }
    else {
        //annars svart
        auto it = std::find(m_black_pieces.begin(), m_black_pieces.end(), piece);
        if (it != m_black_pieces.end()) {
            m_black_pieces.erase(it);
        }
    }
}

//Constructor
ChessBoard::ChessBoard(int boardSize) : m_state(boardSize), m_white_pieces(), m_black_pieces() {
    // Initialize the m_state matrix with nullptrs
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            m_state(i, j) = nullptr;
        }
    }
}
//Default
ChessBoard::ChessBoard() : ChessBoard(8){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_state(i, j) = nullptr;
        }
    }
}

std::shared_ptr<ChessPiece> ChessBoard::getState(int x, int y){
    return m_state(x,y);
}

void ChessBoard::setState(std::shared_ptr<ChessPiece> piece, int x, int y) {
    m_state(x, y) = piece;
}

void ChessBoard::movePiece(ChessMove chess_move) {
    // Implementation goes here
    int from_col = chess_move.from_x;
    int from_row = chess_move.from_y;

    int to_col = chess_move.to_x;
    int to_row = chess_move.to_y;

    ChessPiece * pieceToMove = chess_move.piece;
    if(getState(to_col, to_row) == nullptr){
        // om rutan är tom
        //cout << "noncapmove" << endl;
        std::shared_ptr<ChessPiece> Piecepointer = this->getState(from_col, from_row);
        this->setState(Piecepointer, to_col, to_row);
        this->setState(nullptr, from_col, from_row);
        pieceToMove->m_x = to_col;
        pieceToMove->m_y = to_row;
    }
    else{
        //rutan har en pjäs
        //radera pjäsen som blir captured
        std::shared_ptr<ChessPiece> Piecepointer = this->getState(from_col, from_row);
        std::shared_ptr<ChessPiece> capturedPiece = this->getState(to_col, to_row);
        this->setState(nullptr, to_col, to_row);
        this->removePiece(capturedPiece.get());
        this->setState(Piecepointer, to_col, to_row);
        this->setState(nullptr, from_col, from_row);
        pieceToMove->m_x = to_col;
        pieceToMove->m_y = to_row;
    }
}

vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    vector<ChessMove> allCaptureMoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            shared_ptr<ChessPiece> piece = getState(i, j);
            if (piece !=nullptr && piece->getColor() == is_white) {
            std::vector<ChessMove> capturing_moves = piece->capturingMoves();
            allCaptureMoves.insert(allCaptureMoves.end(), capturing_moves.begin(), capturing_moves.end());
            }
        }
    }
    return allCaptureMoves;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    vector<ChessMove> allNonCaptureMoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            shared_ptr<ChessPiece> piece = getState(i, j);
            if (piece !=nullptr && piece->getColor() == is_white) {
            std::vector<ChessMove> nonCapturing_moves = piece->nonCapturingMoves();
            allNonCaptureMoves.insert(allNonCaptureMoves.end(), nonCapturing_moves.begin(), nonCapturing_moves.end());
            }
        }
    }
    return allNonCaptureMoves;
}

ChessBoard& operator>>(istream& is, ChessBoard& cb) {
    string line;
    int x = 0;
    int y = 7;
    while (getline(is, line)) {
        if (line.length() == 64) {
            for (int i = 0; i < 64; i++) {
                x = i % 8;
                char c = line[i];
                if (c == '.') {
                    // If it's a dot, it's an empty square
                    //continue;
                }
                else {
                    // Determine color of piece
                    bool is_white = (c == toupper(c));
                    // Create shared_ptr to piece
                    shared_ptr<ChessPiece> piece;
                    switch (toupper(c)) {
                        // Determine type of piece
                        case 'P':
                            piece = make_shared<Pawn>(x, y, is_white, &cb);
                            break;
                        case 'R':
                            piece = make_shared<Rook>(x, y, is_white, &cb);
                            break;
                        case 'N':
                            piece = make_shared<Knight>(x, y, is_white, &cb);
                            break;
                        case 'B':
                            piece = make_shared<Bishop>(x, y, is_white, &cb);
                            break;
                        case 'Q':
                            piece = make_shared<Queen>(x, y, is_white, &cb);
                            break;
                        case 'K':
                            piece = make_shared<King>(x, y, is_white, &cb);
                            break;
                    }
                // Place the piece on the board
                cb.setState(piece, x, y);
                }
                if ((i + 1) % 8 == 0) {
                    --y;
                }
            }
        }

        else{
            //cout << line << endl;
            //cout << "HAR" << endl;
            //cout << line.length() << endl;
            for (char c : line) {
                if (c == '.') {
                    // Om . så är den tom
                    x++;
                    continue;
                }
                else {
                    // Kollar upper eller inte
                    bool is_white = (c == toupper(c));
                    //skapar shared_ptr piece
                    shared_ptr<ChessPiece> piece;
                    //för att inte behöva kolla t.ex P och p
                    switch (toupper(c)) {
                        //kollar vilken sorts piece
                        case 'P':
                            piece = make_shared<Pawn>(x, y, is_white, &cb);
                            break;
                        case 'R':
                            piece = make_shared<Rook>(x, y, is_white, &cb);
                            break;
                        case 'N':
                            piece = make_shared<Knight>(x, y, is_white, &cb);
                            break;
                        case 'B':
                            piece = make_shared<Bishop>(x, y, is_white, &cb);
                            break;
                        case 'Q':
                            piece = make_shared<Queen>(x, y, is_white, &cb);
                            break;
                        case 'K':
                            piece = make_shared<King>(x, y, is_white, &cb);
                            break;
                    }

                //placerar pjäsen där den ska vara
                cb.setState(piece, x, y);
                //increment x
                x++;
                }
            }
        //för varje line increment y
        y--;
        x = 0;
        continue;
        }


    
    }
    return cb;
}

ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    os << "  A B C D E F G H\n";
    for (int row = 7; row >= 0; row--) {
        os << row << " ";
        for (int col = 0; col < 8; col++) {
            shared_ptr<ChessPiece> piece = cb.getState(col, row);
            if (piece == nullptr) {
                os << ". ";
            }
            else {
                char sort = (*piece).getLatinRep();
                //char32_t sort = (*piece).getUtfRepresentation();
                os << sort << " ";

                
            }
        }
        os << row << endl;
    }
    os << "  A B C D E F G H\n";
    return cb;
}

void ChessBoard::clearBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            this->setState(nullptr, i, j);
        }
    }
}

void ChessBoard::clearVectors(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::shared_ptr<ChessPiece> piece = this->getState(i, j);
            if(piece != nullptr){
                removePiece(piece.get());
            }
        }
    }
}


