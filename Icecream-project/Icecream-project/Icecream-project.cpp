#include <iostream>
using namespace std;

//struct PERSON {
//   string firstName = "";
//    string lastName = "";
//    int years = 0;
//};

struct PRODUCT {
    string brand = "";
    string cone = "";
    string flavour = "";
    float price = 0;
    int quantity = 0;
    int expDate = 0;
    //PERSON person;
    int id = 0;

};

void showAvailProd(PRODUCT* product, int& productCount);

void clearExpiredProducts();

void deleteProduct(PRODUCT* products, int& productCount, int id);

int findById(PRODUCT*, int&, int);
void YesOrNoQuestion(string yesOrNo);
void orderMenu(PRODUCT* product, int& productCount);
int orderAdditions();
void flavoursMenu();
void additionsMenu();
void iceCreamCones(PRODUCT* product, int& productCount);

bool showMenu(PRODUCT* product, int& productCount, int& maxId) {
    int userInput = 0;
    string yesOrNo = "";
    cout << "\nWelcome to the ice cream program : " << endl;
    cout << "1. Stock the shop.\n";
    cout << "2. Order an ice cream.\n";
    cout << "3. Clear expired products.\n";
    cout << "4. See what flavours you can choose from.\n";
    cout << "5. Quit." << endl;
    cout << "\nEnter option from the menu by typing a number: ";
    cin >> userInput;
    switch (userInput)
    {
    case 1:
        //in need for ideas
        break;

    case 2: {
        iceCreamCones(product, productCount);
        cout << "Do you to see what flavours you can choose from? (Y/N)\n";
        cin >> yesOrNo;
        if (yesOrNo == "Yes" or yesOrNo == "Y" or yesOrNo == "y" or yesOrNo == "yes") {
            flavoursMenu();
            system("PAUSE");
        }
        orderMenu(product, productCount);

        break;
    }

    case 3:
        clearExpiredProducts();
        break;

    case 4:

        break;

    case 5: return false;
    }
    return true;
}

void YesOrNoQuestion(string yesOrNo) {
    cout << "Do you want any additions to your ice cream? Yes/No (Y/N)\n";
    cin >> yesOrNo;
    if (yesOrNo == "Yes" or yesOrNo == "Y" or yesOrNo == "y" or yesOrNo == "yes") {
        orderAdditions();
    }
    if (yesOrNo == "No" or yesOrNo == "N" or yesOrNo == "n" or yesOrNo == "no") {

    }

}

void iceCreamCones(PRODUCT* product, int& productCount) {
    int userOption = 0;
    cout << "In what do you want your ice cream?\n";
    cout << "1. Waffle cone\t(for 1 ball)\tprice: 0.10lv\n";
    cout << "2. Sugar cone\t(for 1 ball)\tprice: 0.15lv\n";
    cout << "3. Double torch\t(for 2 balls)\tprice: 0.20lv\n";
    cout << "4. Cup\t(for more than 2 balls)\tprice: 0.25lv\n";
    cout << "\nEnter option by typing a number: ";
    cin >> userOption;

    switch (userOption)
    {
    case 1:
        product[productCount].cone = "Waffle cone";
        product[productCount].price = 0.1;
        break;
    case 2:
        product[productCount].cone = "Sugar cone";
        product[productCount].price = 0.15;
        break;
    case 3:
        product[productCount].cone = "Double torch";
        product[productCount].price = 0.20;
        break;
    case 4:
        product[productCount].cone = "Cup";
        product[productCount].price = 0.25;
        break;
    }
}

void orderMenu(PRODUCT* product, int& productCount) {
    int userOption;
    string yesOrNo;
    cout << "\nHere are some suggested ice cream masterpieces:\n";
    cout << "1. Chocolate strawberry\n- strawberry ice cream with chocolate filling\nPrice: 1.00 lv\n";
    cout << "2. Extra berry\n- strawberry, raspberry, bluberry and ice cream with strawberry and bluberry filling\nPrice: 2.80 lv\n";
    cout << "3. Biscuitino\n- biscuits, chocolate and vanilia ice cream\nPrice: 2.00 lv\n";
    cout << "4. Chocolate lover\n- chocolate, chocolate ice cream, chocolate liquor\nPrice: 2.30 lv\n";
    cout << "5. Or make your own ice cream\n";
    cout << "\nEnter option by typing a number: ";
    cin >> userOption;
    switch (userOption) {
    case 1:
        product->flavour = "strawberry";
        product->price = product->price + 1.00;

        YesOrNoQuestion(yesOrNo);
        break;
    case 2:

        YesOrNoQuestion(yesOrNo);
        break;
    case 3:

        YesOrNoQuestion(yesOrNo);
        break;
    case 4:

        YesOrNoQuestion(yesOrNo);
        break;
    case 5:
        break;
    }

}

void additionsMenu() {
    cout << "1. Chocolate filling\t price 0.05 lv\n";
    cout << "2. Strawberry filling\t price 0.05 lv\n";
    cout << "3. Blueberry filling\t price 0.05 lv\n";
    cout << "4. Chocolate liquor\t price 0.05 lv\n";
    cout << "5. Biscuts\t price 0.25\n";
    cout << "6. Cherries\t price 0.20\n";
}

int orderAdditions() {
    additionsMenu();
    cout << "Enter the number of addition";
    return 1;
}
void flavoursMenu() {
    cout << "1. Strawberry\t price: 0.60lv\n";
    cout << "2. Chocolate\t price: 0.70lv\n";
    cout << "4. Vanilia\t price: 0.70lv\n";
    cout << "5. Lemon\t price: 0.80lv\n";
    cout << "6. Melon\t price 0.70lv\n";
    cout << "7. Raspberry\t price 0.60lv\n";
    cout << "8. Bluberry\t price 0.70lv\n";
    cout << "The price is for only one ball of ice cream.\n";
}

void showAvailProd(PRODUCT* product, int& productCount) {
    cout << "The list of the entered products: " << endl;
    for (int i = 0; i < productCount; i++)
    {
        //cout << product[i].brand << " " << product[i].flavour << " " << product[i].price << " " << product[i].quantity << " " << product[i].expDate << " " << product[i].person.firstName << " " << product[i].person.lastName << " " << product[i].person.years << endl;
    }
}

void clearExpiredProducts() {

}

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



int main()
{
    PRODUCT product[100];
    int productCount = 0, maxId = 1;
    while (showMenu(product, productCount, maxId));
}
