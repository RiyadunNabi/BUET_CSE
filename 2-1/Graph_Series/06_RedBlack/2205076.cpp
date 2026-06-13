#include "RedBlackTree.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    RedBlackTree inventory;
    string line;
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening input.txt\n";
        return 1;
    }

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "AI") {
            int id, stock;
            string name;

            iss >> id;

            iss >> ws;
            if (iss.peek() == '"') {
                getline(iss, name, '"'); // discard starting quote
                getline(iss, name, '"');
            } else {
                iss >> name;
            }

            iss >> stock;

            inventory.AddItem(id, name, stock);

            inventory.PrintTree(cout, outputFile);
        }

        else if (command == "Clr") {
            inventory.ClearInventory(cout, outputFile);
        } else if (command == "S") {
            inventory.InventorySize(cout, outputFile);
        } else if (command == "Em") {
            inventory.isEmpty(cout, outputFile);
        }

        else if (command == "Itr") {
            inventory.ListInventory(cout, outputFile);
        }

        else if (command == "CI") {
            int id;
            iss >> id;
            inventory.CheckItem(id, cout, outputFile);
        }

        else if (command == "BI") {
            int id, quantity;
            iss >> id >> quantity;
            inventory.BuyItem(id, quantity, cout, outputFile);
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}