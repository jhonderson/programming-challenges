#include <iostream>
#include <algorithm>
#include <math.h>

/**
 * UVA 100: 3n + 1
 * Max cycle length found between 1 and 1000000 is 525.
 *
 * So for find_cycle_length function, no matter what the input is,
 *  the max recursion depth is 525 (for the input limit that the problem
 *  specify).
 *
 * For each entry i,j the time complexity is abs(j-i)*525
 * The space complexity is constant: 1'000.000.
 * */

using namespace std;

const int MAX_INTPUT = 1000001;
unsigned long pre_calculated_cycles[MAX_INTPUT];

int find_cycle_length(unsigned long i)
{
    int cycle_length;
    if (i == 1)
    {
        cycle_length = 1;
    } else if (i < MAX_INTPUT && pre_calculated_cycles[i] != -1)
    {
        cycle_length = pre_calculated_cycles[i];
    } else if (i % 2 == 0)
    {
        cycle_length = 1 + find_cycle_length(i / 2);
    } else
    {
        cycle_length = 1 + find_cycle_length(3 * i + 1);
    }
    if (i < MAX_INTPUT) {
		pre_calculated_cycles[i] = cycle_length;
	}
    return cycle_length;
}

int find_max_cycle_length(unsigned long a, unsigned long b)
{
    int max_cycle_length = -1;
    unsigned long from = std::min(a, b);
    unsigned long to = std::max(a, b);
    for (unsigned long i = to; i >= from; i--)
    {
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
    for (int i = 0; i < MAX_INTPUT; i++)
    {
        pre_calculated_cycles[i] = -1;
    }
    unsigned long i, j;
    while (cin >> i >> j)
    {
        cout << i  << " " << j << " " << find_max_cycle_length(i, j) << endl;
    }
    return 0;
}
