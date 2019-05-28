
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323

using namespace std;

int main()
{
    unsigned int n;
    string format;
    while (cin >> n)
    {
        format = "%." + to_string(n) +  "f\n";
        printf(format.c_str(), PI);
    }
    return 0;
}
