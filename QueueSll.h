#ifndef QUEUESLL_H_INCLUDED
#define QUEUESLL_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
template<class t>
class QueueSll
{
private:
    SLL<t> queue;
public:
    void enqueue(t newValue);
    t dequeue();
    t front();
    bool isEmpty();
    void clear();
};


#endif // QUEUESLL_H_INCLUDED
