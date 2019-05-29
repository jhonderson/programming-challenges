
#include <iostream>
#include <sstream>

using namespace std;

void splitNumbers(string& numbersAsText, int* numbers, unsigned int& size, char delimiter = ' ')
{
    size = 0;
    stringstream strStream(numbersAsText);
    string token;
    while (getline(strStream, token, delimiter))
    {
        stringstream numberStream(token);
        numberStream >> numbers[size++];
    }
}

int evaluateSum(const int* numbers, unsigned int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += numbers[i];
    return sum;
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        int numbers[1000000];
        unsigned int size = 0;
        splitNumbers(line, numbers, size);
        int sum = evaluateSum(numbers, size);
        cout << sum << endl;
    }
    return 0;
}
