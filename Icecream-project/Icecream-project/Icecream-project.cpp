#include <iostream>
using namespace std;

struct FLAVOUR_TYPE {
    string type="";
    float pricePerKg = 0;
};

struct CONTAINER {
    string type = "";
    int capacity = 0;
};

struct PRODUCT {
    FLAVOUR_TYPE flavour;
    CONTAINER container;
    float price = 0;
    int id = 0;
};

/*===================================DATA LAYER===================================*/

int findById(PRODUCT* products, int& productCount, int id)
{
    int lBound = 0, rBound = productCount - 1, mid = 1, lastMid = 0;

    while (mid != lastMid) {
        lastMid = mid;
        mid = (lBound + rBound) / 2;

        if (id == products[mid].id) return mid;
        if (id < products[mid].id) rBound = mid - 1;
        else lBound = mid + 1;
    }

    return -1;
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

void initFlavours(FLAVOUR_TYPE * possibleFlavours, int& flavourCount) {
    possibleFlavours[0] = { "Chocolate",4.00 };
    possibleFlavours[1] = { "Strawberry",3.00 };
    possibleFlavours[2] = { "Vanilia",3.20 };
    possibleFlavours[3] = { "Melon",3.60 };
    possibleFlavours[4] = { "Lemon",2.90 };
    possibleFlavours[5] = { "Cactus",4.20 };
    flavourCount = 6;
}

void initContainers(CONTAINER* possibleContainers, int& containerCount) {
    possibleContainers[0] = { "sugar cone",50 };
    possibleContainers[1] = { "waffle cone",100 };
    possibleContainers[2] = { "Small cup",150 };
    possibleContainers[3] = { "Medium cup",200 };
    possibleContainers[4] = { "Large cup",250 };
    containerCount = 5;
}

void calculateProductPrice(PRODUCT* product)
{
	product->price = (float)product->container.capacity / 1000 * product->flavour.pricePerKg;
}

void createOrder(PRODUCT* products, int& productCount, int& maxId, PRODUCT newProduct) {
    products[productCount].id = maxId++;
    products[productCount] = newProduct;
    calculateProductPrice(products + productCount);
    productCount++;
}

void exampleProducts(PRODUCT* product, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {
    createOrder(product, productCount, maxId, { possibleFlavours[1],possibleContainers[0],0,0});
    createOrder(product, productCount, maxId, { possibleFlavours[0],possibleContainers[1],0,0 });
    createOrder(product, productCount, maxId, { possibleFlavours[2],possibleContainers[2],0,0 });
    createOrder(product, productCount, maxId, { possibleFlavours[3],possibleContainers[1],0,0 });
    createOrder(product, productCount, maxId, { possibleFlavours[5],possibleContainers[4],0,0 });
}

/*===================================PRESENTATION LAYER===================================*/

void showAllIceCreams(PRODUCT* product, int& productCount) {

    for (int i = 0; i < productCount; i++) {
        cout << "Ice cream flavour: ";
        cout << product[i].flavour.type << endl;
        cout << "Ice cream cone: ";
        cout << product[i].container.type << endl;
        cout << "price: ";
        cout << product[i].price << " lv" << endl;
        cout << endl;
    }
}

void showFlavours() {
    cout << "\nIce cream flavours: \n";
    cout << "1. Strawberry\n";
    cout << "2. Chocolate\n";
    cout << "3. Vanilia\n";
    cout << "4. Melon\n";
    cout << "5. Cactus\n";
    cout << "6. Lemon\n";
    cout << "Enter the flavour's number: ";
}

void showCones() {
    cout << "\nIce cream cones: \n";
    cout << "1. Sugar cone\n";
    cout << "2. Waffle cone\n";
    cout << "3. Small cup\n";
    cout << "4. Medium cup\n";
    cout << "5. Large cup\n";
    cout << "Enter the cone's number: ";
}

void createOrderMenu(PRODUCT* product, int& productCount, int& maxId)
{
    PRODUCT newProduct;
    int option;
    showFlavours();
    int choose=0;
    cin >> choose;
    switch (choose)
    {
    case 1: newProduct.flavour.type = "Strawberry"; break;
    case 2:newProduct.flavour.type = "Chocolate"; break;
    case 3:newProduct.flavour.type = "Vanilia"; break;
    case 4:newProduct.flavour.type = "Melon"; break;
    case 5:newProduct.flavour.type = "Cactus"; break;
    case 6:newProduct.flavour.type = "Lemon"; break;
    default:
        break;
    }

    showCones();
    cin >> choose;
    switch (choose)
    {
    case 1: newProduct.container.type = "Sugar cone"; break;
    case 2:newProduct.container.type = "Waffle cone"; break;
    case 3:newProduct.container.type = "Small cup"; break;
    case 4:newProduct.container.type = "Medium cup"; break;
    case 5:newProduct.container.type = "Large cup"; break;
    default:
        break;
    }
 

    createOrder(product, productCount, maxId, newProduct);
}

bool showMenu(PRODUCT* product, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {

    int userInput;
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
        createOrderMenu(product, productCount, maxId);
        break;
    case 3:

        deleteProduct(product, productCount,maxId);
        break;
    case 4:

        break;
    case 5: return false;
    }
    return true;
}

void showInitialGreeting()
{
    cout<<"\n      Interoperable Console - Entrepreneur's Choice for Restocking, Evaluation and Maintenance\n";
    cout<<"                                             /ICECREAM/\n\n";
    cout<<"  Welcome to the ICECREAM.\n";
    cout<<"  Thank you for choosing our software!\n";
    cout<<"  Please refer to the Documentation for a more detailed explanation about using the program.\n";
    cout<<"  The Galaxy Team takes no responsibility for misuse of the ICECREAM.\n\n";
}

int main()
{
    PRODUCT product[100];
    CONTAINER possibleContainers[100];
    FLAVOUR_TYPE possibleFlavours[100];
    int productCount = 0, maxId = 1;
    int containerCount = 0, flavourCount = 0;
    
    initFlavours(possibleFlavours, flavourCount);
    initContainers(possibleContainers, containerCount);
    exampleProducts(product, productCount, maxId,  possibleFlavours, flavourCount,  possibleContainers, containerCount);

    showInitialGreeting();

    while (showMenu(product, productCount, maxId, possibleFlavours, flavourCount, possibleContainers, containerCount));
}