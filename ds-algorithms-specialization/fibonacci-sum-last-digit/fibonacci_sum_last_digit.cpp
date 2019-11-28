#include <iostream>

using namespace std;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
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

int fibonacci_sum_fast(long long n) {
    if (n <= 1)
        return n;

    int fn_mod_10_period[] = {0, 1, 1, 2, 3, 5, 8, 3, 1, 4, 5, 9, 4, 3,
        7, 0, 7, 7, 4, 1, 5, 6, 1, 7, 8, 5, 3, 8, 1, 9, 0, 9, 9,
        8, 7, 5, 2, 7, 9, 6, 5, 1, 6, 7, 3, 0, 3, 3, 6, 9, 5, 4,
        9, 3, 2, 5, 7, 2, 9, 1};
    int fn_mod_10_period_size = 60; // (sizeof(a)/sizeof(*a));
    int fn_mod_10_period_sum = 280;

    long long remainder = n % fn_mod_10_period_size;
    long long quotient = (n - remainder) / fn_mod_10_period_size;

    return ((quotient * fn_mod_10_period_sum)
        + calculate_partial_sum(fn_mod_10_period, remainder)) % 10;
}

int main() {
    long long n = 0;
    cin >> n;
    cout << fibonacci_sum_fast(n) << endl;
}
