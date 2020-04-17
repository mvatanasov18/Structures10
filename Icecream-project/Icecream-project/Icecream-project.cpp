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
    int id;
};

void createOrder(PRODUCT* product, int& productCount);

void showAvailProd(PRODUCT* product, int& productCount);

void clearExpiredProducts();

void deleteProduct(PRODUCT* products, int& productCount, int id);

int findById(PRODUCT*, int&, int);

bool showMenu(PRODUCT* product,int& productCount, int &maxId) {
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
        createOrder(product, productCount);
        break;
    case 2:
        showAvailProd(product, productCount);
        break;
    case 3:
        clearExpiredProducts();
        break;
    case 4:
        deleteProduct(product, productCount, id);
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

void showAvailProd(PRODUCT* product, int& productCount) {
    cout << "The list of the entered products: " << endl;
    for (int i = 0; i < productCount; i++)
    {
        cout << product[i].brand << " " << product[i].flavour << " " << product[i].price << " " << product[i].quantity << " " << product[i].expDate << " " << product[i].person.firstName << " " << product[i].person.lastName << " " << product[i].person.years << endl;
    }
}

void clearExpiredProducts() {
    
}

void deleteProduct(PRODUCT *products, int &productCount, int id)
{
    int delPos;

    delPos=findById(products, productCount, id);

    for (int i = delPos; i < productCount-1; i++) {
        products[i]=products[i+1];
    }

    productCount--;
}

int findById(PRODUCT* products, int& productCount, int id)
{
    int lBound=0, rBound=productCount-1, mid=1, lastMid=0;

    while (mid != lastMid) {
        lastMid=mid;
        mid=(lBound+rBound)/2;

		if (id == products[mid].id) return mid;
        if (id < products[mid].id) rBound=mid-1;
        else lBound=mid+1;
    }

    return -1;
}

int main()
{
    PRODUCT product[100];
    int productCount = 0, maxId=1;
    while(showMenu(product, productCount, maxId));
}
