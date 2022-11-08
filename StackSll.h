#ifndef STACKSLL_H_INCLUDED
#define STACKSLL_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
template <class t>
class StackSll
{
private:
    SLL<t> stack;
public:
    void push(t newvalue);
    t pop();
    t top();
    bool isEmpty();
    void clear();
};


#endif // STACKSLL_H_INCLUDED
