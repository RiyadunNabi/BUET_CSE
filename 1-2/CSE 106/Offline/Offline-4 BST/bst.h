#include <iostream>

using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
};
Node *find(Node *node, int val);

Node *insertNode(Node *node, int val)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be inserted
    // Returns the pointer to the root of the modified BST.
    if (node == nullptr)
    {
        Node *newNode = new Node();
        newNode->val = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (val < node->val)
    {
        node->left = insertNode(node->left, val);
    }
    else if (node->val < val)
    {
        node->right = insertNode(node->right, val);
    }
    return node;
}

Node* deleteNode(Node* node, int val)
{
    if (node == nullptr) 
    {
        return nullptr;
    }

    if (val < node->val)
    {
        node->left = deleteNode(node->left, val);
    }
    else if (node->val < val)
    {
        node->right = deleteNode(node->right, val);
    }
    else
    {
        if (node->left == nullptr && node->right == nullptr) //leaf node //though not necessary
        {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr)  //one right child
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)  //one left child
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else  //with two child
        {
            Node* inOrderSuccess = node->right;
            while (inOrderSuccess->left != nullptr)
            {
                inOrderSuccess = inOrderSuccess->left;
            }
            node->val = inOrderSuccess->val;
            node->right = deleteNode(node->right, inOrderSuccess->val);
        }
    }
    return node;
}


Node *find(Node *node, int val)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be searched.
    // Returns the pointer to the node that contains val.
    // Returns NULL if not found.
    if (node == nullptr || node->val == val)
        return node;
    if (val < node->val)
    {
        return find(node->left, val);
    }
    else
        return find(node->right, val);
}

void inOrder(Node *node)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the in-order traversal of the given BST
    if (node == nullptr)
        return;

    inOrder(node->left);
    cout << node->val << " ";
    inOrder(node->right);
}

void preOrder(Node *node)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the pre-order traversal of the given BST
    if (node == nullptr)
        return;

    cout << node->val << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void postOrder(Node *node)
{
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the post-order traversal of the given BST
    if (node == nullptr)
        return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->val << " ";
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
    cout << ")";

    return;
}