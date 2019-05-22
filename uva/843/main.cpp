
#include <iostream>
#include <string>

/**
 * UVA 843: Crypt kicker
 *
 * Time complexity:
 *
 * Space complexity:
 * */

using namespace std;

string decryptText(string *alphabet, unsigned int alphabetSize, string encryptedText)
{
    return "***";
}

int main()
{
    unsigned int alphabetSize;

    cin >> alphabetSize;

    string alphabet[alphabetSize];
    for (int i = 0; i < alphabetSize; i++)
    {
        cin >> alphabet[i]; 
    }
    string encryptedText;
    string decryptedText;
    while (cin >> encryptedText) {
        decryptedText = decryptText(alphabet, alphabetSize, encryptedText);
        cout << decryptedText << endl;
    }
    return 0;
}
