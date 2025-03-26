#include "bintree.h"
#include <iostream>
using namespace std;
int main(){
    //Print_tree skriver ut trädet från vänster till höger
         /*1
         /   \
        2     3
       / \   / \
      4   5 6   7*/
    //Detta skrivs ut i ordning (4, 2, 5, 1, 6, 3, 7)
    //Först testas print_tree
    Node *root = nullptr;
    delete_tree(root);
    print_tree(root);

    //Här testat insert på empty tree
    insert(root, 5, 10.0);
    cout << "Binary tree, här förväntas endast en nod med (5, 10.0):" << endl;
    print_tree(root);
    remove(root, 5); //Remove då denna används igen senare

    //Här testas find på nullptr tree som då catchar error
    cout << "Här förväntas ett error i find" << endl;
    try {
        const double& result = find(nullptr, 5);
    }
    catch (std::out_of_range& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }

    //Testas error throw på edit
    cout << "ett error i edit väntas" << endl;
    try {
        double& editresult = edit(nullptr, 5);
    }
    catch (std::out_of_range& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }

    cout << "Här väntas tre nollor i rad" << endl;
    //Testar alla djup och storlek på nullptr
    unsigned int resultMax = max_height(nullptr);
    cout << resultMax << std::endl;

    unsigned int resultMin = min_height(nullptr);
    cout << resultMin << std::endl;

    unsigned int treeSize = size(nullptr);
    cout << treeSize << endl;

    cout << "detta ska vara true" << endl;
    bool isBalanced = is_balanced(nullptr);
    if(isBalanced == true){
        //Är balanserat om den är tomt
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }

    //Testar error throw på remove
    Node * removeRoot = nullptr;
    cout << "Här väntas error i remove" << endl;
    try {
        remove(removeRoot, 5);
    }
        catch (std::out_of_range& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }
    //Här är test slut på nullptr

    //Här testas alla funktioner på ett tree med storlek 1.
    Node * test1SizeTree = nullptr;
    insert(test1SizeTree, 3, 10);

    //Har nu ett tree med size 1
    //testar insert
    cout << "Kollar att insert fungerar tree med storlek 1 så print_tree bör ha 2 noder" << endl;
    insert(test1SizeTree, 2, 20);
    print_tree(test1SizeTree);

    cout << "Kollar att remove fungerar tree med storlek 1 så att bintree är endast 1 nod igen" << endl;
    //testar remove
    remove(test1SizeTree, 3);
    print_tree(test1SizeTree);

    cout << "Kollar att find fungerar på tree med storlek 1, här väntas 20 skrivas ut" << endl;
    const double &find1 = find(test1SizeTree, 2);
    cout << "Datan vid noden som hittas: " << find1 << endl;

    double &editRef = edit(test1SizeTree, 2);
    editRef = 5.0;
    cout << "Kollar att edit fungerar: här väntas noden med key 2 ha data = 5" << endl;
    print_tree(test1SizeTree);

    //Här testas alla height och size relaterade funktioner som i detta fall borde bli 1.
    cout << "Tre ettor ska skrivas ut: " << endl;
    unsigned int maxheight = max_height(test1SizeTree);
    cout << "Max height: " << maxheight << endl;

    unsigned int minheight = min_height(test1SizeTree);
    cout << "Min height: " << minheight << endl;

    unsigned int sizeOfTree = size(test1SizeTree);
    cout << "Size of tree: " << sizeOfTree << endl;

    //Här kollas balansen som bör blir true
    cout << "Väntas ett tree balanserat" << endl;
    bool size1TreeIsBalanced = is_balanced(test1SizeTree);
    if(size1TreeIsBalanced == true){
        cout << "Tree balanserat" << endl;
    }
    else{
        cout << "Tree inte balanserat" << endl;
    }
    
    delete_tree(removeRoot);
    delete_tree(test1SizeTree);
    
    //NU testas några funktioner för ett större träd
    insert(root, 5, 10.0);
    insert(root, 3, 7.5);
    insert(root, 7, 12.5);
    insert(root, 2, 5.0);
    insert(root, 4, 8.0);
    insert(root, 6, 11.0);
    insert(root, 8, 13.0);
    insert(root, 9, 14.0);
    insert(root, 0, 3.0);
    insert(root, 1, 2.0);
    insert(root, 4, 40.0);
    insert(root, 2, 20.0); //skriver över värdet med key = 2
    
    //Här kollas några funktioners errors på större träd.
    //Här kollas find
    cout << "Kollar att find fungerar med stort tree, väntas att 20 skrivs ut" << endl;
    const double &findStor = find(root, 2);
    cout << "Datan vid noden som hittas: " << findStor << endl;

    //Här kollas size
    cout << "Här bör 10 skrivas ut" << endl;
    unsigned int sizeOfLargeTree = size(root);
    cout << "Size of large tree: " << sizeOfLargeTree << endl;

    //Här kollas max height
    cout << "Detta blir 5" << endl;
    unsigned int maxheightlarge = max_height(root);
    cout << "Max height for large tree: " << maxheightlarge << endl;

    cout << "Detta blir 3" << endl;
    //Här kollas min height
    unsigned int minheightlarge = min_height(root);
    cout << "Min height for large tree: " << minheightlarge << endl;

    //Nu testas: Test some functions if they properly throw std::out_of_range with a tree size > 1
    cout << "vid detta test skall att keyn inte hittades i edit skrivas ut" << endl;
    cout << "Kollar att edit ger error: " << endl;
    try {
        double &editReflarga = edit(root, 19);
    }
    catch (std::out_of_range& error) {
    std::cout << "Error: " << error.what() << std::endl;
    }

    cout << "vid detta test skall att keyn inte hittades i remove skrivas ut" << endl;
    cout << "Kollar att remove ger error: " << endl;
    try {
        remove(root, 12);
    }
    catch (std::out_of_range& error) {
    std::cout << "Error: " << error.what() << std::endl;
    }



    delete_tree(root);
}