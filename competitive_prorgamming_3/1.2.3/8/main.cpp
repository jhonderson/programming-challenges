
#include <iostream>
#include <math.h>

using namespace std;

void printSubsets(int* numbers, unsigned int size)
{
    unsigned int numberOfCombinations = pow(2, size);
    for (int i = 0; i < numberOfCombinations; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i & (1 << j))
            {
                cout << ' ' << numbers[j];
            }
        }
        cout << endl;
    }
}

int main()
{
    unsigned int size = 20;
    int characters[size];
    for (int i = 0; i < size; i++)
        characters[i] = i;

    printSubsets(characters, size);

    return 0;
}
