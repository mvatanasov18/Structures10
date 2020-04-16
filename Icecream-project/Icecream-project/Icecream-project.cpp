#include <iostream>
using namespace std;

struct PERSON {
    string firstName="";
    string lastName="";
    int years=0;
};

struct PRODUCT {
    string brand="";
    string flavour="";
    float price=0;
    int quantity=0;
    int expDate=0;
    PERSON person;
};

void createOrder(PRODUCT* product, int& productCount);
void showAvailProd();
void clExProd();
void deleteProduct();

bool showMenu(PRODUCT* product,int& productCount) {
    int userInput;
    cout << "\nWelcome to our programme about icecream: " << endl;
    cout << "1. Create a new order" << endl;
    cout << "2. Show the entered stuff" << endl;
    cout << "3. Clear expired products" << endl;
    cout << "4. Buy product" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter option from the menu by typing a number: ";
    cin >> userInput;
    switch (userInput)
    {
    case 1:
        createOrder(PRODUCT * product, int& productCount);
        break;
    case 2:
        showAvailProd();
        break;
    case 3:
        clExProd();
        break;
    case 4:
        deleteProduct();
        break;
    case 5: return false;
    }
    return true;
}

void createOrder(PRODUCT* product, int& productCount) {
    cout << "Enter brand: ";
    cin >> product[productCount].brand;

    cout << "Enter flavour: ";
    cin >> product[productCount].flavour;

    cout << "Enter price: ";
    cin >> product[productCount].price;

    cout << "Enter quantity: ";
    cin >> product[productCount].quantity;

    cout << "Enter expDate: ";
    cin >> product[productCount].expDate;

    cout << "Enter your firstname: ";
    cin >> product[productCount].person.firstName;

    cout << "Enter your lastname: ";
    cin >> product[productCount].person.lastName;

    cout << "Enter your years: ";
    cin >> product[productCount].person.years;

}

void showAvailProd() {

}

void clExProd() {

}

void deleteProduct() {

}

int main()
{
    PRODUCT product[100];
    int productCount = 0;
    while(showMenu(product, productCount));
}
