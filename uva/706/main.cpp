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

struct lcd_digit_side_flags_t {
    bool top;
    bool middle;
    bool bottom;
    bool up_left;
    bool up_right;
    bool bottom_left;
    bool bottom_right;
} zero, one, two, three, four, five, six, seven, eight, nine;

void initialize_digits_flags()
{
    zero.top = true;
    zero.bottom = true;
    zero.up_left = true;
    zero.up_right = true;
    zero.bottom_left = true;
    zero.bottom_right = true;

    one.up_right = true;
    one.bottom_right = true;

    two.top = true;
    two.middle = true;
    two.bottom = true;
    two.up_right = true;
    two.bottom_left = true;

    three.top = true;
    three.middle = true;
    three.bottom = true;
    three.up_right = true;
    three.bottom_right = true;

    four.middle = true;
    four.up_left = true;
    four.up_right = true;
    four.bottom_right = true;

    five.top = true;
    five.middle = true;
    five.bottom = true;
    five.up_left = true;
    five.bottom_right = true;

    six.top = true;
    six.middle = true;
    six.bottom = true;
    six.up_left = true;
    six.bottom_left = true;
    six.bottom_right = true;

    seven.top = true;
    seven.up_right = true;
    seven.bottom_right = true;

    eight.top = true;
    eight.middle = true;
    eight.bottom = true;
    eight.up_left = true;
    eight.up_right = true;
    eight.bottom_left = true;
    eight.bottom_right = true;

    nine.top = true;
    nine.middle = true;
    nine.bottom = true;
    nine.up_left = true;
    nine.up_right = true;
    nine.bottom_right = true;
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

void put_digit_into_board(vector<vector<char> > &lcd_board, unsigned int size, lcd_digit_side_flags_t lcd_digit_side_flags)
{
    int digit_height = get_digit_height(size);
    int digit_width = get_digit_width(size);
    vector<char> empty_row(digit_width, ' ');
    vector<vector<char> > digit_board(digit_height, empty_row);

    for ( int j = 1 ; j < digit_width - 1 ; j++ )
    {
        if (lcd_digit_side_flags.top) {
            digit_board[0][j] = '-';
        }
        if (lcd_digit_side_flags.middle) {
            digit_board[(digit_height - 1) / 2][j] = '-';
        }
        if (lcd_digit_side_flags.bottom) {
            digit_board[digit_height - 1][j] = '-';
        }
    }
    for ( int i = 1 ; i < (digit_height - 1) / 2 ; i++ )
    {
        if (lcd_digit_side_flags.up_left) {
            digit_board[i][0] = '|';
        }
        if (lcd_digit_side_flags.up_right) {
            digit_board[i][digit_width - 1] = '|';
        }
        if (lcd_digit_side_flags.bottom_left) {
            digit_board[digit_height - i - 1][0] = '|';
        }
        if (lcd_digit_side_flags.bottom_right) {
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
    switch(digit) {
        case 0:
            put_digit_into_board(lcd_board, size, zero);
            break;
        case 1:
            put_digit_into_board(lcd_board, size, one);
            break;
        case 2:
            put_digit_into_board(lcd_board, size, two);
            break;
        case 3:
            put_digit_into_board(lcd_board, size, three);
            break;
        case 4:
            put_digit_into_board(lcd_board, size, four);
            break;
        case 5:
            put_digit_into_board(lcd_board, size, five);
            break;
        case 6:
            put_digit_into_board(lcd_board, size, six);
            break;
        case 7:
            put_digit_into_board(lcd_board, size, seven);
            break;
        case 8:
            put_digit_into_board(lcd_board, size, eight);
            break;
        case 9:
            put_digit_into_board(lcd_board, size, nine);
            break;
    }

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
