
#include <iostream>
#include <regex>

using namespace std;

int main()
{
    string text = "a70 line: a70 and z72 will be replaced, aa24 and a872 will not a70";
    regex e("(^|[^\\w|\\d])\\w\\d\\d($|[^\\w|\\d])");
    cout << regex_replace(text, e, "$1***$2") << endl;

    return 0;
}
