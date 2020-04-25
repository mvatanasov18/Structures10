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

bool deleteProduct(PRODUCT* products, int& productCount, int id)
{
    int delPos;

    delPos = findById(products, productCount, id);
    if (delPos==-1) return false;

    for (int i = delPos; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }

    productCount--;

    return true;
}

void initExampleFlavours(FLAVOUR_TYPE * possibleFlavours, int& flavourCount) {
    possibleFlavours[0] = { "Chocolate",21.00 };
    possibleFlavours[1] = { "Strawberry",20.00 };
    possibleFlavours[2] = { "Vanilia",22.20 };
    possibleFlavours[3] = { "Melon",19.60 };
    possibleFlavours[4] = { "Lemon",20.90 };
    possibleFlavours[5] = { "Cactus",24.20 };
    flavourCount = 6;
}

void initExampleContainers(CONTAINER* possibleContainers, int& containerCount) {
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

void initExampleProducts(PRODUCT* products, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {
    createOrder(products, productCount, maxId, { possibleFlavours[1],possibleContainers[0],0,0 });//flavour   container  price  id
    createOrder(products, productCount, maxId, { possibleFlavours[0],possibleContainers[1],0,0 });
    createOrder(products, productCount, maxId, { possibleFlavours[2],possibleContainers[2],0,0 });
    createOrder(products, productCount, maxId, { possibleFlavours[3],possibleContainers[1],0,0 });
    createOrder(products, productCount, maxId, { possibleFlavours[5],possibleContainers[4],0,0 });
}

/*===================================PRESENTATION LAYER===================================*/
void showProduct(PRODUCT* product)
{
    cout << "ID: ";
    cout << product->id << endl;
    cout << "Ice cream flavour: ";
    cout << product->flavour.type << endl;
    cout << "Ice cream cone: ";
    cout << product->container.type << endl;
    cout << "Price: ";
    cout << product->price << " lv" << endl;
}

void showAllProducts(PRODUCT* products, int productCount) {
    showProduct(products);
    for (int i = 1; i < productCount; i++) {
        cout<<endl;
        showProduct(products+i);
    }
}

void showDeleteMenu(PRODUCT* products, int& productCount) {
    int chosenId;
    showAllProducts(products, productCount);
    cout << "Enter the ID of the order that you want to delete: ";
    cin >> chosenId;
    if(!deleteProduct(products, productCount, chosenId)) cout<<"Invalid ID!\n";
}

void showFlavours(FLAVOUR_TYPE *possibleFlavours, int flavourCount) {
    cout << "\nIce cream flavours: \n";
    for (int i = 0; i < flavourCount; i++) {
        cout<<i+1<<". "<<possibleFlavours[i].type<<endl;
    }
}

void showContainers(CONTAINER *possibleContainers, int containerCount) {
    cout << "\nIce cream cones: \n";
    for (int i = 0; i < containerCount; i++) {
        cout<<i+1<<". "<<possibleContainers[i].type<<endl;
    }
}

bool enterFlavour(FLAVOUR_TYPE* possibleFlavours, int flavourCount, PRODUCT* newProduct) {
    int choice;
    cout<<"Enter the number of your choice: ";
    cin >> choice;

    if (choice < 1 or choice > flavourCount) {
        cout<<"Invalid option!\n";
        return false;
    }
    newProduct->flavour = possibleFlavours[choice - 1];

    return true;
}

bool enterContainer(CONTAINER* possibleContainers, int containerCount, PRODUCT* newProduct) {
    int choice;
    cout<<"Enter the number of your choice: ";
    cin >> choice;

    if (choice < 1 or choice > containerCount) {
        cout<<"Invalid option!\n";
        return false;
    }
    newProduct->container = possibleContainers[choice - 1];

    return true;
}

void createOrderMenu(PRODUCT* products, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount)
{
    PRODUCT newProduct;

    showFlavours(possibleFlavours, flavourCount); 
    if (!enterFlavour(possibleFlavours, flavourCount, &newProduct)) return;

    showContainers(possibleContainers, containerCount);
    if (!enterContainer(possibleContainers, containerCount, &newProduct)) return;

    createOrder(products, productCount, maxId, newProduct);
}

void showUpdateOrderMenu(PRODUCT* products, int& productCount, FLAVOUR_TYPE* possibleFlavours, int flavourCount, CONTAINER* possibleContainers, int containerCount) {
    int chosenId,chosenField, indexOfChoice;
    showAllProducts(products, productCount);
    cout << "Enter the ID of the order that you want to update: ";
    cin>>chosenId;

    indexOfChoice=findById(products, productCount, chosenId);
    if (indexOfChoice == -1) {
        cout<<"Invalid ID!\n";
        return;
    }

    cout << "1. Ice cream flavour: ";
    cout << products[indexOfChoice].flavour.type << endl;
    cout << "2. Ice cream cone: ";
    cout << products[indexOfChoice].container.type << endl;
    cout << "Price: ";
    cout << products[indexOfChoice].price << " lv" << endl;
    cout << endl;
    cout << "Enter the field's number that you want to update:  ";
    cin >> chosenField;
    switch (chosenField)
    {
    case 1:
        showFlavours(possibleFlavours, flavourCount);
        enterFlavour(possibleFlavours, flavourCount, products+indexOfChoice);
        break;
    case 2:
        showContainers(possibleContainers, containerCount);
        enterContainer(possibleContainers, containerCount, products+indexOfChoice);
        break;
    default:
        cout << "Incorrect input!!!\n Please enter a valid input!!!\n";
        break;
    }
}

bool showMenu(PRODUCT* products, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {

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
        showAllProducts(products, productCount);
        break;
    case 2:
        createOrderMenu(products, productCount, maxId, possibleFlavours, flavourCount, possibleContainers, containerCount);
        break;
    case 3:
        showDeleteMenu(products, productCount);   
        break;
    case 4:
        showUpdateOrderMenu(products, productCount, possibleFlavours, flavourCount, possibleContainers, containerCount);
        break;
    case 5: return false;
    default: cout << "\nPlease enter a valid option!\n"; break;
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
    PRODUCT products[100];
    CONTAINER possibleContainers[100];
    FLAVOUR_TYPE possibleFlavours[100];
    int productCount = 0, maxId = 1;
    int containerCount = 0, flavourCount = 0;
    
    initExampleFlavours(possibleFlavours, flavourCount);
    initExampleContainers(possibleContainers, containerCount);
    initExampleProducts(products, productCount, maxId,  possibleFlavours, flavourCount,  possibleContainers, containerCount);

    showInitialGreeting();

    while (showMenu(products, productCount, maxId, possibleFlavours, flavourCount, possibleContainers, containerCount));

    cout<<"\nThank you for using the ICECREAM!\n";
}
