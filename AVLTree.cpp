#include <iostream>
#include <fstream>
#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree()
{
    root = nullptr;
}

void AVLTree::rebalance(Node *node)
{
    if(balanceFactor(node)==-2)
    {
        if(balanceFactor(node->right)==1) rotateRight(node->right);
        rotateLeft(node);
    }

    else if(balanceFactor(node)==2)
    {
        if(balanceFactor(node->left)==-1) rotateLeft(node->left);
        rotateRight(node);
    }

    return;
}

void AVLTree::rotateRight(Node *node)
{
    Node *lptr = node->left;
    Node *temp = lptr->right;
    lptr->right = node;
    node->left = temp;
    lptr->parent = node->parent;
    if(lptr->parent)
    {
        if(lptr->parent->left==node) lptr->parent->left=lptr;
        else lptr->parent->right=lptr;
    }
    node->parent = lptr;
    if(root == node) root = lptr;

}

void AVLTree::rotateLeft(Node *node)
{
    Node *rptr = node->right;
    Node *temp = rptr->left;
    node->right = temp;
    rptr->left = node;
    rptr->parent = node->parent;
    if(rptr->parent){
        if( rptr->parent->left==node) rptr->parent->left=rptr;
        else rptr->parent->right=rptr;
    }
    node->parent = rptr;
    if(root == node) root = rptr;
}

void AVLTree::insert(const string &str)
{
    Node *newnode = new Node(str);
    if(root == nullptr) 
    {
        root = newnode;
        return;
    }

    Node *cur = root;
    while(cur != nullptr)
    {
        if(cur->data == newnode->data) {cur->count++; break;}
        else if(cur->data < newnode->data) 
        {
            if(!cur->right) {cur->right = newnode; newnode->parent = cur; break;}
            else cur = cur->right;
        }
        else
        {
            if(!cur->left) {cur->left = newnode; newnode->parent = cur; break;}
            else cur = cur->left;
        }

    }
    
    if(!cur)
    {
        cout<<"error insertion"<<endl;
        return;
    }

    newnode = newnode->parent;
    while(newnode)
    {
        rebalance(newnode);
        newnode = newnode->parent;
    }
}

int AVLTree::height(Node* node)
{
    if(!node) return -1;
    return max(height(node->left), height(node->right))+1;
}

int AVLTree::balanceFactor(Node* node)
{
    return height(node->left) - height(node->right);
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}

void AVLTree::printBalanceFactors()
{
    printBalanceFactors(root);
    cout<<endl;
}


void AVLTree::printBalanceFactors(Node *node)
{
    if(!node) return;
    printBalanceFactors(node->left);
    std::cout<<node->data<<"("<<balanceFactor(node)<<")"<<", ";
    printBalanceFactors(node->right);
    return;
}