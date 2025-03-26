What did you learn from this assignment?
Jag lärde mig mycket men det främsta jag lärde mig var virtual och override var och hur det används.

What was most difficult to do in this assignment?
Det svåraste var att implementera pawn promotion och att plocka bort och lägga till pjäser. Speciellt i den mer
komplicerade AIn OneStepAI som även har några extra regler att följa innan promotion sker.

The code relies on virtual functions. Could the code have been written without virtual functions?
Det är möjligt men det hade varit svårare och väldigt mycket mer tidskrävande och det hade blivit mer och mindre flexibel
kod.

Could ChessPiece have been an abstract class?
Cppreference definierar abstract class "Defines an abstract type which cannot be instantiated, but can be used as a base class." Jag tycker därmed det hade varit möjligt att ha ChessPiece som abstract class då ChessPiece i sig inte behöver använda
några av sina "egna" metoder. ChessPiece::validMove används aldrig t.ex utan overrideas alltid.

There was no separate unit test for each function in this assignment, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?
Nackdelen med detta sätt att testa är att det är svårare att leta upp vart felet ligger någonstans om testet inte get korrekt
resultat. Några fördelar är att inte lika många test behöver skrivas och att det även testar hur funktionerna och metoderna jobbar med varandra till skillnad från unittest som framför allt testar beståndsdelarna av programmet.

What is the problem with a diamond inheritance?
Det främsta problemet med diamond inheritance är att om en klass ärver från två olika klasser som båda har ärvt från samma basklass så kan det bli tvetydigt för kompilatorn vilken av de två klassernas metod den ska kalla på då båda har ärvt den från samma basklass.

Did you encounter any problem with protected member variables and, if so, how did you solve them?
Ja jag stötte på en hel del problem med protected och löste det i princip alltid med get-metoder. Jag testade i början lite med friend men tyckte get var den enklare lösningen.

Create a queen object and try to set the unnecessaryInt in ChessPiece. What happens?
Det ändrar endast drottningens version av unnecessaryInt medans rook och bishop har sina egna kopior av unnecessaryInt.

Think about if it would be better if the queen had a bishop and a rook (as members) instead of inherited from them?
Ja jag tycker att det hade varit bättre då drottningen inte använder all funktionalitet för bishop och rook. Drottningen använder endast deras versioner av validMove för att kolla om ett move är valid så jag tycker det känns onödigt att de den ska ärva av klasserna då det även skapar diamond inheritance problemet som nämndes tidigare.