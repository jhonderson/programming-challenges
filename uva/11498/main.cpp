
#include <iostream>

/**
 * UVa 11498 - Division of Nlogonia
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

using namespace std;

string findIslandLocation(short int n, short int m, short int x, short int y)
{
    if (n == x || m == y)
        return "divisa";

    string location = "SO";

    if (y > m)
        location[0] = 'N';

    if (x > n)
        location[1] = 'E';

    return location;
}

int main()
{
    unsigned short int numberOfQueries;
    short int n, m, x, y;
    string location;
    while( cin >> numberOfQueries, numberOfQueries > 0)
    {
        cin >> n >> m;
        while (numberOfQueries--)
        {
            cin >> x >> y;
            location = findIslandLocation(n, m, x, y);
            cout << location << endl;
        }
    }
    return 0;
}
