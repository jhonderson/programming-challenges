
#include <iostream>

/**
 * UVa 11727 - Cost Cutting
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

using namespace std;

int main()
{
    unsigned short int numberOfTestsCases, caseNumber = 0, salaries[3], winnerSalary;
    cin >> numberOfTestsCases;
    while(caseNumber < numberOfTestsCases)
    {
        for (int i = 0; i < 3; i++)
            cin >> salaries[i];

        winnerSalary = salaries[0];
        if ((salaries[0] - salaries[1]) * (salaries[1] - salaries[2]) > 0)
            winnerSalary = salaries[1];
        else if ((salaries[0] - salaries[2]) * (salaries[2] - salaries[1]) > 0)
            winnerSalary = salaries[2];
        printf("Case %d: %d\n", ++caseNumber, winnerSalary);
    }
    return 0;
}
