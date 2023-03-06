#include <iostream>
#include <fstream>
#include "Node.h"

using namespace std;

class AVLTree
{
    public:
    AVLTree();
    void insert(const string &);
    int balanceFactor(Node*);
    void printBalanceFactors();
    void visualizeTree(const string &);

    private:
    Node* root;
    int height(Node*);
    Node* findUnbalancedNode();
    void visualizeTree(ofstream &, Node *);
    void rebalance(Node*);
    void rotateRight(Node*);
    void rotateLeft(Node*);
    void printBalanceFactors(Node*);

};