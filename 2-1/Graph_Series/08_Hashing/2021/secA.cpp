// #include <iostream>
// #include <unordered_set>
// #include <string>
// #include <algorithm>
// using namespace std;

// // Function to get the reverse complement of a DNA sequence
// string getReverseComplement(const string& dna) {
//     string complement = "";
//     for (char c : dna) {
//         if (c == 'A') complement += 'T';
//         else if (c == 'T') complement += 'A';
//         else if (c == 'C') complement += 'G';
//         else if (c == 'G') complement += 'C';
//     }
//     reverse(complement.begin(), complement.end());
//     return complement;
// }

// int main() {
//     // Hardcoded Input
//     // int n = 5, l = 4;
//     int n=4, l=5;
//     // string sequences[] = {"ATGC", "GCAT", "TACG", "CGTA", "TTAA"};
//     string sequences[] = {"TTAAG","AATTC","CTTAA","CTTAA"};

//     unordered_multiset<string> seen;
//     unordered_set<string> printed;

//     for (int i = 0; i < n; ++i) {
//         seen.insert(sequences[i]);
//     }

//     for (int i = 0; i < n; ++i) {
//         string revComp = getReverseComplement(sequences[i]);
//         seen.erase(sequences[i]);
//         if (seen.count(revComp)) {
//             string a = sequences[i], b = revComp;
//             if (a > b) swap(a, b);
//             string pairKey = a + " " + b;
//             if (!printed.count(pairKey)) {
//                 cout << a << " " << b << endl;
//                 printed.insert(pairKey);
//             }
//         }
//         seen.insert(sequences[i]);
//     }

//     return 0;
// }


// #include <iostream>
// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <algorithm>

// using namespace std;

// // Function to get the complement of a single nucleotide base [cite: 5]
// char get_complement(char base) {
//     switch (base) {
//         case 'A': return 'T';
//         case 'T': return 'A';
//         case 'C': return 'G';
//         case 'G': return 'C';
//         default: return ' ';
//     }
// }

// // Function to compute the reverse complement of a DNA sequence [cite: 5]
// string get_reverse_complement(string dna) {
//     // Replace each base with its complement
//     for (char &base : dna) {
//         base = get_complement(base);
//     }
//     // Reverse the resulting sequence
//     reverse(dna.begin(), dna.end());
//     return dna;
// }

// /**
//  * @brief Finds and prints pairs of reverse complements from a given list of DNA sequences.
//  * * @param n The number of DNA sequences.
//  * @param l The length of each DNA sequence.
//  * @param sequences A vector of strings containing the DNA sequences.
//  */
// void find_reverse_complements(int n, int l, const vector<string>& sequences) {
//     // Use an unordered_map to store the counts of sequences encountered so far.
//     unordered_map<string, int> sequence_counts;

//     // Process each DNA sequence from the input vector.
//     for (const string& current_sequence : sequences) {
//         // Calculate the reverse complement of the current sequence.
//         string rev_comp = get_reverse_complement(current_sequence);

//         // Check if the reverse complement has been seen before.
//         if (sequence_counts[rev_comp] > 0) {
//             // A pair is found. Print the current sequence and its partner.
//             cout << current_sequence << " " << rev_comp << endl;
            
//             // Decrement the count of the found complement, as it's now paired.
//             sequence_counts[rev_comp]--;
//         } else {
//             // If the reverse complement wasn't found, store the current sequence.
//             sequence_counts[current_sequence]++;
//         }
//     }
// }

// int main() {
//     // --- Run Sample 1 ---
//     cout << "Sample Input 1:" << endl;
//     cout << "5 4" << endl;
//     cout << "ATGC\nGCAT\nTACG\nCGTA\nTTAA" << endl << endl;
//     cout << "Sample Output 1:" << endl;
    
//     // Hardcoded data for the first sample input 
//     int n1 = 5;
//     int l1 = 4;
//     vector<string> sequences1 = {"ATGC", "GCAT", "TACG", "CGTA", "TTAA"};
//     find_reverse_complements(n1, l1, sequences1);

//     cout << "\n-----------------------------------\n\n";

//     // --- Run Sample 2 ---
//     cout << "Sample Input 2:" << endl;
//     cout << "4 5" << endl;
//     cout << "TTAAG\nAATTC\nCTTAA\nCTTAA" << endl << endl;
//     cout << "Sample Output 2:" << endl;

//     // Hardcoded data for the second sample input 
//     int n2 = 4;
//     int l2 = 5;
//     vector<string> sequences2 = {"TTAAG", "AATTC", "CTTAA", "CTTAA"};
//     find_reverse_complements(n2, l2, sequences2);

//     return 0;
// }


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to get the complement of a single nucleotide base
char get_complement(char base) {
    switch (base) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default: return ' ';
    }
}

// Function to compute the reverse complement of a DNA sequence
string get_reverse_complement(string dna) {
    reverse(dna.begin(), dna.end());
    for (char &base : dna) {
        base = get_complement(base);
    }
    return dna;
}

/**
 * @brief Finds and prints pairs of reverse complements from a given list of DNA sequences.
 * @param sequences A vector of strings containing the DNA sequences.
 */
void find_reverse_complements(const vector<string>& sequences) {  //be'a'sttttttttt by Gemini
    unordered_map<string, int> counts;
    // 1. Count frequencies of all sequences
    for (const string& s : sequences) {
        counts[s]++;
    }

    unordered_set<string> processed;

    // 2. Iterate through the original sequences to maintain order
    for (const string& s : sequences) {
        if (processed.count(s)) {
            continue; // Already handled this sequence type
        }

        string rc_s = get_reverse_complement(s);

        if (s == rc_s) { // Palindromic complement case
            // Pairs are N * (N-1) / 2     //nC2
            long long n = counts[s];
            long long num_pairs = n * (n - 1) / 2;
            for (int i = 0; i < num_pairs; ++i) {
                cout << s << " " << s << endl;
            }
        } else if (counts.count(rc_s)) { // Regular complement case
            // Number of pairs is count(s) * count(rc_s)
            int num_pairs = counts[s] * counts[rc_s];
            for (int i = 0; i < num_pairs; ++i) {
                cout << s << " " << rc_s << endl;
            }
        }
        
        // Mark both forms as processed to avoid double printing
        processed.insert(s);
        processed.insert(rc_s);
    }
}

// void find_reverse_complements_myCustom(const vector<string>& sequences){
//     vector<pair<string, unordered_set<int>>> matched;
//     unordered_set<string> seen;
//     for (auto &i : sequences){
//         matched.push_back({i, {}});
//         seen.insert(i);
//     }
//     int j=0;
//     for(auto i : matched){
//         string str=i.first;
//         seen.erase(str);
//         string rvrs=get_reverse_complement(str);
//         if(seen.count(rvrs)){
//             i.second.insert()
//         }
//     }
    
// }

int main() {
    // --- Run Sample 1 ---
    cout << "Sample Input 1:" << endl;
    cout << "5 4" << endl;
    cout << "ATGC\nGCAT\nTACG\nCGTA\nTTAA" << endl << endl;
    cout << "Sample Output 1:" << endl;
    
    vector<string> sequences1 = {"ATGC", "GCAT", "TACG", "CGTA", "TTAA"};
    find_reverse_complements(sequences1);

    cout << "\n-----------------------------------\n\n";

    // --- Run Sample 2 ---
    cout << "Sample Input 2:" << endl;
    cout << "4 5" << endl;
    cout << "TTAAG\nAATTC\nCTTAA\nCTTAA" << endl << endl;
    cout << "Sample Output 2:" << endl;

    vector<string> sequences2 = {"TTAAG", "AATTC", "CTTAA", "CTTAA"};
    find_reverse_complements(sequences2);

    return 0;
}