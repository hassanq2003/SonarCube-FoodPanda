#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <conio.h>
#include <iomanip>
using namespace std;



struct Restaurant;
class Restaurant_Manage;
struct Order;
class Menu;
struct Dish;
class Orders;
class Promotion;
struct Customer;
struct Employee;
class HashMap;
class HashMapEmployee;
class ManageCustomer;
class ManageEmployee;




class Graph {
public:
    int numVertices;
    string* vertices;
    int** adjacencyMatrix;

    int getVertexIndex(const string& vertex) {
        for (int i = 0; i < numVertices; ++i) {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        return -1;
    }

public:

    Graph(int n) : numVertices(n) {
        vertices = new string[numVertices];
        adjacencyMatrix = new int* [numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjacencyMatrix[i] = new int[numVertices]();
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
        delete[] vertices;
    }

    void addVertex(int index, const string& vertex) {
        if (index >= 0 && index < numVertices) {
            vertices[index] = vertex;
        }
    }

    void addEdge(const string& from, const string& to, int weight) {
        int fromIndex = getVertexIndex(from);
        int toIndex = getVertexIndex(to);

        adjacencyMatrix[fromIndex][toIndex] = weight;
        adjacencyMatrix[toIndex][fromIndex] = weight; // For undirected graph

    }


    void printAdjacencyMatrix()
    {
        cout << "Adjacency Matrix:" << endl;

        // Print the top row with vertex names
        cout << setw(4) << " "; // Empty space for alignment
        for (int i = 0; i < numVertices; i++)
        {
            cout << setw(4) << vertices[i];
        }
        cout << endl;

        // Print the matrix
        for (int i = 0; i < numVertices; ++i)
        {
            cout << setw(4) << vertices[i]; // Row label
            for (int j = 0; j < numVertices; ++j)
            {
                cout << setw(4) << adjacencyMatrix[i][j]; // Matrix value
            }
            cout << endl;
        }
    }

};


void Print_Sector() {

    string vertices[] = {
      "F-5", "F-6", "F-7", "F-8", "F-9", "F-10", "F-11", "F-12",
      "G-5", "G-6", "G-7", "G-8", "G-9", "G-10", "G-11", "G-12",
      "G-13", "G-14", "H-7", "H-8", "H-9", "H-10",
      "H-11", "H-12", "I-8", "I-9", "I-10",
      "I-11", "I-12", "I-14", "I-15", "I-16"
    };


    cout << endl;
}






int Dj_Algo(Graph* G, string Src, string Dest, bool Print_Path) {

    if (G->numVertices <= 0) {
        cout << "No graph " << endl;
        return 0;
    }

    int Start = G->getVertexIndex(Src);
    int End = G->getVertexIndex(Dest);

    bool found = false, found_2 = false;

    for (int i = 0; i < G->numVertices; i++) {
        if (G->adjacencyMatrix[Start][i] != 0) {
            found = true;
        }
        if (G->adjacencyMatrix[End][i] != 0) {
            found_2 = true;
        }
    }

    if (Start == -1 || End == -1) {
        cout << "Invalid source or destination" << endl;
        return 0;
    }


    bool* Checker = new bool[G->numVertices];
    int* Distance = new int[G->numVertices];
    int* make_path = new int[G->numVertices];

    for (int i = 0; i < G->numVertices; i++)
    {
        Checker[i] = false;
        Distance[i] = INT_MAX;
        make_path[i] = -1;
    }

    Distance[Start] = 0;

    int index = Start;

    while (index != -1) {
        Checker[index] = true;

        for (int i = 0; i < G->numVertices; i++) {
            int W = G->adjacencyMatrix[index][i]; // Use index here instead of Start
            if (W == 0) {
                continue;
            }

            if (Distance[index] + W < Distance[i]) {
                Distance[i] = Distance[index] + W;
                make_path[i] = index;
            }
        }

        index = -1;
        int Min_value = INT_MAX;

        for (int i = 0; i < G->numVertices; i++) {
            if (!Checker[i] && Distance[i] < Min_value) {
                Min_value = Distance[i];
                index = i;
            }
        }
    }

    if (Distance[End] == INT_MAX) {
        if (Print_Path) {
            cout << "No path exists from " << Src << " to " << Dest << endl;
        }
        int p = Distance[End];
        delete[] Distance;
        delete[] Checker;
        delete[] make_path;
        return p;
    }


    if (Print_Path)
    {

        cout << "Minimum Road from " << Src << " to " << Dest << " is " << Distance[End] << endl;

        int Length = 0;
        int* Actual_Path = new int[G->numVertices];

        for (int i = End; i != -1; i = make_path[i])
        {
            Actual_Path[Length] = i;
            ++Length;
        }

        for (int i = Length - 1; i >= 0; i--)
        { // Print path in reverse order
            cout << G->vertices[Actual_Path[i]]; // Access the vertex name using its index
            if (i > 0) cout << " -> ";
        }
        cout << endl;

        delete[] Actual_Path;

    }
    int p = Distance[End];

    delete[] Distance;
    delete[] Checker;

    delete[] make_path;
    return p;
}











struct Dish
{
    static int ID;
    int Dishid = 0;
    string Name, Type;
    int Price = -1;
    Dish* left = nullptr, * right = nullptr;

    Dish(int Id = 0) {
        Dishid = ID;
        ++ID;
    }

    void Print_Dish() { cout << "Name: " << Name << ", Type: " << Type << ", Price: " << Price << endl; }
};

int Dish::ID = 10000;

Dish* Made_Dish(string N, string T, int M) {

    Dish* Temp = new Dish;
    if (!Temp) {
        cout << "Memory not found " << endl;
        return nullptr;
    }
    Temp->Name = N;
    Temp->Type = T;
    Temp->Price = M;
    Temp->left = nullptr;
    Temp->right = nullptr;
    return Temp;

}




class Menu {

    static int ID;
    int Total_Dishes;
    Dish* root;
    int Menuid;

public:
    Menu(Dish* R = nullptr, int T = 0, int I = 0) {
        root = nullptr;
        Menuid = ID;
        ++ID;
        Total_Dishes = T;

    }

    Dish* Get_Root() {
        return root;
    }

    void Add_Dish(string Name, string Type, int Price) {

        Dish* Temp = Made_Dish(Name, Type, Price);
        if (root == nullptr)
        {
            root = Temp;
            return;
        }

        queue<Dish*> D;
        D.push(root);

        while (!D.empty())
        {
            Dish* current = D.front();
            D.pop();


            if (current->left == nullptr) {
                current->left = Temp;
                return;
            }
            else
                D.push(current->left);



            if (current->right == nullptr) {
                current->right = Temp;
                return;
            }
            else
                D.push(current->right);

        }



    }




    void Remove_Dish(string Name, string Type)
    {
        if (root == nullptr) {
            cout << "No dish in the menu" << endl;
            return;
        }

        // Case when the root is the only dish
        if (root->left == nullptr && root->right == nullptr) {
            if (root->Name == Name && root->Type == Type) {
                delete root;
                root = nullptr;
            }
            else {
                cout << "Dish not found" << endl;
            }
            return;
        }

        queue<Dish*> q;
        q.push(root);
        Dish* temp = nullptr;
        Dish* Node_To_Delete = nullptr;

        while (!q.empty()) {
            temp = q.front();
            q.pop();

            // If we find the dish to be deleted, we mark it
            if (temp->Name == Name && temp->Type == Type) {
                Node_To_Delete = temp;
            }

            // Push the children of the current node to the queue
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }

        // If the node to delete is not found, return
        if (Node_To_Delete == nullptr) {
            cout << "Dish not found in the menu" << endl;
            return;
        }

        // Swap the data between nodeToDelete and temp (deepest rightmost node)
        if (Node_To_Delete != temp) {
            Node_To_Delete->Name = temp->Name;
            Node_To_Delete->Type = temp->Type;
            Node_To_Delete->Price = temp->Price;
        }

        // Now delete the deepest rightmost node
        deleteDeepest(root, temp);

        cout << "Dish removed successfully!" << endl;
    }

    void deleteDeepest(Dish* root, Dish* temp)
    {
        queue<Dish*> q;
        q.push(root);

        // Traverse the tree in level order to find and delete the deepest node
        while (!q.empty()) {
            Dish* current = q.front();
            q.pop();

            if (current->left == temp) {
                current->left = nullptr;
                delete temp;
                return;
            }
            else if (current->right == temp) {
                current->right = nullptr;
                delete temp;
                return;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }







    void Print_Menu(Dish* Root) {

        if (Root == nullptr) return;

        Root->Print_Dish();
        Print_Menu(Root->left);
        Print_Menu(Root->right);
    }

};

int Menu::ID = 1000;






struct Order
{
    Customer* cust = nullptr;
    Dish* lists = nullptr;
    int Type = 0, Total = 0;
    Order* next = nullptr;
    string Location = "";
    char Status = 'P';
    Employee* emp = nullptr;   // Pointer to employee who proceed the order

    int Check_Dish(string Name, string Type, Menu* M)
    {
        if (M->Get_Root() == nullptr) {
            return 0;
        }



        Dish* root = M->Get_Root();
        queue<Dish*> q;
        q.push(root);
        bool dishFound = false;

        while (!q.empty())
        {
            Dish* current = q.front();
            q.pop();

            if (current->Name == Name && current->Type == Type)
            {
                cout << "Dish added to your order: " << current->Name << " (" << current->Type << ") - " << current->Price << " units." << endl;
                dishFound = true;
                return current->Price;
                break;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        return 0;


    }

    bool Check_Dish_Order(string Name, string Type, Menu* M)
    {
        if (M->Get_Root() == nullptr) {
            return 0;
        }



        Dish* root = M->Get_Root();
        queue<Dish*> q;
        q.push(root);
        bool dishFound = false;

        while (!q.empty())
        {
            Dish* current = q.front();
            q.pop();

            if (current->Name == Name && current->Type == Type)
            {
                dishFound = true;
                return 1;
                break;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        return 0;


    }



    void Add_Dish(Order* S, Dish* Ptr) {

        if (S->lists == nullptr) {
            S->lists = Ptr;
            return;
        }

        Dish* P = S->lists;

        while (P->right != nullptr) {   // Singly linked list to store the list of dishes in order
            P = P->right;
        }
        P->right = Ptr;
        return;

    }


    void Remove_Dish(Order* S, Dish* Ptr)
    {

        if (S->lists == nullptr) {
            S->lists = Ptr;
            return;
        }

        Dish* P = S->lists;
        Dish* Prev = nullptr;
        bool found = false;

        while (P != nullptr) {   // Singly linked list to store the list of dishes in order
            if (P->Name == Ptr->Name && P->Type == Ptr->Type) {
                found = true;
                break;
            }
            Prev = P;
            P = P->right;
        }


        if (!found) {
            cout << "No Dishes found " << endl; return;
        }


        if (Prev == nullptr) {
            P = P->right;
        }
        else if (Ptr->right == nullptr) {
            Prev->right = nullptr;
        }
        else
        {
            Prev->right = Ptr->right;
        }



    }


    void Print_Order()
    {
        cout << "Order Status: " << Status << ", Price: " << Total << "\n";
        Dish* D = lists;
        while (D != nullptr) {
            D->Print_Dish();
            D = D->right;

        }
        cout << endl;
        return;
    }









};





struct Customer {
    int id;               // 5-digit auto-generated ID
    string name;          // Customer's name
    string email;         // Unique email
    string password;      // Secure password
    Order* history = nullptr;
    Order* current = nullptr;

    // Constructor
    Customer(int id = 0, string name = "", string email = "", string password = "")
        : id(id), name(name), email(email), password(password) {}




    void AddOrder(Order*& order) {

        Order* temp = new Order;
        temp->lists = order->lists;
        temp->Type = order->Type;
        temp->cust = order->cust;
        temp->Total = order->Total;
        temp->Status = order->Status;
        temp->emp = order->emp;

        temp->next = nullptr;
        if (history == nullptr) {
            history = temp;
            history->next = nullptr;
            return;
        }
        Order* Traverse = history;
        while (Traverse->next != nullptr) {
            Traverse = Traverse->next;
        }
        Traverse->next = temp;

        return;

    }











};


Order* Create_Order(int T, Customer*& cust) {

    Order* Temp = new Order;
    Temp->cust = cust;
    Temp->Type = T;
    Temp->lists = nullptr;
    return Temp;

}






class Orders
{


    Order* Start = nullptr, * End = nullptr;

public:

    Orders(Order* S = nullptr, Order* E = nullptr)
    {
        Start = S; End = E;
    }

    void Enqueue(Order* Temp) {
        if (Start == nullptr) {
            Start = Temp;
            Start->next = Start;
            End = Start;
            return;
        }

        Order* Prev = nullptr;
        Order* Ptr = Start;

        do {
            if (Ptr->Type <= Temp->Type) {
                Prev = Ptr;
                Ptr = Ptr->next;
            }
            else {
                break;
            }
        } while (Ptr != Start);

        if (Prev == nullptr) {
            Temp->next = Start;
            End->next = Temp;
            Start = Temp;
        }
        else if (Ptr == Start) {
            End->next = Temp;
            Temp->next = Start;
            End = Temp;
        }
        else {
            Prev->next = Temp;
            Temp->next = Ptr;
        }
    }



    Order* Dequeue()
    {
        if (Start == nullptr) {
            cout << "No orders in the queue " << endl;
            return nullptr;

        }

        if (Start == End) // means only one node
        {
            Order* Temp = Start;
            Start = End = nullptr;
            return Temp;
        }

        Order* Temp = Start;
        Start = Start->next;
        End->next = Start;
        return Temp;

    }

    void CheckCurrentOrders(Customer*& cust) {
        if (Start == nullptr)
        {
            cout << "No orders currently." << endl;
            return;
        }


        Order* Ptr = Start;
        do {
            if (Ptr->cust->id == cust->id) {
                cout << "Order Name: " << Ptr->cust->name << ", Type: " << Ptr->Type << ", Price: " << Ptr->Total << endl;
            }

            Ptr = Ptr->next;
        } while (Ptr != Start);
    }


    void Display()
    {
        if (Start == nullptr)
        {
            cout << "No orders in the queue." << endl;
            return;
        }

        if (Start->next == Start)
        {
            Start->Print_Order();

            return;
        }


        Order* Ptr = Start;
        do {
            Ptr->Print_Order();
            Ptr = Ptr->next;
        } while (Ptr != Start);
    }







};





struct Promo
{
    string Name;
    int Discount = 0, Limit = 0;
    string Id;
    Promo* next = nullptr;

};


Promo* Create_Promo(string Name, int L, int D = 0) {
    Promo* Temp = new Promo;
    Temp->Name = Name;
    Temp->Limit = L;
    Temp->Discount = D;
    Temp->next = nullptr;
    return Temp;
}


class Promotion
{
    Promo* Start = nullptr;

public:
    Promotion(Promo* S = nullptr)
    {
        Start = S;

    }

    void Push(string N, int L, int D) {
        Promo* Temp = Create_Promo(N, L, D);
        if (Start == nullptr) {
            Start = Temp;
            return;
        }

        Temp->next = Start;
        Start = Temp;


    }int Check_Promo()
    {
        while (Start != nullptr)
        {
            if (Start->Limit > 0)
            {
                Start->Limit--;
                return Start->Discount;
            }
            else
            {
                Pop();
            }
        }

        cout << "No valid promotions found." << endl;
        return 0;
    }


    void Pop() {
        if (Start == nullptr)
        {
            return;

        }
        if (Start->next == nullptr)
        {

            Start = nullptr;

            return;
        }

        Start = Start->next;

    }

    void Display_Top()
    {
        if (Start == nullptr)
        {
            cout << "No promotions available." << endl;
            return;
        }

        cout << "Name: " << Start->Name << ", Discount: " << Start->Discount
            << "%, Limit: " << Start->Limit << endl;
    }


    void Print() {
        if (Start == nullptr)
        {
            cout << "No promotions available." << endl;
            return;
        }
        Promo* Ptr = Start;
        while (Ptr != nullptr) {
            cout << "Name: " << Ptr->Name << ", Discount: " << Ptr->Discount
                << "%, Limit: " << Ptr->Limit << endl;
            Ptr = Ptr->next;
        }
        return;
    }
};




struct Employee {
    int id;               // 5-digit auto-generated ID
    string name;          // Customer's name
    string email;         // Unique email
    string password;      // Secure password
    Order* history = nullptr;
    Order* Delivery = nullptr;
    int Count = 0;     // Count number of orders for delivery 

    bool isDeliveryDriver = 0;

    Restaurant* workPlace = nullptr;
    // Constructor
    Employee(int id = 0, string name = "", string email = "", string password = "")
        : id(id), name(name), email(email), password(password) {}




    void History_Orders(Employee* current, Order* order)
    {

        Order* temp = new Order;
        temp->lists = order->lists;
        temp->Type = order->Type;
        temp->cust = order->cust;
        temp->Total = order->Total;
        temp->Status = order->Status;
        temp->next = nullptr;

        if (current->history == nullptr) {
            current->history = temp;
            current->history->next = nullptr;
            return;
        }
        Order* Traverse = current->history;
        while (Traverse->next != nullptr) {
            Traverse = Traverse->next;
        }
        Traverse->next = temp;



    }



    void Delivery_Add(Employee* current, Order* order) {


        if (current->Delivery == nullptr) {
            current->Delivery = order;
            current->Delivery->next = nullptr;
            current->Count++;
            return;
        }
        Order* Traverse = current->Delivery;
        while (Traverse->next != nullptr) {
            Traverse = Traverse->next;
        }
        Traverse->next = order;
        Traverse = Traverse->next;
        Traverse->next = nullptr;


        current->Count++;

    }



    int Return_Orders()
    {
        return Count;
    }









};




struct Restaurant {

    static int id;
    string Name, Type;
    int Rest_Id = 0;
    Menu* menu = nullptr;
    Orders* Queue = nullptr;
    Promotion* Prem = nullptr;
    Restaurant* next = nullptr;
    Employee* Man = nullptr;
    string Location = "";

    Restaurant(int ID = 0) {
        Rest_Id = id++;
    }

};

int Restaurant::id = 10000;


Restaurant* Create_Res(string N, string T) {

    Restaurant* Temp = new Restaurant;
    Temp->Name = N;
    Temp->Type = T;
    Temp->Prem = new Promotion();
    Temp->menu = new Menu();
    Temp->Queue = new Orders();
    return Temp;

}




class Restaurant_Manage {

    Restaurant* Start, * End;
    Restaurant* current;


public:
    Restaurant_Manage() : current(nullptr), Start(nullptr), End(nullptr) {}


    Restaurant* getCurrent() {
        return current;
    }

    void setCurrent(Restaurant* current) {
        this->current = current;
    }

    Restaurant* getStart()
    {
        return Start;
    }

    void GetCustOrder(Customer*& C) {
        current->Queue->CheckCurrentOrders(C);
    }

    void Add_Restaurant(string Name, string Type, string Location, Employee* manager) {

        Restaurant* Temp = Create_Res(Name, Type);

        Temp->Location = Location;


        Temp->Man = manager;
        manager->workPlace = Temp;

        if (Start == nullptr) {
            Start = Temp;
            Start->next = Temp;
            End = Start;
            return;
        }

        End->next = Temp;
        Temp->next = Start;
        End = Temp;



        return;
    }



    void Remove_Restaurant(string Name, string Type) {

        if (Start == nullptr) {
            cout << "No restaurant in the City" << endl;
            return;
        }

        Restaurant* Ptr = Start;
        Restaurant* Prev = nullptr;
        bool found = false;


        do {
            if (Ptr->Name == Name && Ptr->Type == Type)
            {
                found = true;
                break;
            }
            Prev = Ptr;
            Ptr = Ptr->next;
        } while (Ptr != Start);

        if (!found)
        {
            cout << "No restaurant with this name and type found" << endl;
            return;
        }

        if (Start == End)
        {
            delete Start;
            Start = End = nullptr;
        }
        else if (Ptr == Start) {

            Start = Start->next;
            End->next = Start;
            delete Ptr;
        }

        else if (Ptr == End) {
            Prev->next = Start;
            End = Prev;
            delete Ptr;
        }

        else {
            Prev->next = Ptr->next;
            delete Ptr;
        }

        cout << "Restaurant removed successfully!" << endl;
    }

    Restaurant* Return_Restaurant(string Name, string Type) {

        if (Start == nullptr) {
            return nullptr;
        }

        Restaurant* Ptr = Start;
        Restaurant* Prev = nullptr;
        bool found = false;


        do {
            if (Ptr->Name == Name && Ptr->Type == Type)
            {
                found = true;
                break;
            }
            Prev = Ptr;
            Ptr = Ptr->next;
        } while (Ptr != Start);

        if (!found)
        {
            return nullptr;
        }

        return Ptr;

    }


    bool Print_Restaurant()
    {
        if (Start == nullptr) {
            cout << "No restaurants available!" << endl;
            return 0;
        }

        Restaurant* Ptr = Start;
        cout << "Restaurants in the City:" << endl;
        do {
            cout << "Name: " << Ptr->Name << ", Type: " << Ptr->Type << endl;
            Ptr = Ptr->next;
        } while (Ptr != Start);
        return 1;
    }


    bool Found(Restaurant* Ptr)
    {

        bool found = true;

        if (found) {
            int choice = 0;
            do
            {
                cout << "1. Add Dish " << endl;
                cout << "2. Remove Dish " << endl;
                cout << "3. Print Menu " << endl;
                cout << "4. Exit" << endl;


                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1: {
                    string dishName, dishType;
                    int dishPrice;
                    cout << "Enter Dish Name: ";
                    getline(cin, dishName);
                    cout << "Enter Dish Type: ";
                    getline(cin, dishType);
                    cout << "Enter Dish Price: ";
                    cin >> dishPrice;
                    cin.ignore();
                    while (dishPrice < 0) {
                        cout << "Enter Dish Price: ";
                        cin >> dishPrice;
                        cin.ignore();
                    }

                    Ptr->menu->Add_Dish(dishName, dishType, dishPrice);
                    cout << "Dish added successfully!" << endl;
                    break;
                }

                case 2: {
                    string dishName, dishType;
                    cout << "Enter Dish Name: ";
                    getline(cin, dishName);
                    cout << "Enter Dish Type: ";
                    getline(cin, dishType);

                    Ptr->menu->Remove_Dish(dishName, dishType);
                    break;
                }

                case 3: {
                    cout << "Menu:" << endl;
                    Ptr->menu->Print_Menu(Ptr->menu->Get_Root());
                    break;
                }

                case 4:
                    cout << "Exiting menu options." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }

            } while (choice != 4);

            return found;
        }
    }





    bool Make_Order(Customer*& customer, string ResName, string ResType) {


        if (Start == nullptr) {
            cout << "No restaurants available!" << endl;
            return 0;
        }

        Restaurant* Ptr = Start;
        bool found = false;

        do {
            if (Ptr->Name == ResName && Ptr->Type == ResType)
            {
                found = true;
                break;
            }
            Ptr = Ptr->next;
        } while (Ptr != Start);

        current = Ptr;


        Order* Current = new Order;  //Making the order
        int Result = 0;

        if (found)
        {

            Ptr->menu->Print_Menu(Ptr->menu->Get_Root());

            do
            {
                string dishName, dishType;
                cout << "Enter the Dish Name: ";
                getline(cin, dishName);
                cout << "Enter the type of the dish: ";
                getline(cin, dishType);

                Result = Current->Check_Dish(dishName, dishType, Ptr->menu);
                if (!Result) {

                    cout << "Not available in menu " << endl;
                    continue;
                }
                Dish* Temp = Made_Dish(dishName, dishType, Result);
                Current->Add_Dish(Current, Temp);   // Adding in the order list
                Current->Total += Result;

                cout << "Do you want to add more dish (0/1): ";
                cin >> Result;
                cin.ignore();
                while (Result < 0 || Result > 1) {
                    cout << "Choose from (0/1): ";
                    cin >> Result;
                    cin.ignore();
                }

            } while (Result);

            if (Current->lists == nullptr) {   // means no dishes order 
                return 1;
            }
            cout << "Confirm your order (0/1) " << endl;
            cin >> Result;
            cin.ignore();

            while (Result < 0 || Result > 1) {
                cout << "Choose from (0/1): ";
                cin >> Result;
                cin.ignore();
            }

            if (Result) {

                string name;

                int Disco = Ptr->Prem->Check_Promo();
                if (Disco != 0)
                {
                    cout << "Discount Provided " << Disco << " %" << endl;
                    int Discount = (Current->Total * Disco) / 100; // Correct percentage calculation
                    Current->Total = Current->Total - Discount;
                    cout << "Updated Price " << Current->Total << endl;
                }

                string ResLoc;
                string vertices[] = {
                            "F-5", "F-6", "F-7", "F-8", "F-9", "F-10", "F-11", "F-12",
                            "G-5", "G-6", "G-7", "G-8", "G-9", "G-10", "G-11", "G-12",
                            "G-13", "G-14", "H-7", "H-8", "H-9", "H-10",
                            "H-11", "H-12", "I-8", "I-9", "I-10",
                            "I-11", "I-12", "I-14", "I-15", "I-16"
                };


                for (int i = 0; i < 32; i++) {
                    cout << vertices[i] << "  ";
                }

                bool found = false;
                do {

                    cout << "Enter Location from the above: ";
                    getline(cin, ResLoc);
                    for (int i = 0; i < 32; i++) {
                        if (ResLoc == vertices[i]) {
                            found = true;
                        }
                    }
                } while (!found);
                current->Location = ResLoc;

                cout << "Order (Express / Normal / Premium)" << endl;
                getline(cin, name);
                while (name != "Express" && name != "Normal" && name != "Premium") {
                    cout << "Choose from Express / Normal / Premium: ";
                    getline(cin, name);
                }
                if (name == "Express")
                {
                    Current->Type = 2;
                    Current->Total += 200;     // Delivery Charges 

                    int Add = Current->Total / 10;
                    Current->Total = Current->Total + Add;// Addittion of 10 % with premium order
                }
                else if (name == "Premium") {
                    Current->Type = 1;
                    Current->Total += 500;
                }
                else
                {
                    Current->Total += 100;    // Delivery Charges 
                    Current->Type = 3;
                }





                Current->cust = customer;
                customer->current = Current;   // Setting the Customer Current Order


                customer->AddOrder(Current);  // Populating the history 
                Ptr->Queue->Enqueue(Current);


                cout << "Order has been placed " << endl;
            }
        }


        return true;

    }




    bool Insert_Promotion(Restaurant* Ptr) {
        if (Start == nullptr) {
            cout << "No restaurants available!" << endl;
            return 0;
        }




        string N; int Disc, Limit;
        int Choice = 0;

        do
        {
            cout << "1 Add Promotion " << endl;
            cout << "2 Top Promotion " << endl;
            cout << "3 Print Promotions " << endl;
            cout << "4 Exit " << endl;
            cin >> Choice;
            cin.ignore();
            if (Choice == 1) {
                cout << "Promo Name: ";
                getline(cin, N);
                cout << "Dicount provided: ";
                cin >> Disc;
                cin.ignore();
                while (Disc < 0 && Disc >75) {    // Max 75 percent Discount
                    cout << "Dicount provided: ";
                    cin >> Disc;
                    cin.ignore();
                }
                cout << "Limits ? " << endl;
                cin >> Limit;
                cin.ignore();
                while (Disc < 0) {
                    cout << "Limits ? " << endl;
                    cin >> Limit;
                    cin.ignore();
                }
                Ptr->Prem->Push(N, Limit, Disc);
            }
            else if (Choice == 2)
            {
                Ptr->Prem->Display_Top();

            }
            else if (Choice == 3) {
                Ptr->Prem->Print();
            }

        } while (Choice != 4);

        return 1;

    }



    Restaurant* Check_Manager(Employee* Emp) {

        if (Start == nullptr) {
            cout << "No restuarents in the city " << endl;
            return nullptr;
        }

        Restaurant* Ptr = Start;


        bool found = false;

        do {
            if (Ptr->Man->id == Emp->id) {
                found = true;
                break;
            }
            Ptr = Ptr->next;

        } while (Ptr != Start);


        if (!found)
        {
            return nullptr;
        }

        return Emp->workPlace;



    }









    void Print_Queue(string Name) {
        if (Start == nullptr) {
            cout << "No restaurants available!" << endl;
            return;
        }

        Restaurant* Ptr = Start;
        bool found = false;

        do {
            if (Ptr->Name == Name)
            {
                found = true;
                break;
            }
            Ptr = Ptr->next;
        } while (Ptr != Start);
        if (found) {
            Ptr->Queue->Display();
        }
    }


};



class HashMap {
    Customer* customers[100];
    int tableSize;

public:

    HashMap(int tableSize = 100) {
        this->tableSize = tableSize;
        for (int i = 0; i < tableSize; i++) {
            customers[i] = nullptr;
        }
    }

    int PasswordToHashValue(const string& password) {
        if (password.size() < 8) {
            cout << "Password must have at least 8 characters." << endl;
            return 0;
        }
        int hashValue = 0;
        int multiplier = 1;
        for (int i = 0; i < 8; i++) {
            hashValue += password[i] * multiplier;
            multiplier *= 5;
        }
        return hashValue;
    }

    int LinearProbing(int collisionPos, int tableSize) {
        do {
            collisionPos = (collisionPos + 1) % tableSize;
        } while (customers[collisionPos] != nullptr);
        return collisionPos;
    }

    int LinearSearch(string email, string Password, int collisionPos, int tableSize) {
        do {
            collisionPos = (collisionPos + 1) % tableSize;
            if (customers[collisionPos] == nullptr) {
                return -1;
            }
        } while (customers[collisionPos]->email != email || customers[collisionPos]->password != Password);

        return collisionPos;
    }

    int hashFunction(int hashVal, int tableSize) {
        int part1 = hashVal / 10000;
        int part2 = (hashVal / 100) % 100;
        int part3 = hashVal % 100;
        return (part1 + part2 + part3) % tableSize;
    }

    void insert(Customer*& customer, int hashVal) {
        int position = hashFunction(hashVal, tableSize);
        if (customers[position] == nullptr) {
            customers[position] = customer;
        }
        else {
            int NewPos = LinearProbing(position, tableSize);
            customers[NewPos] = customer;
        }
    }

    Customer* Search(int hashVal, string email, string Password) {
        int position = hashFunction(hashVal, tableSize);
        if (customers[position] == nullptr) {
            return nullptr;
        }
        if (customers[position]->email == email && customers[position]->password == Password) {
            return customers[position];
        }
        else {
            int NewPos = LinearSearch(email, Password, position, tableSize);
            if (NewPos == -1) {
                return nullptr;
            }
            return customers[NewPos];
        }
    }

    bool Delete(int hashVal, string email, string Password) {
        Customer* ToDelete = Search(hashVal, email, Password);
        if (ToDelete == nullptr) {
            return 0;
        }
        delete ToDelete;
        ToDelete = nullptr;
        return 1;
    }

};

















class ManageCustomer {
    int id;
    Customer* current;

public:
    ManageCustomer(int id = 10000, Customer* current = nullptr) {
        this->id = id;
        this->current = current;
    }

    Customer* Get_Current()
    {
        return current;
    }

    bool isnum(char c) {
        return c >= 48 && c <= 57;
    }

    bool isUpperCase(char c) {
        return c >= 65 && c <= 90;
    }

    bool isLowerCase(char c) {
        return c >= 97 && c <= 122;
    }

    bool Special(char c) {
        char specialChar[] = { '~', '!', '@','#','$', '%' ,'^','&', '*','(',')', '-', '_', '+' , '=' ,'{','}','[',']' ,'|' , ';' , ':','<','>',',','.','/',',','?' };
        int Size = 29;
        for (int i = 0; i < Size; i++) {
            if (specialChar[i] == c) {
                return 1;
            }
        }
        return 0;
    }

    void PasswordInput(Customer*& cust) {
        bool check = 0;

        while (!check) {

            cout << "Enter your password: ";
            getline(cin, cust->password);
            int Size = cust->password.size();
            if (Size < 8 || Size > 12) {
                cout << "Size should be greater than 8 and less than 12 characters!" << endl;
                check = 0;
                continue;
            }

            string pass = cust->password;
            bool specialChar = 0, num = 0, UpperCase = 0, LowerCase = 0;


            for (int i = 0; i < Size; i++) {
                if (!specialChar && Special(pass[i])) {
                    specialChar = 1;
                }
                if (!num && isnum(pass[i])) {
                    num = 1;
                }
                if (!UpperCase && isUpperCase(pass[i])) {
                    UpperCase = 1;
                }
                if (!LowerCase && isLowerCase(pass[i])) {
                    LowerCase = 1;
                }
            }

            if (specialChar && num && UpperCase && LowerCase) {
                check = 1;
            }

            if (check == 1) {
                cout << "Enter your password again for confirmation: ";
                getline(cin, pass);
                if (pass != cust->password) {
                    cout << "Doesnot match!\nEnter again.\n";
                    check = 0;
                }
            }
            if (check == 0) {
                cout << "Enter again while keeping constrains in mind!" << endl;
            }
        }
    }


    void SignUp(HashMap& hashmap) {
        if (current != nullptr) {
            cout << "Already logged in.\nLogout first." << endl;
            return;
        }

        Customer* NEW = new Customer;
        NEW->id = id;
        id++;

        cout << "Enter your email address (nobody@hotmail.com) : ";
        getline(cin, NEW->email);
        cout << endl;

        bool check = true;
        while (check) {

            int Size = NEW->email.size();
            bool atTheRate = true, Dot = true;
            for (int i = 0; i < Size; i++) {
                if (atTheRate && NEW->email[i] == '@') {
                    atTheRate = false;
                }
                if (!atTheRate && NEW->email[i] == '.') {
                    if (NEW->email[Size - 4] == '.' && NEW->email[Size - 3] == 'c' && NEW->email[Size - 2] == 'o' && NEW->email[Size - 1] == 'm') {
                        Dot = false;
                    }
                }
            }

            if (!atTheRate && !Dot) {
                check = false;
            }
            else {

                cout << "Invalid Email address\nEnter correct email (nobody@hotmail.com) : ";
                getline(cin, NEW->email);
                cout << endl;
            }
        }

        PasswordInput(NEW);


        cout << "Enter your name: ";
        getline(cin, NEW->name);

        int hashVal = hashmap.PasswordToHashValue(NEW->password);
        hashmap.insert(NEW, hashVal);
        cout << "Customer id created successfully!" << endl;
        current = NEW;
    }

    void logout() {
        current = nullptr;
        cout << "Logged out successfully!" << endl;
    }

    string getPassword() {
        string password;
        char ch;
        cout << "Enter your password: ";
        while ((ch = _getch()) != '\r') { // Read until Enter is pressed (Enter = '\r')
            if (ch == '\b' && !password.empty()) { // Handle Backspace
                cout << "\b \b"; // Erase the last '*' on screen
                password.pop_back();
            }
            else if (ch != '\b') { // Ignore other control characters
                cout << '*'; // Display a ''
                password += ch;
            }
        }
        cout << endl; // Move to the next line after Enter
        return password;
    }

    void Login(HashMap& hashmap) {

        if (current != nullptr) {
            cout << "Already logged in.\nLogout first." << endl;
            return;
        }

        string email, password;
        cout << "Enter your email address: ";
        getline(cin, email);

        password = getPassword();
        if (password.size() < 8) {
            cout << "Password cannot be less than 8\n";
            password = getPassword();
        }

        int hashVal = hashmap.PasswordToHashValue(password);


        Customer* log = hashmap.Search(hashVal, email, password);
        if (log == nullptr) {
            cout << "Not Found!\nEmail or password was wrong!" << endl;
        }
        else {
            cout << "Logged In successfully" << endl;
            current = log;
        }
    }

    void DeleteId(HashMap& hashmap) {
        if (current == nullptr) {
            cout << "Login First to delete Id" << endl;
            return;
        }
        int hashVal = hashmap.PasswordToHashValue(current->password);
        bool deleted = hashmap.Delete(hashVal, current->email, current->password);
        if (deleted) {
            cout << "Customer id deleted successfully!" << endl;
            current = nullptr;
        }
        else {
            cout << "Error!\nCouldnot delete id" << endl;
        }
    }

    void Edit(HashMap& hashmap) {
        if (current == nullptr) {
            cout << "Login First to edit Id" << endl;
            return;
        }
        int hashVal = hashmap.PasswordToHashValue(current->password);
        Customer* log = hashmap.Search(hashVal, current->email, current->password);
        if (log == nullptr) {
            cout << "Error!\nCouldnot edit id" << endl;
        }
        else {
            int choice = 1;
            string pass;
            do {
                cout << "Press\n1-Reset Password\n2-Change Name\n3-Exit Edit Id\nEnter choice: ";
                cin >> choice;
                cin.clear();
                cin.ignore();

                Customer* Edited = nullptr;

                switch (choice) {
                case 1:
                    cout << "Enter the old Password: ";
                    getline(cin, pass);
                    if (pass == log->password) {
                        PasswordInput(log);

                        Edited = new Customer;
                        Edited->email = log->email;
                        Edited->id = log->id;
                        Edited->current = log->current;
                        Edited->password = log->password;
                        Edited->history = log->history;
                        Edited->name = log->name;

                        int hashVal1 = hashmap.PasswordToHashValue(pass);
                        hashmap.Delete(hashVal1, log->email, pass);

                        int hashVal = hashmap.PasswordToHashValue(Edited->password);
                        hashmap.insert(Edited, hashVal);
                    }
                    break;
                case 2:
                    cout << "Enter new name: ";
                    getline(cin, log->name);
                    break;
                case 3:
                    break;
                default:
                    cout << "Enter correct chocie!" << endl;
                    break;
                }
            } while (choice != 3);


        }

    }

    void Print() {
        if (current == nullptr) {
            cout << "Login First to Print Id Information" << endl;
            return;
        }

        cout << "Name: " << current->name << "\nEmail: " << current->email << endl;
    }



    void PrintOrder() {
        if (current->history == nullptr) {
            cout << "No order history" << endl;
            return;
        }
        Order* Traverse = current->history;
        while (Traverse->next != nullptr)
        {
            Traverse->Print_Order();
            Traverse = Traverse->next;
        }

        Traverse->Print_Order();
    }


    void Read_File(string Name)
    {

        ifstream Obj(Name + ".txt");//Making File Object for reading
        if (!Obj)
        {
            cout << "File Not Found " << endl;//Not Found 
            return;
        }


        string Line;
        int Count = 0;

        while (getline(Obj, Line))//Reading the whole line
        {
            cout << Line << endl;
        }

        Obj.close();//Close file

    }

};







class HashMapEmployee {
    Employee* employee[100];
    int tableSize;

public:

    HashMapEmployee(int tableSize = 100) {
        this->tableSize = tableSize;
        for (int i = 0; i < tableSize; i++) {
            employee[i] = nullptr;
        }
    }

    int PasswordToHashValue(const string& password) {
        if (password.size() < 8) {
            cout << "Password must have at least 8 characters." << endl;
            return 0;
        }
        int hashValue = 0;
        int multiplier = 1;
        for (int i = 0; i < 8; i++) {
            hashValue += password[i] * multiplier;
            multiplier *= 5;
        }
        return hashValue;
    }

    int LinearProbing(int collisionPos, int tableSize) {
        do {
            collisionPos = (collisionPos + 1) % tableSize;
        } while (employee[collisionPos] != nullptr);
        return collisionPos;
    }

    int LinearSearch(string email, string Password, int collisionPos, int tableSize) {
        do {
            collisionPos = (collisionPos + 1) % tableSize;
            if (employee[collisionPos] == nullptr) {
                return -1;
            }
        } while (employee[collisionPos]->email != email || employee[collisionPos]->password != Password);

        return collisionPos;
    }

    int hashFunction(int hashVal, int tableSize) {
        int part1 = hashVal / 10000;
        int part2 = (hashVal / 100) % 100;
        int part3 = hashVal % 100;
        return (part1 + part2 + part3) % tableSize;
    }

    void insert(Employee*& emp, int hashVal) {
        int position = hashFunction(hashVal, tableSize);
        if (employee[position] == nullptr) {
            employee[position] = emp;
        }
        else {
            int NewPos = LinearProbing(position, tableSize);
            employee[NewPos] = emp;
        }
    }

    Employee* Search(int hashVal, string email, string Password) {
        int position = hashFunction(hashVal, tableSize);
        if (employee[position] == nullptr) {
            return nullptr;
        }
        if (employee[position]->email == email && employee[position]->password == Password) {
            return employee[position];
        }
        else {
            int NewPos = LinearSearch(email, Password, position, tableSize);
            if (NewPos == -1) {
                return nullptr;
            }
            return employee[NewPos];
        }
    }

    bool Delete(int hashVal, string email, string Password) {
        Employee* ToDelete = Search(hashVal, email, Password);
        if (ToDelete == nullptr) {
            return 0;
        }
        delete ToDelete;
        ToDelete = nullptr;
        return 1;
    }

};



// ------------------------------------------------------------- Mananging Employees ---------------------------------------------------






class ManageEmployee {
    int id;
    Employee* current;

public:
    ManageEmployee(int id = 10000, Employee* current = nullptr) {
        this->id = id;
        this->current = current;
    }

    Employee* Get_Current()
    {
        return current;
    }

    void Set_Current(Employee* current) {
        this->current = current;
    }
    bool isnum(char c) {
        return c >= 48 && c <= 57;
    }

    bool isUpperCase(char c) {
        return c >= 65 && c <= 90;
    }

    bool isLowerCase(char c) {
        return c >= 97 && c <= 122;
    }

    bool Special(char c) {
        char specialChar[] = { '~', '!', '@','#','$', '%' ,'^','&', '*','(',')', '-', '_', '+' , '=' ,'{','}','[',']' ,'|' , ';' , ':','<','>',',','.','/',',','?' };
        int Size = 29;
        for (int i = 0; i < Size; i++) {
            if (specialChar[i] == c) {
                return 1;
            }
        }
        return 0;
    }

    void PasswordInput(Employee*& cust) {
        bool check = 0;

        while (!check) {

            cout << "Enter your password: ";
            getline(cin, cust->password);
            int Size = cust->password.size();
            if (Size < 8 || Size > 12) {
                cout << "Size should be greater than 8 and less than 12 characters!" << endl;
                check = 0;
                continue;
            }

            string pass = cust->password;
            bool specialChar = 0, num = 0, UpperCase = 0, LowerCase = 0;


            for (int i = 0; i < Size; i++) {
                if (!specialChar && Special(pass[i])) {
                    specialChar = 1;
                }
                if (!num && isnum(pass[i])) {
                    num = 1;
                }
                if (!UpperCase && isUpperCase(pass[i])) {
                    UpperCase = 1;
                }
                if (!LowerCase && isLowerCase(pass[i])) {
                    LowerCase = 1;
                }
            }

            if (specialChar && num && UpperCase && LowerCase) {
                check = 1;
            }

            if (check == 1) {
                cout << "Enter your password again for confirmation: ";
                getline(cin, pass);
                if (pass != cust->password) {
                    cout << "Doesnot match!\nEnter again.\n";
                    check = 0;
                }
            }
            if (check == 0) {
                cout << "Enter again while keeping constrains in mind!" << endl;
            }
        }
    }

    Employee* ManagerCreation(HashMapEmployee& hashmap) {


        Employee* NEW = new Employee;
        NEW->id = id;
        id++;

        cout << "Enter the manager email address (nobody@hotmail.com) : ";
        getline(cin, NEW->email);
        cout << endl;

        bool check = true;
        while (check) {

            int Size = NEW->email.size();
            bool atTheRate = true, Dot = true;
            for (int i = 0; i < Size; i++) {
                if (atTheRate && NEW->email[i] == '@') {
                    atTheRate = false;
                }
                if (!atTheRate && NEW->email[i] == '.') {
                    if (NEW->email[Size - 4] == '.' && NEW->email[Size - 3] == 'c' && NEW->email[Size - 2] == 'o' && NEW->email[Size - 1] == 'm') {
                        Dot = false;
                    }
                }
            }

            if (!atTheRate && !Dot) {
                check = false;
            }
            else {

                cout << "Invalid Email address\nEnter correct email (nobody@hotmail.com) : ";
                getline(cin, NEW->email);
                cout << endl;
            }
        }

        PasswordInput(NEW);


        cout << "Enter manager name: ";
        getline(cin, NEW->name);

        int hashVal = hashmap.PasswordToHashValue(NEW->password);
        hashmap.insert(NEW, hashVal);
        cout << "manager created successfully!" << endl;
        return NEW;
    }

    void SignUp(HashMapEmployee& hashmap, Restaurant*& WorkPlace) {
        if (current != nullptr) {
            cout << "Already logged in.\nLogout first." << endl;
            return;
        }

        Employee* NEW = new Employee;
        NEW->id = id;
        id++;

        cout << "Enter your email address (nobody@hotmail.com) : ";
        getline(cin, NEW->email);
        cout << endl;

        bool check = true;
        while (check) {

            int Size = NEW->email.size();
            bool atTheRate = true, Dot = true;
            for (int i = 0; i < Size; i++) {
                if (atTheRate && NEW->email[i] == '@') {
                    atTheRate = false;
                }
                if (!atTheRate && NEW->email[i] == '.') {
                    if (NEW->email[Size - 4] == '.' && NEW->email[Size - 3] == 'c' && NEW->email[Size - 2] == 'o' && NEW->email[Size - 1] == 'm') {
                        Dot = false;
                    }
                }
            }

            if (!atTheRate && !Dot) {
                check = false;
            }
            else {

                cout << "Invalid Email address\nEnter correct email (nobody@hotmail.com) : ";
                getline(cin, NEW->email);
                cout << endl;
            }
        }

        PasswordInput(NEW);


        cout << "Enter your name: ";
        getline(cin, NEW->name);
        NEW->workPlace = WorkPlace;

        int hashVal = hashmap.PasswordToHashValue(NEW->password);
        hashmap.insert(NEW, hashVal);

        string boolChoice;
        cout << "Are you a delivery driver (yes/no): ";
        getline(cin, boolChoice);
        while (boolChoice != "yes" && boolChoice != "no") {
            cout << "Choose from (yes/no): ";
            getline(cin, boolChoice);
        }

        NEW->isDeliveryDriver = (boolChoice == "yes");

        cout << "Employee id created successfully!" << endl;
        current = NEW;
    }


    void logout() {
        current = nullptr;
        cout << "Logged out successfully!" << endl;
    }

    string getPassword() {
        string password;
        char ch;
        cout << "Enter your password: ";
        while ((ch = _getch()) != '\r') { // Read until Enter is pressed (Enter = '\r')
            if (ch == '\b' && !password.empty()) { // Handle Backspace
                cout << "\b \b"; // Erase the last '*' on screen
                password.pop_back();
            }
            else if (ch != '\b') { // Ignore other control characters
                cout << '*'; // Display a ''
                password += ch;
            }
        }
        cout << endl; // Move to the next line after Enter
        return password;
    }

    void Login(HashMapEmployee& hashmap) {

        if (current != nullptr) {
            cout << "Already logged in.\nLogout first." << endl;
            return;
        }

        string email, password;
        cout << "Enter your email address: ";
        getline(cin, email);

        password = getPassword();
        if (password.size() < 8) {
            cout << "Password cannot be less than 8\n";
            password = getPassword();
        }

        int hashVal = hashmap.PasswordToHashValue(password);


        Employee* log = hashmap.Search(hashVal, email, password);
        if (log == nullptr) {
            cout << "Not Found!\nEmail or password was wrong!" << endl;
        }
        else {
            cout << "Logged In successfully" << endl;
            current = log;
        }
    }

    void DeleteId(HashMapEmployee& hashmap) {
        if (current == nullptr) {
            cout << "Login First to delete Id" << endl;
            return;
        }
        int hashVal = hashmap.PasswordToHashValue(current->password);
        bool deleted = hashmap.Delete(hashVal, current->email, current->password);
        if (deleted) {
            cout << "Employee id deleted successfully!" << endl;
            current = nullptr;
        }
        else {
            cout << "Error!\nCouldnot delete id" << endl;
        }
    }

    void Edit(HashMapEmployee& hashmap) {
        if (current == nullptr) {
            cout << "Login First to edit Id" << endl;
            return;
        }
        int hashVal = hashmap.PasswordToHashValue(current->password);
        Employee* log = hashmap.Search(hashVal, current->email, current->password);
        if (log == nullptr) {
            cout << "Error!\nCouldnot edit id" << endl;
        }
        else {
            int choice = 1;
            string pass;
            do {
                cout << "Press\n1-Reset Password\n2-Change Name\n3-Exit Edit Id\nEnter choice: ";
                cin >> choice;
                cin.clear();
                cin.ignore();

                Employee* Edited = nullptr;

                switch (choice) {
                case 1:
                    cout << "Enter the old Password: ";
                    getline(cin, pass);
                    if (pass == log->password) {
                        PasswordInput(log);

                        Edited = new Employee;
                        Edited->email = log->email;
                        Edited->id = log->id;
                        Edited->workPlace = log->workPlace;
                        Edited->password = log->password;
                        Edited->history = log->history;
                        Edited->name = log->name;

                        int hashVal1 = hashmap.PasswordToHashValue(pass);
                        hashmap.Delete(hashVal1, log->email, pass);

                        int hashVal = hashmap.PasswordToHashValue(Edited->password);
                        hashmap.insert(Edited, hashVal);

                    }
                    else {
                        cout << "Wrong old Password!" << endl;
                    }
                    break;
                case 2:
                    cout << "Enter new name: ";
                    getline(cin, log->name);
                    break;
                case 3:
                    break;
                default:
                    cout << "Enter correct chocie!" << endl;
                    break;
                }
            } while (choice != 3);


        }

    }

    void Print() {
        if (current == nullptr) {
            cout << "Login First to Print Id Information" << endl;
            return;
        }
        if (current->workPlace) {
            cout << "Resturant: " << current->workPlace->Name << endl;
        }
        cout << "Name: " << current->name << "\nEmail: " << current->email << endl;
    }

    void AddOrder(Order*& order, Customer* C) {

        Order* temp = new Order;
        temp->lists = order->lists;
        temp->Type = order->Type;
        temp->cust = C;
        temp->Total = order->Total;
        temp->next = nullptr;
        if (current->history == nullptr) {
            current->history = temp;
            current->history->next = nullptr;
            return;
        }
        Order* Traverse = current->history;
        while (Traverse->next != nullptr) {
            Traverse = Traverse->next;
        }
        Traverse->next = temp;



    }


    void PrintOrder()   // Printing the orders being proceed
    {
        if (current->history == nullptr) {
            cout << "No order history" << endl;
            return;
        }
        Order* Traverse = current->history;
        while (Traverse->next != nullptr) {
            Traverse->Print_Order();
            Traverse = Traverse->next;
        }

        Traverse->Print_Order();
    }




    void Check_Orders()  // Check the orders in thw Restuarent
    {

        if (current->workPlace != nullptr) {
            current->workPlace->Queue->Display();
            return;
        }

        else {
            cout << "Restuarent not found " << endl;
            return;
        }

        return;
    }

    bool CheckOrder(Order* order) {
        Dish* Temp = order->lists;
        Menu* menu = current->workPlace->menu;

        while (Temp != nullptr) {
            if (!order->Check_Dish_Order(Temp->Name, Temp->Type, menu)) {
                return 0;
            }
            Temp = Temp->right;
        }

        return 1;
    }



    void Proceed_Orders() // Proceeding the orders one by one from queue update their status find in customer history update the status
    {
        char Status;
        Order* Temp = nullptr;
        if (current->isDeliveryDriver) {
            Status = 'A';
            queue <Order*> q;
            Temp = current->workPlace->Queue->Dequeue();
            while (Temp != nullptr && Temp->Status != 'C') {
                q.push(Temp);
                Temp = current->workPlace->Queue->Dequeue();
            }
            while (!q.empty()) {
                Order* EnqueueAgain = q.front();
                current->workPlace->Queue->Enqueue(EnqueueAgain);
                q.pop();
            }
        }
        else {
            Status = 'C';
            queue <Order*> q;
            Temp = current->workPlace->Queue->Dequeue();
            while (Temp != nullptr && Temp->Status != 'P') {
                q.push(Temp);
                Temp = current->workPlace->Queue->Dequeue();
            }
            while (!q.empty()) {
                Order* EnqueueAgain = q.front();
                current->workPlace->Queue->Enqueue(EnqueueAgain);
                q.pop();
            }
        }

        if (Temp == nullptr) {
            cout << "No orders for now " << endl;
            return;
        }

        if (!CheckOrder(Temp)) {
            cout << "Error! Order Dish not present currently" << endl;
            Temp->Status = 'D';
        }
        else {
            Temp->Status = Status;
            current->History_Orders(current, Temp);
            Temp->emp = current;            // Update the employee who proceed the order  

        }

        if (Status == 'C' && Temp->Status != 'D') {
            current->workPlace->Queue->Enqueue(Temp);
        }
        if (Status == 'A' && Temp->Status != 'D') {
            current->Delivery_Add(current, Temp);
        }

        bool found = false;
        // Updating the Status in the Customer history
        Customer* S = Temp->cust;
        if (S != nullptr) {
            Order* History = S->history;

            while (History != nullptr) {
                if (History->Total == Temp->Total && History->Type == Temp->Type) {
                    found = true;
                    break;
                }
                History = History->next;
            }

            if (found) {
                History->Status = Temp->Status;
                return;
            }
        }

        return;

    }






    void Print_Delivery_Orders()
    {


        if (current->Count == 0)
        {
            cout << "No orders for the Delivery yet " << endl;
            return;
        }

        Order* H = current->Delivery;
        while (H != nullptr) {
            H->Print_Order();
            H = H->next;

        }
        cout << endl;
        return;



    }


    void UpdateCustHistory(Order* Temp) {

        bool found = false;
        // Updating the Status in the Customer history
        Customer* S = Temp->cust;
        if (S != nullptr) {
            Order* History = S->history;

            while (History != nullptr) {
                if (History->Total == Temp->Total && History->Type == Temp->Type) {
                    found = true;
                    break;
                }
                History = History->next;
            }

            if (found) {
                History->Status = Temp->Status;
                return;
            }
        }

    }



    void Deliver_Orders(Employee* currentEmp, Graph* graph)
    {

        if (currentEmp->Delivery == nullptr)
        {
            cout << "No Orders to Deliver " << endl;
            return;
        }


        int Number = currentEmp->Count;
        if (!Number) {
            return;
        }

        string* Sector = new string[Number];
        int i = 0;
        Order* Demi = currentEmp->Delivery;
        while (Demi != nullptr)
        {
            Demi->Status = 'R';//Reached
            currentEmp->History_Orders(current, Demi);
            UpdateCustHistory(Demi);
            Sector[i] = Demi->Location;
            i++;
            Demi = Demi->next;
        }
        i = 0;


        bool* Checker = new bool[Number];
        int* Prices = new int[Number];

        for (int i = 0; i < Number; i++)
        {
            Checker[i] = false;
            Prices[i] = INT_MAX;

        }
        string Source = currentEmp->workPlace->Location;

        int Index = 1;
        while (Index != -1)
        {


            for (int j = 0; j < Number; j++) {

                if (!Checker[j])
                {
                    Prices[j] = Dj_Algo(graph, Source, Sector[j], 0);


                }

            }
            Index = Get_Smallest(Prices, Checker, Number);
            if (Index == -1)
                break;
            int Get = Dj_Algo(graph, Source, Sector[Index], 1);

            if (Get == INT_MAX) {
                cout << "No path exists between the sectors (" << Source << ", " << Sector[Index] << ")." << endl;
            }
            else {
                Source = Sector[Index];
            }

            Checker[Index] = true;

        }

        currentEmp->Count = 0;   // Delivery Irders will be 0
        currentEmp->Delivery = nullptr;  // Delivery Orders wll become zero 

        delete[] Sector;
        delete[] Checker;
        delete[] Prices;

    }


    int Get_Smallest(int* Prices, bool* Checker, int Number) {
        int index = -1;
        int  Max = INT_MAX;
        for (int i = 0; i < Number; i++)
        {
            if (!Checker[i] && Prices[i] != INT_MAX)
            {

                if (Prices[i] < Max) {
                    Max = Prices[i];
                    index = i;

                }
            }
        }
        return index;
    }





    void Read_File(string Name)
    {

        ifstream Obj(Name + ".txt");//Making File Object for reading
        if (!Obj)
        {
            cout << "File Not Found " << endl;//Not Found 
            return;
        }


        string Line;
        int Count = 0;

        while (getline(Obj, Line))//Reading the whole line
        {
            cout << Line << endl;
        }

        Obj.close();//Close file


    }


};











struct Reviews {
    int id = 0;
    int Rating = 0;
    string description = "";
    int custId = 0;
    Restaurant* res = nullptr;
};

struct ReviewNode {
    Reviews data;

};

class ManageReviews {
    int idNo;
    ReviewNode* Good[100];
    ReviewNode* Bad[100];
    int Size;

public:
    ManageReviews(int id = 69696, int Size = 100) : idNo(id), Size(Size) {
        for (int i = 0; i < Size; i++) {
            Good[i] = nullptr;
            Bad[i] = nullptr;
        }
    }

    ReviewNode* NewReview(Reviews& data) {
        ReviewNode* New = new ReviewNode;
        New->data = data;
        return New;
    }

    //Swaps data
    void swap(ReviewNode*& a, ReviewNode*& b)
    {
        Reviews temp = b->data;
        b->data = a->data;
        a->data = temp;
    }

    //level order insert
    void insertLO(ReviewNode*& dataGood, ReviewNode*& dataBad) {

        int Index = idNo - 69696;
        Good[Index] = dataGood;
        Bad[Index] = dataBad;

        idNo++;
    }

    void heapifyGood(int n, int i)
    {

        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && Good[l]->data.Rating < Good[largest]->data.Rating)
            largest = l;

        if (r < n && Good[r]->data.Rating < Good[largest]->data.Rating)
            largest = r;

        if (largest != i)
        {

            swap(Good[i], Good[largest]);
            heapifyGood(n, largest);

        }

    }

    void heapSortGood(int n)
    {

        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyGood(n, i);

        for (int i = n - 1; i > 0; i--)
        {

            swap(Good[0], Good[i]);
            heapifyGood(i, 0);

        }

    }

    void heapifyBad(int n, int i)
    {

        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && Bad[l]->data.Rating > Bad[smallest]->data.Rating)
            smallest = l;

        if (r < n && Bad[r]->data.Rating > Bad[smallest]->data.Rating)
            smallest = r;

        if (smallest != i)
        {

            swap(Bad[i], Bad[smallest]);
            heapifyBad(n, smallest);

        }

    }

    void heapSortBad(int n)
    {

        for (int i = n / 2 - 1; i >= 0; i--)

            heapifyBad(n, i);

        for (int i = n - 1; i > 0; i--)
        {

            swap(Bad[0], Bad[i]);
            heapifyBad(i, 0);

        }

    }


    void AddReview(Reviews& data) {
        ReviewNode* newGood = NewReview(data);
        ReviewNode* newBad = NewReview(data);

        newGood->data.id = idNo - 1;
        newBad->data.id = idNo - 1;

        insertLO(newGood, newBad);
        int S = idNo - 69696;
        heapSortGood(S);
        heapSortBad(S);

    }
    ReviewNode* SearchReviewGood(int id) {
        int S = idNo - 69696;
        for (int i = 0; i < S; i++) {
            if (Good[i]->data.id == id) {
                return Good[i];
            }
        }
        return nullptr;
    }

    ReviewNode* SearchReviewGoodCust(int id, int No) {
        int S = idNo - 69696;
        int j = 0;
        for (int i = 0; i < S; i++) {
            if (Good[i]->data.custId == id) {
                j++;
                if (j == No)
                    return Good[i];
            }
        }
        return nullptr;
    }

    ReviewNode* SearchReviewBad(int id) {
        int S = idNo - 69696;
        for (int i = 0; i < S; i++) {
            if (Bad[i]->data.id == id) {
                return Bad[i];
            }
        }
        return nullptr;
    }

    ReviewNode* SearchReviewBadCust(int id, int No) {
        int S = idNo - 69696;
        int j = 0;
        for (int i = 0; i < S; i++) {
            if (Bad[i]->data.custId == id) {
                j++;
                if (j == No)
                    return Bad[i];
            }
        }
        return nullptr;
    }

    int PrintForCust(int idCust) {
        int S = idNo - 69696;
        int No = 0;
        for (int i = 0; i < S; i++) {
            if (Good[i]->data.custId == idCust) {
                No++;
                cout << "\n" << No << "- Resturant:\n";
                cout << "Name: " << Bad[i]->data.res->Name << endl;
                cout << "Rating: ";
                for (int j = 0; j < Good[i]->data.Rating; j++) {
                    cout << "*";
                }
                cout << "\nDescription: " << Good[i]->data.description << endl;

            }
        }
        return No;
    }

    void deleteReview(int idCust) {
        int No = PrintForCust(idCust);//To determine customer review No
        if (No == 0) {
            cout << "No reviews currently." << endl;
        }

        int choice = 0;
        cout << "Enter the review No(1-" << No << "): ";
        cin >> choice;
        cin.clear();
        cin.ignore();

        if (choice<1 || choice>No) {
            cout << "Enter from 1-" << No << ": ";
            cin >> choice;
            cin.clear();
            cin.ignore();
        }

        ReviewNode* ToDelete1 = SearchReviewGoodCust(idCust, choice);

        int S = idNo - 69696;
        S--;
        ReviewNode* Last1 = Good[S];
        ReviewNode* Last2 = Bad[S];

        ReviewNode* ToDelete2 = SearchReviewBad(ToDelete1->data.id);

        if (Last1->data.id == ToDelete1->data.id) {
            delete Last1;
            Last1 = nullptr;
        }
        else {
            swap(Last1, ToDelete1);
            delete Last1;
            Last1 = nullptr;
            heapSortGood(S);
        }

        if (Last2->data.id == ToDelete2->data.id) {
            delete Last2;
            Last2 = nullptr;
        }
        else {
            swap(Last2, ToDelete2);
            delete Last2;
            Last2 = nullptr;
            heapSortBad(S);
        }


        idNo--;
    }

    void EditReview(int idCust) {

        int No = PrintForCust(idCust);//To determine customer review No
        if (No == 0) {
            cout << "No reviews currently." << endl;
        }

        int choice = 0;
        cout << "Enter the review No(1-" << No << "): ";
        cin >> choice;
        cin.clear();
        cin.ignore();

        if (choice<1 || choice>No) {
            cout << "Enter from 1-" << No << ": ";
            cin >> choice;
            cin.clear();
            cin.ignore();
        }

        ReviewNode* toEdit = SearchReviewGoodCust(idCust, choice);
        ReviewNode* toEdit2 = SearchReviewBad(toEdit->data.id);

        cout << "Enter the review rating (1-5): ";
        cin >> toEdit->data.Rating;
        cin.clear();
        cin.ignore();

        while (toEdit->data.Rating < 1 || toEdit->data.Rating>5) {
            cout << "Enter Correct rating: ";
            cin >> toEdit->data.Rating;
            cin.clear();
            cin.ignore();
        }

        toEdit2->data.Rating = toEdit->data.Rating;
        cout << "Enter the description: ";
        getline(cin, toEdit->data.description);
        toEdit2->data.description = toEdit->data.description;

        cout << "Review Edited Successfully!" << endl;
    }

    void ViewReviews() {
        int choice;
        cout << "Press\n1-Print Top 5 Good Reviews\n2-Print Top 5 Bad Reviews\nEnter choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore();

        while (choice != 1 && choice != 2) {
            cout << "Enter correct choice: ";
            cin >> choice;
            cin.clear();
            cin.ignore();
        }

        int S = idNo - 69696;

        if (choice == 1) {
            int No = 0;
            for (int i = 0; i < S + 1; i++) {
                if (i >= 5) {
                    break;
                }
                if (i + 1 == S + 1 && S < 5) {
                    cout << "No more reviews..." << endl;
                    break;
                }
                No++;
                cout << "\n" << No << "- Resturant:\n";
                cout << "Name: " << Bad[i]->data.res->Name << endl;
                cout << "Rating: ";
                for (int j = 0; j < Good[i]->data.Rating; j++) {
                    cout << "*";
                }
                cout << "\nDescription: " << Good[i]->data.description << endl;
            }
        }
        else {
            int No = 0;
            for (int i = 0; i < S + 1; i++) {
                if (i >= 5) {
                    break;
                }
                if (i + 1 == S + 1 && S < 5) {
                    cout << "No more reviews..." << endl;
                    break;
                }
                No++;
                cout << "\n" << No << "- Resturant:\n";
                cout << "Name: " << Bad[i]->data.res->Name << endl;
                cout << "Rating: ";
                for (int j = 0; j < Bad[i]->data.Rating; j++) {
                    cout << "*";
                }
                cout << "\nDescription: " << Bad[i]->data.description << endl;
            }
        }
    }

    void PrintForRes(Restaurant* res) {
        int S = idNo - 69696;
        int No = 0;
        if (S == 0) {
            cout << "No reviews currently...." << endl;
        }

        for (int i = 0; i < S; i++) {
            if (Good[i]->data.res->Name == res->Name && Good[i]->data.res->Type == res->Type) {
                No++;
                cout << "\n" << No << "- Resturant:\n";
                cout << "Name: " << Good[i]->data.res->Name << endl;
                cout << "Rating: ";
                for (int j = 0; j < Good[i]->data.Rating; j++) {
                    cout << "*";
                }
                cout << "\nDescription: " << Good[i]->data.description << endl;
            }
        }
    }


    void ReviewMenu(int custId, Restaurant* res) {
        ManageReviews reviewManager;
        int choice;

        do {
            cout << "\n=== Review Menu ===" << endl;
            cout << "1. Add a Review" << endl;
            cout << "2. Edit a Review" << endl;
            cout << "3. Delete a Review" << endl;
            cout << "4. View Your Reviews" << endl;
            cout << "5. View Top Reviews" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

            switch (choice) {
            case 1: {
                Reviews newReview;
                newReview.custId = custId;
                newReview.res = res;

                cout << "Enter rating (1-5): ";
                cin >> newReview.Rating;
                while (newReview.Rating < 1 || newReview.Rating > 5) {
                    cout << "Invalid rating! Enter a value between 1 and 5: ";
                    cin >> newReview.Rating;
                }

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

                cout << "Enter review description: ";
                getline(cin, newReview.description);

                reviewManager.AddReview(newReview);
                cout << "Review added successfully!" << endl;
                break;
            }
            case 2:
                reviewManager.EditReview(custId);
                break;

            case 3:
                reviewManager.deleteReview(custId);
                break;

            case 4: {
                int reviewsCount = reviewManager.PrintForCust(custId);
                if (reviewsCount == 0) {
                    cout << "You have no reviews currently." << endl;
                }
                break;
            }
            case 5:
                reviewManager.ViewReviews();
                break;

            case 0:
                cout << "Exiting Review Menu..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        } while (choice != 0);
    }


};










Graph Make_Graph(int n)
{
    Graph graph(n);

    string vertices[] = {
        "F-5", "F-6", "F-7", "F-8", "F-9", "F-10", "F-11", "F-12",
        "G-5", "G-6", "G-7", "G-8", "G-9", "G-10", "G-11", "G-12",
        "G-13", "G-14", "H-7", "H-8", "H-9", "H-10",
        "H-11", "H-12", "I-8", "I-9", "I-10",
        "I-11", "I-12", "I-14", "I-15", "I-16"
    };


    for (int i = 0; i < n; ++i) {
        graph.addVertex(i, vertices[i]);
    }

    // Add edges (based on your input)
    graph.addEdge("F-12", "G-6", 12);
    graph.addEdge("G-12", "H-9", 8);
    graph.addEdge("G-8", "F-12", 7);
    graph.addEdge("F-9", "I-8", 11);
    graph.addEdge("G-6", "F-9", 6);
    graph.addEdge("H-8", "I-10", 2);
    graph.addEdge("F-11", "H-9", 5);
    graph.addEdge("F-5", "F-8", 15);
    graph.addEdge("I-11", "I-9", 7);
    graph.addEdge("F-12", "F-6", 13);
    graph.addEdge("H-11", "G-7", 1);
    graph.addEdge("I-15", "G-12", 3);
    graph.addEdge("I-12", "H-8", 9);
    graph.addEdge("I-14", "G-6", 2);
    graph.addEdge("I-12", "I-9", 8);
    graph.addEdge("F-12", "I-16", 10);
    graph.addEdge("F-9", "F-12", 9);
    graph.addEdge("F-11", "G-9", 10);
    graph.addEdge("I-14", "G-11", 1);
    graph.addEdge("F-7", "G-9", 15);
    graph.addEdge("I-9", "H-10", 4);
    graph.addEdge("I-16", "G-14", 2);
    graph.addEdge("F-6", "I-15", 8);
    graph.addEdge("F-12", "I-14", 13);
    graph.addEdge("F-9", "H-11", 10);
    graph.addEdge("H-10", "I-10", 5);
    graph.addEdge("G-14", "G-12", 14);
    graph.addEdge("H-11", "G-13", 1);
    graph.addEdge("I-12", "I-15", 6);
    graph.addEdge("F-9", "G-10", 3);
    graph.addEdge("F-5", "F-10", 2);
    graph.addEdge("G-9", "G-14", 12);
    graph.addEdge("I-9", "F-11", 14);
    graph.addEdge("I-16", "F-7", 5);
    graph.addEdge("F-9", "I-11", 8);
    graph.addEdge("H-9", "G-7", 2);
    graph.addEdge("I-8", "G-11", 10);
    graph.addEdge("H-11", "I-12", 9);
    graph.addEdge("G-12", "F-8", 4);
    graph.addEdge("F-10", "F-7", 6);
    graph.addEdge("F-5", "I-16", 7);
    graph.addEdge("H-8", "I-16", 13);
    graph.addEdge("H-9", "G-8", 6);
    graph.addEdge("I-11", "F-8", 4);
    graph.addEdge("I-12", "G-12", 15);
    graph.addEdge("F-6", "I-9", 3);
    graph.addEdge("I-14", "I-12", 8);
    graph.addEdge("F-11", "G-5", 1);
    graph.addEdge("G-8", "I-9", 5);
    graph.addEdge("H-8", "G-5", 11);
    graph.addEdge("F-10", "F-11", 6);
    graph.addEdge("G-10", "F-12", 5);
    graph.addEdge("G-9", "H-11", 7);
    graph.addEdge("H-9", "F-9", 11);
    graph.addEdge("F-12", "F-5", 2);
    graph.addEdge("F-6", "I-12", 9);
    graph.addEdge("I-15", "F-12", 14);
    graph.addEdge("G-5", "I-14", 12);
    graph.addEdge("F-9", "G-6", 15);
    graph.addEdge("I-15", "F-9", 7);
    graph.addEdge("G-8", "G-7", 2);
    graph.addEdge("F-12", "F-6", 14);
    graph.addEdge("H-9", "I-8", 3);
    graph.addEdge("G-10", "F-11", 1);
    graph.addEdge("I-8", "I-15", 2);
    graph.addEdge("F-9", "I-16", 9);
    graph.addEdge("H-9", "I-10", 3);
    graph.addEdge("H-8", "G-11", 6);
    graph.addEdge("H-11", "G-12", 4);
    graph.addEdge("I-9", "G-12", 7);
    graph.addEdge("I-8", "G-8", 10);
    graph.addEdge("H-10", "I-8", 5);
    graph.addEdge("G-12", "I-11", 12);
    graph.addEdge("I-10", "F-5", 15);
    graph.addEdge("F-10", "G-10", 13);
    graph.addEdge("F-6", "F-12", 1);
    graph.addEdge("I-14", "H-11", 2);
    graph.addEdge("G-11", "F-10", 5);
    graph.addEdge("I-10", "I-16", 14);
    graph.addEdge("F-10", "F-6", 3);
    graph.addEdge("F-12", "F-8", 6);
    graph.addEdge("F-8", "F-6", 7);
    graph.addEdge("G-9", "F-11", 11);
    graph.addEdge("F-6", "H-9", 12);
    graph.addEdge("F-8", "G-9", 4);
    graph.addEdge("F-12", "H-11", 3);
    graph.addEdge("H-11", "I-15", 5);
    graph.addEdge("I-12", "G-14", 8);
    graph.addEdge("G-6", "F-9", 10);
    graph.addEdge("I-9", "G-11", 9);

    return graph;
}










int main()
{
    Restaurant_Manage manager;



    ManageCustomer Cust;
    ManageEmployee employee;
    HashMap CustHashing;
    HashMapEmployee EmpHashing;

    ManageReviews review;

    Graph graph = Make_Graph(32);
    Employee* Populate1 = new Employee;
    Populate1->email = "hamza@gmail.com";
    Populate1->password = "Get123??";
    Populate1->name = "Hamza";
    int hash1 = EmpHashing.PasswordToHashValue(Populate1->password);
    EmpHashing.insert(Populate1, hash1);

    manager.Add_Restaurant("Kfc", "Fast Food", "F-8", Populate1);

    Employee* Populate2 = new Employee;
    Populate2->email = "Irfi@gmail.com";
    Populate2->password = "Got123!!";
    Populate2->name = "Irfan";
    hash1 = EmpHashing.PasswordToHashValue(Populate2->password);
    EmpHashing.insert(Populate2, hash1);

    manager.Add_Restaurant("Lala ke mashoor chole", "desi", "F-12", Populate2);

    Customer* Populate3 = new Customer;
    Populate3->email = "Irfi@gmail.com";
    Populate3->password = "Got123!!";
    Populate3->name = "Irfan";
    hash1 = EmpHashing.PasswordToHashValue(Populate3->password);
    CustHashing.insert(Populate3, hash1);

    Customer* Populate5 = new Customer;
    Populate5->email = "bilu@gmail.com";
    Populate5->password = "gET123??";
    Populate5->name = "meow";
    hash1 = EmpHashing.PasswordToHashValue(Populate5->password);
    CustHashing.insert(Populate5, hash1);

    Employee* Populate4 = new Employee;
    Populate4->email = "Gulab@gmail.com";
    Populate4->password = "12345Aa?";
    Populate4->name = "jamun";
    hash1 = EmpHashing.PasswordToHashValue(Populate4->password);
    EmpHashing.insert(Populate4, hash1);
    Populate4->workPlace = Populate1->workPlace;

    Employee* Populate6 = new Employee;
    Populate6->email = "Ajmal@gmail.com";
    Populate6->password = "Aa12345!!";
    Populate6->name = "ajmal";
    Populate6->isDeliveryDriver = 1;
    hash1 = EmpHashing.PasswordToHashValue(Populate6->password);
    EmpHashing.insert(Populate6, hash1);
    Populate6->workPlace = Populate1->workPlace;

    int choice;

    bool customerLoop = 0, empLoop = 0, AdminLoop = 0, MainLoop = 1;
    bool isEmpLogged = 0, isCustLogged = 0, isAdminLogged = 0;
    bool isDeliveryDriver = 0;

    do {

        if (customerLoop == 0 && empLoop == 0 && AdminLoop == 0 && MainLoop == 1 && isEmpLogged == 0 && isCustLogged == 0 && isAdminLogged == 0) {
            cout << "==============================" << endl;
            cout << "   Restaurant Management      " << endl;
            cout << "==============================" << endl;
            cout << "Are you a:" << endl;
            cout << "1. Customer" << endl;
            cout << "2. Employee" << endl;
            cout << "3. Admin" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
            case 1: {
                customerLoop = 1;
                break;
            }
            case 2: {
                empLoop = 1;
                break;
            }
            case 3: {
                AdminLoop = 1;
                break;
            }

            case 4:
                cout << "Exiting program. Thank you!" << endl;
                MainLoop = 0;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        else if (customerLoop == 1) {
            int choiceCust = 0;
            cout << "----------------Welcome!----------------------" << endl;
            cout << "1. Sign up" << endl;
            cout << "2. Login" << endl;
            cout << "3. Help " << endl;
            cout << "4. Go Back" << endl;
            cin >> choiceCust;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choiceCust) {
            case 1: {
                Cust.SignUp(CustHashing);
                customerLoop = 0;
                isCustLogged = 1;
                break;
            }
            case 2: {
                Cust.Login(CustHashing);
                Customer* cur = Cust.Get_Current();
                if (!cur) {
                    continue;
                }
                customerLoop = 0;
                isCustLogged = 1;
                break;
            }


            case 3:
            {
                Cust.Read_File("Customer");
                break;
            }


            case 4:
                cout << "Going Back..." << endl;
                customerLoop = 0;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
            }

        }
        else if (empLoop == 1) {
            int choiceCust = 0;
            cout << "----------------Welcome!---------------------- - " << endl;
            cout << "1. Sign up" << endl;
            cout << "2. Login" << endl;
            cout << "3. Help " << endl;
            cout << "4. Go Back" << endl;
            cin >> choiceCust;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choiceCust) {
            case 1: {
                cout << "Login from a manager account first:" << endl;
                employee.Login(EmpHashing);
                Employee* cur = employee.Get_Current();
                if (!cur) {
                    continue;
                }
                Restaurant* CheckManager = manager.Check_Manager(cur);
                if (!CheckManager) {
                    cout << "The employee logged in is not a manager\nEnter a manager id to sign up" << endl;
                }
                employee.Set_Current(nullptr);

                employee.SignUp(EmpHashing, CheckManager);
                empLoop = 0;
                isEmpLogged = 1;
                break;
            }
            case 2: {
                employee.Login(EmpHashing);
                Employee* cur = employee.Get_Current();
                if (!cur) {
                    continue;
                }

                empLoop = 0;
                isEmpLogged = 1;
                break;
            }


            case 3:
            {
                Cust.Read_File("Employee");
                break;
            }



            case 4:
                cout << "Going Back..." << endl;
                empLoop = 0;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }

        else if (AdminLoop == 1) {
            int choiceAdmin = 0;
            string adminPassword = "AsimMunir";

            cout << "Salam Sir!" << endl;
            cout << "1. Login kren ge sir " << endl;
            cout << "2. Go Back " << endl;


            cout << "Enter your choice " << endl;
            cin >> choiceAdmin;
            cin.clear();
            cin.ignore();


            if (choiceAdmin == 1)
            {
                cout << "Enter your password: ";
                string pass;
                getline(cin, pass);
                if (pass == adminPassword) {
                    isAdminLogged = 1;
                    AdminLoop = 0;
                }

            }
            else if (choiceAdmin == 2) {
                cout << "Going Back..." << endl;;
                AdminLoop = 0;
            }

            else {
                cout << "Enter valid choice." << endl;
            }

        }

        if (isCustLogged) {
            Customer* Custom = Cust.Get_Current();
            int choice1 = 0;
            do
            {
                cout << "==============================" << endl;
                cout << "        Customer Menu         " << endl;
                cout << "==============================" << endl;
                cout << "1. Place order " << endl;
                cout << "2. Check Order History " << endl;
                cout << "3. Check Current Order Status " << endl;
                cout << "4. Update your information  " << endl;
                cout << "5. Reviews " << endl;
                cout << "6. Delete ID  " << endl;
                cout << "7. Print ID " << endl;
                cout << "8. Logout" << endl;
                cout << "Enter your choice " << endl;
                cin >> choice1;
                cin.clear();
                cin.ignore();


                if (choice1 == 1)
                {
                    if (!manager.Print_Restaurant())
                    {
                        cout << "No resturant currently available" << endl;
                        continue;
                    }

                    string name, type;
                    cout << "Enter Restaurant Name to Search: ";

                    getline(cin, name);
                    cout << "Enter Restaurant Type: ";
                    getline(cin, type);

                    if (!manager.Make_Order(Custom, name, type)) {
                        cout << "Resturant could not be found." << endl;
                    }
                }

                else if (choice1 == 2)
                {
                    Cust.PrintOrder();

                }
                else if (choice1 == 3) {
                    if (Custom->current)
                    {
                        Custom->current->Print_Order();
                    }
                }
                else if (choice1 == 4) {
                    Cust.Edit(CustHashing);
                }
                else if (choice1 == 5) {
                    Restaurant* curr = manager.getCurrent();
                    if (curr == nullptr) {
                        cout << "You have not visited any resturants yet" << endl;
                        continue;
                    }
                    Customer* currentCust = Cust.Get_Current();
                    review.ReviewMenu(currentCust->id, curr);
                }
                else if (choice1 == 6) {
                    Cust.DeleteId(CustHashing);
                }

                else if (choice1 == 7) {
                    Cust.Print();
                }

                else if (choice1 == 8) {
                    Cust.logout();
                    isCustLogged = 0;
                    customerLoop = 1;
                }

                else
                {
                    cout << "Invalid Choice " << endl;
                }



            } while (choice1 != 8);
        }

        if (isEmpLogged) {
            isDeliveryDriver = employee.Get_Current()->isDeliveryDriver;

            if (isDeliveryDriver) {
                int choice2;
                do
                {


                    cout << "==============================" << endl;
                    cout << "        Delivery Driver         " << endl;
                    cout << "==============================" << endl;
                    cout << "1. Proceed order " << endl;
                    cout << "2. Check Order History " << endl;
                    cout << "3. Check Restuarent orders " << endl;
                    cout << "4. Update your information  " << endl;
                    cout << "5. Check Review " << endl;
                    cout << "6. Deliver Orders " << endl;
                    cout << "7. Print Orders " << endl;
                    cout << "8.. Logout " << endl;


                    cout << "Enter your choice " << endl;
                    cin >> choice2;
                    cin.clear();
                    cin.ignore();


                    if (choice2 == 1)
                    {
                        employee.Proceed_Orders();

                    }
                    else if (choice2 == 2) {
                        employee.Print_Delivery_Orders();
                    }
                    else if (choice2 == 3)
                    {
                        employee.Check_Orders();
                    }
                    else if (choice2 == 4) {
                        employee.Edit(EmpHashing);
                    }
                    else if (choice2 == 5) {
                        review.PrintForRes(manager.getCurrent());
                    }

                    else if (choice2 == 6) {
                        employee.Deliver_Orders(employee.Get_Current(), &graph);
                    }
                    else if (choice2 == 7) {
                        employee.Print_Delivery_Orders();
                    }

                    else if (choice2 == 8) {
                        employee.logout();
                        isEmpLogged = 0;
                        empLoop = 1;
                    }

                    else {
                        cout << "Invalid choice!" << endl;
                    }




                } while (choice2 != 8);
            }

            else {
                int choice2;
                do
                {


                    cout << "==============================" << endl;
                    cout << "        Employee Menu         " << endl;
                    cout << "==============================" << endl;
                    cout << "1. Proceed order " << endl;
                    cout << "2. Check Order History " << endl;
                    cout << "3. Check Restuarent orders " << endl;
                    cout << "4. Update your information  " << endl;
                    cout << "5. Check Review " << endl;
                    cout << "6. Promotions " << endl;
                    cout << "7. Set Menu " << endl;
                    cout << "8. Print Id " << endl;
                    cout << "9. Delete Id " << endl;
                    cout << "10.. Logout " << endl;


                    cout << "Enter your choice " << endl;
                    cin >> choice2;
                    cin.clear();
                    cin.ignore();


                    if (choice2 == 1)
                    {
                        employee.Proceed_Orders();

                    }
                    else if (choice2 == 2) {
                        employee.PrintOrder();
                    }
                    else if (choice2 == 3)
                    {
                        employee.Check_Orders();
                    }
                    else if (choice2 == 4) {
                        employee.Edit(EmpHashing);
                    }
                    else if (choice2 == 5) {
                        review.PrintForRes(manager.getCurrent());
                    }

                    else if (choice2 == 6) {
                        Restaurant* Demi = manager.Check_Manager(employee.Get_Current());
                        if (Demi == nullptr) {
                            cout << "You are not a maanger " << endl;
                            continue;

                        }
                        else
                        {
                            manager.Insert_Promotion(Demi);
                        }
                    }
                    else if (choice2 == 7) {
                        Restaurant* Demi = manager.Check_Manager(employee.Get_Current());
                        if (Demi == nullptr) {
                            cout << "You are not a maanger " << endl;
                            continue;

                        }
                        else
                        {
                            manager.Found(Demi);
                        }
                    }

                    else if (choice2 == 8) {
                        employee.Print();
                    }
                    else if (choice2 == 9) {
                        employee.DeleteId(EmpHashing);
                    }

                    else if (choice2 == 10) {
                        employee.logout();
                        isEmpLogged = 0;
                        empLoop = 1;
                    }

                    else {
                        cout << "Invalid choice!" << endl;
                    }




                } while (choice2 != 10);
            }



        }

        if (isAdminLogged) {
            int choice3;
            do
            {


                cout << "==============================" << endl;
                cout << "        Admin Menu         " << endl;
                cout << "==============================" << endl;
                cout << "1. Add Resturant " << endl;
                cout << "2. Remove Resturant " << endl;
                cout << "3. Logout " << endl;


                cout << "Enter your choice " << endl;
                cin >> choice3;
                cin.clear();
                cin.ignore();


                if (choice3 == 1)
                {
                    string ResName, ResType, ResLoc;
                    cout << "Enter Restaurant name: ";
                    getline(cin, ResName);
                    cout << "Enter Restaurant Type: ";
                    getline(cin, ResType);
                    string vertices[] = {
                            "F-5", "F-6", "F-7", "F-8", "F-9", "F-10", "F-11", "F-12",
                            "G-5", "G-6", "G-7", "G-8", "G-9", "G-10", "G-11", "G-12",
                            "G-13", "G-14", "H-7", "H-8", "H-9", "H-10",
                            "H-11", "H-12", "I-8", "I-9", "I-10",
                            "I-11", "I-12", "I-14", "I-15", "I-16"
                    };


                    for (int i = 0; i < 32; i++) {
                        cout << vertices[i] << "  ";
                    }

                    bool found = false;
                    do {

                        cout << "Enter Lcaotion from the above: ";
                        getline(cin, ResLoc);
                        for (int i = 0; i < 32; i++) {
                            if (ResLoc == vertices[i]) {
                                found = true;
                            }
                        }
                    } while (!found);

                    Employee* man = employee.ManagerCreation(EmpHashing);

                    manager.Add_Restaurant(ResName, ResType, ResLoc, man);



                }
                else if (choice3 == 2) {
                    string ResName, ResType;
                    cout << "Enter Restaurant name to remove: ";
                    getline(cin, ResName);
                    cout << "Enter Restaurant Type to remove: ";
                    getline(cin, ResType);
                    ManageEmployee empTemp;

                    Restaurant* TempRes = manager.Return_Restaurant(ResName, ResType);
                    if (TempRes) {
                        empTemp.Set_Current(TempRes->Man);
                        empTemp.DeleteId(EmpHashing);
                        cout << "All employees of the restaurant removed" << endl;
                    }

                    manager.Remove_Restaurant(ResName, ResType);
                }
                else if (choice3 == 3)
                {
                    cout << "Logging out..." << endl;
                    isAdminLogged = 0;
                    AdminLoop = 1;
                }
                else {
                    cout << "Invalid choice!" << endl;
                }



            } while (choice3 != 3);

        }



    } while (MainLoop);

    return 0;
}
