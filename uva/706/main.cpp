
#include <iostream>
#include <math.h>
#include <vector>

/**
 * UVA 706: LCD Display
 *
 * Time complexity:
 *   <# digits> * (2 * <size> + 3)
 *
 * Space complexity:
 *   <# digits> * (2 * <size> + 3) * (<size> + 2)
 * */

using namespace std;

char topEnabled = 1 << 0;
char middleEnabled = 1 << 1;
char bottomEnabled = 1 << 2;
char upLeftEnabled = 1 << 3;
char upRightEnabled = 1 << 4;
char bottomLeftpEnabled = 1 << 5;
char bottomRightEnabled = 1 << 6;

char numbersAsBitFlags[10];

void initialize_digits_flags()
{
    numbersAsBitFlags[8] = topEnabled | middleEnabled | bottomEnabled | upLeftEnabled | upRightEnabled | bottomLeftpEnabled | bottomRightEnabled;
    numbersAsBitFlags[1] = upRightEnabled | bottomRightEnabled;

    numbersAsBitFlags[0] = numbersAsBitFlags[8] & ~middleEnabled;
    numbersAsBitFlags[6] = numbersAsBitFlags[8] & ~upRightEnabled;
    numbersAsBitFlags[9] = numbersAsBitFlags[8] & ~bottomLeftpEnabled;
    numbersAsBitFlags[2] = numbersAsBitFlags[8] & ~upLeftEnabled & ~bottomRightEnabled;
    numbersAsBitFlags[3] = numbersAsBitFlags[8] & ~upLeftEnabled & ~bottomLeftpEnabled;

    numbersAsBitFlags[4] = numbersAsBitFlags[9] & ~topEnabled;

    numbersAsBitFlags[5] = numbersAsBitFlags[6] & ~bottomLeftpEnabled;

    numbersAsBitFlags[7] = numbersAsBitFlags[1] | topEnabled;
}

int get_digit_width(unsigned int size)
{
    return size + 2;
}

int get_digit_height(unsigned int size)
{
    return 2 * size + 3;
}

void print_lcd_board(vector<vector<char> > &lcd_board, unsigned int size)
{
    int number_of_digits = lcd_board.size() / get_digit_height(size);
    int digit_width = get_digit_width(size);
    int digit_height = get_digit_height(size);

    // Three nested for's, do not panic !!, the number of iterations will
    // aways be digit_width * digit_height * number_of_digits

    for (int i = 0; i < digit_height; i++)
    {
        for (int j = i; j < (number_of_digits * digit_height); j += digit_height)
        {
            for (int k = 0; k < digit_width; k++)
            {
                cout << lcd_board[j][k];
            }
            if ((j + digit_height) < number_of_digits * digit_height) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void put_digit_into_board(vector<vector<char> > &lcd_board, unsigned int size, char lcd_flags)
{
    int digit_height = get_digit_height(size);
    int digit_width = get_digit_width(size);
    vector<char> empty_row(digit_width, ' ');
    vector<vector<char> > digit_board(digit_height, empty_row);

    for ( int j = 1 ; j < digit_width - 1 ; j++ )
    {
        if (lcd_flags & topEnabled) {
            digit_board[0][j] = '-';
        }
        if (lcd_flags & middleEnabled) {
            digit_board[(digit_height - 1) / 2][j] = '-';
        }
        if (lcd_flags & bottomEnabled) {
            digit_board[digit_height - 1][j] = '-';
        }
    }
    for ( int i = 1 ; i < (digit_height - 1) / 2 ; i++ )
    {
        if (lcd_flags & upLeftEnabled) {
            digit_board[i][0] = '|';
        }
        if (lcd_flags & upRightEnabled) {
            digit_board[i][digit_width - 1] = '|';
        }
        if (lcd_flags & bottomLeftpEnabled) {
            digit_board[digit_height - i - 1][0] = '|';
        }
        if (lcd_flags & bottomRightEnabled) {
            digit_board[digit_height - i - 1][digit_width - 1] = '|';
        }
    }
    lcd_board.insert(lcd_board.begin(), digit_board.begin(), digit_board.end());
}

void put_digits_into_board(vector<vector<char> > &lcd_board, unsigned long number, unsigned int size)
{
    if (number == 0 && !lcd_board.empty()) {
        return;
    }

    unsigned int digit = number % 10;
    put_digit_into_board(lcd_board, size, numbersAsBitFlags[digit]);

    // tail recursion
    put_digits_into_board(lcd_board, number / 10, size);
}

void print_lcd_number(unsigned long number, unsigned int size)
{
    int number_of_digits;
    if (number == 0) {
        number_of_digits = 1;
    }
    else {
        number_of_digits = ((int) log10 (number)) + 1;
    }

    vector<vector<char> > lcd_board;

    // capacity established to avoid reallocation when new rows are added
    lcd_board.reserve(number_of_digits * (get_digit_height(size)));

    put_digits_into_board(lcd_board, number, size);

    print_lcd_board(lcd_board, size);
}

int main()
{
    initialize_digits_flags();
    unsigned long number;
    unsigned int size;
    while (cin >> size >> number && size != 0)
    {
        print_lcd_number(number, size);
    }
    return 0;
}
