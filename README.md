# Kompilera
För att kompilera koden så använder du:
g++ -c  King.cpp ChessBoard.cpp ChessPiece.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp main.cpp RandomThinkerAI.cpp OneStepAI.cpp
sedan för att länka ihop dom så används:
g++ -o mainrunner main.o King.o ChessBoard.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o RandomThinkerAI.o OneStepAI.o

## Kör
Då skapas mainrunner.exe
För att köra denna fil så ger du vilken AI och vilka färger du har som command line arugments som strängar
Alternativ är ./mainrunner RandomThinkerAI White OneStepAI Black
som sätter den första AIn till RandomthinkerAI vit och den andra till den mer komplicerade AIn som tänker ett steg mer till svart.
./mainrunner OneStepAI White OneStepAI Black
alla liknande fungerar. Ett undantag är att båda inte kan ha samma färg för så avbryts programmet och ett felmeddelande anges.

### Förklaringar
Siffror och bokstäver som skrivs ut är för att få det att se ut mer som ett schackbräde. Vit är de stora bokstäverna och svart är de små.

långt ner i main.cpp där programmet körs finns:
s << "........" << endl;
s << "...P.p.." << endl;
s << "........" << endl;
s << "p......." << endl;
s << "........" << endl;
s << "........" << endl;
s << "...p...." << endl;
s << "........" << endl;
Det är här är hur board state läses in. Vita pjäser börjar längst ner och svarta börjar högst upp på brädet. De två jag har i main.cpp
just nu är två som behandlar pawn promotion och en som hanterar när inga drag är möjliga. Då inga drag är möjliga måste spelet avslutas
då jag avslutar spelet då en av färgerna har slut på pjäser. Om inga drag är möjliga kommer programmet fortsätta för alltid och sedan
krascha. Jag sätter då att om inga drag är möjliga så avslutas spelet och ett felmeddelande skrivs ut. Jag hanterar detta då dessa två
skapade problem men jag lägger denna gång in en vanliga board state. 

#### Testfil kompilering
Jag använde detta för att kompilera testprogrammet:
g++ -c  King.cpp ChessBoard.cpp ChessPiece.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp tests.cpp
sedan för att länka och skapa mainrunnertest.exe:
g++ -o mainrunnertest tests.o King.o ChessBoard.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o

##### Testfil körning
Detta funkade inte för mig i VScode utan bara i ubuntu som jag har fixat på min windowsdator. Men jag använde:
./mainrunnertest < test.in
Detta ger output "All tests successful"