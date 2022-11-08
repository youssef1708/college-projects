#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
using namespace std;
#include <iostream>
class student
{
    public:
    student();
    student(string , string , double );
    void set_Data(string , string , double );
    string get_name();
    string get_ID();
    double get_GPA();
    void Print();
    bool operator<(const student & );

    protected:

    private:
    string name;
    string ID;
    double GPA;
};



#endif // STUDENT_H_INCLUDED
