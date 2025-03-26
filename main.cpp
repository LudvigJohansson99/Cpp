#include <string>
#include <sstream>  
using std::stringstream;
#include <iostream>
#include <fstream>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "King.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
using namespace std;
#include "RandomThinkerAI.h"
#include "OneStepAI.h"

//./mainrunner RandomThinkerAI White RandomThinkerAI Black
//./mainrunner OneStepAI White OneStepAI Black

void runGame(bool player1Randomthinker, bool player2Randomthinker,  bool player1White, ChessBoard& board){
    //Om player 1 är vit och player2 är svart
    if(player1White == true){
        //Om player1 är RandomThinkerAI
        if (player1Randomthinker == true){
            if(player2Randomthinker == true){
                //Båda är randomthinker
                RandomThinkerAI player1(true);
                RandomThinkerAI player2(false);
                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer1 = player1.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer1);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    ChessMove movePlayer2 = player2.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer2);

                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
            //Om player2 är OneStepAI och player1 randomthinker med player1 vit
            else{
                RandomThinkerAI player1(true);
                OneStepAI player2(false);

                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer1 = player1.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer1);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
                    
                    ChessMove movePlayer2 = player2.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer2);

                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
        }
        //OM player1 är OnestepAI och vit
        else{
            //Och om player2 är randomthinker svart
            if(player2Randomthinker == true){
                OneStepAI player1(true);
                RandomThinkerAI player2(false);

                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer1 = player1.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer1);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    ChessMove movePlayer2 = player2.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer2);

                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
            //Och player2 är onestep svart
            else{
                OneStepAI player1(true);
                OneStepAI player2(false);

                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer1 = player1.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer1);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    
                    ChessMove movePlayer2 = player2.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer2);

                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
        }
    }
    //om player2 är vit och player1 är svart
    else{
        //Om player1 är RandomThinkerAI
        if (player1Randomthinker == true){
            if(player2Randomthinker == true){
                //Båda är randomthinker
                RandomThinkerAI player1(false);
                RandomThinkerAI player2(true);
                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer2 = player2.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer2);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    ChessMove movePlayer1 = player1.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer1);
                    
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
            //Om player2 är OneStepAI och player1 randomthinker med player1 svart
            else{
                RandomThinkerAI player1(false);
                OneStepAI player2(true);

                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer2 = player2.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer2);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    ChessMove movePlayer1 = player1.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer1);

                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
        }
        //OM player1 är OnestepAI och svart
        else{
            //Och om player2 är randomthinker vit
            if(player2Randomthinker == true){
                OneStepAI player1(false);
                RandomThinkerAI player2(true);

                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer2 = player2.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer2);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    ChessMove movePlayer1 = player1.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer1);

                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
            //Och player2 är onestep vit
            else{
                OneStepAI player1(false);
                OneStepAI player2(true);

                while (board.getWhitePieces().size() != 0 && board.getBlackPieces().size() != 0){
                    cout << board;

                    ChessMove movePlayer2 = player2.chooseMove(board.getWhitePieces(), board);
                    board.movePiece(movePlayer2);

                    cout << board;
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }

                    ChessMove movePlayer1 = player1.chooseMove(board.getBlackPieces(), board);
                    board.movePiece(movePlayer1);
                    if(board.getWhitePieces().size() == 0 || board.getBlackPieces().size() == 0){
                        break;
                    }
        
                    cout << board;
                }

                if(board.getWhitePieces().size() == 0){
                    cout << "White player wins" << endl;
                }
                else{
                    cout << "Black player wins" << endl;
                }
            }
        }
    }
}




//skapa ny lista med pieces som kan hålla koll på att gamet är över
int main(int argc, char *argv[]){

    bool player1IsWhite;
    bool player2IsWhite;

    bool player1IsRandomThinkerAI = false;
    bool player1IsOneStepAI = false;
    bool player2IsOneStepAI = false;
    bool player2IsRandomThinkerAI = false;
    //Kollar command line arguments
    
    //Kolla att antalet argument stämmer
    
    
    if(argc != 5){
        std::cerr << "Usage: aitype1 aicolor1 aitype2 aicolor2\n";
        exit(1);
    }

    //Kollar färg för AI1
    if(std::string(argv[2]).compare("White") == 0) {
        player1IsWhite = true;
    }
    else if(std::string(argv[2]).compare("Black") == 0){
        player1IsWhite = false;
    }
    else{
        std::cerr << "Must be Black Or White\n";
        exit(1);
    }

    //Kollar färg för AI2
    if(std::string(argv[4]).compare("White") == 0) {
        player2IsWhite = true;
    }
    else if(std::string(argv[4]).compare("Black") == 0){
        player2IsWhite = false;
    }
    else{
        std::cerr << "Must be Black Or White\n";
        exit(1);
    }

    //Kollar att båda inte har samma färg
    if(std::string(argv[2]).compare(std::string(argv[4])) == 0){
        std::cerr << "One of the players must be black and the other white\n";
        exit(1);
    }

    //Kollar AI för player1
    if (std::string(argv[1]).compare("RandomThinkerAI") == 0){
        player1IsRandomThinkerAI = true;
    }
    else if(std::string(argv[1]).compare("OneStepAI") == 0){
        player1IsOneStepAI = true;
    }
    else{
        std::cerr << "Error: Invalid AI type specified for player 1.\n";
        exit(1);
    }

    //Kollar AI för player2
    if (std::string(argv[3]).compare("RandomThinkerAI") == 0) {
        player2IsRandomThinkerAI = true;
    }
    else if(std::string(argv[3]).compare("OneStepAI") == 0){
        player2IsOneStepAI = true;
    }
    else{
        std::cerr << "Error: Invalid AI type specified for player 2.\n";
        exit(1);
    }

    ChessBoard board;
    std::stringstream s;
    /*s << "........" << endl;
    s << "...P.p.." << endl;
    s << "........" << endl;
    s << "p......." << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "...p...." << endl;
    s << "........" << endl;

    s << "...P...." << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "...p...." << endl;*/

    s << "........" << endl;
    s << ".q.P.p.." << endl;
    s << ".....n.." << endl;
    s << "p......." << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "...p..P." << endl;
    s << "B......R" << endl;

    s >> board;
    try{
        runGame(player1IsRandomThinkerAI, player2IsRandomThinkerAI, player1IsWhite, board);
    }
    catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

}