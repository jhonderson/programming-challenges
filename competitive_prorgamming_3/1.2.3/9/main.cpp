
#include <iostream>
#include <math.h>

using namespace std;

long convertToBase10(const string& input, int base)
{
    if(base < 2 || base > 36)
        return 0;

    bool isNegative = (input[0] == '-');

    int startIndex = input.length()-1;
    int endIndex   = isNegative ? 1 : 0;

    long value = 0;
    int digitValue = 1;

    for(int i = startIndex; i >= endIndex; --i)
    {
        char c = input[i];

        if(c >= 'a' && c <= 'z')
            c -= ('a' - 'A');

        if(c >= '0' && c <= '9')
            c -= '0';
        else
            c = c - 'A' + 10;

        if(c >= base)
            return 0;

        value += c * digitValue;

        digitValue *= base;
    }

    if(isNegative)
        value *= -1;

    return value;
}

string convertFromBase10(long value, int base)
{
    if(base < 2 || base > 36)
        return "0";

    bool isNegative = (value < 0);
    if(isNegative)
        value *= -1;

    string output;

    do
    {
        char digit = value % base;

        if(digit < 10)
            digit += '0';
        else
            digit = digit + 'A' - 10;

        output += digit;

        value /= base;

    } while (value > 0);

    if(isNegative)
        output += '-';

    int len = output.size() - 1;
    for(int i = 0; i < len; ++i)
    {
        char temp = output[i];
        output[i] = output[len-i];
        output[len-i] = temp;
    }

    return output;
}

string convertBase(const string& number, unsigned int baseFrom, unsigned int baseTo)
{
    return convertFromBase10(convertToBase10(number, baseFrom), baseTo);
}

int main()
{
    string number = "FF";
    cout << convertBase(number, 16, 10) << endl;
    cout << convertBase(number, 16, 2) << endl;

    return 0;
}
