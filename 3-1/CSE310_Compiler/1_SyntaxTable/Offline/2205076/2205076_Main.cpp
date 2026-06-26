#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "2205076_SymbolTable.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // The spec requires taking filenames via command line arguments [cite: 315]
    if (argc != 3) {
        cout << "Usage: ./run_table <input_file.txt> <output_file.txt>\n";
        return 1;
    }

    ifstream in_file(argv[1]);
    ofstream out_file(argv[2]);

    if (!in_file) {
        cout << "Error: Cannot open input file.\n";
        return 1;
    }

    string line;
    // Read the very first line to get the number of buckets
    if (!getline(in_file, line)) return 0;
    
    // Clean trailing carriage returns in case the file was made in Windows but run on Linux
    if (!line.empty() && line.back() == '\r') line.pop_back();
    
    int num_buckets = stoi(line);
    
    // Initialize the Symbol Table. It will automatically create ScopeTable# 1
    SymbolTable st(num_buckets, out_file);

    int cmd_count = 1;

    // Read the rest of the file line by line
    while (getline(in_file, line)) {
        // Clean trailing whitespaces and Windows '\r' characters
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
            line.pop_back();
        }
        if (line.empty()) continue; // Skip blank lines

        // Print the command header exactly as requested
        out_file << "Cmd " << cmd_count << ": " << line << "\n";
        cmd_count++;

        // Tokenize the line into individual words
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;
        string cmd = tokens[0];

        // --- COMMAND PROCESSING ---
        if (cmd == "I") {
            if (tokens.size() < 3) {
                out_file << "\tNumber of parameters mismatch for the command I\n";
                continue;
            }
            
            string name = tokens[1];
            string type = tokens[2];
            string combined_type = type;

            // Advanced string manipulation to handle FUNCTION, STRUCT, and UNION formatting
            if (type == "FUNCTION") {
                if (tokens.size() >= 4) {
                    combined_type += "," + tokens[3] + "<==(";
                    for (size_t i = 4; i < tokens.size(); i++) {
                        combined_type += tokens[i];
                        if (i != tokens.size() - 1) combined_type += ",";
                    }
                    combined_type += ")";
                }
            } 
            else if (type == "STRUCT" || type == "UNION") {
                if (tokens.size() > 3) {
                    combined_type += ",{";
                    for (size_t i = 3; i < tokens.size(); i += 2) {
                        if (i + 1 < tokens.size()) {
                            combined_type += "(" + tokens[i] + "," + tokens[i+1] + ")";
                            if (i + 2 < tokens.size()) combined_type += ",";
                        }
                    }
                    combined_type += "}";
                }
            } 
            else {
                // For standard variables like 'VAR' or 'NUMBER'
                if (tokens.size() > 3) {
                    out_file << "\tNumber of parameters mismatch for the command I\n";
                    continue;
                }
            }
            st.Insert(name, combined_type);
        } 
        else if (cmd == "L") {
            if (tokens.size() != 2) {
                out_file << "\tNumber of parameters mismatch for the command L\n";
            } else {
                st.Lookup(tokens[1]);
            }
        } 
        else if (cmd == "D") {
            if (tokens.size() != 2) {
                out_file << "\tNumber of parameters mismatch for the command D\n";
            } else {
                st.Remove(tokens[1]);
            }
        } 
        else if (cmd == "P") {
            if (tokens.size() != 2) {
                out_file << "\tNumber of parameters mismatch for the command P\n";
            } else if (tokens[1] == "A") {
                st.PrintAllScopeTable();
            } else if (tokens[1] == "C") {
                st.PrintCurrentScopeTable();
            }
        } 
        else if (cmd == "S") {
            if (tokens.size() != 1) {
                out_file << "\tNumber of parameters mismatch for the command S\n";
            } else {
                st.EnterScope();
            }
        } 
        else if (cmd == "E") {
            if (tokens.size() != 1) {
                out_file << "\tNumber of parameters mismatch for the command E\n";
            } else {
                st.ExitScope();
            }
        } 
        else if (cmd == "Q") {
            // The destructor of SymbolTable will trigger automatically and print the cleanup messages [cite: 360-361]
            break;
        }
    }

    in_file.close();
    out_file.close();
    return 0;
}