#include <bits/stdc++.h>
#include <fstream>
#include "BinomialHeap.hpp"

using namespace std;

int main() {
    BinomialHeap heap;
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening input/output file." << endl;
        return 1;
    }

    string command;
    while (infile >> command) {
        if (command == "I") {
            int key;
            infile >> key;
            heap.insert(key);
        } else if (command == "F") {
            int min = heap.findMin();
            outfile << "Find Min returned: " << min << "\n";
        } else if (command == "E") {
            int min = heap.extractMin();
            outfile << "Extract Min returned: " << min << "\n";
        } else if (command == "D") {
            int oldKey, newKey;
            infile >> oldKey >> newKey;
            heap.decreaseKey(oldKey, newKey);
        } else if (command == "R") {
            int key;
            infile >> key;
            heap.removeKey(key);
        } else if (command == "P") {
            outfile << "Printing Binomial Heap...\n";
            heap.print(outfile);
        }
    }

    infile.close();
    outfile.close();
    return 0;
}
