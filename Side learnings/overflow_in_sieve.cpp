#include<iostream>
#include<vector>
#include<cstdint>
using namespace std;

vector<char> build_sieve(int n){
    if(n < 2){
        throw invalid_argument("build_sieve: n must be a positive integer greater than 1.");
    }

    vector<char> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;

    size_t limit = static_cast<size_t>(n);

    // Mark even numbers > 2 as composite.
    for(size_t p = 4; p <= limit; p+=2){
        isPrime[p] = false;
    }

    // odd optimized sieve.
    for(size_t p = 3; p * p <= limit; p += 2){
        if(!isPrime[p]) continue;
        size_t start = p * p;
        for(size_t j = start; j <= limit; j += p){
            isPrime[j] = false;
        }
    }
    
    return isPrime;
}

bool is_prime_value(int64_t v, const vector<char>& sieve){
    const int64_t limit = static_cast<int64_t>(sieve.size()) - 1;
    if(v < 0 || v > limit){
        throw out_of_range("is_prime_value: v must be between 0 and " + to_string(limit));
    }
    return sieve[static_cast<size_t>(v)];
}


int main(){

    int n = 2e6;
    int64_t v = 1392329;
    vector<char> sieve = build_sieve(n);

    cout << boolalpha;
    cout << is_prime_value(v, sieve);

    return 0;
}