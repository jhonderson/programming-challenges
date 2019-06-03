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
 * 573 - The Snail
 *
 * Time complexity:
 *  Linear
 *
 * Space complexity:
 *  Constant
 * */

using namespace std;

typedef unsigned short int unsig_short_int_t;

bool simulateSnailClimbing(unsig_short_int_t wellHeight,
    double feetsUp, unsig_short_int_t feetsDown,
    double fatigueFactor, unsigned int& finalDay)
{
    finalDay = 1;
    double currentFeet = 0;

    // The distance lost to fatigue is always 10% of the first day's
    // climbing distance.
    double fatigueFeets = feetsUp * fatigueFactor;

    while (true)
    {
        // in the day
        currentFeet += feetsUp;
        if (currentFeet > wellHeight)
            return true;

        // in the night
        currentFeet -= feetsDown;
        if (currentFeet < 0)
            return false;

        feetsUp -= fatigueFeets;

        // The snail never climbs a negative distance. If the fatigue
        // factor drops the snail’s climbing distance below zero, the
        // snail does not climb at all that day.
        if (feetsUp < 0)
            feetsUp = 0;
        finalDay++;
    }
    // logicly unreachable sentence
    return true;
}

void printFormattedAnswer(bool success, unsigned int finalDay)
{
    cout << (success ? "success" : "failure") << " on day "
        << finalDay << endl;
}

int main(int argc, char **argv)
{
    // in variables
    unsig_short_int_t wellHeight, feetsDown;
    double feetsUp, fatigueFactor;

    // out variables
    unsigned int finalDay;
    bool success;
    while (cin >> wellHeight >> feetsUp >> feetsDown >> fatigueFactor, wellHeight > 0)
    {
        fatigueFactor /= 100;
        success = simulateSnailClimbing(wellHeight, feetsUp, feetsDown, fatigueFactor, finalDay);
        printFormattedAnswer(success, finalDay);
    }
    return 0;
}

