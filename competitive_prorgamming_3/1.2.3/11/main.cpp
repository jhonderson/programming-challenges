
#include <iostream>
#include <strstream>

using namespace std;

double evaluateExpression(const string& expression)
{
    string subExpression = "";
    for (int i = 0; i < expression.size(); i++)
    {
        if (('0' <= expression[i] && expression[i] <= '9') || expression[i] == '.')
        {
            subExpression.append(1, expression[i]);
        } else
        {
            if (!subExpression.empty()) {
                cout << " " << subExpression;
                subExpression = "";
            }
            if (expression[i] != ' ')
            {
                cout << " " << expression[i];
            }
            
        }
    }
    cout << endl;

    return 234.234;
}

int main()
{
    string expression = "3 + (8 - 7.5) * 10 / 5 - (2 + 5 * 7)";
    double result = evaluateExpression(expression);
    printf("%s = %f\n", expression.c_str(), result);
    return 0;
}
