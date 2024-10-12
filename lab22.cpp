// COMSC 210 | Lab 22 | Niko Dittmar
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;

        // Constructor
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // push_back() adds a value to the back of the list.
    // arguments: value - the value to add.
    // returns: void
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // push_front() adds a value to the front of the list.
    // arguments: value - the value to add.
    // returns: void
    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // insert_after() adds a value after the specified position in the list.
    // arguments: value - the value to add, position - the index to add the item after.
    // returns: void
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    // delete_val() delete a value from the list. (first occurance)
    // arguments: value - the value to delete.
    // returns: void
    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    // pop_front() removes a value from the front of the list.
    // arguments: none
    // returns: void
    void pop_front() {
        Node* temp = head;
        if (temp) {
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = temp->next;
                head->prev = nullptr;
            }
            delete temp;
        }
    }

    // pop_back() removes a value from the back of the list.
    // arguments: none
    // returns: void
    void pop_back() {
        Node* temp = tail;
        if (temp) {
            if (head == tail) {
                head = tail = nullptr;
            } else {
                tail = temp->prev;
                tail->next = nullptr;
            }
            delete temp;
        }
    }

    // delete_pos() removes a value from a specific position.
    // arguments: position - the position to remove the item.
    // returns: void
    void delete_pos(int position) {
        // Ensure position is greater than 0.
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* temp = head;

        // Handle delete head case.
        if (position == 0) {
            if (head) {
                if (head == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else {
                    head = temp->next;
                    head->prev = nullptr;
                }
                delete temp;
                
            }
            return;
        }

        // Find node at position.
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        // Ensure the node exists.
        if (!temp) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (temp->next) {
            Node* next = temp->next;
            temp->next->prev = temp->prev;
            temp->prev->next = next;
            delete temp;
        } else {
            // Handle delete tail case.
            tail = temp->prev;
            temp->prev->next = nullptr;
            delete temp;
        }

    }

    // print() prints the list in forward order.
    // arguments: none
    // returns: void
    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // print_reverse() prints the list in reverse order.
    // arguments: none
    // returns: void
    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // Delete the list
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Delete end: ";
    list.delete_pos(size - 1);
    list.print();

    cout << "Delete from middle: ";
    list.delete_pos(size - 3);
    list.print();

    cout << "Delete first: ";
    list.delete_pos(0);
    list.print();

    cout << "Pop front: ";
    list.pop_front();
    list.print();

    cout << "Pop back: ";
    list.pop_back();
    list.print();

    cout << "Push back: ";
    list.push_back(987654321);
    list.print();

    cout << "Delete val: ";
    list.delete_val(987654321);
    list.print();

    cout << "Push front: ";
    list.push_front(123456789);
    list.print();

    cout << "Insert after: ";
    list.insert_after(543, 5);
    list.print();

    cout << "Delete val: ";
    list.delete_val(123456789);
    list.print();


    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
