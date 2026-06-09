#include <iostream>
#include <queue>
using namespace std;

// Node class to define the structure of the node
class Node {
public:
    int data;
    Node *left, *right;
    // Parameterized Constructor
    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

// Function to insert nodes
Node* insert(Node* root, int data)
{
    // If tree is empty, new node becomes the root
    if (root == nullptr) {
        root = new Node(data);
        return root;
    }
    // queue to traverse the tree and find the position to
    // insert the node
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        // Insert node as the left child of the parent node
        if (temp->left == nullptr) {
            temp->left = new Node(data);
            break;
        }
        // If the left child is not nullptr push it to the
        // queue
        else
            q.push(temp->left);
        // Insert node as the right child of parent node
        if (temp->right == nullptr) {
            temp->right = new Node(data);
            break;
        }
        // If the right child is not nullptr push it to the
        // queue
        else
            q.push(temp->right);
    }
    return root;
}

/* function to delete the given deepest node
(d_node) in binary tree */
void deleteDeepest(Node* root, Node* d_node)
{
    queue<Node*> q;
    q.push(root);
    // Do level order traversal until last node
    Node* temp;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp == d_node) {
            temp = nullptr;
            delete (d_node);
            return;
        }
        if (temp->right) {
            if (temp->right == d_node) {
                temp->right = nullptr;
                delete (d_node);
                return;
            }
            else
                q.push(temp->right);
        }
        if (temp->left) {
            if (temp->left == d_node) {
                temp->left = nullptr;
                delete (d_node);
                return;
            }
            else
                q.push(temp->left);
        }
    }
}

/* function to delete element in binary tree */
Node* deletion(Node* root, int key)
{
    if (!root)
        return nullptr;
    if (root->left == nullptr && root->right == nullptr) {
        if (root->data == key)
            return nullptr;
        else
            return root;
    }
    queue<Node*> q;
    q.push(root);
    Node* temp;
    Node* key_node = nullptr;
    // Do level order traversal to find deepest
    // node(temp) and node to be deleted (key_node)
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp->data == key)
            key_node = temp;
        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
    if (key_node != nullptr) {
        int x = temp->data;
        key_node->data = x;
        deleteDeepest(root, temp);
    }
    return root;
}

// Inorder tree traversal (Left - Root - Right)
void inorderTraversal(Node* root)
{
    if (!root)
        return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}
// Inorder tree traversal (Right - Root - Left)
void reverseInorderTraversal(Node* root)
{
    if (!root)
        return;
    inorderTraversal(root->right);
    cout << root->data << " ";
    inorderTraversal(root->left);
}

// Function to print only leaf nodes
void printLeafNodes(Node* root) {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->data << " ";
        return;
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Function to count total number of nodes
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to calculate height of the tree
int calculateHeight(Node* root) {
    if (!root) return -1; // Standard height (edges)
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return 1 + max(leftHeight, rightHeight);
}

// Preorder tree traversal (Root - Left - Right)
void preorderTraversal(Node* root)
{
    if (!root)
        return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder tree traversal (Left - Right - Root)
void postorderTraversal(Node* root)
{
    if (root == nullptr)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

// Function for Level order tree traversal
void levelorderTraversal(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        // Count nodes at the current level
        int levelSize = q.size();

        // Process all nodes of the current level
        for (int i = 0; i < levelSize; i++) {
            Node* temp = q.front();
            q.pop();
            cout << temp->data << " ";

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        // Move to a new line after finishing one level
        cout << endl;
    }
}

/* Driver function to check the above algorithm. */
int main()
{
	int n,val;
    Node* root = nullptr;
    // Insertion of nodes
	cout << "Enter the number of nodes to insert: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> val;
        root = insert(root, val);
    }

	cout << "\nReverse Inorder traversal: ";
    reverseInorderTraversal(root);
	
	cout << "\nLeaf Nodes: ";
    printLeafNodes(root);

	cout << "\nTotal number of nodes: " << countNodes(root);

    cout << "\nHeight of the tree: " << calculateHeight(root);
	
	cout << "\nLevel order traversal: " << endl;
    levelorderTraversal(root);

}