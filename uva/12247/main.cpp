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
#include <algorithm>

/**
 * 12247 - Jollo
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

#define NUM_OF_VALUES 6
#define MAX_VALUE 52

using namespace std;

typedef short int short_t;

void swap(short_t& a, short_t& b)
{
    short_t temp = a;
    a = b;
    b = temp;
}

void removeCollisions(short_t* values)
{
    sort(values, values + 5);
    for (short_t i = 0; i < NUM_OF_VALUES - 1; i++)
    {
        if (values[NUM_OF_VALUES - 1] == values[i])
        {
            values[NUM_OF_VALUES - 1]++;
        }
    }
    if (values[NUM_OF_VALUES - 1] > MAX_VALUE)
    {
        values[NUM_OF_VALUES - 1] = -1;
    }
}

short_t findLowestTrickyCard(short_t* values)
{

    sort(values, values + 3);

    if (values[3] > values[4])
    {
        swap(values[3], values[4]);
    }

    short_t i = 2, j = 3 + 1, counter = 0;
    bool thereIsGreaterThanY = false;
    while(i >= 0 && j >= 3)
    {
        if (values[i] > values[j])
        {
            if (j == 4)
            {
                thereIsGreaterThanY = true;
                j--;
            }

            counter++;
            i--;
        } else
        {
            j--;
        }
    }

    if (!thereIsGreaterThanY)
    {
        if (counter > 1)
        {
            values[NUM_OF_VALUES - 1] = values[2] + 1;
        } else if (counter == 1)
        {
            values[NUM_OF_VALUES - 1] = values[1] + 1;
        } else
        {
            // any value will work
            values[NUM_OF_VALUES - 1] = 1;
        }
    } else
    {
        if (counter > 1)
        {
            // now way to win
            values[NUM_OF_VALUES - 1] = -1;
        }
        else if (counter == 1)
        {
            values[NUM_OF_VALUES - 1] = values[i] + 1;
        }
    }

    removeCollisions(values);

    return values[NUM_OF_VALUES - 1];
}

int main(int argc, char **argv)
{
    short_t values[NUM_OF_VALUES];
    while (cin >> values[0] >> values[1] >> values[2] >> values[3] >> values[4],
        values[0] != 0 || values[1] != 0 || values[2] != 0 || values[3] != 0 || values[4] != 0)
    {
        values[NUM_OF_VALUES - 1] = 0;
        findLowestTrickyCard(values);
        cout << values[NUM_OF_VALUES - 1] << endl;
    }
    return 0;
}

