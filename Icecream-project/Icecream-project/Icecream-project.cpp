#include <iostream>
using namespace std;

struct PRODUCT {
    string brand;
    float price;
    int quantity;
    int expDate;
};

void createOrder();
void showAvailProd();
void clExProd();
void deleteProduct();

bool showMenu() {
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
        createOrder();
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

void createOrder() {

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
    
    while(showMenu());
}
