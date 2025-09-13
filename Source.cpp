#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <limits>  // for std::numeric_limits
#include <random>


using namespace std;
//---------------------------Console Colors----------------------------------

string indexToString(int);


void getIntegerInput(int& number) {
    while (true) {
        cout << "Please enter an integer: ";
        cin >> number;

        // Check if the input is valid
        if (cin.fail()) {
            // Clear the error flag and ignore the rest of the input
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            cout << "Invalid input! Please enter a valid integer." << endl;
        }
        else {
            // If the input is valid, break out of the loop
            cout << "You entered: " << number << endl;
            break;
        }
    }
}

void setTextColor(const string& color)
{
    if (color == "black")
    {
        cout << "\033[30m"; // Black
    }
    else if (color == "red")
    {
        cout << "\033[31m"; // Red
    }
    else if (color == "green")
    {
        cout << "\033[32m"; // Green
    }
    else if (color == "yellow")
    {
        cout << "\033[33m"; // Yellow
    }
    else if (color == "blue")
    {
        cout << "\033[34m"; // Blue
    }
    else if (color == "magenta")
    {
        cout << "\033[35m"; // Magenta
    }
    else if (color == "cyan")
    {
        cout << "\033[36m"; // Cyan
    }
    else if (color == "white")
    {
        cout << "\033[37m"; // White
    }
    else if (color == "gray")
    {
        cout << "\033[90m"; // Gray (Bright Black)
    }
    else if (color == "bright_red")
    {
        cout << "\033[91m"; // Bright Red
    }
    else if (color == "bright_green")
    {
        cout << "\033[92m"; // Bright Green
    }
    else if (color == "bright_yellow")
    {
        cout << "\033[93m"; // Bright Yellow
    }
    else if (color == "bright_blue")
    {
        cout << "\033[94m"; // Bright Blue
    }
    else if (color == "bright_magenta")
    {
        cout << "\033[95m"; // Bright Magenta
    }
    else if (color == "bright_cyan")
    {
        cout << "\033[96m"; // Bright Cyan
    }
    else if (color == "bright_white")
    {
        cout << "\033[97m"; // Bright White
    }
    else if (color == "reset")
    {
        cout << "\033[0m"; // Reset to default color
    }
    else
    {
        cout << "\033[0m"; // Reset for unknown color
    }
}
void setBackgroundColor(const string& color)
{
    if (color == "black")
    {
        cout << "\033[40m"; // Black Background
    }
    else if (color == "red")
    {
        cout << "\033[41m"; // Red Background
    }
    else if (color == "green")
    {
        cout << "\033[42m"; // Green Background
    }
    else if (color == "yellow")
    {
        cout << "\033[43m"; // Yellow Background
    }
    else if (color == "blue")
    {
        cout << "\033[44m"; // Blue Background
    }
    else if (color == "magenta")
    {
        cout << "\033[45m"; // Magenta Background
    }
    else if (color == "cyan")
    {
        cout << "\033[46m"; // Cyan Background
    }
    else if (color == "white")
    {
        cout << "\033[47m"; // White Background
    }
    else if (color == "gray")
    {
        cout << "\033[48m"; // Gray (Bright Black) Background
    }
    else if (color == "bright_red")
    {
        cout << "\033[49m"; // Bright Red Background
    }
    else if (color == "bright_green")
    {
        cout << "\033[50m"; // Bright Green Background
    }
    else if (color == "bright_yellow")
    {
        cout << "\033[51m"; // Bright Yellow Background
    }
    else if (color == "bright_blue")
    {
        cout << "\033[52m"; // Bright Blue Background
    }
    else if (color == "bright_magenta")
    {
        cout << "\033[53m"; // Bright Magenta Background
    }
    else if (color == "bright_cyan")
    {
        cout << "\033[54m"; // Bright Cyan Background
    }
    else if (color == "bright_white")
    {
        cout << "\033[55m"; // Bright White Background
    }
    else
    {
        cout << "\033[0m"; // Reset for unknown color
    }
}

// Function to reset text color to default
void resetTextColor()
{
    cout << "\033[0m"; // Reset to default
}

string getPassword() {
    string password = "";
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            cout << '*';
            password += ch;
        }
    }
    cout << endl;
    return password;
}

//------------------------------------------------------------

struct Review;
class ReviewHeap;
class Employee;
class Customer;
struct Order;
class Customer;
struct DeliveryDriver;

//------------------Dish----------------------

struct Dish
{
    // static variable for unique ID
    static int uniqueDish_ID;
    // data members
    string Name;
    string Type;
    double Price;
    int ID;
    Dish* left;
    Dish* right;
    Dish* next;

    Dish(string name, string type, double price)
        : Name(name), Type(type), Price(price), left(nullptr), right(nullptr)
    {
        next = nullptr;
        // Increment the unique ID on object creation
        uniqueDish_ID++;
        ID = uniqueDish_ID; // Assign the unique ID to the current object
    }
};

struct DishHolder {
    Dish* dish;
    DishHolder* next;
    explicit DishHolder(Dish* d) : dish(d), next(nullptr) {}
};
int Dish::uniqueDish_ID = 10000;
//------------------------Dish Menu------------------------------------
struct Menu
{
    // static variable for unique ID
    static int uniqueMenu_ID;
    Dish* root;
    int ID;
    string Name;
    Menu* next;
    int Total_dishes;

    explicit Menu(string name)
    {
        Name = name;
        Total_dishes = 0;
        ID = uniqueMenu_ID;
        uniqueMenu_ID++;
        next = nullptr;
        root = nullptr;
    }
    void addDish()
    {
        string name, type;
        double price;
        cout << "Enter dish name: ";
        cin >> name;
        cout << "Enter dish type: ";
        cin >> type;
        cout << "Enter dish price: ";
        cin >> price;
        root = addDishRecursion(root, name, type, price);
        Total_dishes++;
    }

    Dish* addDishRecursion(Dish* root, string name, string type, double price)
    {
        if (root == nullptr)
        {
            return new Dish(name, type, price);
        }
        else if (price > root->Price)
        {
            root->right = addDishRecursion(root->right, name, type, price);
        }
        else
        {
            root->left = addDishRecursion(root->left, name, type, price);
        }
        return root;
    }

    int getDishPrice(string name)
    {
        return getDishPriceRecursion(root, name);
    }

    int getDishPriceRecursion(Dish* root, string name)
    {
        if (root == nullptr)
        {
            return -1;
        }
        if (root->Name == name)
        {
            return root->Price;
        }
        int leftChild = getDishPriceRecursion(root->left, name);
        int rightChild = getDishPriceRecursion(root->right, name);
        if (leftChild != -1)
        {
            return leftChild;
        }
        else if (rightChild != -1)
        {
            return rightChild;
        }
        else
        {
            return -1;
        }
    }

    void deleteDish()
    {
        string name;
        cout << "Enter dish name to delete: ";
        cin >> name;

        if (getDishPrice(name) != -1)
        {
            root = deleteDishRecursion(root, name, getDishPrice(name));
            Total_dishes--;
            return;
        }
        else
            cout << "Dish not found" << endl;
    }
    Dish* successor(Dish* root)
    {
        Dish* succ = root;
        while (succ->left != nullptr)
        {
            succ = succ->left;
        }
        return succ;
    }

    Dish* deleteDishRecursion(Dish* root, string name, int price)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (price < root->Price)
        {
            root->left = deleteDishRecursion(root->left, name, price);
        }
        else if (price > root->Price)
        {
            root->right = deleteDishRecursion(root->right, name, price);
        }
        else
        {
            if (root->left == nullptr)
            {
                Dish* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Dish* temp = root->left;
                delete root;
                return temp;
            }
            else
            {
                Dish* succ = successor(root->right);
                root->Price = succ->Price;
                root->ID = succ->ID;
                root->Name = succ->Name;
                root->Type = succ->Type;

                root->right = deleteDishRecursion(root->right, succ->Name, succ->Price);
            }
        }
        return root;
    }
    void DisplayMenu()
    {
        if (root == nullptr)
        {
            cout << "Menu has no dishes\n";
            return;
        }
        cout << "--------------------------------------------------------\n";
        DisplayMenuRecursion(root);
        cout << "---------------------------------------------------------\n";
    }

    void DisplayMenuRecursion(Dish* root)
    {
        if (root == nullptr)
        {
            return;
        }
        DisplayMenuRecursion(root->left);
        cout << "Name: " << root->Name << " " << "Price: " << root->Price << " " << "Type: " << root->Type << " " << endl;
        DisplayMenuRecursion(root->right);
    }

    void UpdateDish()
    {
        Dish* dish = getDishByName();
        if (dish != nullptr)
        {
            int choice = 99;
            cout << "What do you want to update?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Price" << endl;
            cout << "3. Type" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;
            if (choice == 1)
            {
                string name;
                cout << "Enter the new name: ";
                cin >> name;
                dish->Name = name;
            }
            else if (choice == 2)
            {
                int price;
                cout << "Enter the new price: ";
                cin >> price;
                dish->Price = price;
            }
            else if (choice == 3)
            {
                string type;
                cout << "Enter the new type: ";
                cin >> type;
                dish->Type = type;
            }
            if (choice >= 1 && choice <= 3)
            {
                cout << "Dish updated successfully" << endl;
                return;
            }
            if (choice == 4)
            {
                cout << "Exiting update menu\n";
                return;
            }
            else
            {
                cout << "Invalid choice" << endl;
                return;
            }
        }
        else
        {
            cout << "Dish not found" << endl;
        }
    }

    Dish* getDishByName()
    {
        string name;
        int price;
        cout << "Enter the name of the dish: ";
        cin >> name;
        return getDishByNameRecursion(root, name);
    }

    Dish* getDishByNameRecursion(Dish* root, string name)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->Name == name)
        {
            return root;
        }

        Dish* leftchild = getDishByNameRecursion(root->right, name);
        Dish* rightchild = getDishByNameRecursion(root->left, name);
        if (leftchild != nullptr)
        {
            return leftchild;
        }
        else if (rightchild != nullptr)
        {
            return rightchild;
        }
        else
        {
            return nullptr;
        }
    }
};
int Menu::uniqueMenu_ID = 10000;




// ------------------Order----------------------

struct Order
{
    static int unique_id;
    int ID;
    float total;
    int Priority;
    bool completed;
    string Ordertype;
    string Location;
    DishHolder* dishHolder;
    Employee* employee;
    Customer* customer;
    DeliveryDriver* driver;
    Order* next;


    Order* history;

    // float DeliveryCharges;

    Order(float total, int priority, Customer* customer)
    {
        ID = unique_id++;
        this->total = total;
        Priority = priority;
        next = nullptr;
        completed = false;
        employee = nullptr;
        history = nullptr;
        dishHolder = nullptr;
        this->customer = customer;
        driver = nullptr;
        Ordertype = " ";
        Location = " ";
        //DeliveryCharges = 0;

    }

    Order(Order* order)
    {
        ID = order->ID;
        total = order->total;
        Priority = order->Priority;
        next = nullptr;
        completed = order->completed;
        employee = order->employee;
        customer = order->customer;
        driver = order->driver;
        Location = order->Location;
        Ordertype = order->Ordertype;
        // DeliveryCharges = 0;
    }
};
int Order::unique_id = 50000;
class OrderPriorityQueue
{
private:
public:
    Order* front;
    int size;
    // priority queue using heap by get order at index functions
    OrderPriorityQueue()
    {
        front = nullptr;
        size = 0;
    }

    void addOrder(Order* order)
    {
        addAtEnd(order);
        for (int n = (size - 1) / 2; n >= 0; n--)
        {
            heapify(front, size, n);
        }
    }



    void ProcessOrder()
    {
        if (front == nullptr)
        {
            cout << "No orders to process" << endl;
            return;
        }
        front->completed = true;
        cout << "Order ID: " << front->ID << " has been processed" << endl;
        cout << "Order Details\n";
        cout << "Total: " << front->total << endl;
        cout << "Priority: " << front->Priority << endl;

        Order* newHead = new Order(getNodeAtIndex(size - 1));
        newHead->next = front->next;
        front = newHead;
        DeleteAtEnd();
        heapify(front, size, 0);
    }

    void DisplayAllOrders()
    {
        if (front == nullptr)
        {
            cout << "No orders to display" << endl;
            return;
        }
        Order* current = front;
        while (current != nullptr)
        {

            cout << "Total: " << current->total << endl;
            cout << "Priority: " << current->Priority << endl;
            cout << "Location: " << current->Location;
            current = current->next;
        }
    }

    void addAtEnd(Order* order)
    {
        if (front == nullptr)
        {
            front = order;
        }

        else
        {
            Order* current = front;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = order;
        }
        size++;
    }

    void heapify(Order* head, int size, int index)
    {
        if (head == nullptr)
        {
            return;
        }
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        Order* leftChild = getNodeAtIndex(left);
        Order* rightChild = getNodeAtIndex(right);

        if (leftChild != nullptr && leftChild->Priority > head->Priority)
        {
            largest = left;
        }

        if (rightChild != nullptr && rightChild->Priority > largest)
        {
            largest = right;
        }

        if (largest != index)
        {
            swap(getNodeAtIndex(index)->Priority, getNodeAtIndex(largest)->Priority);
            swap(getNodeAtIndex(index)->total, getNodeAtIndex(largest)->total);
            swap(getNodeAtIndex(index)->ID, getNodeAtIndex(largest)->ID);
            heapify(head, size, largest);
        }
    }

    Order* getNodeAtIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            return nullptr;
        }

        Order* current = front;
        for (int i = 0; i < index; i++)
        {
            if (current == nullptr)
            {
                return nullptr;
            }
            current = current->next;
        }
        return current;
    }

    void DeleteAtEnd()
    {
        if (front == nullptr)
        {
            return;
        }
        if (front->next == nullptr)
        {
            delete front;
            front = nullptr;
            size--;
            return;
        }
        Order* current = front;
        while (current->next->next != nullptr)
        {
            current = current->next;
        }
        delete current->next;
        size--;
        current->next = nullptr;
    }
};

struct ProcessedOrders {
    Order* order;
    ProcessedOrders* next;
    ProcessedOrders() {
        this->order = nullptr;
        this->next = nullptr;
    }
    ProcessedOrders(Order * order) {
        this->order = order;
        this->next = nullptr;
    }

};
//--------------------------- RestaurantNode----------------------------------
struct RestaurantNode
{

    int ID;
    string name;
    string type; // Fast Food, Cafe, Bakery, Chinese
    string Location;
    RestaurantNode* next;
    Menu* menu; // Pointer to the restaurant's menu
    OrderPriorityQueue orders; // Queue of orders for the restaurant
    Employee* manager;
    Employee* DeliveryDriver;

    RestaurantNode(int id, string n, string t, string l)
        : ID(id), name(n), type(t), Location(l), next(nullptr), menu(nullptr) {
        manager = nullptr;
        DeliveryDriver = nullptr;
    }




};

class RestaurantLinklist
{
private:
    RestaurantNode* head;

    std::mt19937 gen;  // Mersenne Twister engine

    int generateRandomID()
    {
        int id;
        bool unique;
        do
        {
            id = generateId();
            unique = true;
            RestaurantNode* current = head;
            while (current != nullptr)
            {
                if (current->ID == id)
                {
                    unique = false;
                    break;
                }
                current = current->next;
            }
        } while (!unique);
        return id;
    }

public:
    RestaurantLinklist()
        : head(nullptr), gen(std::random_device{}()) 
    {
        // No need for srand()
    }
    int generateId() {
        std::uniform_int_distribution<> dist(10000, 99999);
        return dist(gen);  // returns random 5-digit number
    }

    void addRestaurant(string name, string type, string location)
    {
        int id = generateRandomID();
        RestaurantNode* newNode = new RestaurantNode(id, name, type, location);
        newNode->next = head;
        head = newNode;
        cout << "Added: " << name << " with ID: " << id << endl;
    }

    void removeRestaurant(string name)
    {
        RestaurantNode* current = head;
        RestaurantNode* prev = nullptr;

        while (current != nullptr && current->name != name)
        {
            prev = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Restaurant not found: " << name << endl;
            return;
        }

        if (prev == nullptr)
        {
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        delete current->menu; // Delete the menu associated with the restaurant
        delete current;

        cout << "Deleted: " << name << endl;
    }

    RestaurantNode* findRestaurant(string name) {
        RestaurantNode* current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;

    }

    void addMenuToRestaurant()
    {
        string restaurantName;
        cout << "Enter the name of the restaurant: ";
        cin >> restaurantName;
        string menuName;
        cout << "Enter the name of the menu to add to the restaurant: ";
        cin >> menuName;

        RestaurantNode* current = head;
        while (current != nullptr)
        {
            if (current->name == restaurantName)
            {
                if (current->menu != nullptr)
                {
                    cout << "Restaurant already has a menu. Updating it with the new menu name." << endl;
                }
                current->menu = new Menu(menuName);
                cout << "Menu \"" << menuName << "\" added to restaurant \"" << restaurantName << "\"." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Restaurant not found: " << restaurantName << endl;
    }

    void manageRestaurantMenu()
    {
        string restaurantName;
        cout << "Enter the name of the restaurant: ";
        cin >> restaurantName;

        RestaurantNode* current = head;
        while (current != nullptr)
        {
            if (current->name == restaurantName)
            {
                if (current->menu == nullptr)
                {
                    cout << "This restaurant has no menu. Please add a menu first." << endl;
                    return;
                }

                int choice;
                do
                {
                    cout << "\nManaging Menu for: " << restaurantName << endl;
                    cout << "1. Add Dish\n2. Delete Dish\n3. Display Menu\n4. Update Dish\n5. Exit\n";
                    cout << "Enter choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        current->menu->addDish();
                        break;
                    case 2:
                        current->menu->deleteDish();
                        break;
                    case 3:
                        current->menu->DisplayMenu();
                        break;
                    case 4:
                        current->menu->UpdateDish();
                        break;
                    case 5:
                        cout << "Exiting menu management for: " << restaurantName << endl;
                        break;
                    default:
                        cout << "Invalid choice. Try again." << endl;
                    }
                } while (choice != 5);

                return;
            }
            current = current->next;
        }
        cout << "Restaurant not found: " << restaurantName << endl;
    }

    void displayRestaurants()
    {
        RestaurantNode* current = head;

        if (!current)
        {
            cout << "No restaurants available." << endl;
            return;
        }

        while (current != nullptr)
        {
            cout << " Name: " << current->name << ", Type: " << current->type << ", Location: " << current->Location << endl;
            if (current->menu != nullptr)
            {
                cout << ", Menu Name: " << current->menu->Name;
            }
            else
            {
                cout << ", Menu: None";
            }
            cout << endl;
            current = current->next;
        }
    }
    void displayRestaurantOrders() {
        string restaurantName;
        cout << "Enter the name of the restaurant: ";
        cin >> restaurantName;

        RestaurantNode* current = head;
        while (current != nullptr) {
            if (current->name == restaurantName) {
                if (current->orders.front == nullptr) {
                    cout << "No orders for restaurant: " << restaurantName << endl;
                    return;
                }

                cout << "Orders for restaurant: " << restaurantName << endl;
                Order* currentOrder = current->orders.front;
                while (currentOrder != nullptr) {
                    cout << "Order ID: " << currentOrder->ID << endl;
                    cout << "Total: " << currentOrder->total << endl;
                    cout << "Priority: " << currentOrder->Priority << endl;
                    cout << "Completed: " << (currentOrder->completed ? "Yes" : "No") << endl;
                    currentOrder = currentOrder->next;
                    cout << "----------------------------" << endl;
                }
                return;
            }
            current = current->next;
        }

        cout << "Restaurant not found: " << restaurantName << endl;
    }

    //void addEmployeeToRestaurant() {
    //    string restaurantName;
    //    cout << "Enter the name of the restaurant: ";
    //    cin >> restaurantName;

    //    // Find the restaurant by name
    //    RestaurantNode* current = head;
    //    while (current != nullptr) {
    //        if (current->name == restaurantName) {
    //            // Prompt for employee details
    //            string employeeName, employeeRole;
    //            cout << "Enter employee name: ";
    //            cin >> employeeName;
    //            cout << "Enter employee role (e.g., Manager, Waiter, Chef): ";
    //            cin >> employeeRole;

    //            // Generate a unique ID for the employee (e.g., using random numbers)
    //            int employeeId = rand() % 90000 + 10000; // Random ID between 10000 and 99999

    //            // Create the new employee object
    //            Employee* newEmployee = new Employee(employeeId, employeeName, employeeRole);

    //            // Add the new employee to the restaurant's employee list
    //            if (current->employees == nullptr) {
    //                current->employees = newEmployee;  // First employee
    //            }
    //            else {
    //                Employee* empCurrent = current->employees;
    //                while (empCurrent->next != nullptr) {
    //                    empCurrent = empCurrent->next; // Traverse to the end
    //                }
    //                empCurrent->next = newEmployee; // Add the employee at the end
    //            }

    //            cout << "Employee " << employeeName << " added to restaurant: " << restaurantName << endl;
    //            return;
    //        }
    //        current = current->next;
    //    }

    //    cout << "Restaurant not found: " << restaurantName << endl;
    //}

};



//-----------------------------------------------------------Account Credentials functions-------------------------
bool hasCapitalLetter(string str)
{
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            return true;
        }
    }
    return false;
}

bool hasSmallLetter(string str)
{
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        if (str[i] >= 97 && str[i] <= 122)
        {
            return true;
        }
    }
    return false;
}

bool hasRequiredLength(string str)
{
    int size = str.size();
    if (size >= 8 && size <= 12)
    {
        return true;
    }
    return false;
}

bool hasNumber(string str)
{
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        if (str[i] >= 48 && str[i] <= 57)
        {
            return true;
        }
    }
    return false;
}

bool hasSpecialCharacter(string str)
{
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        if (str[i] >= 33 && str[i] <= 47)
        {
            return true;
        }
    }
    return false;
}

bool isPassWordValid(string str)
{
    if (hasCapitalLetter(str) && hasSmallLetter(str) && hasNumber(str) && hasSpecialCharacter(str) && hasRequiredLength(str))
    {
        return true;
    }
    return false;
}

bool isEmailValid(string Email)
{
    if (Email.find("@gmail.com") != string::npos || Email.find("@hotmail.com") != string::npos)
    {
        return true;
    }
    return false;
}


//-----------------------------------------------------------USERS----------------------------------------------------------------------------




//--------------------------- Review----------------------------------

struct Review {
    static int uniqueId;
    Review* next;
    int ID;               // Unique ID (auto-incremented)
    int Rating;           // 1-5 stars
    string Description;   // Review details
    RestaurantNode* Restaurant; // Pointer to restaurant
    Customer* customer;

    Review(int rating, string description, RestaurantNode* restaurant)
        : Rating(rating), Description(description), Restaurant(restaurant) {
        this->customer = nullptr;
        this->next = nullptr;
        ID = uniqueId++;
    }
};

int Review::uniqueId = 10000;


class ReviewHeap {
private:
    Review* goodHeap[100]; // Max-heap for good reviews (4-5 stars)
    Review* badHeap[100];  // Min-heap for bad reviews (1-3 stars)
    int goodSize;          // Current size of goodHeap
    int badSize;           // Current size of badHeap


public:
    ReviewHeap() : goodSize(0), badSize(0) {}

    // Add a new review to the appropriate heap
    void addReview(Review* newReview) {
        int rating = newReview->Rating;

        if (rating >= 3) {
            if (goodSize != 100) {
                goodHeap[goodSize] = newReview;
                heapifyUp(goodHeap, goodSize, true); // Max-heapify
                goodSize++;
            }
            else {
                cout << "Heap is full!!!\n";
            }
        }
        else {
            if (badSize != 100) {
                badHeap[badSize] = newReview;
                heapifyUp(badHeap, badSize, false); // Min-heapify
                badSize++;
            }
            else {
                cout << "Heap is full!!!\n";
            }
        }

        cout << "Review added to the Review Heap!" << endl;
    }

    // Edit an existing review
    void editReview(int id, int newRating, const string& newDescription) {
        if (!updateHeap(goodHeap, goodSize, id, newRating, newDescription, true) &&
            !updateHeap(badHeap, badSize, id, newRating, newDescription, false)) {
            cout << "Review ID not found." << endl;
        }
        else {
            cout << "Review updated successfully." << endl;
        }
    }

    // Delete a review by ID
    void deleteReview(int id) {
        if (!removeFromHeap(goodHeap, goodSize, id, true) &&
            !removeFromHeap(badHeap, badSize, id, false)) {
            cout << "Review ID not found." << endl;
        }
        else {
            cout << "Review deleted successfully." << endl;
        }
    }

    void displayRestaurantViews() {
        cout << "Enter restaurant name:";
        string name;
        cin >> name;
        bool found = false;
        for (int n = 0; n < goodSize; n++) {
            if (goodHeap[n]->Restaurant->name == name) {
                found = true;
                cout << " Rating: " << goodHeap[n]->Rating << " Description: " << goodHeap[n]->Description << endl;

            }
        }

        for (int n = 0; n < badSize; n++) {
            if (badHeap[n]->Restaurant->name == name) {
                found = true;
                cout << " Rating: " << badHeap[n]->Rating << " Description: " << badHeap[n]->Description << endl;

            }
        }

        if (!found) {
            cout << "Restaurant named: " << name << " does not have any reviews." << endl;
        }
        return;


    }



    // Display the top 5 reviews from the good or bad heap
    void displayTopReviews(bool showGood) {
        Review** heap = showGood ? goodHeap : badHeap;
        int size = showGood ? goodSize : badSize;

        cout << (showGood ? "Top 5 Good Reviews:" : "Top 5 Bad Reviews:") << endl;
        for (int i = 0; i < size && i < 5; i++) {
            cout << ", Rating: " << heap[i]->Rating
                << ", Description: " << heap[i]->Description << endl;
        }
    }

private:
    // Restore heap property by moving up
    void heapifyUp(Review* heap[], int index, bool isMaxHeap) {
        int parent = (index - 1) / 2;

        while (index > 0 && ((isMaxHeap && heap[index]->Rating > heap[parent]->Rating) ||
            (!isMaxHeap && heap[index]->Rating < heap[parent]->Rating))) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // Restore heap property by moving down
    void heapifyDown(Review* heap[], int size, int index, bool isMaxHeap) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int extreme = index;

        if (left < size && ((isMaxHeap && heap[left]->Rating > heap[extreme]->Rating) ||
            (!isMaxHeap && heap[left]->Rating < heap[extreme]->Rating))) {
            extreme = left;
        }

        if (right < size && ((isMaxHeap && heap[right]->Rating > heap[extreme]->Rating) ||
            (!isMaxHeap && heap[right]->Rating < heap[extreme]->Rating))) {
            extreme = right;
        }

        if (extreme != index) {
            swap(heap[index], heap[extreme]);
            heapifyDown(heap, size, extreme, isMaxHeap);
        }
    }

    // Update a review in the heap
    bool updateHeap(Review* heap[], int size, int id, int newRating, const string& newDescription, bool isMaxHeap) {
        for (int i = 0; i < size; i++) {
            if (heap[i]->ID == id) {
                heap[i]->Rating = newRating;
                heap[i]->Description = newDescription;

                // Restore heap property after update
                heapifyUp(heap, i, isMaxHeap);
                heapifyDown(heap, size, i, isMaxHeap);
                return true;
            }
        }
        return false;
    }

    // Remove a review from the heap
    bool removeFromHeap(Review* heap[], int& size, int id, bool isMaxHeap) {

        for (int i = 0; i < size; i++) {
            if (heap[i]->ID == id) {
                delete heap[i];
                heap[i] = heap[size - 1]; // Move the last element to the current position
                size--;

                // Restore heap property after removal
                heapifyDown(heap, size, i, isMaxHeap);
                return true;
            }
        }
        return false;


    }
};

//--------------------------- Employee Class----------------------------------

class Employee
{
private:
    string name;
    string password;
    int ID;
    static int uniqueID;
    string email;


public:
    ProcessedOrders* processedOrder;
    Employee* next; // pointer to the next node in the list
    RestaurantNode* restaurant; // the Resturant hes working for

    void displayProcessedOrders() {
        if (processedOrder == nullptr) {
            cout << "No orders processed yet\n";
        }
        cout << "Your processed orders are displayed below:\n";

        ProcessedOrders* temp = processedOrder;
        while (temp) {
            cout << "_______________________________" << endl;
            // cout << "ID: " << temp->order->ID << endl;
            cout << "Total cost: " << temp->order->total << endl;
            cout << "Priority: " << temp->order->Priority << endl;
            cout << "Location: " << temp->order->Location << endl;
            temp = temp->next;
        }
    }

    Employee(string name, string password, string email)
    {
        this->name = name;
        this->email = email;
        this->ID = uniqueID++;
        this->password = password;
        Employee* next = nullptr;
        processedOrder = nullptr;
    }
    void addDishToMenu() {
        if (restaurant == nullptr) {
            cout << "You are not assigned to any restaurant" << endl;
            return;
        }
        else if (restaurant->menu == nullptr) {
            cout << "Restaurant has no menu available\n";
            return;
        }
        else {
            if (restaurant->manager == this) {
                restaurant->menu->addDish();
            }
            else {
                cout << "You are not the manager of this restaurant.Only managers can access this feature.\n";
                return;
            }
        }
    }

    void addMenuToRestaurant() {
        if (restaurant == nullptr) {
            cout << "You are not assigned to any restaurant" << endl;
            return;
        }
        else if (restaurant->menu != nullptr) {
            cout << "Restaurant already has a menu\n";
            return;
        }
        else {
            if (restaurant->manager == nullptr) {
                string name;
                cout << "Enter menu name: ";
                cin >> name;
                restaurant->menu = new Menu(name);
            }
            else {
                cout << "You are not the manager of this restaurant.Only managers can access this feature.\n";
                return;
            }
        }
    }

    void updateDish() {
        if (restaurant != nullptr && restaurant->menu != nullptr)
            if (restaurant->manager == this) {
                restaurant->menu->UpdateDish();
            }
            else {
                cout << "You are not the manager of this restaurant.Only managers can access this feature.\n";
                return;
            }
        else {
            cout << "Either the restaurant or menu is not assigned\n";
        }
    }
    void setRestaurant(RestaurantNode* restaurant)
    {
        this->restaurant = restaurant;
    }
    string getName()
    {
        return name;
    }
    int getID()
    {
        return ID;
    }
    string getEmail()
    {
        return email;
    }
    string getPassword()
    {
        return password;
    }
    void changeAccountDetails()
    {
        int choice = 99;
        string email;
        string password;
        // also check if email and passwords are valid
        while (choice != 0)
        {
            cout << "Enter 1 to change email" << endl;
            cout << "Enter 2 to change password" << endl;
            cout << "Enter 3 to channge name" << endl;
            cout << "Enter 0 to exit" << endl;
            cin >> choice;
            if (choice == 1)
            {
                cout << "Enter new email" << endl;
                cin >> email;
                while (isEmailValid(email) == false)
                {
                    cout << "Invalid email, please enter a valid email" << endl;
                    cin >> email;
                }
                this->email = email;
            }
            else if (choice == 2)
            {
                cout << "Enter new password" << endl;
                cin >> password;
                while (isPassWordValid(password) == false)
                {
                    cout << "Invalid password, please enter a valid password" << endl;
                    cin >> password;
                }
                this->password = password;
            }
            else if (choice == 3)
            {
                cout << "Enter new name" << endl;
                cin >> name;
                this->name = name;
            }
            else if (choice == 0)
            {
                break;
            }
        }
        return;
    }

    static Employee* createEmployeeAccount()
    {
        string name;
        string password;
        string email;
        cout << "Enter name" << endl;
        cin >> name;
        cout << "Enter email" << endl;
        cin >> email;
        while (isEmailValid(email) == false)
        {
            cout << "Invalid email, please enter a valid email" << endl;
            cin >> email;
        }
        cout << "Enter password" << endl;
        char ch;
        while ((ch = _getch()) != '\r') { // '\r' is Enter key
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    std::cout << "\b \b";
                    password.pop_back();
                }
            }
            else {
                std::cout << '*';
                password += ch;
            }
        }
        cout << endl;
        while (isPassWordValid(password) == false)
        {
            cout << "Invalid password, please enter a valid password" << endl;
            while ((ch = _getch()) != '\r') { // '\r' is Enter key
                if (ch == '\b') { // Handle backspace
                    if (!password.empty()) {
                        std::cout << "\b \b";
                        password.pop_back();
                    }
                }
                else {
                    std::cout << '*';
                    password += ch;
                }
            }
            cout << endl;
        }
        Employee* e = new Employee(name, password, email);
        return e;
    }


};
int Employee::uniqueID = 20000;

class EmployeeHashmap
{
private:


public:
    Employee* employee[10];
    EmployeeHashmap()
    {
        for (int i = 0; i < 10; i++)
        {
            employee[i] = nullptr;
        }
    }
    int hashmapFunction(int id)
    {
        return id % 10;
    }

    void addToHashmap(RestaurantNode* r = nullptr)
    {
        Employee* e = Employee::createEmployeeAccount();
        e->restaurant = r;
        Employee* destination = employee[hashmapFunction(e->getID())];
        if (destination == nullptr)
        {
            destination = e;
            employee[hashmapFunction(e->getID())] = destination;
        }
        else
        {
            e->next = destination;
            destination = e;
            employee[hashmapFunction(e->getID())] = destination;
        }
    }
    Employee* searchByEmail(string email) {
        for (int n = 0; n < 10; n++) {
            Employee* current = employee[n];
            while (current) {
                if (current->getEmail() == email) {
                    return current;
                }
                current = current->next;
            }
        }
        return nullptr;
    }
    void deleteEmployee()
    {
        int id;
        cout << "Enter the id of the employee you want to delete" << endl;
        cin >> id;
        int index = hashmapFunction(id);
        Employee* e = employee[index];
        if (e == nullptr)
        {
            cout << "No employee with that id" << endl;
            return;
        }
        if (e->getID() == id)
        {
            employee[index] = e->next;
            delete e;
            return;
        }
        while (e->next != nullptr)
        {
            if (e->next->getID() == id)
            {
                Employee* temp = e->next;
                e->next = temp->next;
                delete temp;
                return;
            }
            e = e->next;
        }
        cout << "No employee with that id" << endl;
    }
    void searchEmployee()
    {
        int id;
        cout << "Enter the id of the employee you want to search" << endl;
        cin >> id;
        int index = hashmapFunction(id);
        Employee* e = employee[index];
        while (e != nullptr)
        {
            if (e->getID() == id)
            {
                cout << "Employee found" << endl;
                cout << "ID:" << e->getID() << endl;
                cout << "Name:" << e->getName() << endl;
                return;
            }
            e = e->next;
        }
        cout << "Employee not found" << endl;
    }

    Employee* getEmployeeByName(string name)
    {
        for (int n = 0; n < 10; n++) {
            Employee* e = employee[n];
            while (e != nullptr)
            {
                if (e->getName() == name)
                {
                    cout << "Employee found" << endl;
                    cout << "ID:" << e->getID() << endl;
                    cout << "Name:" << e->getName() << endl;
                    return e;;
                }
                e = e->next;
            }
        }
        cout << "Employee not found" << endl;
        return nullptr;
    }

    void printHashmap()
    {
        cout << "Employees in the hashmap" << endl;

        for (int i = 0; i < 10; i++)
        {
            Employee* e = employee[i];
            while (e != nullptr)
            {
                cout << e->getID() << ":" << e->getName() << endl;
                e = e->next;
            }
        }
    }
};
//For logging of Employee
Employee* authenticateEmployee(EmployeeHashmap& employeeDatabase) {
    int id;
    string password;

    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;

    int index = employeeDatabase.hashmapFunction(id);

    Employee* employee = employeeDatabase.employee[index];
    while (employee != nullptr) {
        if (employee->getID() == id && employee->getPassword() == password) {
            cout << "Authentication successful. Welcome, " << employee->getName() << "!\n";
            return employee;
        }
        employee = employee->next;
    }

    cout << "Invalid ID or Password.\n";
    return nullptr;
}


//--------------------------- Customer----------------------------------

class Customer
{
private:

    static int unique_ID;
    int ID;
    string Name;
    string Email;
    string Password;
    
    Review* reviewhistory;


public:
    Order* orderhistory;
    Customer* next;
    Customer(string name, string password, string email)
    {
        ID = unique_ID++;
        Name = name;
        Email = email;
        Password = password;
        orderhistory = nullptr;
        reviewhistory = nullptr;
        next = nullptr;
    }
    Customer(Customer& c)
    {
        ID = c.ID;
        Name = c.Name;
        Email = c.Email;
        Password = c.Password;
        orderhistory = nullptr;
        reviewhistory = nullptr;
        next = nullptr;
    }
    int get_ID()
    {
        return ID;
    }
    string getPassword()
    {
        return Password;
    }
    string getName()
    {
        return Name;
    }
    string getEmail() {
        return Email;
    }
    void DisplayReviewHistory() {
        Review* r = reviewhistory;
        if (!r) {
            cout << "No reviews available.\n";
            return;
        }
        while (r != nullptr) {
            cout << "Displaying review...\n"; // Debug
            cout << " Restaurant Name: "
                << (r->Restaurant ? r->Restaurant->name : "Unknown")
                << " Rating: " << r->Rating
                << " Description: " << r->Description << endl;
            r = r->next;
        }
    }


    void Customize()
    {
        int choice = 99;
        cout << "1: Change name\n";
        cout << "2: Change email\n";
        cout << "3: Change password\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter new name: ";
            cin >> Name;
            break;
        case 2:
            cout << "Enter new email: ";
            cin >> Email;

            while (!(isEmailValid(Email)))
            {
                cout << "Invalid email, please enter again: ";
                cin >> Email;
            }

            break;
        case 3:
            cout << "Enter new password: ";
            cin >> Password;
            while (!isPassWordValid(Password))
            {
                cout << "Invalid password, please enter again: ";
                cin >> Password;
            }
            cout << "Password is changed\n";
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }

    void addReview(RestaurantLinklist& rL, ReviewHeap& rh) {
        string restaurantName;
        cout << "Enter restaurant name: ";
        cin.ignore();
        cin >> restaurantName;
        RestaurantNode* restaurant = rL.findRestaurant(restaurantName);
        if (restaurant == nullptr) {
            cout << "Restaurant not found\n";
            return;
        }
        int rating;

        cout << "Enter rating: ";
        cin.ignore();
        cin >> rating;
        while (rating < 0 || rating > 5) {
            cout << "Invalid rating, please enter again: ";
            cin >> rating;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        string review;
        cout << "Enter review: ";
        getline(cin, review);
        if (review.empty()) {
            cout << "Review cannot be empty.\n";
            return;
        }

        Review* newReview = new Review(rating, review, restaurant);

        rh.addReview(newReview);
        if (!reviewhistory) {
            reviewhistory = newReview;
            reviewhistory->next = nullptr;
        }
        else {
            newReview->next = reviewhistory;
            reviewhistory = newReview;
        }



    }


    void addOrder(RestaurantLinklist& rL) {
        rL.displayRestaurants();
        string restaurantName;
        cout << "Enter restaurant name: ";
        cin >> restaurantName;

        RestaurantNode* restaurant = rL.findRestaurant(restaurantName);
        if (restaurant == nullptr) {
            cout << "No such restaurant found\n";
            return;
        }
        if (restaurant->menu == nullptr) {
            cout << "Restaurant has no menu\n";
            return;
        }
        restaurant->menu->DisplayMenu();

        Dish* dish = nullptr;
        Order* order = new Order(0, 0, this);
        while (true) {
            dish = restaurant->menu->getDishByName();
            if (!dish) {
                cout << "No such dish exists\n";
            }
            else {
                DishHolder* temp = new DishHolder(dish);
                temp->next = order->dishHolder;
                order->dishHolder = temp;
            }
            int choice;
            cout << "Do you want to order another item?\n";
            cout << "Enter 1 for yes and 0 for no: ";
            cin >> choice;

            if (choice == 0) {
                break;
            }
            dish = nullptr;
        }
        if (!(order->dishHolder)) {
            cout << "No dishes ordered\n";
            delete order;  // Free memory for the unused order
            return;
        }
        cout << "----------------------------------Locations available--------------------------------------\n";
        for (int i = 0; i < 38; i++) { // will be an array of prefined location and it will be global
            cout << indexToString(i) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------\n";
        string location;
        cout << "Enter your location:";
        cin >> location;

        order->Location = location;
        int priority;
        cout << "Choose your priority:\n";
        cout << "1) Premium\n";
        cout << "2) Express\n";
        cout << "3) Normal\n";

        int choice;
        cin >> choice;
        while (choice < 1 || choice > 3) {
            cout << "Enter priority again (1-3): ";
            cin >> choice;
        }
        if (choice == 1) {
            priority = 5;
        }
        else if (choice == 2) {
            priority = 3;
        }
        else {
            priority = 1;
        }

        float total = 0;
        for (DishHolder* temp = order->dishHolder; temp != nullptr; temp = temp->next) {
            total += temp->dish->Price;
        }
        order->total = total;

        // Ask for delivery type
        cout << "Choose your delivery type:\n";
        cout << "1) Premium (No delivery charges)\n";
        cout << "2) Express (200 delivery charges)\n";
        cout << "3) Normal (100 delivery charges)\n";

        cin >> choice;
        while (choice < 1 || choice > 3) {
            cout << "Enter delivery type again (1-3): ";
            cin >> choice;
        }

        if (choice == 1) {
            order->Ordertype = " Premium";
            cout << "Since the delivery is Premium, no extra delivery charges will be applied.\n";
        }
        else if (choice == 2) {
            order->Ordertype = "Express";
            cout << "Since the delivery is Express, 200 delivery charges will be applied.\n";
            //order->total += 200;
        }
        else {
            order->Ordertype = "Normal";
            cout << "Since the delivery is Normal, 100 delivery charges will be applied.\n";
            //order->total += 100;
        }

        if (priority == 5) {
            cout << "Since the order is Premium, 500 extra charges will be applied.\n";
            //order->total += 500;
        }
        else if (priority == 3) {
            cout << "Since the order is Express, 200 extra charges will be applied.\n";
            // order->total += 200;
        }

        order->Priority = priority;
        restaurant->orders.addOrder(order);
        order->history = orderhistory;
        orderhistory = order;
    }


    void displayOrderHistory() {
        Order* current = orderhistory;
        if (current == nullptr) {
            setTextColor("red");
            cout << "No orders placed yet\n";
            resetTextColor();
            return;
        }

        setTextColor("blue");

        cout << "Your Order History: " << endl;
        setTextColor("yellow");
        while (current != nullptr) {
            // cout << "Order ID: " << current->ID << endl;
            cout << "Total cost: " << current->total << endl;
            DishHolder* temp = current->dishHolder;
            while (temp != nullptr) {
                cout << "---------------------------------------\n";
                cout << "Dish: " << temp->dish->Name << endl;
                cout << "---------------------------------------\n";
                cout << "Price: " << temp->dish->Price << endl;
                cout << "Type: " << temp->dish->Type << endl;
                // cout << "Dish ID: " << temp->dish->Type << endl;
                temp = temp->next;
            }

            cout << "Priority: " << current->Priority << endl;
            cout << "Completed: " << current->completed << endl;
            if (current->completed) {
                cout << "Order processed by Employee: " << current->employee->getName() << endl;
            }
            current = current->history;
            setTextColor("red");
            cout << "--------------------------------------------------\n";
            setTextColor("yellow");
        }
        resetTextColor();
    }

    void deleteorder() {
        displayOrderHistory();
        cout << endl;

        if (orderhistory == nullptr) {
            cout << "No orders available to delete.\n";
            return;
        }

        int choice = -1;
        cout << "Enter the Order ID you want to remove from your history: ";
        cin >> choice;

        // Search for the order with the specified ID
        Order* prev = nullptr;
        Order* current = orderhistory;

        while (current != nullptr && current->ID != choice) {
            prev = current;
            current = current->history;
        }

        if (current == nullptr) {
            cout << "Order with ID " << choice << " not found in your order history.\n";
            return;
        }
        if (prev == nullptr) {
            orderhistory = current->history;
        }
        else {

            prev->history = current->history;
        }


        cout << "Order ID " << choice << " has been removed from your history.\n";
    }

    void deleteReview(ReviewHeap& RH) {
        DisplayReviewHistory(); // Display current review history

        if (reviewhistory == nullptr) {
            cout << "No reviews available to delete.\n";
            return;
        }

        int choice = -1;
        cout << "Enter the Review ID you want to remove from your history: ";
        cin >> choice;

        // Search for the review with the specified ID
        Review* prev = nullptr;
        Review* current = reviewhistory;

        while (current != nullptr && current->ID != choice) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Review with ID " << choice << " not found in your review history.\n";
            return;
        }

        // Remove the review
        if (prev == nullptr) {
            // The review to delete is the first one in the list
            reviewhistory = current->next;
        }
        else {
            // The review to delete is somewhere in the middle or end
            prev->next = current->next;
        }
        RH.deleteReview(current->ID);

        cout << "Review ID " << choice << " has been removed from your history.\n";
    }
    void editReview(ReviewHeap& RH) {
        DisplayReviewHistory(); // Display current review history

        if (reviewhistory == nullptr) {
            cout << "No reviews available to edit.\n";
            return;
        }

        int choice = -1;
        cout << "Enter the Review ID you want to edit from your history: ";
        cin >> choice;

        // Search for the review with the specified ID
        Review* prev = nullptr;
        Review* current = reviewhistory;

        while (current != nullptr && current->ID != choice) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Review with ID " << choice << " not found in your review history.\n";
            return;
        }
        int rating;
        string description;


        do {
            cout << "Enter the new rating(1-5): ";
            cin >> rating;
            cin.ignore();
        } while (rating < 1 || rating>5);

        cout << "Enter the description: ";

        getline(cin, description);

        RH.editReview(choice, rating, description);



    }


    static Customer* makeCustomerAccount();
};

Customer* Customer::makeCustomerAccount()
{
    string name, email, password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    while (!isEmailValid(email))
    {
        cout << "Invalid email, please enter again: ";
        cin >> email;
    }
    cout << "Enter password: ";
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            std::cout << '*';
            password += ch;
        }
    }
    cout << endl;
    while (!isPassWordValid(password))
    {
        cout << "Invalid password, please enter again: ";
        while ((ch = _getch()) != '\r') { // '\r' is Enter key
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    std::cout << "\b \b";
                    password.pop_back();
                }
            }
            else {
                std::cout << '*';
                password += ch;
            }
        }
        cout << endl;
    }

    return new Customer(name, email, password);
}

int Customer::unique_ID = 90000;



struct CustomerHashmap {
    static const int SIZE = 10;  // Fixed size for array
    Customer* customerArray[SIZE] = { nullptr };  // Array of pointers to Customer (for chaining)

    // Hash function to compute the index for the array
    int hashFunction(int id) {
        return id % SIZE;
    }

    // Add customer to the array (handle collisions using chaining)
    void addCustomer(Customer* c) {
        int index = hashFunction(c->get_ID());

        // Insert at the beginning of the linked list (for simplicity)
        c->next = customerArray[index];
        customerArray[index] = c;
    }

    // Get customer from the array (handle collisions using chaining)
    Customer* getCustomer(int id) {
        int index = hashFunction(id);
        Customer* current = customerArray[index];

        // Traverse the linked list to find the customer with the given ID
        while (current != nullptr) {
            if (current->get_ID() == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;  // Return nullptr if not found
    }

    Customer* getCustomerbyEmail(string email) {
        for (int n = 0; n < 10; n++) {
            Customer* current = customerArray[n];
            while (current) {
                if (current->getEmail() == email) {
                    return current;
                }
                current = current->next;
            }
        }
        return nullptr;
    }

    // Log in function
    Customer* LogIn(string email, string Password) {


        Customer* customer = getCustomerbyEmail(email);
        if (customer == nullptr) {
            cout << "No account is registered with this email.\n";
            return nullptr;
        }

        if (Password != customer->getPassword()) {
            cout << "Wrong password entered.\n";
            return nullptr;
        }
        return customer;


    }

    // Remove customer function
    void removeCustomer() {
        string name;
        int ID;
        cout << "Enter ID: ";
        cin >> ID;
        cout << "Enter Name: ";
        cin >> name;

        int index = hashFunction(ID);
        Customer* current = customerArray[index];
        Customer* prev = nullptr;

        // Traverse the linked list to find the customer to remove
        while (current != nullptr) {
            if (current->get_ID() == ID && current->getName() == name) {
                if (prev == nullptr) {
                    // Remove the first node in the list
                    customerArray[index] = current->next;
                }
                else {
                    // Remove the node from the middle or end of the list
                    prev->next = current->next;
                }
                cout << "Account removed successfully\n";
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Customer not found or name mismatch\n";
    }
};










//---------------------------Promotion Class----------------------------------

class Promotion
{
private:
    static int idGenerator;

public:
    int id;
    string name;
    float discount;
    int limit;

    Promotion() : id(0), name(""), discount(0.0), limit(0) {}

    Promotion(string name, float discount, int limit)
        : name(name), discount(discount), limit(limit)
    {
        id = idGenerator++;
    }

    void display() const
    {
        cout << ", Name: " << name
            << ", Discount: " << discount << "%"
            << ", Limit: " << limit << endl;
    }
};

int Promotion::idGenerator = 10000; // Initialize static variable to start from 10000

class PromotionStack
{
private:
    struct Node
    {
        Promotion promotion;
        Node* next;

        Node(Promotion promo) : promotion(promo), next(nullptr) {}
    };

    Node* top; // Pointer to the top of the stack

public:
    PromotionStack() : top(nullptr) {}

    ~PromotionStack()
    {
        while (top != nullptr)
        {
            pop();
        }
    }

    void push(const Promotion& promotion)
    {
        Node* newNode = new Node(promotion);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty, nothing to pop.\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    Promotion& peek()
    {
        if (isEmpty())
        {
            throw runtime_error("Stack is empty, nothing to peek.");
        }
        return top->promotion;
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void displayPromotions() const
    {
        if (isEmpty())
        {
            cout << "No active promotions.\n";
            return;
        }

        Node* current = top;
        cout << "\nActive Promotions:\n";
        while (current != nullptr)
        {
            current->promotion.display();
            current = current->next;
        }
    }
};

// Function to process orders and apply promotions
void processOrders(PromotionStack& promotionStack, OrderPriorityQueue& orderQueue, Employee* employee)
{
    while (orderQueue.front != nullptr)
    {
        // Fetch the highest-priority order (front of the queue)
        Order* currentOrder = orderQueue.front;

        // Display current order details
        cout << "\nProcessing Order ID: " << currentOrder->ID << endl;
        cout << "Original Total: Rs. " << fixed << setprecision(2) << currentOrder->total << endl;

        float discountedCost = currentOrder->total; // Initialize discounted cost

        // Apply promotions if available
        if (!promotionStack.isEmpty())
        {
            // Apply the current promotion
            Promotion& currentPromotion = promotionStack.peek();
            cout << "Applying Promotion \"" << currentPromotion.name
                << "\" to order total Rs. " << currentOrder->total << endl;
            currentOrder->employee = employee;
            cout << "Order placed by: " << currentOrder->customer->getName() << endl;
            discountedCost = currentOrder->total * (1 - currentPromotion.discount / 100.0f);
            cout << "Discounted Cost: Rs. " << fixed << setprecision(2) << discountedCost << endl;

            // Update promotion usage limit
            currentPromotion.limit--;

            // Remove the promotion if its limit is reached
            if (currentPromotion.limit <= 0)
            {
                cout << "Promotion \"" << currentPromotion.name << "\" expired and removed from the stack.\n";
                promotionStack.pop();
            }
        }
        else
        {
            cout << "No active promotions. Order cost remains: Rs. " << discountedCost << endl;
        }

        // Add premium cost based on order priority
        if (currentOrder->Priority == 5)
        {
            discountedCost += 500;
            cout << "Priority 5 order. Additional premium cost: Rs. 500\n";
        }
        else if (currentOrder->Priority == 3)
        {
            discountedCost += 300;
            cout << "Priority 3 order. Additional premium cost: Rs. 300\n";
        }
        else if (currentOrder->Priority == 1)
        {
            discountedCost += 100;
            cout << "Priority 1 order. Additional premium cost: Rs. 100\n";
        }

        // Apply delivery charges based on order type
        if (currentOrder->Ordertype == "express" || currentOrder->Ordertype == "Express")
        {
            cout << "Delivery Charges applied: Rs. 200\n";
            discountedCost += 200;
        }
        else if (currentOrder->Ordertype == "Normal" || currentOrder->Ordertype == "normal")
        {
            cout << "Delivery Charges applied: Rs. 100\n";
            discountedCost += 100;
        }

        // Calculate final cost after express order fee
        float finalCost = discountedCost * 1.1f; // 10% express order fee
        cout << "Final Cost after Express Order Fee: Rs. " << fixed << setprecision(2) << finalCost << endl;

        // Update the order total with the final cost
        currentOrder->total = finalCost;

        // Mark the order as completed
        currentOrder->completed = true;
        ProcessedOrders* temp = new ProcessedOrders(currentOrder);
        temp->next = employee->processedOrder;
        employee->processedOrder = temp;

        // Remove the processed order from the priority queue
        orderQueue.ProcessOrder(); // This removes the front order and reheapifies
    }

    cout << "Orders have been processed.\n";
}




//----------------------------Delivery------------------------
struct DeliveryDriver {
    string name;
    Order* DeliveredOrdered;
    string path;

    DeliveryDriver(string name) : name(name) {}
};




//--------------------------- Admin class----------------------------------

class Admin
{
private:
    string name;
    string password;
    string email;

public:
    Admin(string name, string password, string email)
    {
        this->name = name;
        this->password = password;
        this->email = email;
    }
    Admin()
    {
        this->name = "Hamas";
        this->password = "Hamas";
        this->email = "Hamas@gmail.com";
    }
    string getpassword() {
        return password;
    }
    string getname() {
        return name;
    }
    string getemail() {
        return email;
    }

    void addEmployee(EmployeeHashmap& eh, RestaurantNode* R = nullptr)
    {
        eh.addToHashmap(R);
    }
    void removeEmployee(EmployeeHashmap& eh)
    {
        eh.deleteEmployee();
    }
    void printEmployee(EmployeeHashmap& eh)
    {
        eh.printHashmap();
    }
    void addRestaurant(RestaurantLinklist& rlist)
    {
        string name;
        string type;
        string location;
        cout << "Enter the name of the restaurant: ";
        cin >> name;
        cout << "Enter the type of the restaurant: ";
        cin >> type;
        cout << "Enter the Location of the restaurant: ";
        cin >> location;
        rlist.addRestaurant(name, type, location);
    }
    void removeRestaurant(RestaurantLinklist& rlist)
    {
        string name;
        cout << "Enter the name of the restaurant: ";
        cin >> name;
        rlist.removeRestaurant(name);
    }
    void displayallRestaurants(RestaurantLinklist& rlist)
    {
        rlist.displayRestaurants();
    }
    void addMenuToRestaurant(RestaurantLinklist& rlist)
    {
        rlist.addMenuToRestaurant();
    }

    void manageRestaurantMenu(RestaurantLinklist& rlist)
    {
        rlist.manageRestaurantMenu();
    }
};
void AdminMenu(RestaurantLinklist& RL, EmployeeHashmap& CH, Admin& admin, PromotionStack& promotionStack)
{
    cout << "              _           _         __  __                   \n";
    cout << "     /\\      | |         (_)       |  \\/  |                  \n";
    cout << "    /  \\   __| |_ __ ___  _ _ __   | \\  / | ___ _ __  _   _ \n";
    cout << "   / /\\ \\ / _` | '_ ` _ \\| | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |\n";
    cout << "  / ____ \\ (_| | | | | | | | | | | | |  | |  __/ | | | |_| |\n";
    cout << " /_/    \\_\\__,_|_| |_| |_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n";
    cout << endl;
    string name2;
    string resname;
    int choice = 99;
    string name;
    string email;
    string password;
    Employee* employee;
    while (true)
    {
        cout << "Select an option:" << endl;
        cout << "\n";
        setTextColor("red");
        cout << "1. Add Restaurant" << endl;
        setTextColor("red");
        cout << "2. Remove Restaurant" << endl;
        setTextColor("blue");
        cout << "3. Display All Restaurants" << endl;
        setTextColor("blue");
        cout << "4. Add Menu to Restaurant" << endl;
        setTextColor("green");
        cout << "5. Manage Restaurant Menu" << endl;
        setTextColor("green");
        cout << "6. Add Employee" << endl;
        setTextColor("yellow");
        cout << "7. Remove Employee" << endl;
        setTextColor("yellow");
        cout << "8. Display All Employees" << endl;
        setTextColor("cyan");
        cout << "9. Assign restaurant to employee" << endl;
        setTextColor("magenta");
        cout << "10. Add Promotions" << endl;
        setTextColor("magenta");
        cout << "11. Remove Promotions" << endl;
        setTextColor("red");
        cout << "12. View Promotions" << endl;
        setTextColor("bright_magenta");
        cout << "13. Assign a manager to a restaurant" << endl;
        setTextColor("red");
        cout << "14. Assign Deliverman" << endl;
        setTextColor("blue");
        cout << "15. Logout" << endl;

        resetTextColor();

        getIntegerInput(choice);
        switch (choice)
        {
        case 1:
            admin.addRestaurant(RL);
            break;
        case 2:
            admin.removeRestaurant(RL);
            break;
        case 3:
            admin.displayallRestaurants(RL);
            break;
        case 4:
            admin.addMenuToRestaurant(RL);
            break;
        case 5:
            admin.manageRestaurantMenu(RL);
            break;
        case 6:
            admin.addEmployee(CH);
            break;
        case 7:
            admin.removeEmployee(CH);
            break;
        case 8:
            admin.printEmployee(CH);
            break;
        case 9:
            admin.displayallRestaurants(RL);
            admin.printEmployee(CH);
            cout << "Enter the name of Employee: ";
            cin >> name2;

            Employee* employee;
            employee = CH.getEmployeeByName(name2);
            if (employee == nullptr) {
                cout << "No such Employee found.\n";
            }
            else {
                cout << "Enter Restaurant Name: ";
                cin >> resname;

                RestaurantNode* restaurant;
                restaurant = RL.findRestaurant(resname);
                if (restaurant == nullptr) {
                    cout << "No Restaurant found!!\n";
                }
                else {
                    employee->restaurant = restaurant;
                    cout << "Employee assigned to Restaurant successfully.\n";
                }
            }
            break;

        case 10: // Add Promotion
        {
            string promoName;
            float discount;
            int limit;

            cout << "Enter Promotion Name: ";
            cin.ignore();
            getline(cin, promoName);

            cout << "Enter Discount Percentage: ";
            cin >> discount;

            cout << "Enter Usage Limit: ";
            cin >> limit;

            Promotion newPromotion{ promoName, discount, limit };
            promotionStack.push(newPromotion);

            cout << "Promotion \"" << promoName << "\" added successfully.\n";
            break;
        }

        case 11: // Remove Promotion
            if (promotionStack.isEmpty())
            {
                cout << "No promotions available to remove.\n";
            }
            else
            {
                Promotion topPromotion = promotionStack.peek();
                cout << "Removing Promotion \"" << topPromotion.name << "\"...\n";
                promotionStack.pop();
                cout << "Promotion removed successfully.\n";
            }
            break;


        case 12:
            promotionStack.displayPromotions();
            break;

        case 13:
            cout << "Note: An employee can only become the manager of the restaurant he currently works at.\n";
            admin.printEmployee(CH);
            cout << "Enter the name of Employee: ";

            cin >> name2;


            employee = CH.getEmployeeByName(name2);
            if (employee == nullptr) {
                cout << "No such Employee found.\n";
            }
            else {
                if (employee->restaurant == nullptr) {
                    cout << "Employee is not assigned to any restaurant.\n";
                }
                else {
                    employee->restaurant->manager = employee;
                    cout << "Employee assigned as manager successfully.\n";
                }

            }
            break;

        case 14:
            cout << "Note: An employee can only become the Delivery Driver of the restaurant he currently works at.\n";
            admin.printEmployee(CH);
            cout << "Enter the name of Employee: ";

            cin >> name2;


            employee = CH.getEmployeeByName(name2);
            if (employee == nullptr) {
                cout << "No such Employee found.\n";
            }
            else {
                if (employee->restaurant == nullptr) {
                    cout << "Employee/Driver is not assigned to any restaurant.\n";
                }
                else {
                    employee->restaurant->DeliveryDriver = employee;
                    cout << "Employee assigned as Delivery Driver of that resturant succesfully successfully.\n";
                }

            }
            break;
        case 15:
            resetTextColor();
            return;

        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}


//---------------------------Main Menu----------------------------------


void CustomerMenu(RestaurantLinklist& restaurantList, ReviewHeap& reviewHeap, Customer* customer1) {
    setTextColor("red");
    cout << "  _____          _                              __  __                   \n";
    cout << "  / ____|        | |                            |  \\/  |                  \n";
    cout << " | |    _   _ ___| |_ ___  _ __ ___   ___ _ __  | \\  / | ___ _ __  _   _ \n";
    cout << " | |   | | | / __| __/ _ \\| '_ ` _ \\ / _ \\ '__| | |\\/| |/ _ \\ '_ \\| | | |\n";
    cout << " | |___| |_| \\__ \\ || (_) | | | | | |  __/ |    | |  | |  __/ | | | |_| |\n";
    cout << "  \\_____\\__,_|___/\\__\\___/|_| |_| |_|\\___|_|    |_|  |_|\\___|_| |_|\\__,_|\n";
    cout << "                                                                         \n";
    cout << "\nWelcome, " << customer1->getName() << "!\n";
    resetTextColor();
    // Main interaction loop
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a review\n";
        cout << "2. Place an order\n";
        cout << "3. View order history\n";
        cout << "4. View review history\n";
        cout << "5. Customize account\n";
        cout << "6. Display top reviews\n";
        cout << "7. Edit review\n";
        cout << "8. Delete review\n";
        cout << "9. Display reviews of restaurant\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        getIntegerInput(choice);

        switch (choice) {
        case 1:
            customer1->addReview(restaurantList, reviewHeap);
            break;

        case 2:
            customer1->addOrder(restaurantList);
            break;

        case 3:
            customer1->displayOrderHistory();
            break;

        case 4:
            customer1->DisplayReviewHistory();
            break;

        case 5:
            customer1->Customize();
            break;

        case 6: {
            cout << "1. Good Reviews (4-5 stars)\n";
            cout << "2. Bad Reviews (1-3 stars)\n";
            int reviewChoice;
            cin >> reviewChoice;
            reviewHeap.displayTopReviews(reviewChoice == 1);
            break;
        }
        case 7:
            customer1->editReview(reviewHeap);
            break;
        case 8:
            customer1->deleteReview(reviewHeap);
            break;
        case 9:
            reviewHeap.displayRestaurantViews();
            break;
        case 10:
            cout << "Exiting the program. Thank you!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return;
}




// Function to map vertex names to matrix indices
int stringToIndex(const string& vertex) {
    if (vertex == "F-5") return 0;
    if (vertex == "F-6") return 1;
    if (vertex == "F-7") return 2;
    if (vertex == "F-8") return 3;
    if (vertex == "F-9") return 4;
    if (vertex == "F-10") return 5;
    if (vertex == "F-11") return 6;
    if (vertex == "F-12") return 7;
    if (vertex == "G-5") return 8;
    if (vertex == "G-6") return 9;
    if (vertex == "G-7") return 10;
    if (vertex == "G-8") return 11;
    if (vertex == "G-9") return 12;
    if (vertex == "G-10") return 13;
    if (vertex == "G-11") return 14;
    if (vertex == "G-12") return 15;
    if (vertex == "G-13") return 16;
    if (vertex == "G-14") return 17;
    if (vertex == "H-5") return 18;
    if (vertex == "H-6") return 19;
    if (vertex == "H-7") return 20;
    if (vertex == "H-8") return 21;
    if (vertex == "H-9") return 22;
    if (vertex == "H-10") return 23;
    if (vertex == "H-11") return 24;
    if (vertex == "H-12") return 25;
    if (vertex == "I-5") return 26;
    if (vertex == "I-6") return 27;
    if (vertex == "I-7") return 28;
    if (vertex == "I-8") return 29;
    if (vertex == "I-9") return 30;
    if (vertex == "I-10") return 31;
    if (vertex == "I-11") return 32;
    if (vertex == "I-12") return 33;
    if (vertex == "I-13") return 34;
    if (vertex == "I-14") return 35;
    if (vertex == "I-15") return 36;
    if (vertex == "I-16") return 37;

    return 9;
    
}

string indexToString(int index) {
    // Define the vertex names as per the index
    string vertices[] = {
        "F-5", "F-6", "F-7", "F-8", "F-9", "F-10", "F-11", "F-12",
        "G-5", "G-6", "G-7", "G-8", "G-9", "G-10", "G-11", "G-12",
        "G-13", "G-14", "H-5", "H-6", "H-7", "H-8", "H-9", "H-10",
        "H-11", "H-12", "I-5", "I-6", "I-7", "I-8", "I-9", "I-10",
        "I-11", "I-12", "I-13", "I-14", "I-15", "I-16"
    };

    if (index >= 0 && index < 38) {
        return vertices[index];  // Return the vertex name for valid index
    }
    return "";  // Return empty string for invalid index
}

// Function to initialize the adjacency matrix
void initializeAdjMatrix(int adjMatrix[38][38]) {
    // Hardcode the matrix values based on the edges and weights
    for (int n = 0; n < 38; n++) {
        for (int m = 0; m < 38; m++) {
            adjMatrix[n][m] = INT_MAX;
        }
    }


    adjMatrix[stringToIndex("F-12")][stringToIndex("G-6")] = 12;
    adjMatrix[stringToIndex("G-6")][stringToIndex("F-12")] = 12;  // Since the graph is undirected

    adjMatrix[stringToIndex("G-12")][stringToIndex("H-9")] = 8;
    adjMatrix[stringToIndex("H-9")][stringToIndex("G-12")] = 8;

    adjMatrix[stringToIndex("G-8")][stringToIndex("F-12")] = 7;
    adjMatrix[stringToIndex("F-12")][stringToIndex("G-8")] = 7;

    adjMatrix[stringToIndex("F-9")][stringToIndex("I-8")] = 11;
    adjMatrix[stringToIndex("I-8")][stringToIndex("F-9")] = 11;

    adjMatrix[stringToIndex("G-6")][stringToIndex("F-9")] = 6;
    adjMatrix[stringToIndex("F-9")][stringToIndex("G-6")] = 6;

    adjMatrix[stringToIndex("H-8")][stringToIndex("I-10")] = 2;
    adjMatrix[stringToIndex("I-10")][stringToIndex("H-8")] = 2;

    adjMatrix[stringToIndex("F-11")][stringToIndex("H-9")] = 5;
    adjMatrix[stringToIndex("H-9")][stringToIndex("F-11")] = 5;

    adjMatrix[stringToIndex("F-5")][stringToIndex("F-8")] = 15;
    adjMatrix[stringToIndex("F-8")][stringToIndex("F-5")] = 15;

    adjMatrix[stringToIndex("I-11")][stringToIndex("I-9")] = 7;
    adjMatrix[stringToIndex("I-9")][stringToIndex("I-11")] = 7;

    adjMatrix[stringToIndex("F-12")][stringToIndex("F-6")] = 13;
    adjMatrix[stringToIndex("F-6")][stringToIndex("F-12")] = 13;

    adjMatrix[stringToIndex("H-11")][stringToIndex("G-7")] = 1;
    adjMatrix[stringToIndex("G-7")][stringToIndex("H-11")] = 1;

    adjMatrix[stringToIndex("I-15")][stringToIndex("G-12")] = 3;
    adjMatrix[stringToIndex("G-12")][stringToIndex("I-15")] = 3;

    adjMatrix[stringToIndex("I-12")][stringToIndex("H-8")] = 9;
    adjMatrix[stringToIndex("H-8")][stringToIndex("I-12")] = 9;

    adjMatrix[stringToIndex("I-14")][stringToIndex("G-6")] = 2;
    adjMatrix[stringToIndex("G-6")][stringToIndex("I-14")] = 2;

    adjMatrix[stringToIndex("I-12")][stringToIndex("I-9")] = 8;
    adjMatrix[stringToIndex("I-9")][stringToIndex("I-12")] = 8;

    adjMatrix[stringToIndex("F-12")][stringToIndex("I-16")] = 10;
    adjMatrix[stringToIndex("I-16")][stringToIndex("F-12")] = 10;

    adjMatrix[stringToIndex("F-9")][stringToIndex("F-12")] = 9;
    adjMatrix[stringToIndex("F-12")][stringToIndex("F-9")] = 9;

    adjMatrix[stringToIndex("F-11")][stringToIndex("G-9")] = 10;
    adjMatrix[stringToIndex("G-9")][stringToIndex("F-11")] = 10;

    adjMatrix[stringToIndex("I-14")][stringToIndex("G-11")] = 1;
    adjMatrix[stringToIndex("G-11")][stringToIndex("I-14")] = 1;

    adjMatrix[stringToIndex("F-7")][stringToIndex("G-9")] = 15;
    adjMatrix[stringToIndex("G-9")][stringToIndex("F-7")] = 15;

    adjMatrix[stringToIndex("I-9")][stringToIndex("H-10")] = 4;
    adjMatrix[stringToIndex("H-10")][stringToIndex("I-9")] = 4;

    adjMatrix[stringToIndex("I-16")][stringToIndex("G-14")] = 2;
    adjMatrix[stringToIndex("G-14")][stringToIndex("I-16")] = 2;

    adjMatrix[stringToIndex("F-6")][stringToIndex("I-15")] = 8;
    adjMatrix[stringToIndex("I-15")][stringToIndex("F-6")] = 8;

    adjMatrix[stringToIndex("F-12")][stringToIndex("I-14")] = 13;
    adjMatrix[stringToIndex("I-14")][stringToIndex("F-12")] = 13;

    adjMatrix[stringToIndex("F-9")][stringToIndex("H-11")] = 10;
    adjMatrix[stringToIndex("H-11")][stringToIndex("F-9")] = 10;

    adjMatrix[stringToIndex("H-10")][stringToIndex("I-10")] = 5;
    adjMatrix[stringToIndex("I-10")][stringToIndex("H-10")] = 5;

    adjMatrix[stringToIndex("G-14")][stringToIndex("G-12")] = 14;
    adjMatrix[stringToIndex("G-12")][stringToIndex("G-14")] = 14;

    adjMatrix[stringToIndex("H-11")][stringToIndex("G-13")] = 1;
    adjMatrix[stringToIndex("G-13")][stringToIndex("H-11")] = 1;

    adjMatrix[stringToIndex("I-12")][stringToIndex("I-15")] = 6;
    adjMatrix[stringToIndex("I-15")][stringToIndex("I-12")] = 6;

    adjMatrix[stringToIndex("F-9")][stringToIndex("G-10")] = 3;
    adjMatrix[stringToIndex("G-10")][stringToIndex("F-9")] = 3;

    adjMatrix[stringToIndex("F-5")][stringToIndex("F-10")] = 2;
    adjMatrix[stringToIndex("F-10")][stringToIndex("F-5")] = 2;

    adjMatrix[stringToIndex("G-9")][stringToIndex("G-14")] = 12;
    adjMatrix[stringToIndex("G-14")][stringToIndex("G-9")] = 12;

    adjMatrix[stringToIndex("I-9")][stringToIndex("F-11")] = 14;
    adjMatrix[stringToIndex("F-11")][stringToIndex("I-9")] = 14;

    adjMatrix[stringToIndex("I-16")][stringToIndex("F-7")] = 5;
    adjMatrix[stringToIndex("F-7")][stringToIndex("I-16")] = 5;

    adjMatrix[stringToIndex("F-9")][stringToIndex("I-11")] = 8;
    adjMatrix[stringToIndex("I-11")][stringToIndex("F-9")] = 8;

    adjMatrix[stringToIndex("H-9")][stringToIndex("G-7")] = 2;
    adjMatrix[stringToIndex("G-7")][stringToIndex("H-9")] = 2;

    adjMatrix[stringToIndex("I-8")][stringToIndex("G-11")] = 10;
    adjMatrix[stringToIndex("G-11")][stringToIndex("I-8")] = 10;

    adjMatrix[stringToIndex("H-11")][stringToIndex("I-12")] = 9;
    adjMatrix[stringToIndex("I-12")][stringToIndex("H-11")] = 9;

    adjMatrix[stringToIndex("G-12")][stringToIndex("F-8")] = 4;
    adjMatrix[stringToIndex("F-8")][stringToIndex("G-12")] = 4;

    adjMatrix[stringToIndex("F-10")][stringToIndex("F-7")] = 6;
    adjMatrix[stringToIndex("F-7")][stringToIndex("F-10")] = 6;

    adjMatrix[stringToIndex("F-5")][stringToIndex("I-16")] = 7;
    adjMatrix[stringToIndex("I-16")][stringToIndex("F-5")] = 7;

    adjMatrix[stringToIndex("H-8")][stringToIndex("I-16")] = 13;
    adjMatrix[stringToIndex("I-16")][stringToIndex("H-8")] = 13;

    adjMatrix[stringToIndex("H-9")][stringToIndex("G-8")] = 6;
    adjMatrix[stringToIndex("G-8")][stringToIndex("H-9")] = 6;

    adjMatrix[stringToIndex("I-11")][stringToIndex("F-8")] = 4;
    adjMatrix[stringToIndex("F-8")][stringToIndex("I-11")] = 4;

    adjMatrix[stringToIndex("I-12")][stringToIndex("G-12")] = 15;
    adjMatrix[stringToIndex("G-12")][stringToIndex("I-12")] = 15;

    adjMatrix[stringToIndex("F-6")][stringToIndex("I-9")] = 3;
    adjMatrix[stringToIndex("I-9")][stringToIndex("F-6")] = 3;

    adjMatrix[stringToIndex("I-14")][stringToIndex("I-12")] = 8;
    adjMatrix[stringToIndex("I-12")][stringToIndex("I-14")] = 8;

    adjMatrix[stringToIndex("F-11")][stringToIndex("G-5")] = 1;
    adjMatrix[stringToIndex("G-5")][stringToIndex("F-11")] = 1;

    adjMatrix[stringToIndex("G-8")][stringToIndex("I-9")] = 5;
    adjMatrix[stringToIndex("I-9")][stringToIndex("G-8")] = 5;

    adjMatrix[stringToIndex("H-8")][stringToIndex("G-5")] = 11;
    adjMatrix[stringToIndex("G-5")][stringToIndex("H-8")] = 11;

    adjMatrix[stringToIndex("F-10")][stringToIndex("F-11")] = 6;
    adjMatrix[stringToIndex("F-11")][stringToIndex("F-10")] = 6;

    adjMatrix[stringToIndex("G-10")][stringToIndex("F-12")] = 5;
    adjMatrix[stringToIndex("F-12")][stringToIndex("G-10")] = 5;

    adjMatrix[stringToIndex("G-9")][stringToIndex("H-11")] = 7;
    adjMatrix[stringToIndex("H-11")][stringToIndex("G-9")] = 7;

    adjMatrix[stringToIndex("H-9")][stringToIndex("F-9")] = 11;
    adjMatrix[stringToIndex("F-9")][stringToIndex("H-9")] = 11;

    adjMatrix[stringToIndex("F-12")][stringToIndex("F-5")] = 2;
    adjMatrix[stringToIndex("F-5")][stringToIndex("F-12")] = 2;

    adjMatrix[stringToIndex("F-6")][stringToIndex("I-12")] = 9;
    adjMatrix[stringToIndex("I-12")][stringToIndex("F-6")] = 9;

    adjMatrix[stringToIndex("I-15")][stringToIndex("F-12")] = 14;
    adjMatrix[stringToIndex("F-12")][stringToIndex("I-15")] = 14;

    adjMatrix[stringToIndex("G-5")][stringToIndex("I-14")] = 12;
    adjMatrix[stringToIndex("I-14")][stringToIndex("G-5")] = 12;

    adjMatrix[stringToIndex("F-9")][stringToIndex("G-6")] = 15;
    adjMatrix[stringToIndex("G-6")][stringToIndex("F-9")] = 15;

    adjMatrix[stringToIndex("I-15")][stringToIndex("F-9")] = 7;
    adjMatrix[stringToIndex("F-9")][stringToIndex("I-15")] = 7;

    adjMatrix[stringToIndex("G-8")][stringToIndex("G-7")] = 2;
    adjMatrix[stringToIndex("G-7")][stringToIndex("G-8")] = 2;

    adjMatrix[stringToIndex("F-12")][stringToIndex("F-6")] = 14;
    adjMatrix[stringToIndex("F-6")][stringToIndex("F-12")] = 14;

    adjMatrix[stringToIndex("H-9")][stringToIndex("I-8")] = 3;
    adjMatrix[stringToIndex("I-8")][stringToIndex("H-9")] = 3;

    adjMatrix[stringToIndex("G-10")][stringToIndex("F-11")] = 1;
    adjMatrix[stringToIndex("F-11")][stringToIndex("G-10")] = 1;

    adjMatrix[stringToIndex("I-8")][stringToIndex("I-15")] = 2;
    adjMatrix[stringToIndex("I-15")][stringToIndex("I-8")] = 2;

    adjMatrix[stringToIndex("F-9")][stringToIndex("I-16")] = 9;
    adjMatrix[stringToIndex("I-16")][stringToIndex("F-9")] = 9;

    adjMatrix[stringToIndex("H-9")][stringToIndex("I-10")] = 3;
    adjMatrix[stringToIndex("I-10")][stringToIndex("H-9")] = 3;

    adjMatrix[stringToIndex("H-8")][stringToIndex("G-11")] = 6;
    adjMatrix[stringToIndex("G-11")][stringToIndex("H-8")] = 6;

    adjMatrix[stringToIndex("H-11")][stringToIndex("G-12")] = 4;
    adjMatrix[stringToIndex("G-12")][stringToIndex("H-11")] = 4;

    adjMatrix[stringToIndex("I-9")][stringToIndex("G-12")] = 7;
    adjMatrix[stringToIndex("G-12")][stringToIndex("I-9")] = 7;

    adjMatrix[stringToIndex("I-8")][stringToIndex("G-8")] = 10;
    adjMatrix[stringToIndex("G-8")][stringToIndex("I-8")] = 10;

    adjMatrix[stringToIndex("H-10")][stringToIndex("I-8")] = 5;
    adjMatrix[stringToIndex("I-8")][stringToIndex("H-10")] = 5;

    adjMatrix[stringToIndex("G-12")][stringToIndex("I-11")] = 12;
    adjMatrix[stringToIndex("I-11")][stringToIndex("G-12")] = 12;

    adjMatrix[stringToIndex("I-10")][stringToIndex("F-5")] = 15;
    adjMatrix[stringToIndex("F-5")][stringToIndex("I-10")] = 15;

    adjMatrix[stringToIndex("F-10")][stringToIndex("G-10")] = 13;
    adjMatrix[stringToIndex("G-10")][stringToIndex("F-10")] = 13;

    adjMatrix[stringToIndex("F-6")][stringToIndex("F-12")] = 1;
    adjMatrix[stringToIndex("F-12")][stringToIndex("F-6")] = 1;

    adjMatrix[stringToIndex("I-14")][stringToIndex("H-11")] = 2;
    adjMatrix[stringToIndex("H-11")][stringToIndex("I-14")] = 2;

    adjMatrix[stringToIndex("G-11")][stringToIndex("F-10")] = 5;
    adjMatrix[stringToIndex("F-10")][stringToIndex("G-11")] = 5;

    adjMatrix[stringToIndex("I-10")][stringToIndex("I-16")] = 14;
    adjMatrix[stringToIndex("I-16")][stringToIndex("I-10")] = 14;

    adjMatrix[stringToIndex("F-10")][stringToIndex("F-6")] = 3;
    adjMatrix[stringToIndex("F-6")][stringToIndex("F-10")] = 3;

    adjMatrix[stringToIndex("F-12")][stringToIndex("F-8")] = 6;
    adjMatrix[stringToIndex("F-8")][stringToIndex("F-12")] = 6;

    adjMatrix[stringToIndex("F-8")][stringToIndex("F-6")] = 7;
    adjMatrix[stringToIndex("F-6")][stringToIndex("F-8")] = 7;

    adjMatrix[stringToIndex("G-9")][stringToIndex("F-11")] = 11;
    adjMatrix[stringToIndex("F-11")][stringToIndex("G-9")] = 11;

    adjMatrix[stringToIndex("F-6")][stringToIndex("H-9")] = 12;
    adjMatrix[stringToIndex("H-9")][stringToIndex("F-6")] = 12;

    adjMatrix[stringToIndex("F-8")][stringToIndex("G-9")] = 4;
    adjMatrix[stringToIndex("G-9")][stringToIndex("F-8")] = 4;

    adjMatrix[stringToIndex("F-12")][stringToIndex("H-11")] = 3;
    adjMatrix[stringToIndex("H-11")][stringToIndex("F-12")] = 3;

    adjMatrix[stringToIndex("H-11")][stringToIndex("I-15")] = 5;
    adjMatrix[stringToIndex("I-15")][stringToIndex("H-11")] = 5;

    adjMatrix[stringToIndex("I-12")][stringToIndex("G-14")] = 8;
    adjMatrix[stringToIndex("G-14")][stringToIndex("I-12")] = 8;

    adjMatrix[stringToIndex("G-6")][stringToIndex("F-9")] = 10;
    adjMatrix[stringToIndex("F-9")][stringToIndex("G-6")] = 10;

    adjMatrix[stringToIndex("I-9")][stringToIndex("G-11")] = 9;
    adjMatrix[stringToIndex("G-11")][stringToIndex("I-9")] = 9;
}


void djikstra(int source, int adjacencyMatrix[38][38], int numVertices, int* weights, bool* visited, string* path) {
    // Initialize arrays
    for (int i = 0; i < numVertices; i++) {
        weights[i] = INT_MAX;
        visited[i] = false;
        path[i] = "";
    }
    weights[source] = 0;
    path[source] = indexToString(source);

    // Dijkstra's algorithm
    for (int count = 0; count < numVertices; count++) {
        int minWeight = INT_MAX;
        int u = -1;

        // Find the unvisited vertex with the smallest weight
        for (int i = 0; i < numVertices; i++) {

            if (!visited[i] && weights[i] < minWeight) {
                minWeight = weights[i];
                u = i;
            }
        }

        if (u == -1) break;  // No more vertices to visit

        visited[u] = true;

        // Update the weights of the neighboring vertices
        for (int v = 0; v < numVertices; v++) {
            if (adjacencyMatrix[u][v] != INT_MAX && !visited[v]) {
                int newWeight = weights[u] + adjacencyMatrix[u][v];
                if (newWeight < weights[v]) {
                    weights[v] = newWeight;
                    path[v] = path[u] + " -> " + indexToString(v);  // Store the path to the vertex
                }
            }
        }
    }
}

void findShortestPath(int source, int* locations, int numLocations, int adjacencyMatrix[38][38], int numVertices) {
    int* weights = new int[numVertices];      // Dynamic array for storing weights (distances)
    bool* visited = new bool[numVertices];    // Dynamic array for visited flags
    string* path = new string[numVertices];   // Dynamic array for storing paths
    int originalSource = source;
    int* remainingLocations = new int[numLocations];  // Copy of locations for processing
    for (int i = 0; i < numLocations; i++) {
        remainingLocations[i] = locations[i];
    }

    // Loop until all locations are processed
    while (numLocations > 0) {
        // Run Dijkstra's algorithm for the current source
        djikstra(source, adjacencyMatrix, numVertices, weights, visited, path);

        // Find the location with the minimum distance from the source
        int minDist = INT_MAX;
        int nextSource = -1;
        int targetLocation = -1;

        for (int i = 0; i < numLocations; i++) {
            int loc = remainingLocations[i];
            if (weights[loc] <= minDist) {
                minDist = weights[loc];
                targetLocation = loc;
                nextSource = loc;
            }
        }

        // Output the shortest path to the target location
        if (targetLocation != -1) {
            if (minDist != INT_MAX) {
                // A path exists
                cout << "Shortest path from " << indexToString(source) << " to " << indexToString(targetLocation) << ": "
                    << path[targetLocation] << " with distance " << minDist << endl;
                source = nextSource;  // Update source to the target location
            }
            else {
                // No path exists for the current target location
                cout << "No path exists from " << indexToString(source) << " to " << indexToString(targetLocation) << endl;
                // Do not update source, just move to the next location
            }

            // Remove the selected location from the remaining locations array by shifting
            for (int i = 0; i < numLocations; i++) {
                if (remainingLocations[i] == targetLocation) {
                    for (int j = i; j < numLocations - 1; j++) {
                        remainingLocations[j] = remainingLocations[j + 1];
                    }
                    numLocations--;  // Decrease the count of remaining locations
                    break;
                }
            }
        }
    }

    // Clean up dynamically allocated memory
    delete[] weights;
    delete[] visited;
    delete[] path;
    delete[] remainingLocations;
}

int totalOrders(ProcessedOrders* order) {
    if (order == nullptr) {
        return 0;
    }
    int n = 0;
    ProcessedOrders* current = order;
    while (current) {
        n++;
        current = current->next;
    }
    return n;
}

int* OrdertoArray(ProcessedOrders* order, int*& arr) {
    arr = new int[totalOrders(order)];
    ProcessedOrders* curr = order;
    for (int n = 0; n < totalOrders(order); n++) {
        arr[n] = stringToIndex(curr->order->Location);
        curr = curr->next;
    }

    return arr;
}

void removeDuplicates(int arr[], int& size) {
    if (size == 0) return;

    // Sort the array first
    sort(arr, arr + size);

    // New index for placing unique elements
    int newSize = 1;

    // Traverse through the array and compare each element with the previous one
    for (int i = 1; i < size; ++i) {
        if (arr[i] != arr[i - 1]) {
            arr[newSize++] = arr[i];
        }
    }

    // Update the size of the array
    size = newSize;
}

void DeliverOrders(ProcessedOrders* order, Employee* employee) {
    if (order == nullptr) {
        cout << "No orders to deliver\n";
    }

    int source = stringToIndex(employee->restaurant->Location);  // Index of "F-8"
    //int locations[] = { 2, 14 };  // Indices of "F-7" and "G-11"

    int numLocations = totalOrders(order);
    int* locations;
    locations = OrdertoArray(order, locations);
    removeDuplicates(locations, numLocations);


    int adjacencyMatrix[38][38];
    initializeAdjMatrix(adjacencyMatrix);
    findShortestPath(source, locations, numLocations, adjacencyMatrix, 38);
}











void employeeMenu(Employee* currentEmployee, ReviewHeap& reviewHeap, PromotionStack& PS, Admin& admin, EmployeeHashmap& EH) {
    setTextColor("red");
    cout << "  ______                 _                         __  __                   \n";
    cout << " |  ____|               | |                       |  \\/  |                  \n";
    cout << " | |__   _ __ ___  _ __ | | ___  _   _  ___  ___  | \\  / | ___ _ __  _   _ \n";
    cout << " |  __| | '_ ` _ \\| '_ \\| |/ _ \\| | | |/ _ \\/ _ \\ | |\\/| |/ _ \\ '_ \\| | | |\n";
    cout << " | |____| | | | | | |_) | | (_) | |_| |  __/  __/ | |  | |  __/ | | | |_| |\n";
    cout << " |______|_| |_| |_| .__/|_|\\___/ \\__, |\\___|\\___| |_|  |_|\\___|_| |_|\\__,_|\n";
    cout << "                  | |             __/ |                                    \n";
    cout << "                  |_|            |___/                                     \n";
    cout << endl;
    int choice = -1;
    resetTextColor();
    if (currentEmployee->restaurant->manager != nullptr) {
        cout << "You are an Manger " << endl;
    }
    else if (currentEmployee->restaurant->DeliveryDriver != nullptr) {
        cout << "You are an Delivery Driver ";
    }
    while (choice != 0) {
        cout << "\n--- Employee Menu ---\n";
        cout << "1. Change Account Details\n";
        cout << "2. View Reviews for Restaurant\n";
        cout << "3. View Orders\n";
        cout << "4. Process Orders\n";
        cout << "----------------Manager only features---------------\n";
        cout << "5. Add Menu\n";
        cout << "6. Add Dish\n";
        cout << "7. Update Dish\n";
        cout << "8. View Processed Orders\n";
        cout << "9. Add employee to restaurant\n";
        cout << "----------------Deliveryman only features---------------\n";
        cout << "10. Deliver Orders\n";
        cout << "0. Log Out\n";
        cout << "Enter your choice: ";

        getIntegerInput(choice);
        switch (choice) {
        case 1:
            currentEmployee->changeAccountDetails();
            break;

        case 2:
            // View reviews for the restaurant

            reviewHeap.displayRestaurantViews();
            break;

        case 3:
            if ((currentEmployee->restaurant) != nullptr) {
                currentEmployee->restaurant->orders.DisplayAllOrders();
            }
            else {
                cout << "Employee is not assigned to a restaurant.\n";
            }
            break;

        case 4:
            if (currentEmployee->restaurant != nullptr) {
                processOrders(PS, currentEmployee->restaurant->orders, currentEmployee);
            }
            else {
                cout << "Employee is not assigned to a restaurant.\n";
            }
            break;
        case 5:
            currentEmployee->addMenuToRestaurant();
            break;
        case 6:
            currentEmployee->addDishToMenu();
            break;
        case 7:
            currentEmployee->updateDish();
            break;
        case 8:
            currentEmployee->displayProcessedOrders();
            break;
        case 9:
            if (currentEmployee->restaurant != nullptr && currentEmployee->restaurant->manager == currentEmployee) {
                admin.addEmployee(EH, currentEmployee->restaurant);
            }
            else {
                if (!currentEmployee->restaurant) {
                    cout << "Employee not assigned to any restaurant\n";
                }
                else {
                    cout << "Employee is not a manager.\n";
                }
            }
            break;
        case 10:
            if (currentEmployee->restaurant->DeliveryDriver != nullptr) {

                int num;
                num = totalOrders(currentEmployee->processedOrder);
                if (num == 0) {
                    cout << "No orders to deliver\n";
                    continue;
                }

                currentEmployee->displayProcessedOrders();

                int toProcess;
                cout << "Enter the number of orders you want to process: ";
                getIntegerInput(toProcess);

                while (toProcess <= 0 || toProcess > num) {
                    cout << "Enter again: ";
                    cin >> toProcess;
                }
                if (toProcess == num) {
                    cout << "Delivering The processed Orders ";
                    DeliverOrders(currentEmployee->processedOrder, currentEmployee);
                    currentEmployee->processedOrder = nullptr;
                    break;

                }

                ProcessedOrders* head = currentEmployee->processedOrder;
                ProcessedOrders* last = nullptr;
                ProcessedOrders* current = currentEmployee->processedOrder;

                // Traverse to the (toProcess)th order
                while (toProcess > 0 && current != nullptr) {
                    last = current;
                    current = current->next;
                    toProcess--;
                }

                // Disconnect the processed orders from the rest of the list
                if (last != nullptr) {
                    last->next = nullptr;  // Last processed order should point to null
                }

                cout << "Delivering The processed Orders ";
                DeliverOrders(head, currentEmployee);

                // After delivery, set the processedOrder to the next set of orders
                currentEmployee->processedOrder = current;
            }

            break;
        case 0:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }
}






void populateOrders(Customer* customer, RestaurantLinklist& restaurantList) {
    // Retrieve the restaurant
    RestaurantNode* restaurant = restaurantList.findRestaurant("PizzaPalace");
    if (restaurant == nullptr || restaurant->menu == nullptr) {
        cout << "Restaurant or menu not found for populating orders.\n";
        return;
    }

    // Array of example locations and priorities
    string locations[] = { "I-8", "F-8", "G-6", "H-10", "E-11" };
    int priorities[] = { 5, 3, 1, 3, 5 }; // Premium, Express, Normal, Express, Premium

    // Add five orders
    for (int i = 0; i < 5; i++) {
        // Create a new order
        Order* order = new Order(0.0f, priorities[i], customer);
        order->Ordertype = (priorities[i] == 5) ? "Premium" : (priorities[i] == 3) ? "Express" : "Normal";
        order->Location = locations[i];

        // Add dishes to the order
        Dish* dish1 = restaurant->menu->getDishByNameRecursion(restaurant->menu->root, "Pizza(Beef)");
        if (dish1) {
            DishHolder* dishHolder1 = new DishHolder(dish1);
            order->dishHolder = dishHolder1;

            Dish* dish2 = restaurant->menu->getDishByNameRecursion(restaurant->menu->root, "Pizza(Chicken)");
            if (dish2) {
                DishHolder* dishHolder2 = new DishHolder(dish2);
                dishHolder1->next = dishHolder2;
            }
        }

        // Calculate the total price for the order
        float total = 0;
        for (DishHolder* temp = order->dishHolder; temp != nullptr; temp = temp->next) {
            total += temp->dish->Price;
        }
        order->total = total;

        // Link the order to the customer's order history
        order->history = customer->orderhistory;
        customer->orderhistory = order;

        // Add the order to the restaurant's order list
        restaurant->orders.addOrder(order);

        cout << "Order " << i + 1 << " added: Location = " << locations[i]
            << ", Priority = " << priorities[i]
            << ", Total = " << total << endl;
    }

    cout << "5 orders populated for the customer.\n";
}




int main()
{
    RestaurantLinklist restaurantList;
    ReviewHeap reviewHeap;
    EmployeeHashmap employeehashmap;
    employeehashmap.employee[0] = new Employee("hassan", "Hassan@2003", "hassan@gmail.com");
    employeehashmap.employee[1] = new Employee("hamas", "Hamas@2003", "hamas@gmail.com");
    employeehashmap.employee[2] = new Employee("Deliveryguy", "delivery@2003", "delivery@gmail.com");

    CustomerHashmap customerhashmap;
    customerhashmap.customerArray[0] = new Customer("Naveed", "Naveed@2003", "Naveed@gmail.com"); //this is placing the orders
    customerhashmap.customerArray[1] = new Customer("Qureshi", "Qureshi@2003", "qureshi@gmail.com");

    // Prepopulate restaurant and menu details
    restaurantList.addRestaurant("PizzaPalace", "Fast Food", "G-6");
    restaurantList.addRestaurant("CafeDelight", "Cafe", "G-8");
    restaurantList.addRestaurant("ChinaTown", "Chinese", "G-10");
    restaurantList.findRestaurant("PizzaPalace")->menu = new Menu("Italian Deluxe");
    restaurantList.findRestaurant("CafeDelight")->menu = new Menu("Cafe Delight");
    restaurantList.findRestaurant("ChinaTown")->menu = new Menu("Chinese Food");

    restaurantList.findRestaurant("PizzaPalace")->menu->root = new Dish("Pizza(Beef)", "Italian", 150.99);
    restaurantList.findRestaurant("PizzaPalace")->menu->root->left = new Dish("Pizza(Chicken)", "Italian", 140.99);
    restaurantList.findRestaurant("PizzaPalace")->menu->root->right= new Dish("Pizza(BBQ)", "Italian", 160.59);
    restaurantList.findRestaurant("PizzaPalace")->menu->root->left->left = new Dish("Pizza(Cheesy)", "Italian", 110.59);
    restaurantList.findRestaurant("PizzaPalace")->menu->root->left->right = new Dish("Pizza(Spicy)", "Italian", 120.59);


    restaurantList.findRestaurant("ChinaTown")->menu->root = new Dish("Pizza", "Junkies", 12.99);

    employeehashmap.employee[1]->restaurant = restaurantList.findRestaurant("ChinaTown");
    employeehashmap.employee[0]->restaurant = restaurantList.findRestaurant("PizzaPalace");
    employeehashmap.employee[2]->restaurant = restaurantList.findRestaurant("PizzaPalace");
    employeehashmap.employee[2]->restaurant->DeliveryDriver = employeehashmap.employee[2];// assigning 2 as the delivery guy of pizzaplace 
    employeehashmap.employee[1]->restaurant->DeliveryDriver = employeehashmap.employee[1];// assigning 2 as the delivery guy of pizzaplace 
    PromotionStack promotionStack;
    promotionStack.push(Promotion{ "Black Friday", 50.0, 5 });



    //populateOrders(customerhashmap.customerArray[0], restaurantList);

    // Admin Details
    Admin admin("admin", "admin123", "admin@example.com");

    // Display welcome message
    system("cls");
    cout << "  _____           _                              _     _    _       _     \n";
    cout << " |  __ \\         | |                            | |   | |  | |     | |    \n";
    cout << " | |__) |___  ___| |_ __ _ _   _ _ __ __ _ _ __ | |_  | |__| |_   _| |__  \n";
    cout << " |  _  // _ \\/ __| __/ _` | | | | '__/ _` | '_ \\| __| |  __  | | | | '_ \\ \n";
    cout << " | | \\ \\  __/\\__ \\ || (_| | |_| | | | (_| | | | | |_  | |  | | |_| | |_) |\n";
    cout << " |_|  \\_\\___||___/\\__\\__,_|\\__,_|_|  \\__,_|_| |_|\\__| |_|  |_|\\__,_|_.__/ \n";

    while (true)
    {
        int loginChoice;
        setTextColor("blue");
        do
        {
            cout << "\n1) Log In\n2) Sign Up\n3) Exit\n";
            cin >> loginChoice;
        } while (loginChoice < 1 || loginChoice > 3);
        resetTextColor();
        if (loginChoice == 1)
        {
            // Login
            string email, password;
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Password: ";
            password = getPassword();

            // Check credentials
            if (admin.getemail() == email && admin.getpassword() == password)
            {
                cout << "Logged in as Admin\n";
                AdminMenu(restaurantList, employeehashmap, admin, promotionStack);
            }
            else if (Employee* employee = employeehashmap.searchByEmail(email))
            {
                if (employee->getPassword() == password)
                {
                    cout << "Logged in as Employee\n";
                    employeeMenu(employee, reviewHeap, promotionStack, admin, employeehashmap);
                }
                else
                {
                    cout << "Incorrect password\n";
                }
            }
            else if (Customer* customer = customerhashmap.LogIn(email, password))
            {
                cout << "Logged in as Customer\n";
                CustomerMenu(restaurantList, reviewHeap, customer);
            }
            else
            {
                cout << "No account found for the entered credentials.\n";
            }
        }
        else if (loginChoice == 2)
        {
            // Sign up
            Customer* newCustomer = Customer::makeCustomerAccount();
            customerhashmap.addCustomer(newCustomer);
            cout << "Account created successfully. You can now log in.\n";
        }
        else if (loginChoice == 3)
        {
            // Exit
            return 0;
        }
        else
        {
            cout << "Invalid input\n";
        }
    }
    return 0;
}
