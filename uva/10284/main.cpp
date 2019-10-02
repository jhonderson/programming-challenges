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
 * UVa 10284 - Chessboard in FEN
 *
 * Time complexity:
 *  Constant
 *
 * Space complexity:
 *  Constant
 * */

#define CHESS_SIZE 8
#define MAX_FEN_LENGTH 72
#define EMPTY_CELL '0'

using namespace std;

typedef unsigned short int short_t;

char chess[CHESS_SIZE+2][CHESS_SIZE+2];

// TODO Remove this
void printChess()
{
    for (short_t i = 0; i < CHESS_SIZE+2; i++)
    {
        for (short_t j = 0; j < CHESS_SIZE+2; j++)
        {
            cout << ' ' << chess[i][j];
        }
        cout << endl;
    }
}

void intializeChessFromFEN(char fen[MAX_FEN_LENGTH])
{
    short_t row = 1, col = 1, emptyCells;
    for (short_t charIndex = 0; charIndex < MAX_FEN_LENGTH; charIndex++)
    {
        if (row > CHESS_SIZE)
        {
            break;
        }

        char fenChar = fen[charIndex];
        if (fenChar == '/' || col > CHESS_SIZE)
        {
            row++;
            col = 1;
        } else if ('1' <= fenChar && fenChar <= '8')
        {
            emptyCells = fenChar - '0';
            while (emptyCells--)
            {
                chess[row][col++] = EMPTY_CELL;
            }
        } else
        {
            chess[row][col++] = fenChar;
        }
    }
}

bool isCellUnderAttack(short_t row, short_t col)
{
    return false;
}

short_t findNumOfSafeCells()
{
    short_t numOfSafeCells = 0;
    for (short_t row = 1; row <= CHESS_SIZE; row++)
    {
        for (short_t col = 1; col <= CHESS_SIZE; col++)
        {
            if (chess[row][col] == EMPTY_CELL && !isCellUnderAttack(row, col))
            {
                numOfSafeCells++;
            }
        }
    }
    return numOfSafeCells;
}

int main(int argc, char **argv)
{
    char fen[MAX_FEN_LENGTH];
    string readingFormat = "%" + to_string(MAX_FEN_LENGTH) + "s";
    short_t numOfSafeCells;
    while (scanf(readingFormat.c_str(), fen) != EOF)
    {
        intializeChessFromFEN(fen);
        //printChess();
        numOfSafeCells = findNumOfSafeCells();
        cout << numOfSafeCells << endl;
    }
    return 0;
}

