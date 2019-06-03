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

#include <algorithm>
#include <iostream>

/**
 * UVa 10141 - Request for Proposal
 *
 * Time complexity:
 *  n log(n), where n is the number of proposals.
 *
 * Space complexity:
 *  n, where n is the number of proposals.
 * */

using namespace std;

int main(int argc, char **argv)
{
    short int numOfRequirements, numOfProposals, numOfMetReqs, refId = 1;
    char reqName[81], propName[81];
    double propPrice;
    short int maxMetReq;
    double minPrice;
    string nameOfWinProporsal;
    while (cin >> numOfRequirements >> numOfProposals, numOfRequirements != 0 && numOfProposals != 0)
    {
        maxMetReq = -1;
        minPrice = 999999999999999;
        nameOfWinProporsal = "";

        // Leave a blank line between the output for each pair of RFPs
        if (refId > 1)
            cout << endl;

        cin.ignore();

        for (int i = 0; i < numOfRequirements; i++)
            cin.getline(reqName, sizeof(reqName));

        for (int i = 0; i < numOfProposals; i++)
        {
            cin.getline(propName, sizeof(propName));
            cin >> propPrice >> numOfMetReqs;
            cin.ignore();

            if (numOfMetReqs > maxMetReq)
            {
                minPrice = propPrice;
                maxMetReq = numOfMetReqs;
                nameOfWinProporsal = string(propName);
            } else if (numOfMetReqs == maxMetReq && propPrice < minPrice)
            {
                minPrice = propPrice;
                nameOfWinProporsal = string(propName);
            }

            for (int j = 0; j < numOfMetReqs; j++)
                cin.getline(reqName, sizeof(reqName));
        }

        printf("RFP #%d\n", refId);
        printf("%s\n", nameOfWinProporsal.c_str());
        refId++;
    }
    return 0;
}

