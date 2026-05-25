#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>
// #include "HashFunctions.h"
#include "HashTable.h"
#include "WordGenerator.cpp"

using namespace std;

template <typename InputIt, typename OutputIt, typename RNG>
void random_sample(InputIt first, InputIt last, OutputIt out, size_t n, RNG &&g) {
    vector<typename iterator_traits<InputIt>::value_type> pool(first, last);
    shuffle(pool.begin(), pool.end(), g);
    for (size_t i = 0; i < min(n, pool.size()); ++i) {
        *out++ = pool[i];
    }
}

void run_test(const string &method_name, int hash_func_choice, double load_factor, int n_prime, vector<string> &words, int S_linear_probe) {

    string strategy;
    if (method_name.find("Chaining") != string::npos)
        strategy = "chaining";
    if (method_name.find("Linear") != string::npos)
        strategy = "linear";
    if (method_name.find("Double") != string::npos)
        strategy = "double";

    HashTable ht(n_prime, strategy, hash_func_choice, S_linear_probe);
    long long N = find_next_prime(n_prime);
    int num_to_insert = static_cast<int>(load_factor * N);

    vector<string> inserted_keys;
    int value_counter = 1;
    int word_idx = 0;

    while (inserted_keys.size() < num_to_insert && word_idx < words.size()) {
        string &key = words[word_idx++];
        if (ht.search(key).first == -1) {
            ht.insert(key, value_counter++);
            inserted_keys.push_back(key);
        }
    }

    long long insertion_collisions = ht.getCollisions();

    // --- Search Test Before Deletion ---
    vector<string> search_before_set;
    if (!inserted_keys.empty()) {
        int num_to_search = max(1, (int)(inserted_keys.size() * 0.1));
        random_sample(inserted_keys.begin(), inserted_keys.end(), back_inserter(search_before_set),
                      num_to_search, mt19937{random_device{}()});
    }

    auto start_before = chrono::high_resolution_clock::now();
    long long total_probes_before = 0;
    for (auto &key : search_before_set) {
        total_probes_before += ht.search(key).second;
    }
    auto end_before = chrono::high_resolution_clock::now();
    // chrono::duration<double, std::chrono::microseconds::period> time_before = end_before - start_before;
    // double avg_time_before = search_before_set.empty() ? 0 : time_before.count() / search_before_set.size();
    chrono::nanoseconds time_before_ns = chrono::duration_cast<chrono::nanoseconds>(end_before - start_before);
    double avg_time_before = search_before_set.empty() ? 0.0 : time_before_ns.count() / (double) search_before_set.size();
    double avg_probes_before = search_before_set.empty() ? 0 : (double)total_probes_before / search_before_set.size();

    // --- Deletion ---
    vector<string> to_be_deleted = search_before_set;
    for (auto &key : to_be_deleted) {
        ht.remove(key);
    }

    // --- Search Test After Deletion ---
    vector<string> search_after_set;
    vector<string> remaining_keys;
    set<string> deleted_set(to_be_deleted.begin(), to_be_deleted.end());
    for (const auto &key : inserted_keys) {
        if (deleted_set.find(key) == deleted_set.end()) {
            remaining_keys.push_back(key);
        }
    }

    if (!search_before_set.empty()) {
        int half_size = search_before_set.size() / 2;
        if (remaining_keys.size() >= half_size && !remaining_keys.empty()) {
            random_sample(remaining_keys.begin(), remaining_keys.end(), back_inserter(search_after_set),
                          half_size, mt19937{random_device{}()});
        }
        if (to_be_deleted.size() >= (search_before_set.size() - search_after_set.size()) && !to_be_deleted.empty()) {
            random_sample(to_be_deleted.begin(), to_be_deleted.end(), back_inserter(search_after_set),
                          search_before_set.size() - search_after_set.size(), mt19937{random_device{}()});
        }
    }

    auto start_after = chrono::high_resolution_clock::now();
    long long total_probes_after = 0;
    for (auto &key : search_after_set) {
        total_probes_after += ht.search(key).second;
    }
    auto end_after = chrono::high_resolution_clock::now();
    // chrono::duration<double, std::chrono::microseconds::period> time_after = end_after - start_after;
    // double avg_time_after = search_after_set.empty() ? 0 : time_after.count() / search_after_set.size();
    chrono::nanoseconds time_after_ns = chrono::duration_cast<chrono::nanoseconds>(end_after - start_after);
    double avg_time_after = search_after_set.empty() ? 0.0 : time_after_ns.count() / (double) search_after_set.size();
    double avg_probes_after = search_after_set.empty() ? 0 : (double)total_probes_after / search_after_set.size();

    // --- Print Results ---
    string hash_func_name = (hash_func_choice == 1 ? "Hash1" : "Hash2");

    cout << "Method=" << hash_func_name
         << ", no of collisions=" << insertion_collisions
         << "\n   before deletion: avg_search_time=" << fixed << setprecision(4) << avg_time_before;

    if (strategy == "chaining")
        cout << ", avg_probes=N/A";
    else
        cout << ", avg_probes=" << fixed << setprecision(4) << avg_probes_before;

    cout << "\n   after deletion: avg_search_time=" << fixed << setprecision(4) << avg_time_after;
    if (strategy == "chaining")
        cout << ", avg_probes=N/A";
    else
        cout << ", avg_probes=" << fixed << setprecision(4) << avg_probes_after;

    cout << endl;
}

int main() {
    int min_length = 5, max_length = 10;
    int NUM_WORDS = 10000;
    // int N_PRIME = 9973;
    const int N_PRIME = 10007;
    const int S_LINEAR_PROBE = 5;

    vector<string> words;
    GenerateWords(words, NUM_WORDS, min_length, max_length);

    cout << "Project VaultX: Performance Report" << endl;
    cout << "Initial Table Size (N'): " << N_PRIME << endl;
    cout << "Step size for Linear Probing (S): " << S_LINEAR_PROBE << endl;

    vector<double> load_factors = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    for (double lf : load_factors) {
        cout << "\n\n"
             << string(60, '=') << "\n";
        cout << "Table for Load Factor: " << fixed << setprecision(1) << lf << endl;
        cout << string(60, '=') << endl;

        cout << "\n### Separate Chaining with Balanced BST ###\n"
             << endl;
        run_test("Separate Chaining", HASH1, lf, N_PRIME, words, S_LINEAR_PROBE);
        run_test("Separate Chaining", HASH2, lf, N_PRIME, words, S_LINEAR_PROBE);

        cout << "\n### Linear Probing with Step Adjustment ###\n"
             << endl;
        run_test("Linear Probing", HASH1, lf, N_PRIME, words, S_LINEAR_PROBE);
        run_test("Linear Probing", HASH2, lf, N_PRIME, words, S_LINEAR_PROBE);

        cout << "\n### Double Hashing ###\n"
             << endl;
        run_test("Double Hashing", HASH1, lf, N_PRIME, words, S_LINEAR_PROBE);
        run_test("Double Hashing", HASH2, lf, N_PRIME, words, S_LINEAR_PROBE);
    }

    return 0;
}
