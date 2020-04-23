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
    possibleFlavours[0] = { "Chocolate",21.00 };
    possibleFlavours[1] = { "Strawberry",20.00 };
    possibleFlavours[2] = { "Vanilia",22.20 };
    possibleFlavours[3] = { "Melon",19.60 };
    possibleFlavours[4] = { "Lemon",20.90 };
    possibleFlavours[5] = { "Cactus",24.20 };
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
    products[productCount] = newProduct;
    products[productCount].id = maxId++;
    calculateProductPrice(products + productCount);
    productCount++;
}

void exampleProducts(PRODUCT* product, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {
    createOrder(product, productCount, maxId, { possibleFlavours[1],possibleContainers[0],0,0});//flavour   container  price  id
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
        cout << "ID: ";
        cout << product[i].id << endl;
        cout << endl;
    }
}

void showDeleteMenu(PRODUCT* product, int& productCount) {
    int chosenId;
    showAllIceCreams(product, productCount);
    cout << "Enter the ID of the order that you want to delete: ";
    cin >> chosenId;
    deleteProduct(product, productCount, chosenId);
}

void showFlavours(FLAVOUR_TYPE *possibleFlavours, int flavourCount) {
    cout << "\nIce cream flavours: \n";
    for (int i = 0; i < flavourCount; i++) {
        cout<<i+1<<". "<<possibleFlavours[i].type<<endl;
    }
}

void showCones(CONTAINER *possibleContainers, int containerCount) {
    cout << "\nIce cream cones: \n";
    for (int i = 0; i < containerCount; i++) {
        cout<<i+1<<". "<<possibleContainers[i].type<<endl;
    }
}

void enterFlavour(FLAVOUR_TYPE* possibleFlavours, PRODUCT* newProduct) {
    int choice;
    cout<<"Enter the number of your choice: ";
    cin >> choice;
    newProduct->flavour = possibleFlavours[choice - 1];
}

void enterContainer(CONTAINER* possibleContainers, PRODUCT* newProduct) {
    int choice;
    cout<<"Enter the number of your choice: ";
    cin >> choice;
    newProduct->container = possibleContainers[choice - 1];
}

void createOrderMenu(PRODUCT* product, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount)
{
    PRODUCT newProduct;

    showFlavours(possibleFlavours, flavourCount); 
    enterFlavour(possibleFlavours, &newProduct);

    showCones(possibleContainers, containerCount);
    enterContainer(possibleContainers, &newProduct);

    createOrder(product, productCount, maxId, newProduct);
}

void showUpdateOrderMenu(PRODUCT* product, int& productCount, FLAVOUR_TYPE* possibleFlavours, int flavourCount, CONTAINER* possibleContainers, int containerCount) {
    int chosenId,chosenField, indexOfChoice;
    showAllIceCreams(product, productCount);
    cout << "Enter the ID of the order that you want to update: ";
    cin>>chosenId;

    indexOfChoice=findById(product, productCount, chosenId);

    cout << "1. Ice cream flavour: ";
    cout << product[indexOfChoice].flavour.type << endl;
    cout << "2. Ice cream cone: ";
    cout << product[indexOfChoice].container.type << endl;
    cout << "price: ";
    cout << product[indexOfChoice].price << " lv" << endl;
    cout << endl;
    cout << "Enter the field's number that you want to update:  ";
    cin >> chosenField;
    switch (chosenField)
    {
    case 1:
        showFlavours(possibleFlavours, flavourCount);
        enterFlavour(possibleFlavours, product+indexOfChoice);
        break;
    case 2:
        showCones(possibleContainers, containerCount);
        enterContainer(possibleContainers, product+indexOfChoice);
        break;
    default:
        cout << "Incorrect input!!!\n Please enter a valid input!!!\n";
        break;
    }
}

bool showMenu(PRODUCT* product, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {

    int userInput;
    cout << "\n1. See all ice creams" << endl;
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
        createOrderMenu(product, productCount, maxId, possibleFlavours, flavourCount, possibleContainers, containerCount);
        break;
    case 3:
        showDeleteMenu(product, productCount);   
        break;
    case 4:
        showUpdateOrderMenu(product, productCount, possibleFlavours, flavourCount, possibleContainers, containerCount);
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