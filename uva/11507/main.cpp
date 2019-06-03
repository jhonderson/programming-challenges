/*
 * main.cpp
 *
 * Copyright 2019 Jhon Anderson Cardenas <jhonderson2007@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <iostream>

/**
 * UVa 11507 - Bender B. Rodriguez
 *
 * Time complexity:
 *  Linear
 *
 * Space complexity:
 *  Linear
 * */

#define MAX_NUM_OF_STEPS 100000

using namespace std;

string findDirectionOfLastSegmentAfterMovements(unsigned int L, const string* steps)
{
    char axisOfLS = 'x';
    bool signOfAxisOfLS = true;
    string dirOfLastSegment = "+x", currentStep;
    for (int i = 1; i <= L - 1; i++)
    {
        currentStep = steps[i];
        
        if (currentStep == "No")
            continue;

        if (axisOfLS == 'x' && currentStep[0] == '-')
            signOfAxisOfLS = !signOfAxisOfLS;
        else if (axisOfLS == 'y' && currentStep[1] == 'y' && currentStep[0] == '+')
            signOfAxisOfLS = !signOfAxisOfLS;
        else if (axisOfLS == 'z' && currentStep[1] == 'z' && currentStep[0] == '+')
            signOfAxisOfLS = !signOfAxisOfLS;

        if (axisOfLS == 'x')
            axisOfLS = currentStep[1];
        else if ((axisOfLS =='y' && currentStep[1] == 'y') || (axisOfLS =='z' && currentStep[1] == 'z'))
            axisOfLS = 'x';
    }
    string dirOfLS;
    dirOfLS.push_back((signOfAxisOfLS ? '+' : '-' ));
    dirOfLS.push_back(axisOfLS);
    return dirOfLS;
}

int main(int argc, char **argv)
{
    unsigned int L;
    string steps[MAX_NUM_OF_STEPS + 1];
    while (cin >> L, L >= 2)
    {
        for (int i = 1; i <= L - 1; i++)
            cin >> steps[i];

        string dirOfLastSegment = findDirectionOfLastSegmentAfterMovements(L, steps);
        cout << dirOfLastSegment << endl;
    }
    return 0;
}

