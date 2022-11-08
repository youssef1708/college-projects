#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

template<class t>
class Node
{
private:
    t info;
    Node* next;
public:
     Node();
     Node* getNext();
     void setNext(Node* n);
     t getInfo();
     void setInfo(t newInfo);

};

#endif // NODE_H_INCLUDED
