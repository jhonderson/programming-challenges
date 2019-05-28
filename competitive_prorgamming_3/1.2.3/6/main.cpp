
#include <iostream>

using namespace std;

int comparisons = 0;
int maxComparisons = -1;

int current = 0;
int UniqueNumber () { return ++current; }

bool arrayContains(int* numbers, unsigned int from, unsigned int to, int element)
{
    comparisons += 1;
    bool elementFound = false;
    int middle = (to - from) / 2 + from;

    if (from <= middle && middle < to)
    {
        if (element < numbers[middle])
        {
            return arrayContains(numbers, from, middle, element);
        } else if (element > numbers[middle])
        {
            return arrayContains(numbers, middle + 1, to, element);
        } else
        {
            elementFound = true;
        }
    }
    return elementFound;
}

void bookSolution()
{
    int n = 5, L[] = {10, 7, 5, 20, 8}, v = 7;
    sort(L, L + n);
    printf("%d\n", binary_search(L, L + n, v));
}

int main()
{
    unsigned size = 1000000;
    int n[size];
    generate_n (n, size, UniqueNumber);

    bool elementFound = true;
    for (int i=0; i<size; ++i)
    {
        comparisons = 0;
        elementFound = elementFound && arrayContains(n, 0, size, n[i]);
        if (comparisons > maxComparisons)
            maxComparisons = comparisons;
    }
    cout << elementFound << endl;
    cout << maxComparisons << endl;
    
    bookSolution();

    return 0;
}
