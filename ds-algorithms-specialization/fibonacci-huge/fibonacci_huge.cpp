#include <iostream>
#include <vector>

using namespace std;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

bool is_a_period(vector<long long> &numbers) {
    int size = numbers.size();
    int half_size = size / 2;
    bool is_a_period = size > 0 && size % 2 == 0;
    for (int i = 0; is_a_period && i < half_size; ++i) {
        is_a_period = numbers[i] == numbers[i + half_size];
    }
    return is_a_period;
}

vector<long long> find_period(long long m) {
    vector<long long> period;

    long long previous = 0 % m;
    long long current  = 1 % m;

    period.push_back(previous);
    period.push_back(current);

    while (true) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
        period.push_back(current);
        if (is_a_period(period)) {
            period.erase (period.begin() + (period.size() / 2), period.end());
            break;
        }
    }
    return period;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    if (n <= 1)
        return n;

    vector<long long> period = find_period(m);
    int size = period.size();

    return period[n % size];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
