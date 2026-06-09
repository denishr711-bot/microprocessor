#include <iostream>
#include "bst.h"

using namespace std;

// TO-DO 1 : Insert a book into BST
Node* BST::insert(Node* root, Book book) {
    Node* newNode = new Node(book);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (book.id < current->book.id) {
            current = current->left;
        } else if (book.id > current->book.id) {
            current = current->right;
        } else {
            delete newNode; // Duplicate ID found, clean up memory
            return root;
        }
    }

    if (book.id < parent->book.id) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// TO-DO 2 : Search for a book using Book ID
Node* BST::search(Node* root, int id) {
  Node* current = root;
    while (current != NULL) {
        if (current->book.id == id) {
            return current;
        } else if (id < current->book.id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

// TO-DO 3 : Print books in sorted order
void BST::inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << "ID: " << root->book.id 
         << " | Title: " << root->book.title 
         << " | Shelf: " << root->book.shelf << endl;
    inorder(root->right);
}
