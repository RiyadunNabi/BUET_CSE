#include <iostream>
#include <string>

using namespace std;

// Hash1: Polynomial Rolling Hash
long long hash1(const string &key, long long N) {
    long long hash_val = 0;
    long long p = 31; // A small prime number
    long long p_pow = 1;
    for (char c : key) {
        hash_val = (hash_val + (c - 'a' + 1) * p_pow) % N;
        p_pow = (p_pow * p) % N;
    }
    return hash_val;
}

// Hash2: djb2
long long hash2(const string &key, long long N) {
    unsigned long hash_val = 5381;
    for (char c : key) {
        hash_val = ((hash_val << 5) + hash_val) + c; // hash * 33 + c
    }
    return (hash_val % (N - 1)) + 1;
}

bool is_prime(long long n) {
    if (n <= 1)
        return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

long long find_next_prime(long long n_prime) {
    if (n_prime <= 1)
        return 2;
    long long prime = n_prime;
    while (true) {
        if (is_prime(prime))
            return prime;
        prime++;
    }
}

// int main(){
//     cout<<find_next_prime(10000);
// }