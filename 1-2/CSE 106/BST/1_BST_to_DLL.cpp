#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Convert a Binary Tree to a Circular Doubly Linked List using Morris Traversal
Node* treeToCDLL(Node* root) {
    if (!root) return nullptr;

    Node* head = nullptr, *prev = nullptr;
    Node* current = root;

    while (current) {
        if (current->left) {
            // Find the inorder predecessor (rightmost node of left subtree)
            Node* pred = current->left;
            while (pred->right && pred->right != current)
                pred = pred->right;

            // Establish a temporary thread to current
            if (!pred->right) {
                pred->right = current;
                current = current->left;
            } else {
                pred->right = nullptr;
                // Process current node
                if (!head) head = current;
                if (prev) {
                    prev->right = current;
                    current->left = prev;
                }
                prev = current;
                current = current->right;
            }
        } else {
            // Process current node
            if (!head) head = current;
            if (prev) {
                prev->right = current;
                current->left = prev;
            }
            prev = current;
            current = current->right;
        }
    }

    // Making the list circular
    prev->right = head;
    head->left = prev;

    return head;
}

// Display function
void displayCDLL(Node* head) {
    if (!head) return;
    Node* temp = head;
    do {
        cout << temp->data << " <-> ";
        temp = temp->right;
    } while (temp != head);
    cout << "(head)" << endl;
}

// Driver code
int main() {
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(20);
    root->right->left = new Node(15);
    root->right->right = new Node(25);

    Node* head = treeToCDLL(root);
    cout << "Circular Doubly Linked List: ";
    displayCDLL(head);

    return 0;
}


/* or


// Function to convert a Binary Tree to a Circular Doubly Linked List (CDLL)
void convert(Node* root, Node*& head, Node*& prev) {
    if (root == nullptr) 
        return;

    // Recursively convert the left subtree
    convert(root->left, head, prev);

    // If this is the first node, set it as head
    if (prev == nullptr) {
        head = root;
    } else {
        // Link previous node with current node
        prev->right = root;
        root->left = prev;
    }

    // Update previous pointer to current node
    prev = root;

    // Recursively convert the right subtree
    convert(root->right, head, prev);
}

// Function to initialize and convert Binary Tree to CDLL
Node* treeToLL(Node* root) {
    Node* prev = nullptr;
    Node* head = nullptr;

    convert(root, head, prev);

    // Make the linked list circular
    prev->right = head;
    head->left = prev;

    return head;
}









*/





/* or, storing in an array

#include <iostream>
#include <vector>
using namespace std;

// Definition of Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to perform inorder traversal and store nodes in an array
void inorderTraversal(Node* root, vector<Node*>& nodes) {
    if (!root) return;
    inorderTraversal(root->left, nodes);
    nodes.push_back(root);
    inorderTraversal(root->right, nodes);
}

// Function to convert array to Circular Doubly Linked List
Node* arrayToCDLL(vector<Node*>& nodes) {
    if (nodes.empty()) return nullptr;

    int n = nodes.size();
    for (int i = 0; i < n; i++) {
        nodes[i]->left = (i == 0) ? nodes[n - 1] : nodes[i - 1];  // Previous pointer
        nodes[i]->right = (i == n - 1) ? nodes[0] : nodes[i + 1];  // Next pointer
    }

    return nodes[0];  // Head of CDLL
}

// Function to convert Binary Tree to Circular Doubly Linked List
Node* treeToCDLL(Node* root) {
    vector<Node*> nodes;
    inorderTraversal(root, nodes);
    return arrayToCDLL(nodes);
}

// Function to display the Circular Doubly Linked List
void displayCDLL(Node* head) {
    if (!head) return;

    Node* temp = head;
    do {
        cout << temp->data << " <-> ";
        temp = temp->right;
    } while (temp != head);
    cout << "(head)" << endl;
}

// Driver code
int main() {
    // Constructing a Binary Tree
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(20);
    root->right->left = new Node(15);
    root->right->right = new Node(25);

    // Convert tree to Circular Doubly Linked List
    Node* head = treeToCDLL(root);

    // Display the Circular Doubly Linked List
    cout << "Circular Doubly Linked List: ";
    displayCDLL(head);

    return 0;
}










*/