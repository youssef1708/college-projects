#ifndef SLL_H_INCLUDED
#define SLL_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
template<class t>
class SLL
{
private:
     Node<t> *head , *tail;
public:
     SLL();
     void addToHead(t newValue);
     void addToTail(t newValue);
     t removeFromHead();
     t removeFromTail();
     t getValueAtHead();
     bool isEmpty();
     void clear();
     void display();
     friend ostream& operator<<(ostream& stream, const SLL<t>& list);
};


#endif // SLL_H_INCLUDED
