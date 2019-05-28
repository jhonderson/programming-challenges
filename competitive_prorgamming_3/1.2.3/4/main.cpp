
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void printSortedAndUniqueArray(int *array, unsigned int n)
{
    vector<int> data(array, array + n);
    sort(data.begin(), data.end());
    vector<int>::iterator it = unique(data.begin(), data.end());
    data.resize(distance(data.begin(), it));
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << " ";
    cout << endl;
}

int main()
{
    int n[] = {6,34,5,8,2,3,8,9,3,2,5,6,75,3,2,2,5,4,6,8,6,2};
    printSortedAndUniqueArray(n, 22);
    return 0;
}
