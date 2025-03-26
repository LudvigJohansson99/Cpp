#include "bintree.h"
#include <iostream>
using namespace std;


void insert(Node *&p, int key, double to_be_inserted) {
    if (p == nullptr) {
        // Om rotnoden inte finns så skapas ett nytt träd där (den första noden som läggs till blir rotnoden)
        p = new Node{key, to_be_inserted, nullptr, nullptr};
    }
    else if (key < p->key) {
        // Recursively insert the node in the left subtree
        insert(p->left, key, to_be_inserted);
    }
    else if (key > p->key) {
        // Recursively insert the node in the right subtree
        insert(p->right, key, to_be_inserted);
    }
    else {
        // The key already exists, so overwrite the value
        p->data = to_be_inserted;
    }
}

void print_tree(Node *p) {
    if (p == nullptr) {
        return;
    }
    print_tree(p->left);
    std::cout << "Key: " << p->key << ", Data: " << p->data << std::endl;
    print_tree(p->right);
}

void delete_tree(Node *&p) {
    if (p == nullptr) {
        return;
    }
    delete_tree(p->left);
    delete_tree(p->right);
    delete p;
    p = nullptr;
}

const double& find(Node* p, const int& to_be_found) {
    if (p == nullptr) {
        // Om p är nullptr så har listan letats igenom
        // Serverar som basfall i recursion
        throw std::out_of_range("Key not found");
    }
    else if (to_be_found == p->key) {
        // Om nodens key är den man letar efter, returnera data.
        return p->data;
    }
    else if (to_be_found < p->key) {
        // Om keyn man letar efter är mindre än nodens key, leta i vänstra delträdet
        return find(p->left, to_be_found);
    }
    else {
        // Om keyn man letar efter är mindre än nodens key, leta i högra delträdet
        return find(p->right, to_be_found);
    }
}

double& edit(Node* p, const int& to_be_changed) {
    if (p == nullptr) {
        //Den har nått slutet av trädet utan att hitta noden
        throw std::out_of_range("Key not found in edit");
    }
    if (p->key == to_be_changed) {
        //Om p->key == to_be_changed så har noden hittats
        return p->data;
    }
    else if (p->key > to_be_changed) {
        // om p->key är större än to_be_changed så letas vänsta delen igenom
        return edit(p->left, to_be_changed);
    }
    else {
        // om p->key är mindre än to_be_changed så letas högra delen igenom
        return edit(p->right, to_be_changed);
    }
}

unsigned int max_height(Node *p) {
    if (p == nullptr) {
        return 0;
    }
    //kollar igenom båda sidorna för deras djup
    unsigned int left_height = max_height(p->left);
    unsigned int right_height = max_height(p->right);
    unsigned int max_height_sub_tree = max(left_height, right_height);
    return 1 + max_height_sub_tree;
}

unsigned int min_height(Node *p) {
    if (p == nullptr) {
        return 0;
    }
    unsigned int left_height = min_height(p->left);
    unsigned int right_height = min_height(p->right);
    if (left_height < right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

unsigned int size(Node *p) {
    if (p == nullptr) {
        return 0;
    } else {
        return size(p->left) + size(p->right) + 1;
    }
}
//Vad är balanced binary tree?
//The height of the left and right tree for any node does not differ by more than 1.
//The left subtree of that node is also balanced.
//The right subtree of that node is also balanced.

bool is_balanced(Node *p) {
    if (p == nullptr) {
        return true;
    }
    //Kollar det maximala djupet i både det vänsta och högre subträdet
    int left_height = get_height(p->left);
    int right_height = get_height(p->right);

    if (abs(left_height - right_height) > 1) {
        return false;
    }
    //Kollar rekursivt om detta gäller för alla nivåer i trädet
    bool left_balanced = is_balanced(p->left);
    bool right_balanced = is_balanced(p->right);
    bool totalBalance = left_balanced && right_balanced;
    return totalBalance && right_balanced;
}

//Hjälpfunktion som gör is_balanced(Node *p) mer lätttolkad
int get_height(Node *p) {
    if (p == nullptr) {
        return 0;
    }
    
    int left_height = get_height(p->left);
    int right_height = get_height(p->right);

    int maxHeight = max(left_height, right_height);
    return 1 + maxHeight;
}

void remove(Node * & p, const int & key) {
    if (p == nullptr) {
        throw std::out_of_range("Key not found in remove");
        return;
    }

    Node * parent = nullptr;
    Node * current = p;

    // Hitta noden som ska tas bort och dess parent nod
    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        // Noden hittas ej
        throw std::out_of_range("Key not found in remove");
        return;
    }
    //Current är den som ska tas bort m
    if (current->left != nullptr && current->right != nullptr) {
        // Noden har två children, hitta maximala i dess vänsta subträd
        Node * maxNode = current->left;
        Node * maxNodeParent = current;

        while (maxNode->right != nullptr) {
            maxNodeParent = maxNode;
            maxNode = maxNode->right;
        }

        //MaxNode håller nu noden som är maximal i vänstra subträdet k
        // Kopiera datan från noden som hittas till den som ska bli removed M blir K
        //Current blir till K och MaxNode är K
        current->key = maxNode->key;
        current->data = maxNode->data;

        // Ta bort Maximala noden från sin parent node
        if (maxNode == current->left) {
            current->left = maxNode->left;
        }
        else {
            maxNodeParent->right = maxNode->left;
        }
        delete maxNode;
    }
    else {
        //Current är den som ska blir removed och parent är dess parent node
        // Nod har en eller två child nodes
        //Om den har left child sätts child till current->left annars till current->right
        Node * child = current->left != nullptr ? current->left : current->right;
        if (parent == nullptr) {
            // Specialfall
            p = child;
        }
        else if (current == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        delete current;
    }
}