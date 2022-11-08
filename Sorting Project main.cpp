#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "student.h"
using namespace std;


student::student() {
        name = "";
        ID = "";
        GPA = 0;

    }

student::student(string n, string id, double gpa) {
        name = n;
        ID = id;
        GPA = gpa;
    }




void student::set_Data(string n, string id, double gpa)
{
        name = n;
        ID = id;
        GPA = gpa;
    }
string student:: get_name()
    {
        return name;

    }
string student:: get_ID()
    {
        return ID;

    }
double student:: get_GPA()
    {
        return GPA;

    }
void student:: Print()
    {
        cout<<name<<endl;
        cout<<ID<<endl;
        cout<<GPA<<endl;
    }




bool student::operator<(const student & second) {
        bool check;
        if (name < second.name) {
            check= true;
        } else {
            check= false;

        }
        return check;


    }

int counter=0;

template <class T>
void selectionSort(T selectionarr[], int n) {
    counter=0;
    for (int i = 0, j, least; i < n-1; i++) {
        for (j = i+1, least = i; j < n; j++) {
            counter++;
            if (selectionarr[j] < selectionarr[least]) {

                least = j;
            }
        }
        swap (selectionarr [least], selectionarr[i]);
    }

}

template <class T>
void shellsort(T a[], int n) {
    int i, j,increment;
    T tmp ;
    for (increment = pow(2, (int)( log(n)/log(2) ) )-1 ; increment > 0; increment /= 2) {
        for (i = increment; i < n; i++) {
            tmp = a[i];
            for (j = i; j >= increment; j -= increment) {
                counter++;
                if (tmp < a[j - increment]) {
                    a[j] = a[j - increment];
                } else {
                    break;
                }
            }
            a[j] = tmp;
        }


    }
}
int count =0;


template <class T >
int partition(T array[], int low, int high) {

    // select the rightmost element as pivot
    T pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        count++;
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j

            swap(array[i],array[j]);


        }
    }

    // swap pivot with the greater element at i
    swap(array[i + 1], array[high]);

    // return the partition point
    return (i + 1);
}


template <class T>
void quickSort(T array[], int low, int high) {
    count++;
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on righ of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}
template <class T>
int binarySearch(T *arr, int left, int right, T x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x) {
            return mid;
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}





int main() {
    int selector;
    string name, id;
    double gpa;

    student *a1;
    student *a2;
    student *a3;


    int size = 0;
    char input[100];
    fstream namefile;
    namefile.open("students.txt", ios::in);
    if (namefile) {
        namefile.getline(input, 100);
        size = stoi(input);
        string array[size * 3];


        while (namefile)
        {
            a1 = new student[size];
            for (int i = 0; i < size ; ++i)
            {
                namefile.getline(input, 100);
                name = input;
                namefile.getline(input, 100);
                id = input;
                namefile.getline(input, 100);
                gpa = stod(input);
                a1[i].set_Data(name, id, gpa);

            }
            break;



        }


        namefile.close();
        a3 = a2 = a1;


    }
    else
    {
        cout << "error" << endl;
    }

    int choice=1;
    while (choice=1) {
        cout << "Enter your choice:" << endl;
        cout << "1- Show number of comparisons and sorted array of selection sort " << endl;
        cout << "2- Show number of comparisons and sorted array of shell sort " << endl;
        cout << "3- Show number of comparisons and sorted array of quick sort " << endl;
        cout << "4- search by name" << endl;
        cout << "5- Exit" << endl;
        cout << "Choice: ";
        cin >> selector;
        while ((selector < 1) || (selector > 5)) {
            cout << "Invalid choice, re-enter a valid one: ";
            cin >> selector;
        }
        switch (selector) {
            case 1: {
                student temp;
                string array[size];
                for (int i = 0; i < size; ++i)
                {
                    array[i]=a1[i].get_name();

                }
                selectionSort(array, size);
                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < size; ++j)
                    {
                        if (array[i] == a1[j].get_name())
                        {
                            temp=a1[i];
                            a1[i]=a1[j];
                            a1[j]=temp;

                        }

                    }

                }


                ofstream selec_file ("selection.txt",ios::out);
                selec_file<<"Number of comparisons: "<<counter<<endl;
                counter=0;
                for (int i=0; i<5;i++)
                {
                    selec_file<<a1[i].get_name()<<endl;
                    selec_file<<a1[i].get_ID()<<endl;
                    selec_file<<a1[i].get_GPA()<<endl;
                }


                break;

            }
            case 2: {
                student temp;
                string array[size];
                for (int i = 0; i < size; ++i)
                {
                    array[i]=a2[i].get_name();

                }
                shellsort(array, size);
                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < size; ++j)
                    {
                        if (array[i] == a2[j].get_name())
                        {
                            temp=a2[i];
                            a2[i]=a2[j];
                            a2[j]=temp;

                        }

                    }

                }
                ofstream shell_file ("shell.txt",ios::out);
                shell_file<<"Number of comparisons: "<<counter<<endl;
                counter=0;
                for (int i=0; i<5;i++)
                {
                    shell_file<<a2[i].get_name()<<endl;
                    shell_file<<a2[i].get_ID()<<endl;
                    shell_file<<a2[i].get_GPA()<<endl;
                }




                break;

            }
            case 3: {
                student temp;
                string array[size];
                for (int i = 0; i < size; ++i)
                {
                    array[i]=a3[i].get_name();

                }
                quickSort(array, 0, size - 1);
                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < size; ++j)
                    {
                        if (array[i] == a3[j].get_name())
                        {
                            temp=a3[i];
                            a3[i]=a3[j];
                            a3[j]=temp;

                        }

                    }

                }


                ofstream quick_file ("quick.txt",ios::out);
                quick_file<<"Number of comparisons: "<<count<<endl;
                count=0;
                for (int i=0; i<5;i++)
                {
                    quick_file<<a3[i].get_name()<<endl;
                    quick_file<<a3[i].get_ID()<<endl;
                    quick_file<<a3[i].get_GPA()<<endl;
                }


                break;

            }
            case 4:
            {


                string searchName;
                cout<<"please enter the name: ";
                cin.ignore();
                getline(cin,searchName);

                string arrr[size];
                selectionSort(a1,size);
                for (int i = 0; i < size; ++i)
                {
                    arrr[i]=a1[i].get_name();

                }
                selectionSort(arrr,size);



                 int x= binarySearch(arrr,0,size-1,searchName);

                cout<<a1[x].get_name()<<endl;
                cout<<a1[x].get_ID()<<endl;
                cout<<a1[x].get_GPA()<<endl;



                break;

            }
            case 5: {
                cout << "Thank you for using this program." << endl;
                exit(EXIT_SUCCESS);
            }
        }
    }

    return 0;
}
