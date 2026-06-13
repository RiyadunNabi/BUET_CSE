#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip> // for setw()
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree
{
    Node *root;

public:
    BinaryTree()
    {
        root = nullptr;
    }
    BinaryTree()
    {
        root = nullptr;
    }
    Node *getRoot()
    {
        return root;
    }

    void insert(int data)
    {
        Node *newNnode = new Node(data);

        if (this->root == nullptr)
        {
            this->root = newNnode;
            return;
        }
        Node *temp = root;
        while (1)
        {
            if (data < temp->data) // left subtree
            {
                if (temp->left == nullptr)
                {
                    temp->left = newNnode;
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if (temp->right == nullptr)
                {
                    temp->right = newNnode;
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    }
    // Function to calculate the height of the tree
    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Function to print the tree in visual manner
    void printTree(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        int h = height(root);         // Height of the tree
        int maxWidth = pow(2, h) - 1; // Maximum width of the last level

        // Queue for level-order traversal
        queue<Node *> q;
        q.push(root);

        int level = 0;

        // Loop through each level of the tree
        while (!q.empty())
        {
            int nodesAtThisLevel = pow(2, level); // Number of nodes at the current level
            int spacesBetweenNodes = maxWidth / nodesAtThisLevel;

            for (int i = 0; i < nodesAtThisLevel; i++)
            {
                if (q.empty())
                    break;

                Node *node = q.front();
                q.pop();

                // Print the node with proper spacing
                if (node != nullptr)
                {
                    cout << setw(spacesBetweenNodes) << node->data;
                    q.push(node->left);
                    q.push(node->right);
                }
                else
                {
                    cout << setw(spacesBetweenNodes) << " ";
                    q.push(nullptr);
                    q.push(nullptr);
                }
            }
            cout << endl;

            if (level < h - 1)
            { // Print branches if not the last level
                printBranches(spacesBetweenNodes, nodesAtThisLevel);
            }

            level++;
        }
    }

    // Function to print branches (slashes / and \ )
    void printBranches(int spacesBetweenNodes, int nodesAtThisLevel)
    {
        int branchOffset = spacesBetweenNodes / 4;
        for (int i = 0; i < nodesAtThisLevel; i++)
        {
            cout << setw(branchOffset) << "/" << setw(branchOffset * 2) << "\\"; // print / and \
        }
            cout << endl;
        }
    };
};

int main()
{
    BinaryTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(3);
    tree.insert(7);
    tree.insert(15);
    tree.insert(25);

    
    return 0;
}