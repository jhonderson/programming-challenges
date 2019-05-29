
#include <iostream>

/**
 * UVa 11172 - Relational Operators
 *
 * Time compexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 */

using namespace std;

int main()
{
    unsigned int numberOfSets = 0;
    int a,b;
    cin >> numberOfSets;
    while (numberOfSets--)
    {
        cin >> a >> b;
        cout << (a < b ? "<" : a > b ? ">" : "=") << endl;
    }
    return 0;
}
