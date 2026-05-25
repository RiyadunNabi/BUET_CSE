#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <chrono>

using namespace std;

string generate_random_word() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> len_dist(5, 10);
    uniform_int_distribution<> char_dist(0, 25);

    int length = len_dist(gen);
    string word;
    for (int i = 0; i < length; ++i) {
        char letter = 'a' + char_dist(gen);
        word += letter;
    }
    return word;
}

string generate_random_word(int min_len, int max_len, mt19937 &generator) {
    uniform_int_distribution<int> len_dist(min_len, max_len);
    uniform_int_distribution<char> char_dist('a', 'z');
    int len = len_dist(generator);
    string word = "";
    for (int i = 0; i < len; ++i) {
        word += char_dist(generator);
    }
    return word;
}

void GenerateWords(vector<string> &words, int num_words, int min_len, int max_len) {
    set<string> unique_words;
    mt19937 generator(static_cast<unsigned long>(
        chrono::high_resolution_clock::now().time_since_epoch().count()));
    while (unique_words.size() < static_cast<size_t>(num_words)) {
        unique_words.insert(generate_random_word(min_len, max_len, generator));
    }
    words.assign(unique_words.begin(), unique_words.end());
}

// int main() {
//     vector<string> words;
//     int total_words = 10000;
//     for (int i = 0; i < total_words; ++i) {
//         words.push_back(generate_random_word());
//     }

//     for (int i = 0; i < 10; ++i) {
//         cout << words[i] << endl;
//     }

//     return 0;
// }
