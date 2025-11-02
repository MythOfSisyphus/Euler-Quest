#include<iostream>
#include<vector>
#include<tuple>
#include<numeric>
using namespace std;

int digital_sum(int a, int b, int base = 10){
    if(a <= 0 || b < 0 || base < 2){
        throw invalid_argument("Please enter valied values of a >= 0, b > 0 and base >= 2.");
    }

    vector<int> d(1, 1); // represents current value, intially 1.
    for(int i = 0; i < b; ++i){
        int carry = 0;
        for(int j = 0; j < (int)d.size(); ++j){
            long long x = 1LL * d[j] * a + carry;
            d[j] = x % base;
            carry = x / base;
        }

        while(carry){
            d.push_back(carry % base);
            carry /= base;
        }
    }

    return accumulate(d.begin(), d.end(), 0);
}

int main(){

    vector<tuple<int, int, int>> Tests = {{2, 1000, 10}, {31, 3333, 5}, {459, 2898, 11}};

    for(const auto& [a, b, base] : Tests){
        cout << "Digital sum of " << a << " to the power " << b << " in base " << base << " is : ";
        cout << digital_sum(a, b, base) << ".\n";
    }

    return 0;
}