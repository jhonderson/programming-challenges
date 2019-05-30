
#include <iostream>

/**
 * UVa 10114 - Loansome Car Buyer
 *
 * Time complexity:
 *  Linear: O(n), where n is number of months
 *
 * Space complexity:
 *  Linear: O(m), where m is number of deprecation records
 * */

using namespace std;

unsigned short int findFirstMonthDebtIsLessThanCarPrice(unsigned short int months,
    double downPayment, double loanAmount, unsigned short int* deprecationMonts,
    double* deprecationPercentages, unsigned short int numOfDeprecationRecords)
{
    double montlyPayment = loanAmount / (double) months;
    double lastLoanAmount = loanAmount + montlyPayment;
    double lastCarValue = loanAmount + downPayment;
    double lastDeprecationPercentage;
    unsigned short int deprecationIndex = 0;

    for (unsigned short int month = 0; month < months; month++)
    {
        if (deprecationIndex < numOfDeprecationRecords && month == deprecationMonts[deprecationIndex])
        {
            lastDeprecationPercentage = deprecationPercentages[deprecationIndex];
            deprecationIndex++;
        }
        lastLoanAmount -= montlyPayment;
        lastCarValue = lastCarValue - lastCarValue * lastDeprecationPercentage;
        if (lastLoanAmount < lastCarValue)
            return month;
    }

    return months;
}

void printFormattedMonth(unsigned short int month)
{
    cout << month << " " << (month == 1 ? "month" : "months") << endl;
}

int main()
{
    short int months;
    unsigned short int numOfDeprecationRecords, deprecationIndex, monthAnswer;
    double downPayment, loanAmount;
    while (cin >> months >> downPayment >> loanAmount >> numOfDeprecationRecords, months >= 0)
    {
        unsigned short int deprecationMonts[numOfDeprecationRecords];
        double deprecationPercentages[numOfDeprecationRecords];
        deprecationIndex = -1;
        while(++deprecationIndex < numOfDeprecationRecords)
        {
            cin >> deprecationMonts[deprecationIndex] >> deprecationPercentages[deprecationIndex];
        }
        monthAnswer = findFirstMonthDebtIsLessThanCarPrice(months,
            downPayment, loanAmount, deprecationMonts,
            deprecationPercentages, numOfDeprecationRecords);
        printFormattedMonth(monthAnswer);
    }
    return 0;
}
