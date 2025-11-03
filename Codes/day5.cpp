#include <iostream>
#include <string>
#include<vector>
#include <unordered_map>
using namespace std;

// num to words map.
unordered_map<int, string> w = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"},
    {9, "nine"}, {10, "ten"}, {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"},
    {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}, {20, "twenty"}, {30, "thirty"},
    {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}, {100, "hundred"},
    {1000, "thousand"}
};

// Recursive function to get any "n" in words if n in [1, 1000].
string in_words(int n){
    if (n < 1){
        throw invalid_argument("n should be greater than or equal to 1.");
    }

    if(n == 1000) return "one thousand";
    
    if(n < 20) return w[n]; // we can write directly.
    // For instance, if n = 89 then n = 80 + 9.
    if(n < 100){
        return w[n - n%10] + (n%10 ? " " + w[n%10] : "");
    }

    if(n < 1000){
        int hundreds = n / 100; // how many hundreds?
        int rest = n % 100; // remainder.

        string res = w[hundreds] + " hundred";
        if(rest != 0){
            // as per British English number wording.
            res += " and " + in_words(rest);
        }

        return res;
    }
    
    return "Please enter n in [1, 1000).";
}

// iterative version of above function.
string in_words_iterative(int n){
    if (n < 1 || n > 1000){
        throw invalid_argument("n should in range [1, 1000].");
    }
    
    if(n == 1000) return "one thousand.";
    string res;
    
    while(n > 0){
        if(n < 20){
            res += w[n];
            break;
        }

        else if(n < 100){
            res += w[n - n%10];
            if(n%10) res += " " + w[n%10];
            break;
        }

        else{ // n < 1000
            int hundreds = n / 100;
            int rest = n % 100;
        
            res += w[hundreds] + " hundred";
            if(rest != 0){
                res += " and ";
            }

            n = rest;
        }
    }

    return res;
}

// Can handle all numbers less than 1 billion.
string num_to_letters(int n){
    vector<string> scale = {"", "thousand", "million"};
    int i = 0;
    string result;

    while(n > 0){
        int chunk = n % 1000;

        if(chunk != 0){
            string part = in_words_iterative(chunk);
            if(scale[i] != "") part += " " + scale[i];
            result = part + " " + result;
        }

        n /= 1000;
        i++;
    }

    return result;
}

// It gives solution problem 17.
int count_letters(int n){
    if(n < 1 || n > 1000){
        throw invalid_argument("Please enter n in range [1, 1000].");
    }

    if(n == 1000) return 11; // 11 = strlen("onethousand")
    int total = 0;

    while(n > 0){
        if(n <= 20){
            total += w[n].size();
            break;
        }

        else if(n < 100){
            total += w[n - n%10].size();
            if(n%10) total += w[n%10].size();
            break;
        }

        else{
            int hundreds = n / 100;
            int rest = n % 100;

            total += w[hundreds].size() + 7; // 7 = strlen("hundred")
            if (rest != 0) total += 3;       // 3 = strlen("and")

            n = rest;
        }
    }

    return total;
}

int main(){

    int letter_counts = 0;
    for(int i = 1; i <= 1000; ++i){
        letter_counts += count_letters(i);
    }

    cout << letter_counts;

    return 0;
}