//g++ main3.cpp bst.cpp -o main3
//main3.exe
#include <iostream>
#include <chrono>
#include <fstream> // Required for file saving
#include "bst.h"
#include "lcd.h"

using namespace std;
using namespace std::chrono;

// Helper function to recursively save node data to a file in sorted order
void saveInorder(Node* root, ofstream& file) {
    if (root == NULL) return;
    saveInorder(root->left, file);
    file << "ID: " << root->book.id 
         << ", Title: " << root->book.title 
         << ", Shelf: " << root->book.shelf << "\n";
    saveInorder(root->right, file);
}

int main() {
    BST tree;
    LCD lcd;

    // Insert books
    tree.root = tree.insert(tree.root, Book(100, "Data Structures", "A1"));
    tree.root = tree.insert(tree.root, Book(200, "Operating Systems", "B2"));
    tree.root = tree.insert(tree.root, Book(150, "Computer Networks", "C3"));
    tree.root = tree.insert(tree.root, Book(250, "Digital Logic", "D4"));

    // -------------------------------------------------
    // Plot Data: Number of Books vs Search Time
    // -------------------------------------------------
    cout << endl;
    cout << "Books\tSearch Time (nanoseconds)" << endl;

    for (int n = 1000; n <= 10000; n += 1000) {
        BST tempTree;
        // Insert n books into BST
        for (int i = 1; i <= n; i++) {
            tempTree.root = tempTree.insert(tempTree.root, Book(i, "Book", "A1"));
        }

        // Measure search execution time
        auto start = high_resolution_clock::now();
        tempTree.search(tempTree.root, n);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << n << "\t" << duration.count() << endl;
    }

    // -------------------------------------------------
    // User Search
    // -------------------------------------------------
    int target;
    cout << endl;
    cout << "Enter Book ID: ";
    cin >> target;

    Node* result = tree.search(tree.root, target);

    if (result != NULL) {
        lcd.display(result->book.title, "Shelf: " + result->book.shelf);
    } else {
        lcd.display("Book Not Found", "Try Again");
    }

    // -------------------------------------------------
    // TO-DO 4: Print records in sorted order & save to file
    // -------------------------------------------------
    cout << "\n--- Sorted Book Records ---" << endl;
    tree.inorder(tree.root);

    ofstream outFile("sorted_books.txt");
    if (outFile.is_open()) {
        saveInorder(tree.root, outFile);
        outFile.close();
        cout << "\nRecords successfully saved to 'sorted_books.txt'." << endl;
    } else {
        cout << "\nError: Could not create or open the file." << endl;
    }

    return 0;
}
