
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
    double downPayment, double loanAmount, unsigned short int* deprecationMonths,
    double* deprecationPercentages, unsigned short int numOfDeprecationRecords)
{
    double monthlyPayment = loanAmount / (double) months;

    // trick to treat month 0 like the others months, i.e the loan
    // amount is the before loan amount less the monthly payment, which
    // in the case of month 0 is the original loan amount:
    //   (loanAmount + monthlyPayment) - monthlyPayment = loanAmount
    double lastLoanAmount = loanAmount + monthlyPayment;

    double lastCarValue = loanAmount + downPayment;
    double lastDeprecationPercentage;
    unsigned short int deprecationIndex = 0;

    for (unsigned short int month = 0; month < months; month++)
    {
        if (deprecationIndex < numOfDeprecationRecords && month == deprecationMonths[deprecationIndex])
        {
            lastDeprecationPercentage = deprecationPercentages[deprecationIndex];
            deprecationIndex++;
        }
        lastLoanAmount -= monthlyPayment;
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
        unsigned short int deprecationMonths[numOfDeprecationRecords];
        double deprecationPercentages[numOfDeprecationRecords];
        deprecationIndex = -1;
        while(++deprecationIndex < numOfDeprecationRecords)
        {
            cin >> deprecationMonths[deprecationIndex] >> deprecationPercentages[deprecationIndex];
        }
        monthAnswer = findFirstMonthDebtIsLessThanCarPrice(months,
            downPayment, loanAmount, deprecationMonths,
            deprecationPercentages, numOfDeprecationRecords);
        printFormattedMonth(monthAnswer);
    }
    return 0;
}
