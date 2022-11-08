/*
 * Youssef Magdi,
 * Youssef Yasser, 
 */
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class MyPhoneBook
{
private:
    string* names;
    string* phones;
    int phoneBookSize;
    int* ZeroOneArray; //Returns an array of zeros and ones to be used in displayAtIndices
    static int entryCount; //static variable to show the number of phonebook entries when required
    static bool is_digits(const string &);

public:
    MyPhoneBook(int); //Takes size
    MyPhoneBook(const MyPhoneBook&); //Copy Constructor
    bool addEntry(string, string);
    bool displayEntryAtIndex(int);
    void displayEntryAtIndices(int*);
    void displayAll();
    int* findByName(string );
    int* findByPhone(string);
    bool updateNameAt(string, int);
    bool updatePhoneAt(string, int);
    ~MyPhoneBook();
};

int MyPhoneBook::entryCount = 0; //Initialization of static counter to zero

MyPhoneBook::MyPhoneBook(int phoneBookSize) {   //Constructor
    this->phoneBookSize = phoneBookSize;        //Allocating phonebook size to pointer
    names = new string[phoneBookSize];          //Allocating names array size dynamically
    phones = new string[phoneBookSize];         //Allocating phones array size dynamically
    ZeroOneArray = new int[phoneBookSize];      //Allocating the array of zeros and ones dynamically
    for (int i = 1 ; i <= phoneBookSize; i++) { //Loop to help the user enter a new entry
        entryCount++;
        addEntry(names[i-1], phones[i-1]);      //Calling the addEntry function everytime data has to be input
    }
}

MyPhoneBook::MyPhoneBook(const MyPhoneBook &obj) { //Copy constructor
    phoneBookSize =obj.phoneBookSize;              //Creation of new object of the same class
    names = new string[phoneBookSize];
    phones = new string[phoneBookSize];
    ZeroOneArray = new int[phoneBookSize];
    for (int i = 0; i < phoneBookSize; i++) {      //Copying the values to the new object
        names[i] = obj.names[i];
        phones[i] = obj.phones[i];
    }
}
bool MyPhoneBook::is_digits(const string &str)   //Function used to check if a string contains digits only
{
    return str.find_first_not_of("0123456789") == string::npos;
}

bool MyPhoneBook::addEntry(string n, string p) {
    if((n.empty()) && (p.empty()) ) {                  // checking if this place in the array is empty or not
        cout << "Enter name " << entryCount << ": ";
        cin.ignore();
        getline(cin, n);                         // taking name from the user
        while ((n.length() < 1) || (is_digits(n))) {          // checking if the name entered is only alphabet and the string entered is not empty
            cout << "A valid name has to be input. Please re-enter: ";
            cin.ignore();
            getline(cin, n);
        }
        names[entryCount-1] = n;

        cout << "Enter phone " << entryCount << ": ";
        cin >> p;
        phones[entryCount-1] = p;

        while ((phones[entryCount-1].size() != 11) || (!is_digits(phones[entryCount-1]))) {  // checking if the phone number entered is 11 number and only digits
            cout << "Incorrect phone number format, please re-enter an 11-digit number." << endl;
            cout << "Enter phone " << entryCount << ": ";
            cin >> phones[entryCount - 1];
        }
        return true;
    }
    else
        return false;
}


bool MyPhoneBook::displayEntryAtIndex(int index)
{
    cout << "Please enter the index number: ";
    cin >> index;                                         // taking index from the user
    while ((index>=phoneBookSize) || (index < 0))                          // checking if the index is valid
    {
        cout << "Wrong index number, please try again."<< endl;
        cout<<  "Please enter the index number: ";
        cin >> index;
    }
    cout << "Name: "<< names[index]<< "       "<< "Phone number: "<< phones[index]<< endl;
    return true;
}

void MyPhoneBook::displayEntryAtIndices(int *ParameterArray) {
    cout << setw(5) << "Index" << setw(20) << "Name" << setw(16) << "Phone" << endl;
    cout << "-----------------------------------------" << endl;
    for (int j = 0; j < phoneBookSize; j++) {
        if (ParameterArray[j] == 1) {
            cout << setw(5) << j << setw(20) << names[j] << setw(16) << phones[j] << endl;
        }
    }
}

void MyPhoneBook::displayAll() {
    cout << setw(5) << "Index" << setw(20) << "Name" << setw(16) << "Phone" << endl;
    cout << "-----------------------------------------" << endl;
    for (int j = 0; j < phoneBookSize; j++) {                  // calling all phonebook elements
        cout << setw(5) << j << setw(20) << names[j] << setw(16) << phones[j] << endl;
    }
}

int* MyPhoneBook::findByName(string Name)
{
    ZeroOneArray = new int[phoneBookSize];
    for (int i = 0; i < phoneBookSize; i++) {
        ZeroOneArray[i] = 0;
    }
    cout << "Please enter the name: " ;
    cin.ignore();
    getline(cin, Name);
    bool NameFound = false;
    for (int i = 0; i <phoneBookSize ; ++i)  // for loop to find the entered name and display its number
    {
        if (names[i].find(Name) != string::npos) {   // function to get the name if the entered name is only part from the names
            NameFound = true;
            ZeroOneArray[i] = 1;
        }
    }
    if (!NameFound) {        // if condition to give the user another chance to reenter the name if it was entered with incorrect way
        cout << "Name not found. You have another chance before returning to the main menu." << endl;
        cout <<"Please re-enter a name to search for: " ;
        cin.ignore();
        getline(cin, Name);
        for (int i = 0; i <phoneBookSize ; ++i)
        {
            if (names[i].find(Name) != string::npos) {
                ZeroOneArray[i] = 1;
            }
        }
    }
    return ZeroOneArray;
}


int* MyPhoneBook::findByPhone(string phoneNumber )
{
    ZeroOneArray = new int[phoneBookSize];
    for (int i = 0; i < phoneBookSize; i++) {
        ZeroOneArray[i] = 0;
    }
    cout <<"Please enter the number: " ;
    cin >> phoneNumber;
    bool NumFound = false;
    for (int i = 0; i <phoneBookSize ; ++i)              // for loop to find the entered phone number and display its name
    {
        if (phones[i].find(phoneNumber) != string::npos) {    // function to get the number if the entered name is only part from the phone number
            NumFound = true;
            ZeroOneArray[i] = 1;
        }
    }
    if (!NumFound) {           // if condition to give the user another chance to reenter the phone number if it was entered with incorrect way
        cout << "Number not found. You have another chance before returning to the main menu." << endl;
        cout <<"Please re-enter a number to search for: " ;
        cin >> phoneNumber;
        for (int i = 0; i <phoneBookSize ; ++i) {
            if (phones[i].find(phoneNumber) != string::npos) {
                ZeroOneArray[i] = 1;
            }
        }
    }
    return ZeroOneArray;
}





bool MyPhoneBook::updateNameAt(string UpdatedName, int Index){
    cout << "Please enter the index you want to update: ";
    cin >> Index;
    while(Index>=phoneBookSize)     // checking if the index is valid
    {
        cout << "Wrong index number please try again."<< endl;
        cout<<  "Please enter the index number: ";
        cin >> Index;
    }
    if (Index<phoneBookSize) {
        cout << "Your index name is: " << names[Index] << endl;
        cout << "Please enter the new name: ";
        cin.ignore();
        getline(cin, UpdatedName);
        names[Index] = UpdatedName;      // updating the name and display the new name .
        cout << "Name updated successfully " << endl;
        cout << "Name: " << names[Index] << "       " << "Phone number: " << phones[Index] << endl;
        return true;
    }
    else
        return false;
}


bool MyPhoneBook::updatePhoneAt(string UpdatedPhoneNumber, int Index)
{
    cout << "Please enter the index you want to update: ";
    cin >> Index;
    while (Index >= phoneBookSize) {                      // checking if the index is valid
        cout << "Wrong index number please try again" << endl;
        cout << "Please enter the index number: ";
        cin >> Index;
    }
    if (Index < phoneBookSize) {

        cout << "Your index phone is: " << phones[Index] << endl;
        cout << "Please enter the new phone: ";
        cin >> UpdatedPhoneNumber;
        while ((UpdatedPhoneNumber.size() != 11) || (!is_digits(UpdatedPhoneNumber))) {
            cout << "Incorrect phone number format, please re-enter an 11-digit number." << endl;
            cout << "Enter phone: ";
            cin >> UpdatedPhoneNumber;
        }
        phones[Index] = UpdatedPhoneNumber;          // updating phone number and display the new one .
        cout << "Phone number updated successfully." << endl;
        cout << names[Index] << "       " << phones[Index] << endl;
        return true;
    }
    else
        return false;
}


MyPhoneBook::~MyPhoneBook() {    // deconstructor to delete arrays and free the memory
    delete [] names;
    delete [] phones;
    delete [] ZeroOneArray;
}

int main() {
    int selector, BookSize;
    string Choice;
    cout << "Enter the size of your phone book: ";
    cin >> BookSize;
    while (BookSize <= 0) {                           // checking if the phonebook size entered is more than zero
        cout << "Invalid book size, please re-input: ";
        cin >> BookSize;
    }
    MyPhoneBook book(BookSize);
    string PhoneNumber;
    string Name;
    string UpdatedName,UpdatedNumber;
    int Index,Indexx, p;
    char IndexChoice;
    int IndicesNum;
    while (true) {
        cout << "Enter your choice:" << endl;
        cout << "1- Display all phone book" << endl;
        cout << "2- Search for entry/entries by name" << endl;
        cout << "3- Search for entry/entries by phone" << endl;
        cout << "4- Find an entry by index" << endl;
        cout << "5- Update name by index" << endl;
        cout << "6- Update phone by index" << endl;
        cout << "7- Copy phone book to another and display entries of the new phone book" << endl;
        cout << "8- Exit" << endl;
        cout << "Choice: ";
        cin >> Choice;
        while(cin.fail() || !(Choice.find_first_not_of("0123456789") == string::npos)) {  // checking that the entered choice is real digit
            cout << "Incorrect data type, please re-enter: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> Choice;
        }
        selector = stoi(Choice);
        while ((selector < 1) || (selector > 8) ||cin.fail() || !(Choice.find_first_not_of("0123456789") == string::npos)) {
            cout << "Invalid choice number, re-enter a valid one: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> Choice;
            selector = stoi(Choice);
        }
        switch (selector) {     // Switch to call functions
            case 1: {
                book.displayAll();
                cout << endl;
                continue;
            }
            case 2: {
                book.displayEntryAtIndices(book.findByName(Name));
                cout << endl;
                continue;
            }
            case 3: {
                book.displayEntryAtIndices(book.findByPhone(PhoneNumber));
                cout << endl;
                continue;
            }
            case 4: {
                cout << "a) Find by a single index. " << endl;
                cout << "b) Find by several indices. " << endl;
                cout << "Enter your choice: ";
                cin >> IndexChoice;
                IndexChoice = tolower(IndexChoice);
                if (IndexChoice == 'a') {
                    book.displayEntryAtIndex(p);
                }
                else if (IndexChoice == 'b') {
                    int* ParameterArray = new int[BookSize];
                    for (int i = 0; i < BookSize; i++) {
                        ParameterArray[i] = 0;
                    }
                    int TempIndex;
                    cout << "How many indices would you like to search for? ";
                    cin >> IndicesNum;
                    while ((IndicesNum <= 0) || (IndicesNum > BookSize)) {
                        cout << "This number of indices doesn't exist, please re-enter: ";
                        cin >> IndicesNum;
                    }
                    cout << "Enter the indices: " << endl;
                    for (int a = 1; a <= IndicesNum; a++) {
                        cout << a << ") ";
                        cin >> TempIndex;
                        while ((TempIndex < 0) || (TempIndex >= BookSize)) {
                            cout << "Index not present in range, please re-enter a valid one: ";
                            cin >> TempIndex;
                        }
                        ParameterArray[TempIndex] = 1;
                    }
                    book.displayEntryAtIndices(ParameterArray);
                }
                else {
                    cout << "Invalid choice. You have another chance before returning to the main menu." << endl;
                    cout << "a) Find by a single index. " << endl;
                    cout << "b) Find by several indices. " << endl;
                    cout << "Enter your choice: ";
                    cin >> IndexChoice;
                    if (IndexChoice == 'a') {
                        book.displayEntryAtIndex(p);
                    }
                    else if (IndexChoice == 'b') {
                        int* ParameterArray = new int[BookSize];
                        for (int i = 0; i < BookSize; i++) {
                            ParameterArray[i] = 0;
                        }
                        int TempIndex;
                        cout << "How many indices would you like to search for? ";
                        cin >> IndicesNum;
                        while ((IndicesNum <= 0) || (IndicesNum > BookSize)) {
                            cout << "This number of indices doesn't exist, please re-enter: ";
                            cin >> IndicesNum;
                        }
                        cout << "Enter the indices: " << endl;
                        for (int a = 1; a <= IndicesNum; a++) {
                            cout << a << ") ";
                            cin >> TempIndex;
                            while ((TempIndex < 0) || (TempIndex >= BookSize)) {
                                cout << "Index not present in range, please re-enter a valid one: ";
                                cin >> TempIndex;
                            }
                            ParameterArray[TempIndex] = 1;
                        }
                        book.displayEntryAtIndices(ParameterArray);
                    }
                }
                cout << endl;
                continue;
            }
            case 5: {
                book.updateNameAt(UpdatedName,Index);
                cout << endl;
                continue;
            }
            case 6: {
                book.updatePhoneAt(UpdatedNumber,Indexx);
                cout << endl;
                continue;
            }
            case 7: {
                MyPhoneBook newBook = book;
                cout << "Phonebook copied to a new one successfully." << endl;
                newBook.displayAll();
                cout << endl;
                continue;
            }
            case 8: {
                cout << "Thank you for using this program." << endl;
                cout << endl;
                exit(EXIT_SUCCESS);
            }
        }
    }
}