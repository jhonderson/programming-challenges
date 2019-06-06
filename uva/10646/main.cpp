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
 * UVa 10646 - What is the Card?
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

#define NUM_OF_CARDS 52
#define NUM_OF_CARDS_TO_TAKE 25
#define NUM_OF_REPETITIONS 3

typedef short int short_t;

using namespace std;

short_t getCardValue(string card)
{
    short_t cardNumericalValue = card[0] - '0';
    return cardNumericalValue > 9 ? 10 : cardNumericalValue;
}

void readInput(string* cards)
{
    for (short_t cardIndex = 0; cardIndex < NUM_OF_CARDS; cardIndex++)
    {
        cin >> cards[cardIndex];
    }
}

string determineYCardsOfThePile(string* cards)
{
    short_t yIndex = 0, topCardValue;
    short_t topOfPile = NUM_OF_CARDS - NUM_OF_CARDS_TO_TAKE - 1;
    for (short_t repetitionId = 0; repetitionId < NUM_OF_REPETITIONS; repetitionId++)
    {
        // Take the top card of the cards of the pile and determine its value
        topCardValue = getCardValue(cards[topOfPile]);

        // Add the top card value to Y
        yIndex += topCardValue;

        // Put this card and the top (10 − topCardValue) cards of the pile away
        topOfPile -= (10 - topCardValue) + 1;
    }
    // Y -th is not zero-indexed
    yIndex--;
    if (yIndex > topOfPile)
    {
        if (topOfPile < 0)
        {
            yIndex = (NUM_OF_CARDS - NUM_OF_CARDS_TO_TAKE) + yIndex;
        } else
        {
            yIndex = (NUM_OF_CARDS - NUM_OF_CARDS_TO_TAKE) + (yIndex - topOfPile - 1);
        }
    }
    return cards[yIndex];
}

int main(int argc, char **argv)
{
    short_t numOfTestCases;
    cin >> numOfTestCases;

    string cards[NUM_OF_CARDS];
    for (short_t caseId = 1; caseId <= numOfTestCases; caseId++)
    {
        readInput(cards);
        string yCard = determineYCardsOfThePile(cards);
        printf("Case %d: %s\n", caseId, yCard.c_str());
    }

    return 0;
}
