#include "RandomThinkerAI.h"
#include <cstdlib>
#include <ctime>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "King.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "ChessMove.h"
#include <stdexcept>

RandomThinkerAI::RandomThinkerAI(bool is_white) {
    m_is_white = is_white;
    // Seed för random number
    std::srand(std::time(nullptr));
}

ChessMove RandomThinkerAI::chooseMove(vector<ChessPiece *> &my_pieces, ChessBoard& board) {
    //väljer moves i prioriteringsordning: promotion, capture, noncapture
    //skapa två vektorer, en med alla capturing moves för en färg och en med alla noncapturing moves
    if(this->m_is_white == true){

        //kollar alla capturing moves för vit
        std::vector<ChessMove> capturing_moves_white;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //lägg till alla capturing moves för alla pieces i en vektor som
            //därmed håller alla capturing moves för en färg
            std::vector<ChessMove> allcapmoveswhite = piece->capturingMoves();
            capturing_moves_white.insert(capturing_moves_white.end(), allcapmoveswhite.begin(), allcapmoveswhite.end());
        }
        if (capturing_moves_white.empty() == false) {
            int random_index = std::rand() % capturing_moves_white.size();
            return capturing_moves_white[random_index];
        }

        std::vector<ChessMove> promotion_moves_white;
        for (const auto& piece : my_pieces) {
            if (piece->getLatinRep() == 'P' && piece->getColor() == true) {
                int row = piece->getRow();
                int col = piece->getColumn();
                if(row == 6){
                    //kollar om den kan göra ett noncapture move
                    shared_ptr<ChessPiece> blockpiecewhite = board.getState(col, row+1);
                    if(blockpiecewhite == nullptr){
                        //promote
                        int random_number = std::rand() % 4;
                        if(random_number == 0){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> white_promoted_rook = make_shared<Rook>(col, row, true, &board);
                            board.setState(white_promoted_rook, col, row);
                            board.addPiece(white_promoted_rook.get());
                            ChessMove promotemove = ChessMove(col, row, col, row+1, white_promoted_rook.get());
                            return promotemove;
                        }
                        else if(random_number == 1){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> white_promoted_knight = make_shared<Knight>(col, row, true, &board);
                            board.setState(white_promoted_knight, col, row);
                            board.addPiece(white_promoted_knight.get());
                            ChessMove promotemove = ChessMove(col, row, col, row+1, white_promoted_knight.get());
                            return promotemove;
                        }
                        else if(random_number == 2){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> white_promoted_queen = make_shared<Queen>(col, row, true, &board);
                            board.setState(white_promoted_queen, col, row);
                            board.addPiece(white_promoted_queen.get());
                            ChessMove promotemove = ChessMove(col, row, col, row+1, white_promoted_queen.get());
                            return promotemove;
                        }
                        else if(random_number == 3){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> white_promoted_bishop = make_shared<Bishop>(col, row, true, &board);
                            board.setState(white_promoted_bishop, col, row);
                            board.addPiece(white_promoted_bishop.get());
                            ChessMove promotemove = ChessMove(col, row, col, row+1, white_promoted_bishop.get());
                            return promotemove;
                        }
                    }
                }
            }
        }

        //kollar noncapturing moves för vit
        std::vector<ChessMove> non_capturing_moves_white;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //cout << "2" << endl;
            //se till att samma färg
            //lägg till alla capturing moves för alla pieces i en vektor som
            //därmed håller alla capturing moves för en färg
            std::vector<ChessMove> allnoncapmoveswhite = piece->nonCapturingMoves();
            non_capturing_moves_white.insert(non_capturing_moves_white.end(), allnoncapmoveswhite.begin(), allnoncapmoveswhite.end());
        }

    
        // Om det ej finns capturing moves, välj ett non-capturing move slumpmässigt
        if(non_capturing_moves_white.empty() == true && capturing_moves_white.empty() == true){
            throw std::runtime_error("No moves possible for white.");
        }
        else{
            int random_index = std::rand() % non_capturing_moves_white.size();
            return non_capturing_moves_white[random_index];
        }
    }

    //om m_is_white är false
    //kolla för svart börjar här med promotion
    else if (this->m_is_white == false){

        //kollar alla capturing moves för svart
        std::vector<ChessMove> capturing_moves_black;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            
            //lägg till alla capturing moves för alla pieces i en vektor som
            //därmed håller alla capturing moves för en färg
            std::vector<ChessMove> allcapmovesblack = piece->capturingMoves();
            capturing_moves_black.insert(capturing_moves_black.end(), allcapmovesblack.begin(), allcapmovesblack.end());
        }

        if (capturing_moves_black.empty() == false) {
            int random_index = std::rand() % capturing_moves_black.size();
            return capturing_moves_black[random_index];
        }

        std::vector<ChessMove> promotion_moves_black;
        for (const auto& piece : my_pieces) {
            if (piece->getLatinRep() == 'p' && piece->getColor() == false) {
                int row = piece->getRow();
                int col = piece->getColumn();
                if(row == 1){
                    shared_ptr<ChessPiece> blockpieceblack = board.getState(col, row-1);
                    if(blockpieceblack == nullptr){
                        //promote
                        int random_number = std::rand() % 4;
                        if(random_number == 0){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> black_promoted_rook = make_shared<Rook>(col, row, false, &board);
                            board.setState(black_promoted_rook, col, row);
                            ChessMove promotemove = ChessMove(col, row, col, row-1, black_promoted_rook.get());
                            board.addPiece(black_promoted_rook.get());
                            return promotemove;
                        }
                        else if(random_number == 1){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> black_promoted_knight = make_shared<Knight>(col, row, false, &board);
                            board.setState(black_promoted_knight, col, row);
                            ChessMove promotemove = ChessMove(col, row, col, row-1, black_promoted_knight.get());
                            board.addPiece(black_promoted_knight.get());
                            return promotemove;
                        }
                        else if(random_number == 2){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> black_promoted_queen = make_shared<Queen>(col, row, false, &board);
                            board.setState(black_promoted_queen, col, row);
                            board.addPiece(black_promoted_queen.get());
                            ChessMove promotemove = ChessMove(col, row, col, row-1, black_promoted_queen.get());
                            return promotemove;
                        }
                        else if(random_number == 3){
                            shared_ptr<ChessPiece> pieceToRemove = board.getState(col, row);
                            board.removePiece(pieceToRemove.get());
                            board.setState(nullptr, col, row);
                            shared_ptr<ChessPiece> black_promoted_bishop = make_shared<Bishop>(col, row, false, &board);
                            board.setState(black_promoted_bishop, col, row);
                            board.addPiece(black_promoted_bishop.get());
                            ChessMove promotemove = ChessMove(col, row, col, row-1, black_promoted_bishop.get());
                            return promotemove;
                        }
                    }
                }
            }
        }

        //kollar noncapturing moves för svart
        std::vector<ChessMove> non_capturing_moves_black;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //se till att samma färg
            //lägg till alla capturing moves för alla pieces i en vektor som
            //därmed håller alla capturing moves för en färg
            std::vector<ChessMove> allnoncapmovesblack = piece->nonCapturingMoves();
            non_capturing_moves_black.insert(non_capturing_moves_black.end(), allnoncapmovesblack.begin(), allnoncapmovesblack.end());
        }
        
        if(non_capturing_moves_black.empty() == true && capturing_moves_black.empty() == true){
            throw std::runtime_error("No moves possible for black.");
        }
        else{
            int random_index = std::rand() % non_capturing_moves_black.size();
            return non_capturing_moves_black[random_index];
        }
    }
    throw std::runtime_error("No moves possible.");
}