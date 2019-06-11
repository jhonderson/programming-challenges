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
 * UVa 00696 - How Many Knights
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

using namespace std;

typedef unsigned int int_t;

void swap(int_t& a, int_t& b)
{
    int_t temp = a;
    a = b;
    b = temp;
}

int_t getMaxNumOfKnightsInBoard(int_t m, int_t n)
{
    if (m > n)
    {
        swap(m, n);
    }

    if (m == 1)
    {
        // number of cols
        return n;
    } else if (m == 2)
    {
        // if there are 2 rows, the knights are grouped in 2*2 blocks of
        // fileds. Each block needs to be separated by 2
        // columns. Then, for each 4 columns, 4 knights can be located.
        // The remaining columns (n % 4) are considered like this:
        //   2 elements if the remaning column is just 1.
        //   4 elements if the remaining comlumn is 2 or 3.

        int_t numOfGroupsOfFourFields = (n / 4);
        int_t residueOfGroupsOfFourFields = (n % 4);
        if (residueOfGroupsOfFourFields > 2)
        {
            residueOfGroupsOfFourFields = 2;
        }

        return (numOfGroupsOfFourFields * 4 + residueOfGroupsOfFourFields * 2);
    }
    // number of fields in all the diagonals of the same color,
    // taking as base color the corner filed.
    return (m * n + 1) / 2;
}

int main(int argc, char **argv)
{
    int_t m, n, maxNumOfKnights;
    while (cin >> m >> n, m != 0 || n != 0)
    {
        maxNumOfKnights = getMaxNumOfKnightsInBoard(m, n);
        printf("%d knights may be placed on a %d row %d column board.\n", maxNumOfKnights, m, n);
    }
    return 0;
}
