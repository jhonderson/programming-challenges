#include <iostream>
#include <vector>

using namespace std;

long long MaxPairwiseProduct(const vector<int>& numbers) {
    long long product = 0;
    int n = numbers.size();
    int firstMaxValueIndex = -1;
    int secondMaxValueIndex = -1;
    int maxValue = -1;
    for (int i = 0; i < n; ++i) {
        if (firstMaxValueIndex == -1 || numbers[i] > maxValue) {
            firstMaxValueIndex = i;
            maxValue = numbers [i];
        }
    }
    maxValue = -1;
    for (int i = 0; i < n; ++i) {
        if (firstMaxValueIndex != i && (secondMaxValueIndex == -1 || numbers[i] > maxValue)) {
            secondMaxValueIndex = i;
            maxValue = numbers [i];
        }
    }
    return ((long long) numbers[firstMaxValueIndex]) * numbers[secondMaxValueIndex];
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    long long product = MaxPairwiseProduct(numbers);
    cout << product << "\n";
    return 0;
}
