/***************************************************************************
* COMSC-210 | Lab 17 | Grant Luo
* Editor: CLion
* Compiler: Apple clang version 16.0.0
*/
#include <iostream>
using namespace std;

const int SIZE = 7;  

struct Node
{
    float value;
    Node* next;

    Node() : value(0.0), next(nullptr) {}
    ~Node() {} // Destructor intentionally left empty to prevent recursive deletion
};

// Function Prototypes
void createList(Node* &);
void output(Node*);
void traverse(Node* &, Node* &, int const);
int getEntry(const string, Node*);
void insertNode(Node* &);
void deleteNode(Node* &);
void deleteList(Node* &);
void print_id(string const& lab_desc);

int main()
{
    print_id("Lab 17: Modularize the Linked List Code");

    Node *head = nullptr;

    // create a linked list of SIZE with random numbers 0-99
    createList(head);
    output(head);

    // deleting a node
    deleteNode( head);
    output(head);

    // insert a node
    insertNode(head);
    output(head);

    // deleting the linked list
    deleteList(head);
    output(head);

    head = nullptr;

    return 0;
}

/******************************************************************************************************************
 * FUNCTION: creates a linked list of SIZE consisting of random float values
 *
 * @param head
 *
 * @return NONE;
 */
void createList(Node* &head)
{
    for (int i = 0; i < SIZE; i++)
    {
        int tmp_val = rand() % 100;
        Node *newVal = new Node;

        // adds node at head
        if (head == nullptr)
        { // if this is the first node, it's the new head
            head = newVal;
            newVal->next = nullptr;
            newVal->value = static_cast<float>(tmp_val);
        }
        else
        { // its a second or subsequent node; place at the head
            newVal->next = head;
            newVal->value = static_cast<float>(tmp_val);
            head = newVal;
        }
    }
}

/*********************************************************
 * FUNCTION: displays the content of the linked list
 *
 * @param hd
 *
 * @return NONE;
 */
void output(Node* hd)
{
    if (hd == nullptr)
    {
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    const Node* current = hd;
    while (current != nullptr)
    {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << endl;
}

/**********************************************************************
 * FUNCTION: reroutes the pointers to the entry position for deletion/insertion
 *
 * @param current
 * @param prev
 * @param theEntry
 *
 * @return NONE;
 */
void traverse(Node* &current, Node* &prev, int const theEntry)
{
    for (int i = 1; i <= theEntry; i++)
        if (i != 1)
        {
            prev = current;
            current = current->next;
        }
}

/********************************************************
 * FUNCTION: asks users for the entry position with error handling
 * @param message
 * @param head
 *
 * @return NONE;
 */
int getEntry(const string message, Node* head)
{
    cout << message << '\n';
    output(head);
    int theEntry;
    string entry;

    while (true)
    {
        try
        {
            cout << "Choice --> ";
            cin >> entry;
            cin.ignore(1000, '\n');
            theEntry = stoi(entry);

            if (theEntry > 0)
                break;
            else
                cout << "Please enter a positive number\n";
        }
        catch (invalid_argument &)
        {
            cout << "Error: You did not enter a valid entry.\n";
        }
    }

    return theEntry;
}

/***********************************************************
 * FUNCTION: deletes the node at the entry position
 *
 * @param head
 *
 * @return NONE;
 */
void deleteNode(Node* &head)
{
    Node* current = head;
    Node* prev = nullptr;

    string message = "Which node to delete? ";
    int theEntry = getEntry(message, head);

    traverse(current, prev, theEntry);

    // at this point, delete current and reroute pointers
    if (current == nullptr) // checks for current to be valid before deleting the node
        cout << "Empty list - nothing to delete\n";
    else
    {
        if (prev == nullptr) // Deleting the head node
        {
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        delete current;
        current = nullptr;
    }
}

/***********************************************************************
 * FUNCTION: inserts a new node right after the entry position
 *
 * @param head
 *
 * @return NONE;
 */
void insertNode(Node* &head)
{
    Node* current = head;
    Node* prev = nullptr;

    string message = "After which node to insert 10000? ";
    int theEntry = getEntry(message, head);

    traverse(current, prev, theEntry);
    Node* newNode = new Node;
    newNode->value = 10000.0;
    newNode->next = current->next;
    current->next = newNode;
}

/***********************************************************
 * FUNCTION: deletes the entire linked list to free up the allocated memory in heap
 *
 * @param head
 *
 * @return NONE;
 */
void deleteList(Node* &head)
{
    Node* current;
    while (head != nullptr)
    {
        current = head;
        head = current->next;
        delete current;
    }
}

void print_id(string const& lab_desc)
{
    cout << "\nCOMSC210 | Grant Luo | " << lab_desc << "\n";
    cout << "Editor: CLion\n";
    cout << "Compiler: Apple clang version 16.0.0\n";
    cout << "File: " << __FILE__ << "\n";
    cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}