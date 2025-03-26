
Kompilering görs inte via makefile utan
t.ex med testbalance.cpp
 g++ -c testbalance.cpp bintree.cpp
 g++ -o balancerunner testtree.o testbalance.o
 ./testrunner

What did you learn from this assignment?
Jag lärde mig mycket om rekursion och har nu mycket djupare förståelse för det

What was hardest to implement in this assignment?
Remove functionen var defenitivt svårast att implementera. Att ändra om pekarna och leta upp vilken pekare som skulle
ändras när man tar bort en nod orsakade en del problem för mig.

If the signature of insert was changed like below, changing the key of p would not have the desired effect, why is that?
Skillnaden är att den nu är en kopia av pekaren och inte en referens. Det betyder att alla förändringar som sker görs på p
görs på kopian istället för orginalnoden.


Are you able to pass a value, such as 17, to a const int & parameter ?
Ja, detta skapar en referens till const int:en som ges till funktionen.

How do you check if two objects are equal if they only have operator< and not operator==?
om man använder if(a < b), else if(a > b) och else{} så har man else som == då om ingen av dom är större än den andra så
är de lika stora.

Does a < b and !(b < a) compare the same thing?
a < b kollar om a är mindra än b medans !(b < a) kollar om den b inte är mindre än a. Detta är ekvivalent med att kolla om 
a är större eller lika stor som b så de är inte riktigt samma

Write down data from your test runs, Första omgången med std::shuffle och next_permutation
The average height of the tree in at least 800 iterations: 30.68
The highest maximum height: 37
The average minimum height: 5.08
The lowest minimum height: 1
The average difference between minimum and maximum height: 25.60
The greatest difference between minimum and maximum height: 35
The lowest difference between minimum and maximum height: 20

Med annan shuffle och 5000 istället för 9000 i storlek. Gjordes med 
The average height of the tree in at least 800 iterations: 28.26
The highest maximum height: 36
The average minimum height: 4.88
The lowest minimum height: 2
The average difference between minimum and maximum height: 23.38
The greatest difference between minimum and maximum height: 32
The lowest difference between minimum and maximum height: 17


