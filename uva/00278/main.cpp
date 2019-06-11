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
#include <math.h>

/**
 * UVa 00278 - Chess
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

using namespace std;

typedef unsigned short int short_t;

void swap(short_t& a, short_t& b)
{
    short_t temp = a;
    a = b;
    b = temp;
}

short_t getMaxNumOfChessPiecesInBoard(short_t m, short_t n, char chessPiece)
{
    if (m > n)
    {
        swap(m, n);
    }

    switch (chessPiece)
    {
        case 'r':
            // number of fields in the largest diagonal
            return m;
        case 'k':
            // number of fields in all the diagonals of the same color,
            // taking as base color the corner filed.
            return (m * n + 1) / 2;
        case 'Q':
        {
            // for each row, # of fields separated by 2 fields; for each
            // col 1 field.
            short_t increasingValue = (n + 1) / 2;
            return (m / increasingValue) * increasingValue + (m % increasingValue);
        }
        case 'K':
            // number of fields of the same color in the same row
            // (taking as base color the first field), multiplied by the
            // number of intercaled rows (rows separated by another row)
            return (short_t)((m + 1) / 2) * (short_t)((n + 1) / 2);
    }
    // locally unreachable
    return 0;
}

int main(int argc, char **argv)
{
    short_t numOfProblems, m, n, maxNumOfChessPieces;
    char chessPiece;
    cin >> numOfProblems;
    while (numOfProblems--)
    {
        cin >> chessPiece >> m >> n;
        maxNumOfChessPieces = getMaxNumOfChessPiecesInBoard(m,n, chessPiece);
        cout << maxNumOfChessPieces << endl;
    }
    return 0;
}
