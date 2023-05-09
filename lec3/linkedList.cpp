#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    int value;
    Node* previous;
    Node* next;
};

void printForward(Node* head) {
    Node* traverse = head;
    while (traverse != nullptr) {
        cout << traverse->value << " ";
        traverse = traverse->next;
    }
}

void printBackward(Node* tail) {
    Node* traverse = tail;
    while (traverse != nullptr) {
        cout << traverse->value << " ";
        traverse = traverse->previous;
    }
}

int main() {
    Node* head;
    Node* tail;

    // first node
    Node* node = new Node();
    node->value = 4;
    node->previous = nullptr;
    node->next = nullptr;
    head = node;
    tail = node;

    // second node
    node = new Node();
    node->value = 5;
    node->previous = tail;
    node->next = nullptr;
    tail->next = node;
    tail = node;

    // third node
    node = new Node();
    node->value = 6;
    node->previous = tail;
    node->next = nullptr;
    tail->next = node;
    tail = node;


    cout << "Print forwards" << endl;
    printForward(head);
    cout << "\n" << "---------------" << endl;
    cout << "Print backwards" << endl;
    printBackward(tail);
}