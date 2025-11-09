#include<iostream>
#include<vector>
#include<string>
#include<functional>
#include<unordered_map>
#include<stack>
using namespace std;

long long longest_Collatz(long long limit){
    if(limit < 1) return -1;

    unordered_map<long long, long long> get_terms = {{1, 1}};

    function<long long(long long)> dfs = [&](long long n) -> long long {
        if(get_terms.count(n)) return get_terms[n];

        if(n % 2 == 0){
            return get_terms[n] = 1 + dfs(n / 2);
        } else{
            return get_terms[n] = 1 + dfs(3 * n + 1);
        }
    };

    long long result = 1;       // number that gives longest sequence
    long long max_length = 1;   // length of that sequence

    for(long long i = 1; i <= limit; ++i){
        long long length = dfs(i);
        if(length > max_length){
            max_length = length;
            result = i;
        }
    }

    return result;
}


long long longest_Collatz_iterative(long long limit){
    if(limit < 1) return -1;

    unordered_map<long long, long long> get_terms;
    get_terms[1] = 1; // base case

    auto compute_length = [&](long long n) -> long long {
        if(get_terms.count(n)) return get_terms[n];

        long long query_num = n;

        stack<long long> chain; // number in collatz chain.
        chain.push(query_num);

        while(true){
            // update query_num with its next number in the chain.
            query_num = (query_num % 2 == 0) ? query_num / 2 : 3 * query_num + 1;

            // unwind the chain while filling memoized lengths.
            if(get_terms.count(query_num)){
                while(!chain.empty()){
                    long long num = chain.top();
                    chain.pop();
                    long long next = (num % 2 == 0) ? num / 2 : 3 * num + 1;
                    get_terms[num] = 1 + get_terms[next];
                }
                break;
            }
            
            // otherwise, keep building the chain.
            chain.push(query_num);
        }

        return get_terms[n];
    };

    long long best_num = 1;       // number that gives longest sequence
    long long max_length = 1;   // length of that sequence

    for(long long i = 1; i <= limit; ++i){
        long long length = compute_length(i);
        if(length > max_length){
            max_length = length;
            best_num = i;
        }
    }

    return best_num;
}


int main(){

    int result = longest_Collatz_iterative(1e6);
    cout << result;

    return 0;
}