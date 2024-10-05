#include <iostream>
using namespace std;

const int SIZE = 7;  

struct Node
{
    float value;
    Node* next;

    Node() : value(0.0), next(nullptr) {}
    ~Node()
    {
        delete next;
        next = nullptr;
    }
};

void createList(Node* &);
void output(const Node*);
void traverse(Node* &, Node* &);
int getEntry(const string, Node*);
void insertNode(Node*, Node*, Node*);
void deleteNode(Node*, Node*, Node*);
void deleteList(Node*);

int main() {
    Node *head = nullptr;
    int count = 0;

    // create a linked list of size SIZE with random numbers 0-99
    createList(head);
    output(head);

    Node* current = head;
    Node* prev = nullptr;
    // deleting a node
    deleteNode(current, prev, head);

    // insert a node
    insertNode(current, prev, head);
    output(head);

    // deleting the linked list
    deleteList(head);
    output(head);

    head = nullptr;

    return 0;
}

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
            newVal->value = tmp_val;
        }
        else
        { // its a second or subsequent node; place at the head
            newVal->next = head;
            newVal->value = tmp_val;
            head = newVal;
        }
    }
}

void output(Node* hd) {
    if (hd == nullptr)
    {
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    Node* current = hd;
    while (current != nullptr)
    {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << endl;
}

void traverse(Node* &current, Node* &prev, int const theEntry)
{
    for (int i = 1; i <= theEntry; i++)
        if (i != 1)
        {
            prev = current;
            current = current->next;
        }
}

int getEntry(const string message, Node* head)
{
    cout << message << '\n';
    output(head);
    int theEntry;
    string entry;
    do
    {
        cout << "Choice --> ";
        cin >> entry;
        cin.ignore(1000, '\n');
        while (true)
        {
            try
            {
                theEntry = stoi(entry);
                break;
            }
            catch (invalid_argument &)
            {
                cout << "Error: You did not enter a valid entry.\n";
            }
        }
    }
    while (theEntry <= 0);

    return theEntry;
}

void deleteNode(Node* current, Node* prev, Node* head)
{
    string message = "Which node to delete? ";
    int theEntry = getEntry(message, head);

    traverse(current, prev, theEntry);

    // at this point, delete current and reroute pointers
    if (current == nullptr) // checks for current to be valid before deleting the node
        cout << "Empty list - nothing to delete\n";
    else
    {
        prev->next = current->next;
        delete current;
        current = nullptr;
    }
    output(head);
}

void insertNode(Node* current, Node* prev, Node* head)
{
    string message = "After which node to insert 10000? ";
    int theEntry = getEntry(message, head);

    traverse(current, prev, theEntry);
    Node* newNode = new Node;
    newNode->value = 1000.0;
    newNode->next = current->next;
    current->next = newNode;
}

void deleteList(Node* head)
{
    Node* current;
    while (head != nullptr)
    {
        current = head;
        head = current->next;
        delete current;
    }
}