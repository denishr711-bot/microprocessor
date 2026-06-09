/*
Seattle University - ECEGR-2030
Project: Linked-List Exercise
Description: C++ program to implement a singly linked list.
Author: Eddy Ferre - ferree@seattleu.edu
Modified by:
*/
#include <iostream>
using namespace std;

// Define the Node struct
struct Node {
    double data;
    Node* next;
};

// Linked list class
class LinkedList {
private:
    Node* head; // Pointer to the head of the list

public:
    // Constructor: Initialize an empty list
    LinkedList() {
        head = nullptr;
    }

    // Insert a new node at the end of the list
    void appendNode(double data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Delete a node at the given index
    void deleteNode(unsigned int index) {
        if (head == nullptr) {
            cout << "ERROR: List is empty." << endl;
            return;
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* prev = nullptr;
        Node* curr = head;
        unsigned int counter = 0;

        while (curr != nullptr && counter < index) {
            prev = curr;
            curr = curr->next;
            counter++;
        }

        if (curr == nullptr) {
            cout << "ERROR: Index out of range." << endl;
            return;
        }

        prev->next = curr->next;
        delete curr;
    }

    // Print the elements of the list
    void printList() {
        Node* temp = head;
        cout << "{ ";
        while (temp != nullptr) {
            cout << temp->data;
            temp = temp->next;
            if (temp != nullptr) {
                cout << ", ";
            }
        }
        cout << " }" << endl;
    }

    // Destructor: Clean up memory
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList myList;

    myList.appendNode(42);
    myList.appendNode(-51.5);
    myList.appendNode(3e-3);

    cout << "Linked List elements: ";
    myList.printList();

    cout << "Deleting element at index 2: ";
    myList.deleteNode(2);
    myList.printList();

    cout << "Deleting element at index 3: ";
    myList.deleteNode(3);

    cout << "Deleting element at index 0: ";
    myList.deleteNode(0);
    myList.printList();

    cout << "Deleting element at index 0: ";
    myList.deleteNode(0);
    myList.printList();

    cout << "Deleting element at index 0: ";
    myList.deleteNode(0);

    return 0;
}
