#include "color.hpp"
#include <bits/stdc++.h>
using namespace std;

enum Color { RED,
             BLACK };

class Node {
  public:
    int productID;
    string productName;
    int stock;
    Color color;
    Node *left, *right, *parent;

    Node(int id, string name, int stock) {
        productID = id;
        productName = name;
        this->stock = stock;

        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
  private:
    Node *root;
    Node *NIL;
    int ProductCount;

    Node *insertBST(Node *root, Node *newNode, bool &inserted) {
        if (root == NIL) {
            inserted = true;
            return newNode;
        }
        if (newNode->productID < root->productID) {
            root->left = insertBST(root->left, newNode, inserted);
            root->left->parent = root;
        } else if (newNode->productID > root->productID) {
            root->right = insertBST(root->right, newNode, inserted);
            root->right->parent = root;
        } else {
            // already exists
            root->productName = newNode->productName;
            root->stock = newNode->stock;
            inserted = false;
        }

        return root;
    }

    Node *find(Node *node, int id) {
        if (node == NIL || node->productID == id)
            return node;
        if (id < node->productID) {
            return find(node->left, id);
        } else {
            return find(node->right, id);
        }
    }

    void clearTree(Node *node) {
        if (node == NIL)
            return;

        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    void inOrder(Node *node, ostream &out1, ostream &out2) {
        if (node == NIL) {
            return;
        }
        inOrder(node->left, out1, out2);
        // cout << node << " ";
        if (node->color == RED) {
            out1 << dye::red(to_string(node->productID) + " => " + node->productName + " (" + to_string(node->stock) + ")") << endl;
            out2 << dye::red(to_string(node->productID) + " => " + node->productName + " (" + to_string(node->stock) + ")") << endl;
        } else {
            out1 << (to_string(node->productID) + " => " + node->productName + " (" + to_string(node->stock) + ")") << endl;
            out2 << (to_string(node->productID) + " => " + node->productName + " (" + to_string(node->stock) + ")") << endl;
        }
        inOrder(node->right, out1, out2);
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        //==================================
        x->left = y->right;
        if (y->right != NIL)
            y->right->parent = x;
        //=================================
        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        //================================
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node *k) {
        Node *u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right; // uncle
                if (u->color == RED) {
                    // Case 1
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // Case 2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // Case 3
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                // mirror case
                u = k->parent->parent->left;
                if (u->color == RED) {
                    // Case 1
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // Case 2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // Case 3
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root)
                break;
        }
        root->color = BLACK;
    }

    void transplant(Node *u, Node *v) {
        if (u->parent == NIL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }
    Node *minimum(Node *node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }
    void fixDelete(Node *x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *w = x->parent->right; // Sibling

                // Case 1: x's sibling w is RED
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                // Case 2: both of w's children are BLACK
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    // Case 3: w's right child is BLACK, left is RED
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    // Case 4: w's right child is RED
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }

            } else { // mirror left/right
                Node *w = x->parent->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void deleteNode(Node *z) {
        Node *y = z;
        Node *x;
        Color y_original_color = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            // if (y->parent == z) {
            //     x->parent = y;
            // } else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK)
            fixDelete(x);
    }

  public:
    RedBlackTree() {
        ProductCount = 0;

        NIL = new Node(-1, "", 0);
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;

        root = NIL;
    }

    void AddItem(int productID, string productName, int stock) {
        Node *newNode = new Node(productID, productName, stock);
        newNode->left = newNode->right = newNode->parent = NIL;

        bool inserted = false;
        root = insertBST(root, newNode, inserted);

        if (inserted) {
            ProductCount++;
            fixInsert(newNode);
        }
    }

    void CheckItem(int id, ostream &out1, ostream &out2) {
        Node *node = find(root, id);
        if (node != NIL) {
            out1 << "Stock left: " << node->stock << endl;
            out2 << "Stock left: " << node->stock << endl;
        } else {
            out1 << "Not available" << endl;
            out2 << "Not available" << endl;
        }
    }

    void ClearInventory(ostream &out1, ostream &out2) {
        if (root == NIL) {
            out1 << "unsuccessful" << endl;
            out2 << "unsuccessful" << endl;
            return;
        }

        clearTree(root);
        root = NIL;
        ProductCount = 0;
        out1 << "successful" << endl;
        out2 << "successful" << endl;
    }
    void InventorySize(ostream &out1, ostream &out2) {
        out1 << ProductCount << endl;
        out2 << ProductCount << endl;
    }

    void isEmpty(ostream &out1, ostream &out2) {
        if (ProductCount == 0) {
            out1 << "yes" << endl;
            out2 << "yes" << endl;
        } else {
            out1 << "no" << endl;
            out2 << "no" << endl;
        }
    }

    void ListInventory(ostream &out1, ostream &out2) {
        inOrder(root, out1, out2);
        // out1<<endl;
        // out2<<endl;
    }

    void PrintTree(ostream &out1, ostream &out2) {
        printTree(root, out1, out2);
        out1 << endl;
        out2 << endl;
    }
    void printTree(Node *node, ostream &out1, ostream &out2) {
        if (node != NIL) {
            if (node->color == RED) {
                out1 << dye::red(to_string(node->productID) + "_" + node->productName);
                out2 << dye::red(to_string(node->productID) + "_" + node->productName);
            } else {
                out1 << node->productID << "_" << node->productName;
                out2 << node->productID << "_" << node->productName;
            }
            if (node->left == NIL && node->right == NIL) {
                return;
            }
        } else {
            return;
        }

        if (node->left != NIL || node->right != NIL) {
            out1 << "(";
            out2 << "(";
        }

        printTree(node->left, out1, out2);
        out1 << ",";
        out2 << ",";
        printTree(node->right, out1, out2);
        out1 << ")";
        out2 << ")";
    }

    void BuyItem(int id, int quantity, ostream &out1, ostream &out2) {
        Node *node = find(root, id);
        if (node == nullptr || node == NIL) {
            out1 << "Not available" << endl;
            out2 << "Not available" << endl;
            return;
        }

        if (node->stock < quantity) {
            out1 << "Not enough stock" << endl;
            out2 << "Not enough stock" << endl;
            return;
        }

        node->stock -= quantity;

        if (node->stock == 0) {
            deleteNode(node);
            ProductCount--;
        }

        PrintTree(out1, out2);
    }
};