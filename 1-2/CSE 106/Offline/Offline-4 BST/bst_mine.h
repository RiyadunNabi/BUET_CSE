#include <iostream>

using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
};
Node *find(Node *node, int val);

Node *insertNode(Node *root, int val)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be inserted
    // Returns the pointer to the root of the modified BST.
    Node *newNode = new Node;
    newNode->val = val;
    newNode->left = newNode->right = nullptr;

    if (root == nullptr)
    {
        root = newNode;
        return root;
    }

    Node *current = root;
    Node *parent;

    while (current != nullptr)
    {
        parent = current;
        if (val < current->val)
        {
            current = current->left;
        }
        else if (current->val < val)
        {
            current = current->right;
        }
        else
        {
            delete newNode;
            return root;
        }
    }
    if (val < parent->val)
    {
        parent->left = newNode;
    }
    else if (parent->val < val)
    {
        parent->right = newNode;
    }
    return root;
}

Node *deleteNode(Node *node, int val)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be deleted.
    // Returns the pointer to the root of the modified BST.
    // Node * root=node;
    // Node *deleteNode=find(node, val);

    Node *deleteNode = node;
    Node *parent = nullptr;
    while (deleteNode != nullptr && deleteNode->val != val) //(current->val != val && current !=nullptr) will cause error
    {
        parent = deleteNode;
        if (val < deleteNode->val)
        {
            deleteNode = deleteNode->left;
        }
        else
        {
            deleteNode = deleteNode->right;
        }
    }
    // cout << parent->val << endl;
    cout << deleteNode->val << endl;

    //for leaf nodes
    if (deleteNode->left == nullptr && deleteNode->right == nullptr)
    {
        if (node == deleteNode)
        {
            delete deleteNode;
            return nullptr;
        }
        if (val < parent->val)
        {
            parent->left = nullptr;
        }
        else if (parent->val < val)
        {
            parent->right = nullptr;
        }
        delete deleteNode;
        return node;
    }
    //only one child
    else if (deleteNode->left != nullptr ^ deleteNode->right != nullptr)
    {
        if (deleteNode->right == nullptr)
        {
            Node *temp = deleteNode->left;
            deleteNode->val = temp->val;
            delete temp;
            deleteNode->left = nullptr;
            // return;
        }
        else
        {
            Node *temp = deleteNode->right;
            deleteNode->val = temp->val;
            delete temp;
            deleteNode->right = nullptr;
        }
        return node;
    }
    // The node to be deleted has two children
    Node *inOrderSuccessor = deleteNode->right;
    Node *inOrderSuccessorParent=deleteNode;
    while (inOrderSuccessor->left != nullptr)
    {
        inOrderSuccessorParent = inOrderSuccessor;
        inOrderSuccessor = inOrderSuccessor->left;
    }
    deleteNode->val = inOrderSuccessor->val;
    delete inOrderSuccessor;
    inOrderSuccessorParent->left = nullptr;
    return node;
}

Node *find(Node *node, int val)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be searched.
    // Returns the pointer to the node that contains val.
    // Returns NULL if not found.
    Node *current = node;
    while (current != nullptr && current->val != val) //(current->val != val && current !=nullptr) will cause error
    {
        if (val < current->val)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

void inOrder(Node *node)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the in-order traversal of the given BST
}

void preOrder(Node *node)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the pre-order traversal of the given BST
}

void postOrder(Node *node)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the post-order traversal of the given BST
}

void printTree(Node *root)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints parenthesized representation of the given BST
    if (root != nullptr)
    {
        cout << root->val;
        if (root->left == nullptr && root->right == nullptr)
        {
            return;
        }
    }
    else
    {
        cout << "_";
        return;
    }
    if (root->left != nullptr || root->right != nullptr)
    {
        cout << "  (";
    }

    printTree(root->left);
    cout << ",  ";
    printTree(root->right);
    cout << " )";

    return;
}