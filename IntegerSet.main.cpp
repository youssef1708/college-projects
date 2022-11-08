//Ahmed Mohamed Sayed 
//Youssef Yasser Abo el naga
#include <iostream>

using namespace std;

class integerSet
{
private:

    int array[101];


public:
    integerSet()
    {
        for(int i =0; i<101;i++)
        {
            array[i]=0;
        }

    }
    integerSet(int userArray[101],int size )
    {

        for (int i = 0; i < 101; ++i)
        {
            if(userArray[i]!=0)
            {
                array[i]=1;
            }
            else
            {
                array[i]=0;
            }
        }
    }



    integerSet unionOfSets( integerSet second)
    {

        integerSet third;
        for (int i = 0; i < 101; ++i)
        {
            if (array[i] == 1 )
            {
                third.array[i] = 1;
            }
            if( second.array[i] == 1)
            {
                third.array[i] = 1;
            }
        }
        return third;
    }




    integerSet intersectionOfSets(integerSet second)
    {
        integerSet third;
        for (int i = 0; i < 101; ++i)
        {
            if (array[i] == 1 && second.array[i] == 1)
            {
                third.array[i] = 1;

            } else
            {
                third.array[i] = 0;
            }
        }

        return third;
        }



    void insertElement(int element)
    {
        array[element]=1;
        cout<<"{";
        for (int i = 0; i < 101; ++i)
        {
            if (array[i]==1)
            {
                cout << i << ",";
            }
        }
        cout<<"}"<<endl;
    }



    void deleteElement(int element)
    {
        array[element]=0;
        cout<<"{";
        for (int i = 0; i < 101; ++i)
        {
            if (array[i]==1)
            {
                cout << i << ",";
            }
        }
        cout<<"}"<<endl;

    }




    void printSet()
    {
        cout<<"{";
        for (int i = 0; i < 101; ++i)
        {
            if(array[i]==1)
            {
                break;
            }
            else if (i==100)
            {
                cout<<"---";

            } else
            {
                continue;
            }
        }

        for (int i = 0; i < 101; ++i)
        {
            if (array[i]==1)
            {
                cout<<i<<",";
            }
        }
        cout<<"}"<<endl;
    }




    void isEqualTo(integerSet secondSet)
    {
        bool end;
        for (int i = 0; i < 101; ++i)
        {
            if (array[i]!=secondSet.array[i])
            {
                end = true;

            }

        }
        if (end == false)
        {
            cout<< "two sets are equal"<< endl;
        }
        else
        {
            cout<< "two sets are not equal"<<endl;
        }
    }




    integerSet operator-(integerSet secondSet)
    {
        integerSet thirdSet;
        for (int i = 0; i <= 101; i++)
        {
            if(array[i]==secondSet.array[i])
            {
                thirdSet.array[i]=0;
            } else
            {
                thirdSet.array[i]=1;
            }
        }

        return thirdSet;
    }




    integerSet operator ! ()
    {

        integerSet secondSet;
        for (int i = 0; i < 101; ++i)
        {
            if (array[i]==1)
            {
                secondSet.array[i]=0;
            }
            else
            {
                secondSet.array[i]=1;
            }
        }

        return secondSet;
    }



};


int main()
{
    int firstSet[101]={0,1,2,3,4,5,6,7,8,9};
    int secondSet[101]={0,1,2,3,4,5};
    int thirdSet[101]={0,0,0,0,0,0,};
    int fifthSet[101]={0,1,2,3,4,5,6};
     integerSet first(firstSet,6);
     integerSet second(secondSet,6);
     integerSet third(thirdSet,10);
     integerSet fifth(fifthSet,7);
     integerSet fourth;
     fourth=second.unionOfSets(first);
     fourth.printSet();
     fourth=first.intersectionOfSets(second);
     fourth.printSet();
     third.printSet();
     fifth.deleteElement(3);
     fifth.insertElement(25);
     first.isEqualTo(third);
     fourth=second-third;
     fourth.printSet();
     fourth=!first;
     fourth.printSet();




    return 0;
}
