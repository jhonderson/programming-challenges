
#include <iostream>
#include <math.h>

/**
 * UVA 10038: Jully Jumpers
 *
 * Time complexity:
 *   O(n)
 *
 * Space complexity:
 *   O(n)
 * */

using namespace std;

bool is_sequence_a_jolly_jumper(int *sequence, unsigned int n)
{
    if (n == 1)
        return true;

    bool differences_found[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        differences_found[i] = false;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int difference = abs(sequence[i] - sequence[i + 1]);
        if (1 <= difference && difference <= n - 1 && !differences_found[difference - 1])
        {
            differences_found[difference - 1] = true;
        } else
        {
            return false;
        }
    }
    return true;
}

int main()
{
    unsigned int n;
    while (cin >> n && n > 0)
    {
        int sequence[n];
        for (int i = 0; i < n; i++)
        {
            cin >> sequence[i];
        }
        cout << (is_sequence_a_jolly_jumper(sequence, n) ? "Jolly" : "Not jolly") << endl;
    }
    return 0;
}
