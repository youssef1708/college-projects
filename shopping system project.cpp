//Authors:
		//youssef yasser aboel-naga   
		//omar ahmed badr  



#include <iostream>
#include <string>

using namespace std;

class Item
{
private:
    static int ID; // static id to save last value of id
    int quantity;
    int ID1;
    double price;
    string name;
public:
    Item();
    Item(int,double ,string );
    Item(const Item&);
    void setquantity(int);
    void setprice(double);
    void  setname(string);
    int getID();
    int getquantity();
    double getprice();
    string  getname();
    bool operator==(const Item&);
    void operator+=(const Item&);
    void operator-=( int );
    friend istream& operator>>(istream& os, Item& obj);
    friend ostream& operator<<(ostream& is, const Item& obj);

};

istream& operator>>(istream& is, Item& obj){ //overloading operator to assign item information
    cout<<"Enter the name:";
    is.ignore();
    getline(is, obj.name);
    cout<<"Enter the quantity:";
    is >>obj.quantity;
    cout<<"Enter the price:";
    is >>obj.price;


}
ostream& operator<<(ostream& os, const Item& obj){ // overloading operator to print item information
    os << endl;
    os << "item name: "<< obj.name <<endl;
    os << "item quantity: "<<obj.quantity<<endl;
    os << "item price: "<<obj.price<<endl;
    os << "item id: "<<obj.ID1<<endl;

    return os;


}

int Item::ID = 0; // set ID by zero to start increasing each time the constructor is called

class Seller
{
private:
    string Seller_name;
    string Seller_email;
    Item* Items;
    int maxItems;
    Item ItemInfo;
public:
    Seller(int,string,string);
    friend ostream& operator<<(ostream& output,const Seller&);
    string getSellerName(){ return Seller_name; };
    string getSellerEmail(){ return Seller_email; };
    bool addItem(Item);
    bool sellItem(string,int);
    bool printItems();
    Item findById(int);
    ~Seller(){ delete [] Items; };
    friend class Item;
};


Item::Item()
{
    ID++; // increasing id by one
    ID1=ID; // saving id value in ID1 to call it
    quantity = 0;
    price = 0.0;
    name = "none";
}

Item::Item(int quantity,double price, string name){
    this-> quantity=quantity;
    this-> price = price;
    this-> name = name;
}

Item::Item(const Item &obj) {   //copy constructor
    ID = obj.ID;
    ID1 = obj.ID1;
    quantity = obj.quantity;
    price = obj.price;
    name = obj.name;
}

void Item::setname(string name ) {
    this->name=name;
}

void Item::setprice(double price) {
    this->price=price;
}

void Item::setquantity(int quantity) {
    this->quantity=quantity;
}

int Item::getID() {
    return ID1;   // calling item id
}

int Item::getquantity() {
    return quantity;
}

double Item::getprice() {
    return price;
}

string Item::getname() {
    return name;
}

bool Item::operator==(const Item &SellerItem) {
    if(name==SellerItem.name)         // check if the name of item is equal to entered name
    {
        return true;
    }
    else{
        return false;
    }
}

void Item::operator+=(const Item &Item) {
    this->quantity = quantity+Item.quantity;  // increasing quantity by the entered quantity
}

void Item::operator-=(const int p) {
    this->quantity = quantity-p ;      // decreasing item by the int of quantity entered
}



ostream& operator<<(ostream& os, const Seller& obj){  // overloading operator to print seller information
    os << endl;
    os << "Seller name: "<< obj.Seller_name <<endl;
    os << "Seller Email: "<<obj.Seller_email <<endl;
    return os;
}

Seller::Seller(int maxItems ,string Seller_name,string Seller_email)
{
    this->maxItems=maxItems;
    this-> Seller_name=Seller_name;
    this->Seller_email=Seller_email;
    Items = new Item[maxItems]; // making dynamic array
}

bool Seller::addItem(Item Item1)
{
    string item_name;
    cout<< "please enter item name: ";
    cin>>item_name;
    Item1.setname(item_name); // using setters to set item information
    int item_quantity;
    cout<< "please enter item quantity: ";
    cin>> item_quantity;
    Item1.setquantity(item_quantity);
    double item_price;
    cout<< "please enter item price: ";
    cin>> item_price;
    Item1.setprice(item_price);
    int x=0;
    for(int i=0; i <= maxItems;i++)
    {
        if( Items[i].getname()==item_name) // checking if the item is already exist or not
        {
            Items[i]+=Item1;   // increasing item quantity if its already exist
            cout<<"item is already exist only quantity is added "<< endl;
            cout<<"-----------------------------------------------------"<<endl;
            x=1;
        }
    }
    if(x!=1)
    {
        for (int (i) = 0; (i) < maxItems; ++(i)) {
            if(Items[i].getname()=="none")//checkin empty place in the array
            {
                Items[i].setname(item_name); // assign item information in the first empty place in the array
                Items[i].setquantity(item_quantity);
                Items[i].setprice(item_price);
                cout<<"new item is added"<< endl;
                cout<<"-----------------------------------------------------"<<endl;
                break;
            }
        }
    }
}

bool Seller::sellItem(string item_name, int item_quantity) {
    string item_name1;
    cout<<"please enter name of item: ";
    cin >> item_name1;
    int x = 0; // declaring integer to save number if the name is found
    item_name = item_name1;
    for (int i = 0; i < maxItems; ++i) {
        if(Items[i].getname()==item_name) // check if the entered name item is exist or not
        {
            cout<<"please enter name of quantity: ";
            cin>> item_quantity; // if item is exist the taking quantity from user
            x=1;
            if(item_quantity<=Items[i].getquantity())  // check  the availability of the requested quantity
            {
                Items[i]-=item_quantity; // if the requested quantity is available then decrease the quantity by the requested number of items
                cout<<"operation successfully done "<<endl;
                cout<<"-----------------------------------------------------"<<endl;
                break;
            }
            else
            {
                cout<< "sorry,there is only  "<<Items[i].getquantity() <<" "<<"left"<<endl;
                cout<<"-----------------------------------------------------"<<endl;// if the requested quantity is more than the available
                break;
            }
        }

    }
    if(x!=1) // checking if the entered name is found or not
    {
        cout<< "item name not found , please try again "<< endl;
        cout<<"-----------------------------------------------------"<<endl;
    }

}

bool Seller::printItems() {
    for (int i = 0; i < maxItems; ++i) {
        if(Items[i].getname()!="none") {  // if condition to find the assigned places in the dynamic array only (not empty)
            cout << "item  " << i + 1 << " " << endl;
            cout << "name: ";
            cout << Items[i].getname() << endl; //calling item information
            cout << "quantity:  ";
            cout << Items[i].getquantity() << endl;
            cout << "price: ";
            cout << Items[i].getprice() << endl;
            cout << "ID:  ";
            cout << Items[i].getID()-2 << endl;
            cout<<"-----------------------------------------------------"<<endl;
        }
    }

}

Item Seller::findById(int item_id) {
    cout << "please enter item ID: ";
    cin>>item_id;
    int x=0;
    for (int i = 0; i < maxItems; ++i) {
        if(Items[i].getID()==item_id+2)  //check each id in the array to print its inromation
        {
            x=1;                           // take 1 in x to prove that id id found
            cout << "name: ";
            cout<< Items[i].getname()<<endl;
            cout << "quantity:  ";
            cout<<Items[i].getquantity()<<endl;
            cout << "price: ";
            cout<<Items[i].getprice()<<endl;
            cout<<"-----------------------------------------------------"<<endl;
            break;
        }
    }
    if(x!=1)          // if x not equal to 1 this means that id entered not found
    {
        cout<<"invalid ID, please try again "<<endl;
        cout<<"-----------------------------------------------------"<<endl;
    }
}

int main()
{
    string name;
    int quantity,id;
    int selector;
    string choice;
    string seller_name;
    string seller_email;
    int MaxNumberOfItems;
    Item item1;
    cout<<"please enter seller name: ";
    cin>>seller_name;
    cout << "please enter seller email: ";
    cin>>seller_email;
    cout << "please enter number of maximum items: ";
    cin>>MaxNumberOfItems;
    Seller seller1(MaxNumberOfItems,seller_name,seller_email);
    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1- Print my Info " <<endl;
        cout << "2- Add an Item " << endl;
        cout << "3- Sell an Item " <<endl;
        cout << "4- Print Items " <<endl;
        cout << "5- Find an Item by ID "<<endl;
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
                cout<<"Name: ";
                cout<<seller1.getSellerName() <<endl;
                cout << "Email: ";
                cout<<seller1.getSellerEmail()<<endl;
                cout << "Maximum items: ";
                cout << MaxNumberOfItems<<endl;
                cout<<"-----------------------------------------------------"<<endl;
                continue;
            }
            case 2: {
                seller1.addItem(item1 );
                continue;
            }
            case 3: {
                seller1.sellItem(name,quantity);
                continue;
            }
            case 4: {
                seller1.printItems();
                continue;
            }
            case 5: {
                seller1.findById(id);
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
}