#include<iostream>
#include<vector>
#include<cmath>
#include<unordered_set>
using namespace std;

int sum_proper_divisors(int n){
    int total = 1; // 1 as n's first proper divisors.
    int limit = static_cast<int>(sqrt(n));

    // sum of proper divisors.
    for(int i = 2; i <= limit; ++i){
        if(n % i == 0){
            total += i;
            if(i != n / i) total += n / i;
        }
    }
    return total;
}

vector<int> sieve_sum_proper_divisors(int n){
    vector<int> div_sum(n+1, 1); // 1 is always a proper divisor for n > 1.
    div_sum[0] = 0; // not used.
    div_sum[1] = 0; // 1 has no proper divisor.

    for(int i = 2; i <= n / 2; ++i){
        for(int j = 2*i; j <= n; j+=i){
            div_sum[j] += i;
        }
    }

    return div_sum;
}

// Problem 23.
int solution(int n){
    if(n < 1) throw invalid_argument("n should be greater than or equal to 1.");
    vector<int> div_sum = sieve_sum_proper_divisors(n+1);
    vector<int> abundant_nums;

    for(int i = 1; i <= n; ++i){
        if(div_sum[i] > i) abundant_nums.push_back(i);
    }

    // any num in nums can be written as sum of two abundant numbers.
    vector<bool> can_be_written(n+1, false);
    int m = abundant_nums.size();
    for(int i = 0; i < m; ++i){
        for(int j = i; j < m; ++j){
            int s = abundant_nums[i] + abundant_nums[j];
            if(s > n) break;
            can_be_written[s] = true;
        }
    }

    int total_sum = 0; // required sum
    for(int i = 1; i <= n; ++i){
        // notice "!"
        if(!can_be_written[i]) total_sum += i;
    }

    return total_sum;
}

// Problem 21
int sum_amicable_numbers_sieve(int n){
    vector<int> divisor_sum = sieve_sum_proper_divisors(n);
    int total = 0;

    for(int i = 2; i <= n; ++i){
        int a = divisor_sum[i];
        if(a <= n && a != i && i == divisor_sum[a]){
            total += i;
        }
    }

    return total;
}

int sum_amicable_numbers_memo(int n){
    vector<int> divisor_sum(n+1);
    for(int i = 1; i <= n; ++i){
        divisor_sum[i] = sum_proper_divisors(i);
    }

    int total = 0;
    for(int i = 1; i <= n; ++i){
        int a = divisor_sum[i];
        if(a <= n && i == divisor_sum[a] && a != i){
            total += i;
        }
    }

    return total;
}


int main(){


    return 0;
}