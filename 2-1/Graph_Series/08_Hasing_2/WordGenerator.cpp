#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

// Generates a random word of length between 5 and 10
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

int main() {
    vector<string> words;
    const int total_words = 10000;
    for (int i = 0; i < total_words; ++i) {
        words.push_back(generate_random_word());
    }

    // Example: print first 10 words
    for (int i = 0; i < 10; ++i) {
        cout << words[i] << endl;
    }

    return 0;
}
