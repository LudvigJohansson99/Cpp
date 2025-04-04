struct Node {
    int key;
    double data;
    Node * right;
    Node * left;
};

void insert(Node * & p, int key, double to_be_inserted);  // Note: reference to pointer
void print_tree(Node *p);
void remove(Node * & p, const int & key);
const double & find(Node * p, const int & to_be_found);
double & edit(Node * p, const int & to_be_changed);
void delete_tree(Node * & p);
int get_height(Node *p);

unsigned int max_height(Node * p);
unsigned int min_height(Node * p);
unsigned int size(Node * p);
bool is_balanced(Node * p);