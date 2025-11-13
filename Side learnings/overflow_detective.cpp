#include<iostream>
#include<cstdint> // for int32_t, int64_t, INTMAX_32 and INTMIN_32
#include<limits> // for numeric_limits
#include<optional>
using namespace std;

// return true of `a + b` overflows.
bool add_overflow(int32_t a, int32_t b){
    int64_t sum = static_cast<int64_t>(a) + static_cast<int64_t>(b);
    return (sum > numeric_limits<int32_t>::max()
    || sum < numeric_limits<int32_t>::min());
}

// same as checking whether `a + b` lies in [INT32_MIN, INT32_MIN]
bool add_overflow_branching(int32_t a, int32_t b){
    if(b > 0) return a > static_cast<int32_t>(numeric_limits<int32_t>::max() - b);
    if(b < 0) return a < static_cast<int32_t>(numeric_limits<int32_t>::min() - b);
    return false; // b = 0 => no overflow.
}

// return true if `a*b` overflows else update `out`
bool mul_overflows(int64_t a, int64_t b, int64_t &out){
    // Fast path: multiplication by 0 cannot overflow.
    if(a == 0 || b == 0){
        out = 0;
        return false;
    }

    // perform multiplication in 128-bit precision
    __int128_t result = static_cast<__int128_t>(a) * static_cast<__int128_t>(b);
    if(result > numeric_limits<int64_t>::max() ||
       result < numeric_limits<int64_t>::min()){
        return true; // overflow
    }

    // cast back to 64-bit
    out = static_cast<int64_t>(result);
    return false;
}

/*
Task: Write optional<int64_t> safe_quad(int a, int b, int n, int64_t limit)
that returns n^2 + a*n + b if value is in [LLONG_MIN, LLONG_MAX] and <= limit, otherwise returns nullopt.
*/
optional<int64_t> safe_quad(int a, int b, int n, int64_t limit){
    __int128_t quad = (__int128_t)n * n + (__int128_t)a * n + (__int128_t)b;

    if(quad < numeric_limits<int64_t>::min() ||
       quad > numeric_limits<int64_t>::max() || quad > limit){
        return nullopt;
    }

    return (int64_t)quad;
}

int main(){

    int64_t a = 1'123'344, b = 345'442'453;
    int64_t out = 1;

    // cout << boolalpha;
    // cout << mul_overflows(a, b, out) << ", " << out;

    auto quad = safe_quad(10, 20, 30, 2e3);
    if(quad.has_value()) cout << *quad;


    return 0;
}