#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/auxiliary.h"

const unsigned int FULL_BITSET = 0x1ff;
const unsigned int LINE_LEN = 26;

const char NUMBER_LINE[] = "| x x x | x x x | x x x |\n";

unsigned int num_to_bitset(int number)
{
    assert(number > 0 && number < 10);

    return 0x1 << (number - 1);
}

unsigned int bitset_drop(unsigned int original, int number)
{
    assert(original <= FULL_BITSET);
    assert(number > 0 && number < 10);

    return original & (~num_to_bitset(number));
}

bool bitset_is_set(unsigned int original, int query)
{
    assert(original <= FULL_BITSET);
    assert(query > 0 && query < 10);

    return (original >> (query - 1)) & 0x1;
}

bool bitset_is_unique(unsigned int original)
{
    assert(original <= FULL_BITSET);

    if (original == 0)
        return false;

    return (original & (original - 1)) == 0;
}

int bitset_next(unsigned int bitset, int previous)
{
    assert(bitset <= FULL_BITSET);
    assert(previous >= 0 && previous < 10);

    ++previous;

    while (previous < 10) {
        if ((bitset >> (previous - 1)) & 0x1)
            return previous;

        ++previous;
    }

    return -1;
}

int box_bitset(unsigned int sudoku[9][9], int row_index, int col_index)
{
    assert(row_index == 0 || row_index == 3 || row_index == 6);
    assert(col_index == 0 || col_index == 3 || col_index == 6);

    int done = 0x00;

    for (int i = row_index; i < row_index + 3; ++i) {
        for (int j = col_index; j < col_index + 3; ++j) {

            unsigned int bitset = sudoku[i][j];
            if (bitset_is_unique(bitset))
                done |= bitset;
        }
    }

    return done;
}

int row_bitset(unsigned int sudoku[9][9], int row_index)
{
    assert(row_index >= 0 && row_index < 10);

    int done = 0x00;

    for (int i = 0; i < 9; ++i) {

        unsigned int bitset = sudoku[row_index][i];
        if (bitset_is_unique(bitset))
            done |= bitset;

    }

    return done;
}

int col_bitset(unsigned int sudoku[9][9], int col_index)
{
    assert(col_index >= 0 && col_index < 10);

    int done = 0x00;

    for (int i = 0; i < 9; ++i) {

        unsigned int bitset = sudoku[i][col_index];
        if (bitset_is_unique(bitset))
            done |= bitset;

    }

    return done;
}

bool box_conflict(unsigned int sudoku[9][9], int row_index, int col_index)
{
    assert(row_index == 0 || row_index == 3 || row_index == 6);
    assert(col_index == 0 || col_index == 3 || col_index == 6);

    int done = 0x00;

    for (int i = row_index; i < row_index + 3; ++i) {
        for (int j = col_index; j < col_index + 3; ++j) {

            unsigned int bitset = sudoku[i][j];

            if (bitset_is_unique(bitset)) {
                if ((done & bitset) > 0)
                    return true;

                done |= bitset;
            }
        }
    }

    return false;
}

bool row_conflict(unsigned int sudoku[9][9], int row_index)
{
    assert(row_index >= 0 && row_index < 10);

    int done = 0x00;

    for (int i = 0; i < 9; ++i) {

        unsigned int bitset = sudoku[row_index][i];

        if (bitset_is_unique(bitset)) {
            if ((done & bitset) > 0)
                return true;

            done |= bitset;
        }
    }

    return false;
}

bool col_conflict(unsigned int sudoku[9][9], int col_index)
{
    assert(col_index >= 0 && col_index < 10);

    int done = 0x00;

    for (int i = 0; i < 9; ++i) {

        unsigned int bitset = sudoku[i][col_index];

        if (bitset_is_unique(bitset)) {
            if ((done & bitset) > 0)
                return true;

            done |= bitset;
        }
    }

    return false;
}

bool load_in_line_format(unsigned int sudoku[9][9], int ch)
{
    for (int count = 0; count < 81; count++) {

        if (ch == '0')
            sudoku[count / 9][count % 9] = FULL_BITSET; 

        else if (ch >= '1' && ch <= '9')
            sudoku[count / 9][count % 9] = num_to_bitset(ch - '0');

        else
            return false;

        ch = getchar();
    }

    return ch == '\n' || ch == EOF;
}

int load_number_lines(unsigned int sudoku[9][9], int count)
{
    int ch;

    for (size_t j = 0; j < 3 * LINE_LEN; j++) {

        ch = getchar();

        if (ch == NUMBER_LINE[j % 26] && ch != 'x')
            continue;

        if ('x' == NUMBER_LINE[j % 26]) {

            unsigned int new;

            if (ch >= '1' && ch <= '9')
                new = num_to_bitset(ch - '0');
    
            else if (ch == '.' || ch == '0')
                new = FULL_BITSET;

            else
                return count;

            sudoku[count / 9][count % 9] = new;
            count++;
        }
    }

    return count;
}

bool load_in_square_format(unsigned int sudoku[9][9], int ch)
{
    int count = 0;

    for(int i = 0; i < 4; i++) {

        for (size_t j = 0; j < LINE_LEN - 1; j++) {
            if (ch != LINE[j])
                return false;

            ch = getchar();
        }

        // in this if the function ends
        if (i == 3)
            return ch == '\n';

        if (ch != '\n')
            return false;

        count = load_number_lines(sudoku, count);
        if (count % 27 != 0)
            return false;

        ch = getchar();
    }

    assert(false);
}
