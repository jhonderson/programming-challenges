#include <iostream>

using namespace std;

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int calculate_partial_sum(int *numers, int to) {
    int sum = 0;
    for (int i = 0; i <= to; ++i) {
        sum += numers[i];
    }
    return sum;
}

int fibonacci_sum_squares_fast(long long n) {
    int fn_sqr_mod_10_period[] = {0, 1, 1, 4, 9, 25, 64, 9, 1, 16, 25, 81,
        16, 9, 49, 0, 49, 49, 16, 1, 25, 36, 1, 49, 64, 25, 9, 64, 1, 81,
        0, 81, 81, 64, 49, 25, 4, 49, 81, 36, 25, 1, 36, 49, 9, 0, 9, 9,
        36, 81, 25, 16, 81, 9, 4, 25, 49, 4, 81, 1};

    int fn_sqr_mod_10_period_size = 60; // (sizeof(a)/sizeof(*a));
    int fn_sqr_mod_10_period_sum = 1800;

    long long remainder = n % fn_sqr_mod_10_period_size;
    long long quotient = (n - remainder) / fn_sqr_mod_10_period_size;

    return ((quotient * fn_sqr_mod_10_period_sum)
        + calculate_partial_sum(fn_sqr_mod_10_period, remainder)) % 10;
}

void print_fn_sqr_mod_10_period() {
    int fn_mod_10_period[] = {0, 1, 1, 2, 3, 5, 8, 3, 1, 4, 5, 9, 4, 3,
        7, 0, 7, 7, 4, 1, 5, 6, 1, 7, 8, 5, 3, 8, 1, 9, 0, 9, 9,
        8, 7, 5, 2, 7, 9, 6, 5, 1, 6, 7, 3, 0, 3, 3, 6, 9, 5, 4,
        9, 3, 2, 5, 7, 2, 9, 1};
    int fn_mod_10_period_size = 60; // (sizeof(a)/sizeof(*a));
    int fn_sqr_mod_10_period_sum = 0;

    cout << "{";
    for (int i = 0; i < fn_mod_10_period_size; i++) {
        int val = fn_mod_10_period[i] * fn_mod_10_period[i];
        fn_sqr_mod_10_period_sum += val;
        cout << val << ", ";
    }
    cout << "}" << endl;
    cout << fn_sqr_mod_10_period_sum << endl;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n) << endl;
    //print_fn_sqr_mod_10_period();
}
