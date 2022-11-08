// Youssef Mohamed Emam Ahmed
// Youssef Yasser Abo ElNaga

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void reservation(char **arr, int rows, int columns); // Prototype of the first function.
void recommendation(char **arr, int rows, int columns); // Prototype of the second function.
void CancelReservation(char **arr, int rows, int columns); // Prototype of the third function .
void ClearReservations(char **arr, int rows, int columns); // prototype of fourth function.
void statistics(char **arr, int rows, int columns);// prototype of fifth function.


int main() {
    int rows, columns;
    int var = 65; // Using ascii to print the letters.
    char choice;
    int FinalChoice;


    cout << "Please enter the number of rows: ";
    cin >> rows;
    cin.clear(); // Clearing buffer to avoid errors.
    cin.ignore(1000, '\n');

    cout << "Please enter the number of columns: ";
    cin >> columns;
    cin.clear();// Clearing buffer to avoid errors.
    cin.ignore(1000, '\n');

    // Checking if the columns entered is a correct value.
    while (columns > 25 || columns < 0)
    {
        cout << "Please input a correct value." << endl;
        cin >> columns;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Declaring 2d dynamic array.
    char **hall = new char *[rows];

    for (int i = 0; i < rows; ++i)
    {
        hall[i] = new char[columns];
    }

    // Resetting array elements to dashes.
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            hall[i][j] = '-';
        }
    }

    // Do while loop too keep the program running.
    do {
        var = 65; // Setting var to 65 so when converted to char, it prints the alphabet.

        cout << setw(columns + 4) << "Screen" << endl;
        cout << "       ";

        // To print letters on top of array.
        for (int i = 0; i < columns; i++)
        {
            cout << (char) var;
            var++;
        }
        cout << endl;

        //To print the array.
        // Outer for loop for rows.
        for (int k = 0; k < rows; k++)
        {
            if (k >= 9)
            {
                cout << "Row " << k + 1 << " ";
            }
            else
            {
                cout << " " << "Row " << k + 1 << " ";
            }

            // inner for loop for columns.
            for (int i = 0; i < columns; i++)
            {
                cout << hall[k][i];
            }
            cout << endl;
        }

        // Printing the menu.
        cout << "\na- Reserve a number of seats."<< endl;
        cout << "b- Get seats recommendation." << endl;
        cout << "c- Cancel a number of seat reservations."<< endl;
        cout << "d- Clear all reservations." << endl;
        cout << "e- Display statistics about the current reservations." << endl;
        cout << "f- Exit" << endl;


        cout << "Enter The required process: ";
        cin >> choice;

        // Converting the choice that was entered to a number starting from 1.
        FinalChoice = static_cast <int> (choice) -96;


        // Switch statement to call the appropriate function.
        switch (FinalChoice)
        {
            case 1:
            {
                reservation(hall, rows, columns);
                break;
            }
            case 2:
            {
                recommendation(hall, rows, columns);
                break;
            }
            case 3:
            {
                CancelReservation(hall, rows, columns);
                break;
            }
            case 4:
            {
                ClearReservations(hall,rows,columns);
                break;
            }
            case 5:
            {
                statistics(hall,rows,columns);
                break;
            }
            case 6:
            {
                continue;
            }
            default:
            {
                cout << "Please enter a correct value" << endl;
                break;
            }

        }

    }while(FinalChoice != 6 ); // Condition to keep the loop running unless the user entered 'f';

    // loop to delete the dynamic array.
    for (int i = 0; i < rows ; i++)
    {
        delete [] hall [i];

    }
    delete [] hall;

    return 0;
}
// First function to reserve seats.
void reservation(char **arr, int rows, int columns)
{

    int NumberOfseats;
    int column;
    int row;
    char alphabet;
    cout << "Please enter number of seats: "; //Asking user to enter the number of required seats
    cin >> NumberOfseats;
    int o, p;
    o = rows;
    p = columns;


    for (int i = 0; i < NumberOfseats;i++) // For loop to take the information of each seat
    {
        cout << "Please enter the number of seat number " << i + 1 <<" : " ;
        cin >> row;
        cin >> alphabet;
        alphabet = toupper(alphabet);
        column = static_cast<int> (alphabet); //changing the alphabet into number of column using Ascii
        column = column -64; // Subtracting 64 from ascii number to get the column number
        while (row > o)// checking if the number of tow is invalid
        {
            cout << "Sorry this seat is invalid." << endl;
            cout << "Please enter the number of seat number " << i + 1 <<" : " ;
            cin >> row;
            cin >> alphabet;
            column = static_cast<int> (alphabet);
            column = column -64;
        }
        while (column > p)// checking if the number of column is invalid
        {
            cout << "Sorry this seat is invalid." << endl;
            cout << "Please enter the number of seat number " << i + 1 <<" : " ;
            cin >> row;
            cin >> alphabet;
            alphabet = toupper(alphabet);

            column = static_cast<int> (alphabet);
            column = column -64;
        }
        while  (arr[row-1][column-1] == '$') // checking if the seat is already booked or not
        {
            cout << "Sorry this seat is already booked." << endl;
            cout << "Please enter the number of seat number " << i + 1 <<" : " ;
            cin >> row;
            cin >> alphabet;
            alphabet = toupper(alphabet);

            column = static_cast<int> (alphabet);
            column = column -64;
        }
        arr[row-1][column-1] = '$'; // Reserve the seat for the user
    }
}
// Second Function to recommend seats.
void recommendation(char **arr, int rows, int columns)
{
    int RequiredSeats,AvailableSeats, j =0;
    int i = 0;
    char line='-',StartPosition ,EndPosition;
    cout << "Please enter number of seats: ";
    cin>> RequiredSeats;
    for(;i < rows;i++)
    {
        for (; j < columns; j++)
        {
            StartPosition = j + 'A';
            while (j < columns && arr[i][j]==line)
            {
                j += 1;
                AvailableSeats += 1;
            }
            EndPosition = j + 'A' - 1;

        }
        if (AvailableSeats >= RequiredSeats)
        {

            cout << "Any " << RequiredSeats << " Seats from " << i+1 << StartPosition << " to " << i + 1<< EndPosition << endl;
            break;
        }
        AvailableSeats = 0;


    }

}
// Third function to cancel reservation.
void CancelReservation(char **arr, int rows, int columns)
{
    int NumberOfseats;
    int column;
    int row;
    char alphabet;
    cout << "Please enter number of seats: ";//Asking user to enter the number of required seats to cancel reservation
    cin >> NumberOfseats;
    int o, p;
    o = rows;
    p = columns;


    for (int i = 0; i < NumberOfseats;i++)// For loop to take the information of each seat
    {
        cout << "Please enter the number of seat number " << i + 1 <<" : " ;
        cin >> row;
        cin >> alphabet;
        alphabet = toupper(alphabet);

        column = static_cast<int> (alphabet);//changing the alphabet into number of column using Ascii
        column = column -64;// Subtracting 64 from ascii number to get the column number
        while (row > o)// checking if the number of tow is invalid
        {
            cout << "Sorry this seat is invalid." << endl;
            cout << "Please enter the number of seat number " << i + 1 <<" : " ;
            cin >> row;
            cin >> alphabet;
            column = static_cast<int> (alphabet);
            column = column -64;
        }
        while (column > p)// checking if the number of column is invalid
        {
            cout << "Sorry this seat is invalid." << endl;
            cout << "Please enter the number of seat number " << i + 1 <<" : " ;
            cin >> row;
            cin >> alphabet;
            alphabet = toupper(alphabet);

            column = static_cast<int> (alphabet);
            column = column -64;
        }
        while  (arr[row-1][column-1] == '-') // checking if the seat is already booked or not
        {
            cout << "Sorry this seat is not booked." << endl;
            cout << "Please enter the number of seat number " << i + 1 <<" : " ;
            cin >> row;
            cin >> alphabet;
            alphabet = toupper(alphabet);

            column = static_cast<int> (alphabet);
            column = column -64;
        }
        arr[row-1][column-1] = '-'; // Cancelling the reservation of the seat
    }
}
// Fourth function to clear all reservation.
void ClearReservations(char **arr, int rows, int columns)
{
    // Resetting array elements to dashes.
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            arr[i][j] = '-';
        }
    }
}
// Fifth function to display statistics.
void statistics(char **arr, int rows, int columns)
{
    // Variables used for the function to hold different values.
    float occupied = 0, seats = 0;
    float occupancy , RowOccupancy;

    for (int i = 0; i < rows; ++i)// Outer loop to iterate on the rows.
    {
        for (int j = 0; j < columns; ++j)// Inner loop to iterate on the columns.
        {
            // If statement to check if the seat is booked.
            if (arr [i][j] == '$')
            {
                occupied = occupied + 1;
            }
            seats = seats + 1; // To calculate the number of total seats.
        }
    }

    occupancy = (occupied/seats) * 100; // Getting percentage of the occupied seats.
    cout << "Percentage of occupancy of the cinema = " << occupancy << "%" << endl;

    for (int i = 0; i < rows; ++i)// Outer loop to iterate on the rows.
    {
        // Resetting values to 0 to make the calculations on the row only
        occupied = 0, seats = 0;

        for (int j = 0; j < columns; ++j)// Inner loop to iterate on the columns.
        {
            // If statement to check if the seat is booked.
            if (arr [i][j] == '$')
            {
                occupied = occupied + 1;
            }
            seats = seats + 1;
        }
        RowOccupancy = (occupied / seats)*100; // Calculating the percentage of occupied seats each row.
        cout << "Occupancy of row " << i+1 << " = " << RowOccupancy << "%" <<endl;
    }
}
