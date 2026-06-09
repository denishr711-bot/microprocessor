#ifndef BST_H
#define BST_H

#include "book.h"

class Node {
public:
    Book book;
    Node* left;
    Node* right;

    Node(Book b) : book(b) {
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = NULL;
    }

    Node* insert(Node* root, Book book);

    Node* search(Node* root, int id);

    void inorder(Node* root);
};

#endif
