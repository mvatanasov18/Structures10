#include <iostream>
using namespace std;

struct PRODUCT {
    string flavour = "";
    string cone = "";
    float price = 0;
    int balls = 0;
    int id = 0;
};


void exampleProducts(PRODUCT* product, int& productCount, int& maxId);
void createOrder(PRODUCT* product, int& productCount, int& maxId, PRODUCT newProduct);
void showAllIceCreams(PRODUCT* product, int& productCount);
void deleteProduct(PRODUCT* products, int& productCount, int id);
int findById(PRODUCT*, int&, int);



bool showMenu(PRODUCT* product, int& productCount, int& maxId) {

    int userInput;
    cout << "\nWelcome to our programme about icecream: " << endl;
    cout << "1. See all ice creams" << endl;
    cout << "2. Create new order" << endl;
    cout << "3. Delete order" << endl;
    cout << "4. Update order" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter option from the menu by typing a number: ";
    cin >> userInput;
    switch (userInput)
    {
    case 1:
        showAllIceCreams(product, productCount);
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5: return false;
    }
    return true;
}

void exampleProducts(PRODUCT* product, int& productCount, int& maxId) {
    createOrder(product, productCount, maxId, { "strawberry","sugar cone",1.00,1,0 });
    createOrder(product, productCount, maxId, { "chocolate","waffle cone",1.10,2,1 });
    createOrder(product, productCount, maxId, { "vanilia","cup",2.10,4,2 });
    createOrder(product, productCount, maxId, { "melon","waffle cone",1,1,3 });
    createOrder(product, productCount, maxId, { "lemon","cup",2.40,3,4 });
}

void createOrder(PRODUCT* product, int& productCount, int& maxId, PRODUCT newProduct) {
    product[productCount].id = maxId++;
    product[productCount] = newProduct;
    productCount++;
}



void showAllIceCreams(PRODUCT* product, int& productCount) {

    for (int i = 0; i < productCount; i++) {
        cout << "Flavour: ";
        cout << product[i].flavour << endl;
        cout << "Ice-cream cone: ";
        cout << product[i].cone << endl;
        cout << "price: ";
        cout << product[i].price << " lv" << endl;
        cout << "Balls of ice cream: ";
        cout << product[i].balls << endl;
        cout << endl;
    }
}

void deleteProduct(PRODUCT* products, int& productCount, int id)
{
    int delPos;

    delPos = findById(products, productCount, id);

    for (int i = delPos; i < productCount - 1; i++) {
        products[i] = products[i + 1];
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
    int productCount = 0, maxId = 1;
    exampleProducts(product, productCount, maxId);

    while (showMenu(product, productCount, maxId));
}