#include <string>
using namespace std;

class Node
{
    public:
    string data;
    int count;
    Node *left;
    Node *right;
    Node *parent;

    Node(const string& str):data(str),count(0),left(nullptr),right(nullptr),parent(nullptr){}

};