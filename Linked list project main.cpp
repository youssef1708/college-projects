//youssef yasser abo elnaga 20205003 NCS2
// Ahmed Mohamed MOkhtar 20205001 NCS2

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

template<class t>
class Node
{

    t info;
    Node* next;
public:

    Node()
    {
        next=NULL;

    }


    Node* getNext()
    {
        return next;
    }

    void setNext(Node* n)
    {
        next=n;
    }
    t getInfo()
    {
        return info;
    }
    void setInfo(t newInfo)
    {
        info=newInfo;
    }


};


template<class t>
class SLL
{
    Node<t> *head , *tail;
public:
    SLL()
    {
        head=tail=NULL;
    }
    void addToHead(t newValue)
    {
        Node<t>* newNode= new Node<t>();
        newNode->setInfo(newValue);
        if (isEmpty())
        {
            newNode->setNext(NULL);
            head=tail=newNode;
        }
        else
        {
            newNode->setNext(head);
            head=newNode;
        }

    }
    void addToTail(t newValue)
    {
        Node<t>* newNode= new Node<t>();
        newNode->setInfo(newValue);
        if(isEmpty())
        {
            tail=head=newNode;

        }
        else
        {
            tail->setNext(newNode);
            tail=newNode;
            newNode->setNext(NULL);
        }

    }

    t removeFromHead()
    {
        t removedValue;
        Node<t> *deletePointer;
        deletePointer=head;
        head=head->getNext();
        removedValue= deletePointer->getInfo();
        delete deletePointer;
        return removedValue;
    }
    t removeFromTail()
    {

        t removedValue;
        Node<t> *deletePointer;
        Node<t> *readPointer;
        deletePointer=readPointer=head;
        while (deletePointer->getNext()!=NULL)
        {
            readPointer=deletePointer;
            deletePointer=deletePointer->
                    getNext();
        }
        tail=readPointer;
        tail->setNext(NULL);
        removedValue=deletePointer->
                getInfo();
        delete deletePointer;
        return removedValue;


    }
    t getValueAtHead()
    {
        t valueOfHead;
        valueOfHead=head->getInfo();
        // cout<< valueOfHead<<" "<<endl;
        return valueOfHead;
    }
    bool isEmpty()
    {
        bool x;
        x= false;
        if(head==NULL)
        {
            x = true;
        }
        return x;
    }
    void clear()
    {
        Node<t>* deletepointer;
        deletepointer=head;
        while (head!=NULL)
        {
            deletepointer=head;
            head=head->getNext();
            delete deletepointer;
        }


    }
    void display()
    {
        if (isEmpty())
        {
            cout<<"the linked list is empty"<<endl;
        }
        Node<t> *temp;
        temp=head;
        while (temp!=NULL)
        {
            cout<<temp->getInfo()<<" ";
            temp=temp->getNext();
        }
        cout<<endl;


    }

    friend ostream& operator<<(ostream& stream, const SLL<t>& list)
    {

        Node<t> *temp;
        temp=list.head;

        while (temp->getNext()!=NULL)
        {
            stream<<temp->getInfo();
            stream<<"->";
            temp=temp->getNext();

        }
        stream << temp->getInfo();
        stream << (temp->getNext() == NULL ? "" : "-> ");
        return stream;
    }

};

template <class t>
class StackSll
{
    SLL<t> stack;
public:
    void push(t newvalue)
    {
        stack.addToHead(newvalue);

    }
    t pop()
    {
        if(isEmpty())
        {
            cout<<"empty stack"<<endl;
        }
        t temp;
        temp=stack.removeFromHead();
        return temp;

    }
    t top()
    {
        if(isEmpty())
        {
            cout<<"empty stack"<<endl;
        }
        t temp;
        temp=stack.getValueAtHead();

        return temp;
    }
    bool isEmpty()
    {
        return stack.isEmpty();
    }
    void clear()
    {
        stack.clear();
    }




};


template<class t>
class QueueSll
{


    SLL<t> queue;
public:
    void enqueue(t newValue)
    {
        queue.addToTail(newValue);

    }
    t dequeue()
    {
        if(isEmpty())
        {
            cout<<"empty Queue"<<endl;
        }
        t temp;
        temp=queue.removeFromHead();
        return temp;

    }
    t front()
    {
        if(isEmpty())
        {
            cout<<"empty Queue"<<endl;
        }
        t temp;
        temp=queue.getValueAtHead();

        return temp;

    }

    bool isEmpty()
    {
        return queue.isEmpty();
    }
    void clear()
    {
        queue.clear();
    }




};
bool check_pair(char open,char close) // function to check opening and closing brackets
{
    if(open=='('&& close==')') return true;
    if(open=='{'&& close=='}') return true;
    if(open=='['&& close==']') return true;
    else{return false;}

}

bool chkBalanced(string exp)
{
    StackSll<char> stack1;
    for (int i=0;i<exp.length();i++)
    {
        if (exp[i]=='('||exp[i]=='{'||exp[i]=='['||exp[i]=='<')
        {
            stack1.push(exp[i]);
        }
        else if(exp[i]==')'||exp[i]=='}'||
                exp[i]==']'||exp[i]=='>')

        {
            if (stack1.isEmpty())return false;
            else if (check_pair(stack1.top(),exp[i])==false)
            {
                return false;}
            stack1.pop();
        }
    }
    if (stack1.isEmpty())return true;
    else return false;
}

int binary_length(int num) // function to know number of bits for binary
{ int n=0;
    while (2^n<num)
    {
        n++;
    }
    return n;
}
string convertToBinary(int num)
{
    StackSll<string> binary;
    int a ;
    string c;
    while (num>0)
    {
        a=num%2;
        num/=2;
        c=to_string(a);
        binary.push(c);

    }
    while (binary.isEmpty()!=true)
    {
        cout<<binary.pop();

    }
    cout<<endl;
    return"end";
}
int ChkPriority(char element)
{
    if (element =='-'||'+'||'*'||'/'||'^')
    {
        if (element=='-'|| element =='+') return 1;
        else if (element=='*'||element=='/') return 2;
        else if (element=='^') return 3;
        else return 0;}

    else{return -1; } // element is not operator

}

string convertInfixToPostfix(string exp)
{
    StackSll<char> postfix;
    string output="";
    if (chkBalanced(exp)==true) {
        for (int i = 0; i < exp.length(); i++) {
            if (exp[i] == ' ') continue;
            if (isdigit(exp[i]) || isalpha(exp[i]))
                output += exp[i];

                // bracket opening
            else if (exp[i]=='(')
                postfix.push('('); // adds the brackets opening to the stack

                // bracket closing
            else if (exp[i]==')')
            {
                while (postfix.top()!='(')
                {
                    output+=postfix.top();
                    postfix.pop();
                }
                postfix.pop(); // removes "("
            }

                // operator
            else {
                if (ChkPriority(exp[i])==-1) {return " Math error";}
                while ( postfix.isEmpty() !=true && ChkPriority(exp[i])<=
                                                    ChkPriority(postfix.top()) )

                {
                    output+=postfix.top();
                    postfix.pop();
                }
                postfix.push(exp[i]);
            }
        }

        while (postfix.isEmpty()!=true )
        {output+=postfix.top();
            postfix.pop();
        }
        return output;
    }
    else {
        cout<<exp << " Syntax error please make sure yo wrote it correctly"<<endl;
        return " Syntax error please make sure yo wrote it correctly";
    }
}
float DetectOperator(float operand1,float operand2 ,char operat )
{
    if (operat=='+'){return operand1+operand2;}
    else if (operat=='-'){return operand1-operand2;}
    else if (operat=='*'){return operand1*operand2;}
    else if (operat=='/'){return operand1/operand2;}


}

float evaluatePostfix(string exp)
{
    string output=convertInfixToPostfix(exp);
    if (output=="error")
    {
        cout <<" Syntax error please make sure you wrote it correctly"<<endl;
    }
    StackSll<float> stack;
    for (int i=0; i<output.length();i++)
    {
        if (isdigit(output[i]))
        {
            stringstream x(output[i]);
            int num=0;
            x>>num;
            stack.push(num);
        }
        else {
            float operand2=stack.top();
            stack.pop();

            float operand1=stack.top();
            stack.pop();

            float res= DetectOperator(operand1,operan
            d2,exp[i]);
            stack.push(res);
        }
    }
    return stack.top();
}






template<class t>
bool moveNthElem(QueueSll<t>queue,int n)
{
    bool x= false;
    int counter=0;
    t temp;
    QueueSll<t> newQueue;
    QueueSll<t> tempQueue;
    while (queue.isEmpty() == false)
    {
        if(counter==n)
        {
            temp=queue.front();
            tempQueue.enqueue(temp);
            queue.dequeue();
            x= true;
            counter++;
            continue;
        }
        temp=queue.front();
        newQueue.enqueue(temp);
        queue.dequeue();
        counter++;

    }
    while (newQueue.isEmpty()== false)
    {
        temp=newQueue.front();
        tempQueue.enqueue(temp);
        newQueue.dequeue();
    }
    while (tempQueue.isEmpty()== false)
    {
        temp=tempQueue.front();
        queue.enqueue(temp);
        cout<<" "<<tempQueue.dequeue();
    }
    cout<<endl;


    return x;

}



template<class t>
void reverseQueue(QueueSll<t> &queue)
{

    StackSll<t> stack1;
    t temp;
    while (queue.isEmpty()== false)
    {
        temp=queue.front();
        stack1.push(temp);
        queue.dequeue();
    }
    while (stack1.isEmpty()== false)
    {
        temp=stack1.top();
        queue.enqueue(temp);
        cout<<" "<<stack1.pop();
    }
    cout<<endl;

}





int main()
{
    SLL<int> linkedList1;
    StackSll<int> stack1;
    QueueSll<int> queue1;
    int selector;
    string choice;

    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1-  Check for balanced brackets " <<endl;
        cout << "2-  Convert to binary " << endl;
        cout << "3-  Convert infix to postfix expression and evaluate" <<endl;
        cout << "4-  Move Nth element to front in a queue of strings. " <<endl;
        cout << "5-  Reverse elements of a queue of doubles. "<<endl;
        cout << "6- EXIT "<<endl;
        cout<<"-----------------------------------------------------"<<endl;
        cin >> choice;
        while(cin.fail() || !(choice.find_first_not_of("123456789") == string::npos)){ //check tha entered choice is correct
            cout << "Incorrect data type, please re-enter: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> choice;
        }
        selector = stoi(choice);
        while ((selector < 1) || (selector > 6) ||cin.fail() || !(choice.find_first_not_of("0123456789") == string::npos)) {
            cout << "Invalid choice number, re-enter a valid one: "; // make sure that user can enter from 1 to 6 only
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
            selector = stoi(choice);
        }
        switch (selector){
            case 1: {
                string checkBalanceString;
                cout<<"Please enter the string: ";
                cin>>checkBalanceString;
                chkBalanced(
                        checkBalanceString);
                cout<< endl;
                cout<<"-----------------------------------------------------"<<endl;
                continue;
            }
            case 2: {
                double decimalNum;
                cout<<"Please enter decimal number: ";
                cin>>decimalNum;
                convertToBinary(decimalNum);

                continue;
            }
            case 3: {
                cout << "enter your expression ";
                string expression;
                getline(cin,expression );
                cout << evaluatePostfix(expression)<<endl;

                continue;
            }
            case 4: {
                int a,b,c,d,e;
                cout<<"Please enter the queue elements of size 5: ";
                cin>>a;
                cin>>b;
                cin>>c;
                cin>>d;
                cin>>e;
                queue1.enqueue(a);
                queue1.enqueue(b);
                queue1.enqueue(c);
                queue1.enqueue(d);
                queue1.enqueue(e);
                int index;
                cout<<"enter the number of index you want to move to the head of the queue: ";
                cin>>index;
                moveNthElem(queue1,index);


                continue;
            }
            case 5: {
                int a,b,c,d,e;
                cout<<"Please enter the queue elements of size 5: ";
                cin>>a;
                cin>>b;
                cin>>c;
                cin>>d;
                cin>>e;
                queue1.enqueue(a);
                queue1.enqueue(b);
                queue1.enqueue(c);
                queue1.enqueue(d);
                queue1.enqueue(e);
                cout<<"the reversed queue: ";
                reverseQueue(queue1);


                continue;
            }
            case 6: {
                cout << "Thank you for using this program." << endl;
                cout << endl;
                exit(EXIT_SUCCESS);
            }
        }
    }





    return 0;
}}