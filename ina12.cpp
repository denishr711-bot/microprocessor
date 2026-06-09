// Binary Search Tree operations in C++

#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

// Create a node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = nullptr;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != nullptr) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    cout << root->key << " -> ";

    // Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  if (node == nullptr) return newNode(key);

  // Traverse to the right place and insert the node
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != nullptr)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Return if the tree is empty
  if (root == nullptr) return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    // If the node is with only one child or no child
    if (root->left == nullptr) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == nullptr) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// Find and print maximum value
void findMax(struct node* root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    struct node* current = root;
    while (current->right != nullptr)
        current = current->right;
    cout << "Maximum value in tree: " << current->key << endl;
}

// Print nodes within a given range
void printRange(struct node* root, int low, int high) {
    if (root == nullptr) return;

    if (low < root->key)
        printRange(root->left, low, high);

    if (low <= root->key && high >= root->key)
        cout << root->key << " ";

    if (high > root->key)
        printRange(root->right, low, high);
}

// Check if tree is a valid BST
bool isValidBST(struct node* root, long minVal, long maxVal) {
    if (root == nullptr) return true;
    if (root->key <= minVal || root->key >= maxVal) return false;
    return isValidBST(root->left, minVal, root->key) && 
           isValidBST(root->right, root->key, maxVal);
}

// Search for a key
void search(struct node* root, int key) {
    if (root == nullptr) {
        cout << "Search: Key " << key << " NOT found." << endl;
        return;
    }
    if (root->key == key) {
        cout << "Search: Key " << key << " exists in the tree." << endl;
        return;
    }
    if (key < root->key) search(root->left, key);
    else search(root->right, key);
}

// Driver code
int main() {
  struct node *root = nullptr;
  root = insert(root, 8);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 6);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 14);
  root = insert(root, 4);

  cout << "Inorder traversal: ";
  inorder(root);
  cout << endl;
  
  // Find Max
  findMax(root);
  
  // Range Print
  cout << "Nodes between 1 and 2: ";
  printRange(root, 1, 2);
  cout << endl;
  
  // Validate BST
  if (isValidBST(root, LONG_MIN, LONG_MAX))
    cout << "The tree is a valid BST." << endl;
  else
    cout << "The tree is NOT a valid BST." << endl;

  // Search
  search(root, 6);
  search(root, 11);
  
}