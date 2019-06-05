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
 * UVa 00462 - Bridge Hand Evaluator
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

#define NUMBER_OF_CARDS 13
#define NUMBER_OF_SUITS 4

#define MIN_SCORE 14
#define NO_TRUMP_SCORE 16

// suits counting related variables
#define SUITS_INFO_COLUMNS 5
#define ACES_COUNT_INDEX 0
#define KINGS_COUNT_INDEX 1
#define QUEENS_COUNT_INDEX 2
#define JACKS_COUNT_INDEX 3
#define TOTAL_COUNT_INDEX 4

using namespace std;

typedef short int short_t;

string suits = "SHDC";

short_t getSuitIndex(char suite)
{
    return suits.find_first_of(suite);
}

bool calculateSuitsRelatedPoints(short_t countBySuite[NUMBER_OF_SUITS][SUITS_INFO_COLUMNS],
    short_t& basicPoints, short_t& specialPoints)
{
    bool allSuitsStopped = true;
    for (int i = 0; i < NUMBER_OF_SUITS; i++)
    {
        if (countBySuite[i][TOTAL_COUNT_INDEX] == 0)
        {
            // rule 7
            specialPoints += 2;
        } else if (countBySuite[i][TOTAL_COUNT_INDEX] == 1)
        {
            // rule 6
            specialPoints += 2;
            if (countBySuite[i][KINGS_COUNT_INDEX] == 1)
            {
                // rule 2
                basicPoints--;
            }
        } else if (countBySuite[i][TOTAL_COUNT_INDEX] == 2)
        {
            // rule 5
            specialPoints += 1;
        }
        if (countBySuite[i][QUEENS_COUNT_INDEX] == 1 && countBySuite[i][TOTAL_COUNT_INDEX] <= 2)
        {
            // rule 3
            basicPoints--;
        }
        if (countBySuite[i][JACKS_COUNT_INDEX] == 1 && countBySuite[i][TOTAL_COUNT_INDEX] <= 3)
        {
            // rule 4
            basicPoints--;
        }
        if (allSuitsStopped
            && !(countBySuite[i][ACES_COUNT_INDEX] > 0
                || (countBySuite[i][KINGS_COUNT_INDEX] == 1 && countBySuite[i][TOTAL_COUNT_INDEX] >= 2)
                || (countBySuite[i][QUEENS_COUNT_INDEX] == 1 && countBySuite[i][TOTAL_COUNT_INDEX] >= 3)))
        {
            allSuitsStopped = false;
        }
    }
    return allSuitsStopped;
}

string findRecommendedBid(short_t countBySuite[NUMBER_OF_SUITS][SUITS_INFO_COLUMNS],
    short_t basicPoints, short_t specialPoints, bool allSuitsStopped)
{
    if (basicPoints + specialPoints < MIN_SCORE)
    {
        return "PASS";
    } else if (basicPoints >= NO_TRUMP_SCORE && allSuitsStopped)
    {
        return "BID NO-TRUMP";
    } else
    {
        short_t bestSuitIndex = -1, maxSuiteCount = -1;
        for (int i = 0; i < NUMBER_OF_SUITS; i++)
        {
            if (countBySuite[i][TOTAL_COUNT_INDEX] > maxSuiteCount)
            {
                maxSuiteCount = countBySuite[i][TOTAL_COUNT_INDEX];
                bestSuitIndex = i;
            }
        }
        string recommendedBid = "BID X";
        recommendedBid[4] = suits[bestSuitIndex];
        return recommendedBid;
    }
}

int main(int argc, char **argv)
{
    // countBySuite contains a row for each suite in the game. Each of
    // the 5 positions contains the follow information:
    // [counting of aces, counting of kings, counting of queens, counting of jacks, total counting]
    short_t countBySuite[NUMBER_OF_SUITS][SUITS_INFO_COLUMNS];

    for (int i = 0; i < NUMBER_OF_SUITS; i++)
    {
        for (int j = 0; j < SUITS_INFO_COLUMNS; j++)
        {
            countBySuite[i][j] = 0;
        }
    }

    // basicPoints stores the points described in the rules 1, 2, 3 and 4.
    // specialPoints stores the points described in the rules 5,6 and 7.
    short_t basicPoints = 0, specialPoints = 0, cardsCounter = 0;
    char card[3];
    while (scanf("%2s", card) != EOF)
    {
        cardsCounter++;

        char rank = card[0];
        char suit = card[1];
        short_t suitIndex = getSuitIndex(suit);
        countBySuite[suitIndex][TOTAL_COUNT_INDEX]++;

        switch (rank)
        {
            case 'A':
                // rule 1
                basicPoints += 4;
                countBySuite[suitIndex][ACES_COUNT_INDEX]++;
                break;
            case 'K':
                basicPoints += 3;
                countBySuite[suitIndex][KINGS_COUNT_INDEX]++;
                break;
            case 'Q':
                basicPoints += 2;
                countBySuite[suitIndex][QUEENS_COUNT_INDEX]++;
                break;
            case 'J':
                basicPoints += 1;
                countBySuite[suitIndex][JACKS_COUNT_INDEX]++;
                break;
        }
        if (cardsCounter % 13 == 0)
        {
            bool allSuitsStopped = calculateSuitsRelatedPoints(countBySuite, basicPoints, specialPoints);

            string recommendedBid = findRecommendedBid(countBySuite, basicPoints, specialPoints, allSuitsStopped);

            cout << recommendedBid << endl;

            for (int i = 0; i < NUMBER_OF_SUITS; i++)
            {
                for (int j = 0; j < SUITS_INFO_COLUMNS; j++)
                {
                    countBySuite[i][j] = 0;
                }
            }
            basicPoints = 0, specialPoints = 0;
        }

    }

    return 0;
}

