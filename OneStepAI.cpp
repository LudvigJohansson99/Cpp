#include "OneStepAI.h"
#include <random>
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
#include <stdexcept>

OneStepAI::OneStepAI(bool is_white){
    m_is_white = is_white;
    // Seed för random number
    std::srand(std::time(nullptr));
}
int OneStepAI::CaptureAfterPromotion(int x, int y, bool is_white, ChessBoard& board){
    //för denna på ett sätt så att jag kan använda promotionkoden i RandomThinkerAI som inte är
    //optimal men den funkar och har varit den överlägset svåraste delen av labben för mig

    //Rook Knight Queen Bishop är ordningen
    if(this->m_is_white == true){
        //Vit Rook
        shared_ptr<ChessPiece> white_promoted_rook = make_shared<Rook>(x, y, true, &board);

        //tar bort bonden tillfälligt då den kan påverka pjäsens förmåga att göra capture
        shared_ptr<ChessPiece> pawnToRemove = board.getState(x, y-1);
        board.setState(nullptr, x, y-1);

        std::vector<ChessMove> capturemoves = white_promoted_rook->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y-1);
            board.removePiece(white_promoted_rook.get());
            return 0;
        }

        board.removePiece(white_promoted_rook.get());

        //Vit Knight
        board.setState(nullptr, x, y);
        shared_ptr<ChessPiece> white_promoted_knight = make_shared<Knight>(x, y, true, &board);
        capturemoves = white_promoted_knight->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y-1);
            board.removePiece(white_promoted_knight.get());
            return 1;
        }

        board.removePiece(white_promoted_knight.get());

        //Vit Queen
        board.setState(nullptr, x, y);
        shared_ptr<ChessPiece> white_promoted_queen = make_shared<Queen>(x, y, true, &board);

        capturemoves = white_promoted_queen->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y-1);
            board.removePiece(white_promoted_queen.get());
            return 2;
        }


        board.removePiece(white_promoted_queen.get());

        //Vit Bishop
        board.setState(nullptr, x, y);
        shared_ptr<ChessPiece> white_promoted_bishop = make_shared<Bishop>(x, y, true, &board);

        capturemoves = white_promoted_bishop->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y-1);
            board.removePiece(white_promoted_bishop.get());
            return 3;
        }

        board.removePiece(white_promoted_bishop.get());

        board.setState(pawnToRemove, x, y-1);

        //För att visa för funktionen som kallar att den inte hittade något
        return 4;
    }
    else if(this->m_is_white == false){
        //Svart Rook
        shared_ptr<ChessPiece> black_promoted_rook = make_shared<Rook>(x, y, false, &board);

        //tar bort bonden tillfälligt då den kan påverka pjäsens förmåga att göra capture
        shared_ptr<ChessPiece> pawnToRemove = board.getState(x, y+1);
        board.setState(nullptr, x, y+1);

        std::vector<ChessMove> capturemoves = black_promoted_rook->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y+1);
            board.removePiece(black_promoted_rook.get());
            return 0;
        }
        board.removePiece(black_promoted_rook.get());

        //Svart Knight
        board.setState(nullptr, x, y);
        shared_ptr<ChessPiece> black_promoted_knight = make_shared<Knight>(x, y, false, &board);
        capturemoves = black_promoted_knight->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y+1);
            board.removePiece(black_promoted_knight.get());
            return 1;
        }
        board.removePiece(black_promoted_knight.get());

        //Svart Queen
        board.setState(nullptr, x, y);
        shared_ptr<ChessPiece> black_promoted_queen = make_shared<Queen>(x, y, false, &board);

        capturemoves = black_promoted_queen->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y+1);
            board.removePiece(black_promoted_queen.get());
            return 2;
        }
        board.removePiece(black_promoted_queen.get());


        //Svart Bishop
        board.setState(nullptr, x, y);
        shared_ptr<ChessPiece> black_promoted_bishop = make_shared<Bishop>(x, y, false, &board);

        capturemoves = black_promoted_bishop->capturingMoves();

        if(capturemoves.empty() == true){
            //återställ brädan och returnera
            board.setState(nullptr, x, y);
            board.setState(pawnToRemove, x, y+1);
            board.removePiece(black_promoted_bishop.get());
            return 3;
        }
        board.removePiece(black_promoted_bishop.get());

        board.setState(pawnToRemove, x, y+1);

        //För att visa för funktionen som kallar att den inte hittade något
        return 4;
    }
    return 4;
}

bool OneStepAI::forceCapture(int x, int y, bool is_white, ChessBoard& board) {
    // Motståndarens pjäser
    vector<ChessPiece*> opponent_pieces;
    if(is_white == true){
        opponent_pieces = board.getBlackPieces();
    }
    else{
        opponent_pieces = board.getWhitePieces();
    }

    for (auto piece : opponent_pieces) {
        //Kolla så att pjäsen ej är bonde då dessa behöver behandlas separat
        if(piece->getLatinRep() != 'P' && piece->getLatinRep() != 'p'){
            if(piece->getValidMove(x,y) != 0){
                //om det för motståndarpjäsen är ett valid move så är det ett capture move för motståndaren
                return true;
            }
        }
        //Kollar motståndarens bonde
        else if(piece->getLatinRep() == 'P'){
            //Bonden är vit
            if(piece->getRow() == y-1){
                if(piece->getColumn() == x+1){
                    return true;
                }
                else if(piece->getColumn() == x-1){
                    return true;
                }
                else{
                    ;
                }
            }
        }
        else if(piece->getLatinRep() == 'p'){
            //Bonden är svart
            if(piece->getRow() == y+1){
                if(piece->getColumn()== x+1){
                    return true;
                }
                else if(piece->getColumn() == x-1){
                    return true;
                }
                else{
                    ;
                }
            }
        }
    }
    //Bönder är de enda pjäserna som inte capturar på samma sätt som de rör sig så
    // If no opponent piece can capture at the intended square, return false
    return false;
}

ChessMove OneStepAI::chooseMove(vector<ChessPiece *> &my_pieces, ChessBoard& board){
    if(this->m_is_white == true){

        //kollar alla capturing moves för vit
        std::vector<ChessMove> capturing_moves_white;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //lägg till alla capturing moves för en färg i en vektor
            std::vector<ChessMove> allcapmoveswhite = piece->capturingMoves();
            capturing_moves_white.insert(capturing_moves_white.end(), allcapmoveswhite.begin(), allcapmoveswhite.end());
        }

        for(const auto& move : capturing_moves_white){
            //forceCapture(int x, int y, bool is_white, ChessBoard& board)
            if(forceCapture(move.to_x, move.to_y, true, board) == true){
                return move;
            }
        }

        if(capturing_moves_white.empty() == false){
            int random_index = std::rand() % capturing_moves_white.size();
            return capturing_moves_white[random_index];
        }
        //Logik för capturing moves klar här

        //Pawn promotion Vit
        std::vector<ChessMove> promotion_moves_white;
        for (const auto& piece : my_pieces) {
            //cout << "1" << endl;
            //cout << piece->getLatinRep() << " " << piece->getColor() << endl;
            if (piece->getLatinRep() == 'P' && piece->getColor() == true) {
                //cout << "2" << endl;
                int row = piece->getRow();
                int col = piece->getColumn();
                if(row == 6){
                    //cout << "3" << endl;
                    //kollar om den kan göra ett noncapture move
                    shared_ptr<ChessPiece> blockpiecewhite = board.getState(col, row+1);
                    if(blockpiecewhite == nullptr){
                        //promote

                        //Här kollas ifall pjäsen kan bli promoted till en pjäs som inte kan göra
                        //capture nästa move. Annars är det random
                        int promoteToCapture = CaptureAfterPromotion(col, row+1, this->m_is_white, board);
                        //cout << "promoteToCapture Vit: " << promoteToCapture << endl;
                        int random_number = 0;
                            if(promoteToCapture == 4){
                                random_number = std::rand() % 4;
                            }
                            else{
                                random_number = promoteToCapture;
                            }

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
        //Slut pawn promotion Vit

        //Noncapturing moves
        //kollar alla noncapturing moves för vit
        std::vector<ChessMove> non_capturing_moves_white;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //lägg till alla noncapturing moves för en färg i en vektor
            std::vector<ChessMove> allnoncapmoveswhite = piece->nonCapturingMoves();
            non_capturing_moves_white.insert(non_capturing_moves_white.end(), allnoncapmoveswhite.begin(), allnoncapmoveswhite.end());
        }

        for(const auto& move : non_capturing_moves_white){
            //forceCapture(int x, int y, bool is_white, ChessBoard& board)
            if(forceCapture(move.to_x, move.to_y, true, board) == true){
                return move;
            }
        }
    
    
        if(non_capturing_moves_white.empty() == true && capturing_moves_white.empty() == true){
            throw std::runtime_error("No moves possible for white.");
        }
        else{
            int random_index = std::rand() % non_capturing_moves_white.size();
            return non_capturing_moves_white[random_index];
        }
    //Logik för vit färg klar här
    }

    //om m_is_white är false
    //kolla för svart börjar här
    else if (this->m_is_white == false){
        //kollar alla capturing moves för svart
        std::vector<ChessMove> capturing_moves_black;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //lägg till alla capturing moves för en färg i en vektor
            std::vector<ChessMove> allcapmovesblack = piece->capturingMoves();
            capturing_moves_black.insert(capturing_moves_black.end(), allcapmovesblack.begin(), allcapmovesblack.end());
        }

        for(const auto& move : capturing_moves_black){
            //forceCapture(int x, int y, bool is_white, ChessBoard& board)
            if(forceCapture(move.to_x, move.to_y, false, board) == true){
                return move;
            }
        }

        if(capturing_moves_black.empty() == false){
            int random_index = std::rand() % capturing_moves_black.size();
            return capturing_moves_black[random_index];
        }
        //Logik för capturing moves klar här

        //Pawn promotion Svart

        std::vector<ChessMove> promotion_moves_black;
        for (const auto& piece : my_pieces) {
            if (piece->getLatinRep() == 'p' && piece->getColor() == false) {
                int row = piece->getRow();
                int col = piece->getColumn();
                if(row == 1){
                    shared_ptr<ChessPiece> blockpieceblack = board.getState(col, row-1);
                    if(blockpieceblack == nullptr){
                        //promote

                        //Här kollas ifall pjäsen kan bli promoted till en pjäs som inte kan göra
                        //capture nästa move. Annars är det random
                        int promoteToCapture = CaptureAfterPromotion(col, row-1, this->m_is_white, board);
                        //cout << "promoteToCapture Svart: " << promoteToCapture << endl;
                        int random_number = 0;
                            if(promoteToCapture == 4){
                                random_number = std::rand() % 4;
                            }
                            else{
                                random_number = promoteToCapture;
                            }

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

        //Noncapturing moves
        //kollar alla noncapturing moves för svart
        std::vector<ChessMove> non_capturing_moves_black;
        //för varje pjäs i vektorn my_pieces
        for (const auto& piece : my_pieces) {
            //lägg till alla noncapturing moves för en färg i en vektor
            std::vector<ChessMove> allnoncapmovesblack = piece->nonCapturingMoves();
            non_capturing_moves_black.insert(non_capturing_moves_black.end(), allnoncapmovesblack.begin(), allnoncapmovesblack.end());
        }

        for(const auto& move : non_capturing_moves_black){
            //forceCapture(int x, int y, bool is_white, ChessBoard& board)
            if(forceCapture(move.to_x, move.to_y, false, board) == true){
                return move;
            }
        }
    
        if(non_capturing_moves_black.empty() == true && capturing_moves_black.empty() == true){
          throw std::runtime_error("No moves possible for black.");
        }
        else{
            int random_index = std::rand() % non_capturing_moves_black.size();
            return non_capturing_moves_black[random_index];
        }
    
    //Logik för svart färg klar här
    }
   throw std::runtime_error("No moves possible.");
}