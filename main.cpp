/*
 * Authors: 1- Youssef Mohamed Emam
 *          2- Youssef Yasser Abo El-naga
 *
 * Purpose: This Program takes a .txt file as an input, performs some operations on the text
 *          then prints the output text in another file.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class FloatArray
{
public:
    /* Constructor */
    FloatArray(int);
    /*  Destructor  */
    virtual ~FloatArray();
    /* Virtual function to be overridden */
    virtual void addFloat(float);
    /*Stream Insertion and Extraction Operators Overloading */
    friend ofstream& operator<< (ofstream& fout, FloatArray& floatArray);
    friend ifstream& operator>> (ifstream& fin,FloatArray* floatArray);
    /* static member function to set the static variable index */
    static void setIndex(int);

/* Protected members to be inherited by derived classes */
protected:

    /* Float array to store the output of function addFloat */
    float* array = 0;
    int sizeOfArray = 0;

    /* Static member to keep track of the index */
    static int index;
};

/* setting index value by zero */

int FloatArray::index = 0;

/*
 * Parameterized Constructor:
 * - Executed when an instance is created with a parameter (int).
 * - Doesn't return any value.
 * What it does:
 * -Assigns size of array to the class.
 */
FloatArray::FloatArray(int sizeOfArray)
{
    this->sizeOfArray = sizeOfArray;
    array = new float [this->sizeOfArray];

}

/* Destructor:
 * - Doesn't return any value.
 * What it does:
 * - Deallocates memory of the dynamic array.
 * - Sets pointer array to 0.
 */
FloatArray::~FloatArray()
{
    delete [] array;
    array = 0;
}

/* void setIndex():
 * - Sets the index to the value of the parameter integer passed.
 * - Doesn't return any value.
 */
void FloatArray::setIndex(int index)
{
    FloatArray::index = index;
}

/* void addFloat():
 * - Takes float as a parameter.
 * - Add the parameter at the end of the array.
 * - Increments the index of the class.
 * - Doesn't return any value.
 */
void FloatArray::addFloat(float number)
{
    array [index] = number;
    index = index + 1;
}

 /* Operator >>:
  * - Friend of FloatArray class.
  * - Overloaded to get input from file and call addFloat() function.
  * - Takes two parameters, an ifstream object and a FloatArray pointer.
  * - Declares float number and set its value by zero.
  * - Appends number to the ifstream.
  * - Calls addFloat function() with the arrow operator to call the appropriate function.
  * - Returns an ifstream object.
  */
ifstream& operator>> (ifstream& fin, FloatArray* floatArray)
{
    float number = 0;
    fin >> number;
    floatArray->addFloat(number);
    return fin;
}

/* Operator <<:
 * - friend of FloatArray class.
 * - Overloaded to print the size of the array and the array of floats.
 * - Ofstream object is returned
 */
ofstream& operator<< (ofstream& fout, FloatArray& floatArray)
{

    fout << left << setw(1) << floatArray.sizeOfArray <<"|";
    for (int i = 0; i < floatArray.sizeOfArray; i++)
    {
        fout << "   " <<setw(5) << left << floatArray.array[i];
    }
    fout << "\n";

    return fout;
}


/* Class SortedArray That inherits from the class FloatArray */
class SortedArray:public FloatArray
{
public:
    /* Constructor */
    SortedArray(int);
    /* Destructor */
    virtual ~SortedArray();
    /* addFloat() Function that overrides the addFloat Function in the FloatArray class */
    virtual void addFloat(float);
};

/* Parameterized Constructor:
 * - Executed when an instance is created with an integer as a parameter.
 * - Doesn't return any value.
 * What it does:
 * - Calls the base class' constructor with the entered integer as a parameter.
 */
SortedArray::SortedArray(int sizeOfArray): FloatArray(sizeOfArray)
{
}

/* Destructor:
 * - Doesn't take any value.
 * - Doesn't return any value.
 */
SortedArray::~SortedArray()
{
}


/* Void addFloat():
 * - Overridden function of the base class.
 * - Takes a float as a parameter.
 * - Puts the entered float in its correct position.
 * - Doesn't return any value.
 */
void SortedArray::addFloat(float number)
{
    // For the first entry.
    if (index == 0)
    {
        array [index] = number;
        index = index + 1;
        return;
    }

    // If the number entered is smaller than the first element.
    else if (number < array[0])
    {
        // For loop to shift elements in the array to the right.
        for (int i = sizeOfArray -1; i >= 0; i--)
        {
            array [i] = array [i-1];
        }
        array[0] = number;
        index = index + 1;
        return;
    }

    // If the number is larger than the last element entered.
    else if(number > array[index -1])
    {
        array[index] = number;
        index = index + 1;
        return;
    }

    // If the number should be put between 2 numbers.
    else
    {
        // For loop to check where the element should be put.
        for (int i = 1; i < sizeOfArray; i++)
        {
            // If condition to check if the element should be put between array[i-1] and array[i].
            if(array[i-1] < number && array[i] > number)
            {
                // For loop to shift elements to the right until the position of i.
                for (int j = sizeOfArray -1; j > i; j--)
                {
                    array [j] = array [j-1];
                }
                array[i] = number;
                index = index + 1;
                break;
            }
        }
    }
}


/* Class FrontArray That inherits from the class FloatArray */
class FrontArray : public FloatArray
{
public:
    /* Constructor */
    FrontArray(int);
    /* Destructor */
    ~FrontArray();
    /* addFloat() Function that overrides the addFloat Function in the FloatArray class */
    void addFloat(float);
};


/* Parameterized Constructor:
 * - Executed when an instance is created with an integer as a parameter.
 * - Doesn't return any value:
 * What it does:
 * - Calls the base class' constructor with the entered integer as a parameter.
 */
FrontArray::FrontArray(int SizeOfArray): FloatArray(SizeOfArray)
{
}

/* Destructor:
 * - Doesn't take any value.
 * - Doesn't return any value.
 */
FrontArray::~FrontArray()
{
}

/* Void addFloat():
 * - Overridden function of the base class.
 * - Takes a float as a parameter.
 * - Puts the entered float in its correct position (inverses the array).
 * - Doesn't return any value.
 */
void FrontArray::addFloat(float number)
{
    int index = 0;
    for (int i = 0; i < sizeOfArray; i++)
    {
        if(array[i] == 0)
        {
            index = index + 1;
        }
    }
    array[index - 1] = number;
}


/* Class PositiveArray That inherits from the class SortedArray */
class PositiveArray : public  SortedArray
{
public:
    /* Constructor */
    PositiveArray(int);
    /* Destructor */
    ~PositiveArray();
    /* addFloat() Function that overrides the addFloat Function in the base class */
    void addFloat(float);
};

/* Parameterized Constructor:
 * - Executed when an instance is created with an integer as a parameter.
 * - Doesn't return any value:
 * What it does:
 * - Calls the base class' constructor with the entered integer as a parameter.
 */
PositiveArray::PositiveArray(int SizeOfArray) : SortedArray(SizeOfArray)
{
}

/* Destructor:
 * - Doesn't take any value.
 * - Doesn't return any value.
 */
PositiveArray:: ~PositiveArray()
{
}

/* Void addFloat():
 * - Overridden function of the base class.
 * - Takes a float as a parameter.
 * - Checks if the parameter is positive then calls the function addFloat() of SortedArray.
 * - If the parameter is negative, it decreases the sizeOfArray by 1, to print correct output.
 * - Doesn't return any value.
 */
void PositiveArray::addFloat(float number)
{
    if(number > 0)
    {
        SortedArray::addFloat(number);
    }
    else
    {
        sizeOfArray = sizeOfArray -1;
    }

}


/* Class NegativeArray That inherits from the class SortedArray */
class NegativeArray : public  SortedArray
{
public:
    /* Constructor */
    NegativeArray(int);
    /* Destructor */
    ~NegativeArray();
    /* addFloat() Function that overrides the addFloat Function in the base class */
    void addFloat(float);
};

/* Parameterized Constructor:
 * - Executed when an instance is created with an integer as a parameter.
 * - Doesn't return any value:
 * What it does:
 * - Calls the base class' constructor with the entered integer as a parameter.
 */
NegativeArray::NegativeArray(int SizeOfArray) : SortedArray(SizeOfArray)
{
}

/* Destructor:
 * - Doesn't take any value.
 * - Doesn't return any value.
 */
NegativeArray:: ~NegativeArray()
{
}

/* Void addFloat():
 * - Overridden function of the base class.
 * - Takes a float as a parameter.
 * - Checks if the parameter is negative then calls the function addFloat() of SortedArray.
 * - If the parameter is positive, it decreases the sizeOfArray by 1, to print correct output.
 * - Doesn't return any value.
 */
void NegativeArray::addFloat(float number)
{
    if(number < 0)
    {
        SortedArray::addFloat(number);
    }
    else
    {
        sizeOfArray = sizeOfArray -1;
    }
}



int main()
{
    // Declaring 2 strings to hold the names of the .txt files for input and output.
    string inputFileName = " ", outputFileName = " ";

    // Declaring an array of pointers of size 10 and type FloatArray to achieve polymorphism.
    FloatArray* floatArray [10];

    cout << "Enter the name of the input file: ";
    cin >> inputFileName;

    // Creating an ifstream object for input and opening the .txt file.
    ifstream inputFile;
    inputFile.open(inputFileName.c_str(), ios::in);

    // While loop to check for errors opening the file.
    while(!inputFile)
    {
        inputFile.clear();
        cout << "Please enter a valid file name for input." << endl;

        cout << "Enter the name of the input file: ";
        cin >> inputFileName;

        inputFile.open(inputFileName.c_str(), ios::in);
    }


    string typeOfClass;
    int sizeOfArray;

    cout <<  "Enter the name of the output file: ";
    cin >> outputFileName;

    // Creating an Ofstream object for input and opening the .txt file.
    ofstream outputFile;
    outputFile.open(outputFileName.c_str(), ios::out);

    // Taking the type of class and the size of the array from the opened file.
    inputFile >> typeOfClass;
    inputFile >> sizeOfArray;

    /*
     * - For loop with 10 iterations for the 10 rows in the text file.
     * - Contains if else cases for each type of the classes.
     */
    for (int i = 0; i < 10; i++)
    {
        if(typeOfClass == "Sorted")
        {
            // Dynamically allocating Memory for the floatArray* [i], with the type being SortedArray.
            floatArray [i] = new SortedArray(sizeOfArray);

            // For loop to take input based on the size of the array written in the .txt file.
            for (int j = 0; j < sizeOfArray; j++)
            {
                inputFile >> floatArray[i];
            }

            // Printing the output in the opened .txt file.
            outputFile << *floatArray[i];

        }

        else if(typeOfClass == "Front")
        {
            // Dynamically allocating Memory for the floatArray* [i], with the type being FrontArray.
            floatArray[i] = new FrontArray(sizeOfArray);

            // For loop to take input based on the size of the array written in the .txt file.
            for (int j = 0; j < sizeOfArray ; j++)
            {
                inputFile >> floatArray[i];
            }

            // Printing the output in the opened .txt file.
            outputFile << *floatArray[i];

        }

        else if(typeOfClass == "Positive")
        {
            // Dynamically allocating Memory for the floatArray* [i], with the type being PositiveArray.
            floatArray[i] = new PositiveArray(sizeOfArray);

            // For loop to take input based on the size of the array written in the .txt file.
            for (int j = 0; j < sizeOfArray; j++)
            {
                inputFile >> floatArray[i];
            }

            // Printing the output in the opened .txt file.
            outputFile << *floatArray[i];
        }

        else if(typeOfClass == "Negative")
        {
            // Dynamically allocating Memory for the floatArray* [i], with the type being NegativeArray.
            floatArray[i] = new NegativeArray(sizeOfArray);

            // For loop to take input based on the size of the array written in the .txt file.
            for (int j = 0; j < sizeOfArray ; j++)
            {
                inputFile >> floatArray[i];
            }

            // Printing the output in the opened .txt file.
            outputFile << *floatArray[i];
        }

        else if(typeOfClass=="Array")
        {
            // Dynamically allocating Memory for the floatArray* [i], with the type being FloatArray.
            floatArray[i] = new FloatArray(sizeOfArray);

            // For loop to take input based on the size of the array written in the .txt file.
            for (int j = 0; j < sizeOfArray ; j++)
            {
                inputFile >> floatArray[i];
            }

            // Printing the output in the opened .txt file.
            outputFile << *floatArray[i];
        }

        /* Setting the index to 0 by calling the static function setIndex().
         * The program sets the index to 0 to avoid logical errors from selecting the wrong index.
         */
        FloatArray::setIndex(0);

        // Taking input again from the file before the loop ends.
        inputFile >> typeOfClass;
        inputFile >> sizeOfArray;
    }


    // For loop that iterates on the floatArray and deletes the elements to free the dynamic memory.
    for (int i = 0; i < 10; i++)
    {
        delete floatArray[i];
    }

    // Closing the input file.
    inputFile.close();
    // Closing the output file.
    outputFile.close();
    return 0;
}