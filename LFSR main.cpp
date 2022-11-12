// Name: youssef yasser abo el_naga   ,  ID: 20205003  , group: NCS2
// Name: Ahmed Mohamed Mokhtar        ,  ID:20205001   , group: NCS2
//subject: cryptography assignment 1
#include <iostream>
#include <string>
#include<stdio.h>
#include<string.h>
#include <sstream>
#include <cstring>
using namespace std;



int main()
{
    //taking inputs from the user

    int sizeOfVector =0;
    int sizeOfBinary =0;
    cout<< "please enter the size of your binary text: ";
    cin>> sizeOfBinary;
    int Xi[sizeOfBinary];                                           //xi is the binary text
    cout<<"please enter the binary plain text(number by number): ";
    for (int z = 0; z < sizeOfBinary; z++)                         //for loop to get array of binary numbers
    {
        cin >> Xi[z];
    }
    cout<<"please enter the size of vector: ";                    // taking size of vectors to determine no. of flipflops
    cin>> sizeOfVector;
    int vector1[sizeOfVector];
    cout<<"please enter the Initial Vector(number by number): ";
    for (int i = 0; i < sizeOfVector; i++) {
        cin >> vector1[i];
    }



    cout<< "please continue your Polynomial of LFSR as following(in capital letter plaese): ";
    cout<< "X"<< sizeOfVector<< "+";          // give the user first part of the equation depends on the entered value of size of vectors
    string pol;
    cin>>pol;
    cout<<"here is your full Polynomial equation: "<<"X"<< sizeOfVector<< "+"<< pol<<endl;
    int sizeOfPoly= pol.size();               // using built in function to determine the size of entered string
    int cArray[sizeOfVector];
    for (int i = 0; i < sizeOfVector; ++i)
    {
        cArray[i]=0;

    }
    for (int i = 0; i < sizeOfPoly; ++i)
    {
        if (pol[i] == 'X')                    //check the first char must be X to make sure that the equation entered is polynomial
        {
            string x;
            x = pol[i+1];                    // the next number to X is the power of the next X so  saving  it in new string alone
            int y = stoi(x);                 // using built in function to change number in string to integer
            cArray[y] = 1;                   // changing the value of this index in the coefficient array
            i++;
            continue;
        }
        else if(pol[i]== '1')             //if condition to detect '1' which is X to the power of zero
        {
            string x;
            x = pol[i];
            int y = stoi(x);
            cArray[y-1] = 1;
        }



    }

    int clock = 0;
    clock = sizeOfBinary;
    int outputArray[clock];
    for (int i = 0; i < clock; i++)
    {
        outputArray[i]=0;

    }
    cout<<"clock-vector table: "<<endl;
    cout<<"C<--"<<endl;


    for (int m = 0; m < clock; m++)
    {
        cout<<m;

        int x=0;
        for (int i = 0; i < sizeOfVector; i++)
        {

            if (cArray[i]==1)            //searching for the first XOR coefficient
            {

                for (int j = i+1; j <sizeOfVector ; j++)  //for loop on the rest of the vectors to find the other XOR operation coefficient
                {
                    if(cArray[j]==1)         // finding the next coefficient
                    {     // XOR table //
                        if (vector1[i]==0 && vector1[j]==0)
                        {
                            x=0;
                        }
                        else if (vector1[i]==1 && vector1[j]==0 )
                        {
                            x=1;


                        }
                        else if (vector1[i]==0 && vector1[j]==1 )
                        {
                            x=1;

                        }
                        else if (vector1[i]==1 && vector1[j]==1 )
                        {
                            x=0;
                        }
                        i++; // increment on i also to prevent starting from beginning in the next loop
                        for (int k = j+1; k <sizeOfVector ; k++) // for loop to check if there is more than two coefficient for the XOR operation
                        {
                            if (cArray[k]==1)
                            {
                                if (x==0 && vector1[k]==0)
                                {
                                    x=0;
                                }
                                else if (x==1 && vector1[k]==0 )
                                {
                                    x=1;

                                }
                                else if (x==0 && vector1[k]==1 )
                                {
                                    x=1;

                                }
                                else if (x==1 && vector1[k]==1 )
                                {
                                    x=0;
                                }
                                i++;
                                j++;

                            }

                        }


                        outputArray[m]=vector1[0];                      //shifting S0 to the output array
                        for (int p = 0; p < sizeOfVector; p++)          // for loop to shift  elements in vector array
                        {
                            vector1[p]=vector1[p+1];
                            if (p==sizeOfVector-1)                     // giving the output of the XOR to the last element in the vectors array
                            {
                                vector1[p]=x;

                            }
                            
                        }



                    }


                }
            }

        }
        for (int k = 0; k < sizeOfVector; k++)              //printing clock-shift table
        {
            cout<<vector1[k];

        }
        cout<<endl;

    }
    cout<<"key stream: ";
    for (int i = 0; i < clock; i++)                  //printing key stream(each x resulted in each array
    {
        cout<<outputArray[i];

    }
    cout<<endl;
    int cipherText[sizeOfBinary];
    for (int i = 0; i < sizeOfBinary; i++)          //for loop to solve the XORbetween binary text and key and give the ciphertext result
    {
        if (outputArray[i]==0 && Xi[i]==0)
        {
            cipherText[i]=0;
        }
        else if (outputArray[i]==0 && Xi[i]==1)
        {
            cipherText[i]=1;
        }
        else if (outputArray[i]==1 && Xi[i]==0)
        {
            cipherText[i]=1;
        }
        else if (outputArray[i]==1 && Xi[i]==1)
        {
            cipherText[i]=0;
        }

    }
    cout<<"ciphertext: ";
    for (int i = 0; i < sizeOfBinary; i++)             //for loop to print ciphertext
    {
        cout<<cipherText[i];

    }
    cout<<endl;











    return 0;
}
