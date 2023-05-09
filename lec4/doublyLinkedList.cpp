#include <iostream>

using namespace std;

// Define a Node struct to hold data and links to the next and previous nodes
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Define a class for the doubly linked list
class DoublyLinkedList {
private:
    Node* head; // Pointer to the first node in the list
    Node* tail; // Pointer to the last node in the list
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Function to insert a new node at the beginning of the list
    void insertBegin(int data) {
        // create a pointer to newNode

        Node* newNode = new Node;

        // assign the data from the input data
        newNode->data = data;

        // update the newNode_next pointer to point to the head pointer and the newNode_previous pointer to point to the nullptr
        newNode->next = head;
        newNode->prev = nullptr;

        // if the head pointer is not point to nullptr then update the head_previous pointer to point to the newNode pointer
        if (head != nullptr) {
            head->prev = newNode;
        // else update the tail pointer to point to newNode pointer
        } else {
            tail = newNode;
        }
        // update the head pointer to point to newNode
        head = newNode;
    }

    // Function to insert a new node at the end of the list
    void insertEnd(int data) {
        // create a pointer to newNode
        Node* newNode = new Node;

        // assign the data from the input data
        newNode->data = data;

        // update the newNode_next pointer to point to the nullptr and the newNode_previous pointer to point to the tail pointer
        newNode->next = nullptr;
        newNode->prev = tail;

        // if the tail pointer is not nullptr then update the tail_next pointer to point to the newNode pointer
        if (tail != nullptr) {
            tail->next = newNode;
        // else update the head pointer to point to the newNode pointer
        } else {
            head = newNode;
        }
        // update the tail pointer to point to the newNode pointer
        tail = newNode;
    }

    // Function to search for a node with a given data value
    Node* search(int data) {
        // create a currNode pointer to point to the head pointer
        Node* currNode = head;

        // while the currNode pointer is not nullptr and the currNode pointer pointing data is not the same as the input data,
        // update the currNode pointer to point to the currNode_next pointer
        while (currNode != nullptr && currNode->data != data) {
            currNode = currNode->next;
        }

        // return the currNode pointer
        return currNode;
    }

    // Function to delete a node with a given data value
    void deleteNode(int data) {
        // create a currNode pointer to point the pointer which points to node having the data value that needs to be deleted
        Node* currNode = search(data);

        // if the currNode pointer is not nullptr
        if (currNode != nullptr) {
            // if the currNode pointer is the head pointer
            if (currNode == head) {
                // then update the head pointer to point to the currNode_next pointer
                head = currNode->next;
            // else update the currNode_previous_next pointer to point to the currNode_next
            } else {
                currNode->prev->next = currNode->next;
            }
            // if the currNode pointer is the tail pointer then update the tail pointer to point to the currNode_previous pointer
            if (currNode == tail) {
                tail = currNode->prev;
            // else update the currNode_next_previous to point to the currNode_previous
            } else {
                currNode->next->prev = currNode->prev;
            }
            // delete currNode
            delete currNode;
        }
    }

    // Function to print the contents of the list
    void printList() {
        // create a currNode pointer to point to the head pointer
        Node* currNode = head;

        // while the currNode pointer is not a nullptr
        while (currNode != nullptr) {
            // then print out currNode_data
            cout << currNode->data << " ";
            // update the currNode pointer to point to the currNode_next pointer
            currNode = currNode->next;
        }
        // print endl
        cout << endl;
    }

    // Function to print the data needed to find
    void dataSearch(int data) {
        Node* currNode;
        if (!(currNode = search(data))) {
            cout << "Data " << data <<" search error! "<< endl;
        }
        else {
            cout << "Data " << data << " was found. " << endl;
        }
    }
};

int main() {
    // create a list of nodes
    DoublyLinkedList list;

    // Insert some nodes
    list.insertEnd(1);
    list.insertEnd(2);
    list.insertEnd(2);
    list.insertBegin(0);
    list.insertEnd(4);



    // Print the list
    list.printList(); // Output: 0 1 2 3 4
    list.deleteNode(2);
    // Search for a node and delete it


    // Print the list again
    list.printList(); // Output: 0 1 3 4

    // Search for the data
    list.dataSearch(1);
    list.dataSearch(5);
    return 0;
}