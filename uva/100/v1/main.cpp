#include <iostream>

using namespace std;

int iterations = 0;

/**
 * @brief find_cycle_length using tail recursion
 * @param i value to calculate cycle length
 * @param acc accumulative previouslly calculated cycle length
 * @return cycle lentgh of i
 */
int find_cycle_length(int i, int acc)
{
	iterations++;
    if (i == 1)
    {
        return acc + 1;
    } else if (i % 2 == 0)
    {
        return find_cycle_length(i / 2, acc + 1);
    } else
    {
        return find_cycle_length(3 * i + 1, acc + 1);
    }
}

int find_cycle_length(int i)
{
    return find_cycle_length(i, 0);
}

int find_max_cycle_length(int a, int b)
{
    int max_cycle_length = -1;
    for (int i = a; i <= b; i++) {
        int cycle_length = find_cycle_length(i);
        if (cycle_length > max_cycle_length)
        {
            max_cycle_length = cycle_length;
        }
    }
    return max_cycle_length;
}

int main()
{
    int i, j;
    while (cin >> i >> j)
    {
		iterations = 0;
        cout << i  << " " << j << " " << find_max_cycle_length(i, j) << endl;
        cout << iterations << endl;
    }
    return 0;
}
