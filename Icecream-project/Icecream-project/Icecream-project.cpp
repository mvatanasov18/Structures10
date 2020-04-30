#include <iostream>
#include <string>

using namespace std;

//Contain data about ice cream's flavour
struct FLAVOUR_TYPE {
    string type="";
    float pricePerKg = 0;
    int remaining=0;
};

//Contain data about ice cream's container
struct CONTAINER {
    string type = "";
    int capacity = 0;
    int remaining=0;
};

//Contain data about the order
struct PRODUCT {
    FLAVOUR_TYPE *flavour=nullptr;
    CONTAINER *container=nullptr;
    float price = 0;
    int id = 0;

};

/*===================================DATA LAYER===================================*/

//Searching for given ID from orders
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

//"Delete" any order that you want
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
    possibleFlavours[0] = { "Chocolate", 21.00, 2000 };
    possibleFlavours[1] = { "Strawberry", 20.00, 2500 };
    possibleFlavours[2] = { "Vanilia", 22.20, 1800 };
    possibleFlavours[3] = { "Melon", 19.60, 1300 };
    possibleFlavours[4] = { "Lemon", 20.90, 1000 };
    possibleFlavours[5] = { "Cactus", 24.20, 1100 };
    flavourCount = 6;
}

void initExampleContainers(CONTAINER* possibleContainers, int& containerCount) {
    possibleContainers[0] = { "Sugar cone", 50, 70 };
    possibleContainers[1] = { "Waffle cone", 100, 100 };
    possibleContainers[2] = { "Small cup", 150, 40 };
    possibleContainers[3] = { "Medium cup", 200, 15 };
    possibleContainers[4] = { "Large cup", 250, 20 };
    containerCount = 5;
}

void calculateProductPrice(PRODUCT* product)
{
	product->price = (float)product->container->capacity / 1000 * product->flavour->pricePerKg;
}

//Registering a new customer's order 
void createOrder(PRODUCT* products, int& productCount, int& maxId, PRODUCT newProduct) {
    products[productCount] = newProduct;
    products[productCount].id = maxId++;
    calculateProductPrice(products + productCount);
    productCount++;

    newProduct.flavour->remaining-=newProduct.container->capacity;
    newProduct.container->remaining--;
}

//We need those products to see how our code work at all
void initExampleProducts(PRODUCT* products, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {
    createOrder(products, productCount, maxId, { possibleFlavours+1, possibleContainers+0, 0,0 });  //flavour   container   price   id
    createOrder(products, productCount, maxId, { possibleFlavours+0, possibleContainers+1, 0,0 });
    createOrder(products, productCount, maxId, { possibleFlavours+2, possibleContainers+2, 0,0 });
    createOrder(products, productCount, maxId, { possibleFlavours+3, possibleContainers+1, 0,0 });
    createOrder(products, productCount, maxId, { possibleFlavours+5, possibleContainers+4, 0,0 });
}

//
void parseUserInput(int &out)
{
    string in;
    
    getline(cin, in);

    for (int i=0; i<in.size(); i++){
        if (in[i]<'0' or in[i]>'9'){
            out=-1;
            return;
        }
    }

    out=stoi(in);
}

//Get user input
void parseUserInput(char &out)
{
    string in;

    getline(cin, in);

    out=in[0];
}
/*===================================PRESENTATION LAYER===================================*/

//Display order
void showProduct(PRODUCT* product)
{
    cout << "ID: ";
    cout << product->id << endl;
    cout << "Ice cream flavour: ";
    cout << product->flavour->type << endl;
    cout << "Ice cream cone: ";
    cout << product->container->type << endl;
    cout << "Price: ";
    cout << product->price << " lv" << endl;
}

//Listing all order that have been made
void showAllProducts(PRODUCT* products, int productCount) {
    for (int i = 0; i < productCount; i++) {
        cout<<endl;
        showProduct(products+i);
    }
}

void showDeleteMenu(PRODUCT* products, int& productCount) {
    int chosenId;
    showAllProducts(products, productCount);
    cout << "\nEnter the ID of the order that you want to delete: ";
    parseUserInput(chosenId);

    if(!deleteProduct(products, productCount, chosenId)) cout<<"Invalid ID!\n";
}

//Listing ice cream's flavour, price per kilogram and its remaining quantity 
bool showFlavour(FLAVOUR_TYPE *flavour, int maxQuantityToShow)
{
    if (flavour->remaining>maxQuantityToShow and maxQuantityToShow!=0) return false;
    
    cout<<flavour->type<<" ("<<flavour->pricePerKg<<" lv/kg): "<<flavour->remaining<<" g\n";
    return true;
}

//Display all available flavours
void showFlavours(FLAVOUR_TYPE *possibleFlavours, int flavourCount) {
    cout << "\nIce cream flavours: \n";
    for (int i = 0; i < flavourCount; i++) {
        cout<<i+1<<". "<<possibleFlavours[i].type<<endl;
    }
}

//Display flavours in stock mode
void showFlavours(FLAVOUR_TYPE *possibleFlavours, int flavourCount, int maxQuantityToShow)
{
    bool check=false;

    cout << "\nCurrent flavour stock: \n";
    for (int i = 0; i < flavourCount; i++) {
        if (showFlavour(possibleFlavours+i, maxQuantityToShow)) check=true;
    }

    if (!check) cout<<"No flavours match your criteria.\n";
}

//Listing ice cream's container and its remaining quantity 
bool showContainer(CONTAINER *container, int maxQuantityToShow)
{
    if (container->remaining>maxQuantityToShow and maxQuantityToShow!=0) return false;

    cout<<container->type<<": "<<container->remaining<<endl;
    return true;
}

//Display all available containers
void showContainers(CONTAINER *possibleContainers, int containerCount) {
    cout << "\nIce cream cones: \n";
    for (int i = 0; i < containerCount; i++) {
        cout<<i+1<<". "<<possibleContainers[i].type<<endl;
    }
}

//Display containers in stock mode
void showContainers(CONTAINER *possibleContainers, int containerCount, int maxQuantityToShow)
{
    bool check=false;

    cout << "\nCurrent container stock: \n";
    for (int i = 0; i < containerCount; i++) {
        if (showContainer(possibleContainers+i, maxQuantityToShow)) check=true;
    }

    if (!check) cout<<"No containers match your criteria.\n";
}

bool enterFlavour(FLAVOUR_TYPE* possibleFlavours, int flavourCount, PRODUCT* newProduct) {
    int choice;
    bool check=false;

    cout<<"Enter the number of your choice: ";
    parseUserInput(choice);

    if (choice < 1 or choice > flavourCount) {
        cout<<"Invalid option!\n";
        return false;
    }

    //If this is an update operation, return the flavour and update the new flavour
    if (newProduct->container){
        check=true;
        //Return the correct ammount to the previous flavour
        newProduct->flavour->remaining+=newProduct->container->capacity;
    }
    newProduct->flavour = possibleFlavours + choice - 1;
    if (check) newProduct->flavour->remaining-=newProduct->container->capacity;

    return true;
}

//A part from the "Create order" option which takes user's input and check whether the input is correct
bool enterContainer(CONTAINER* possibleContainers, int containerCount, PRODUCT* newProduct) {
    int choice;
    bool check=false;

    cout<<"Enter the number of your choice: ";
    parseUserInput(choice);

    if (choice < 1 or choice > containerCount) {
        cout<<"Invalid option!\n";
        return false;
    }

    //If this is an update operation, return the container
    if (newProduct->container){
        check=true;
        newProduct->container->remaining++;
    }
    newProduct->container = possibleContainers + choice - 1;
    if (check) newProduct->container->remaining--;

    return true;
}

void createOrderMenu(PRODUCT* products, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount)
{
    PRODUCT newProduct;

    cout<<"\n----- Create Order -----\n";

    showFlavours(possibleFlavours, flavourCount); 
    if (!enterFlavour(possibleFlavours, flavourCount, &newProduct)) return;

    showContainers(possibleContainers, containerCount);
    if (!enterContainer(possibleContainers, containerCount, &newProduct)) return;

    createOrder(products, productCount, maxId, newProduct);
}

void showUpdateOrderMenu(PRODUCT* products, int& productCount, FLAVOUR_TYPE* possibleFlavours, int flavourCount, CONTAINER* possibleContainers, int containerCount) {
    int chosenId,chosenField, indexOfChoice;

    cout<<"\n----- Update Order -----\n";

    showAllProducts(products, productCount);
    cout << "\nEnter the ID of the order that you want to update: ";
    parseUserInput(chosenId);

    indexOfChoice=findById(products, productCount, chosenId);
    if (indexOfChoice == -1) {
        cout<<"Invalid ID!\n";
        return;
    }

    cout << "\n1. Ice cream flavour: ";
    cout << products[indexOfChoice].flavour->type << endl;
    cout << "2. Ice cream cone: ";
    cout << products[indexOfChoice].container->type << endl;
    cout << "Price: ";
    cout << products[indexOfChoice].price << " lv" << endl;
    cout << "\nEnter the number of the field you want to update:  ";
    parseUserInput(chosenField);
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

    calculateProductPrice(products+indexOfChoice);
}

//A part from the restock mode that display the data from the structure "FLAVOUR_TYPE" 
void showFlavourStockMenu(FLAVOUR_TYPE *possibleFlavours, int flavourCount)
{
    int maxQuantityToShow;

    cout<<"Maximum quantity to search for (enter 0 to list all): ";
    parseUserInput(maxQuantityToShow);

    if (maxQuantityToShow<-1) maxQuantityToShow=0;
    showFlavours(possibleFlavours, flavourCount, maxQuantityToShow);
}

//A part from the restock mode that display the data from the structure "CONTAINER"
void showContainerStockMenu(CONTAINER *possibleContainers, int containerCount)
{
    int maxQuantityToShow;

    cout<<"Maximum quantity to search for (enter 0 to list all): ";
    parseUserInput(maxQuantityToShow);

    if (maxQuantityToShow<-1) maxQuantityToShow=0;
    showContainers(possibleContainers, containerCount, maxQuantityToShow);
}

//Function used in iteractive restock
void showFlavourRestockMenu(FLAVOUR_TYPE *flavourToRestock)
{
    int userInputQuantity;

    cout<<"\n-- Restock Flavour --\n\n";

    cout<<"Enter new quantity (in grams): ";
    parseUserInput(userInputQuantity);

    if (userInputQuantity>flavourToRestock->remaining) flavourToRestock->remaining=userInputQuantity;
    else cout<<"You cannot reduce the quantity of a flavour!\n";
}

//Menu from the restock mode specific for the ice creams' flavour
void showFlavourRestockMenu(FLAVOUR_TYPE *possibleFlavours, int flavourCount)
{
    int userInputFlavour, userInputQuantity;

    cout<<"\n--- Restock Flavour ---\n\n";
    for (int i=0; i<flavourCount; i++){
        cout<<i+1<<". ";
        showFlavour(possibleFlavours+i, 0);
    }
    cout<<"Choose flavour to restock: ";
    parseUserInput(userInputFlavour);

    if (userInputFlavour<1 or userInputFlavour>flavourCount){
        cout<<"Invalid option!\n";
        return;
    }

    cout<<endl;
    showFlavour(possibleFlavours+userInputFlavour-1, 0);

    cout<<"Enter new quantity (in grams): ";
    parseUserInput(userInputQuantity);

    if (userInputQuantity>possibleFlavours[userInputFlavour-1].remaining) possibleFlavours[userInputFlavour-1].remaining=userInputQuantity;
    else cout<<"You cannot reduce the quantity of a flavour!\n";
}

//Function used in iteractive restock 
void showContainerRestockMenu(CONTAINER *containerToRestock)
{
    int userInputQuantity;

    cout<<"\n-- Restock Container --\n\n";
    showContainer(containerToRestock, 0);

    cout<<"Enter new quantity: ";
    parseUserInput(userInputQuantity);

    if (userInputQuantity>containerToRestock->remaining) containerToRestock->remaining=userInputQuantity;
    else cout<<"You cannot reduce the ammount of containers!\n";
}

void showContainerRestockMenu(CONTAINER *possibleContainers, int containerCount)
{
    int userInputContainer, userInputQuantity;

    cout<<"\n--- Restock Container ---\n\n";
    for (int i=0; i<containerCount; i++){
        cout<<i+1<<". ";
        showContainer(possibleContainers+i, 0);
    }
    cout<<"Choose container type to restock: ";
    parseUserInput(userInputContainer);

    if (userInputContainer<1 or userInputContainer>containerCount){
        cout<<"Invalid option!\n";
        return;
    }

    cout<<endl;
    showContainer(possibleContainers+userInputContainer-1, 0);

    cout<<"Enter new quantity: ";
    parseUserInput(userInputQuantity);

    if (userInputQuantity>possibleContainers[userInputContainer-1].remaining) possibleContainers[userInputContainer-1].remaining=userInputQuantity;
    else cout<<"You cannot reduce the ammount of containers!\n";
}

//Function used in "showRestockMenu"
void runAutoRestock(FLAVOUR_TYPE *possibleFlavours, int flavourCount, CONTAINER* possibleContainers, int containerCount)
{
    int maxQuantityToShow;
    char userInputYN;

    cout<<"\n---- Interactive Restock ----\n\n";

    cout<<"--- Flavours ---\n\n";
    cout<<"Enter quantity in grams above which you do not want to restock (0 to list all): ";
    parseUserInput(maxQuantityToShow);

    if (maxQuantityToShow<-1) maxQuantityToShow=0;

    for (int i=0; i<flavourCount; i++){
        if (showFlavour(possibleFlavours+i, maxQuantityToShow)){
            cout<<"Would you like to restock (y/n): ";
            parseUserInput(userInputYN);

            if (userInputYN=='y' or userInputYN=='Y'){
                showFlavourRestockMenu(possibleFlavours+i);
            }
            cout<<endl;
        }
    }

    cout<<"\n---- Containers ----\n\n";
    cout<<"Enter quantity above which you do not want to restock (0 to list all): ";
    parseUserInput(maxQuantityToShow);

    if (maxQuantityToShow<-1) maxQuantityToShow=0;

    for (int i=0; i<containerCount; i++){
        if (showContainer(possibleContainers+i, maxQuantityToShow)){
            cout<<"Would you like to restock (y/n): ";
            parseUserInput(userInputYN);

            if (userInputYN=='y' or userInputYN=='Y'){
                showContainerRestockMenu(possibleContainers+i);
            }
            cout<<endl;
        }
    }
}

//Menu for restock mode
bool showRestockMenu(FLAVOUR_TYPE *possibleFlavours, int flavourCount, CONTAINER* possibleContainers, int containerCount)
{
    int userInput;

    cout<<"\n---- Restock Menu ----\n\n";
    cout<<"1. Run interactive restock\n";
    cout<<"2. View current flavour availability\n";
    cout<<"3. View current container stock\n";
    cout<<"4. Restock flavour\n";
    cout<<"5. Restock container type\n";
    cout<<"6. Return to Main Menu\n";
    cout<<"Enter option from the menu by typing a number: ";
    parseUserInput(userInput);

    switch (userInput){
        case 1:
            runAutoRestock(possibleFlavours, flavourCount, possibleContainers, containerCount);
            break;
        case 2:
            showFlavourStockMenu(possibleFlavours, flavourCount);
            break;
        case 3:
            showContainerStockMenu(possibleContainers, containerCount);
            break;
        case 4:
            showFlavourRestockMenu(possibleFlavours, flavourCount);
            break;
        case 5:
            showContainerRestockMenu(possibleContainers, containerCount);
            break;
        case 6:
            return false;
        default:
            cout<<"\nPlease enter a valid option!\n";
            break;
    }
    return true;
}

//Function which work's until showRestockMenu() returns false 
void restockMode(FLAVOUR_TYPE *possibleFlavours, int flavourCount, CONTAINER* possibleContainers, int containerCount)
{
    while (showRestockMenu(possibleFlavours, flavourCount, possibleContainers, containerCount));
}

//Main menu
bool showMenu(PRODUCT* products, int& productCount, int& maxId, FLAVOUR_TYPE* possibleFlavours, int& flavourCount, CONTAINER* possibleContainers, int& containerCount) {

    int userInput;

    cout << "\n------- Main Menu -------\n";
    cout << "\n1. See all ice creams" << endl;
    cout << "2. Create new order" << endl;
    cout << "3. Delete order" << endl;
    cout << "4. Update order" << endl;
    cout << "5. Enter restocking mode" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(userInput);

    switch (userInput)
    {
    case 1:
		//In this case you can list all ice creams
        showAllProducts(products, productCount);
        break;
    case 2:
		//You can create your own order
        createOrderMenu(products, productCount, maxId, possibleFlavours, flavourCount, possibleContainers, containerCount);
        break;
    case 3:
		//"Delete" any order that you want 
        showDeleteMenu(products, productCount);   
        break;
    case 4:
		//In this case you can change any field of any order in need 
        showUpdateOrderMenu(products, productCount, possibleFlavours, flavourCount, possibleContainers, containerCount);
        break;
    case 5:
		//Restocking the storage
        restockMode(possibleFlavours, flavourCount, possibleContainers, containerCount);
        break;
    case 6:
		//Exit option 
		return false;
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

void showGoodbyeMessage()
{
    cout<<"\n  Thank you for using the ICECREAM!\n\n";
    cout<<"  Copyright (c) 2020 The Galaxy Team\n";;
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

    showGoodbyeMessage();
}
