#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/auxiliary.h"
#include "../include/input_output.h"

const unsigned int FULL_BITSET = 0x1ff;
const unsigned int LINE_LEN = 26;

const char LINE[] = "+=======+=======+=======+\n";
const char NUMBER_LINE[] = "| x x x | x x x | x x x |\n";

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

    for (int i = 0; i < 4; i++) {

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

bool load(unsigned int sudoku[9][9])
{
    int ch = getchar();

    if (ch == '+') {
        if (!load_in_square_format(sudoku, ch))
            goto error;
    }
    
    else if (ch >= '0' && ch <= '9') {
        if (!load_in_line_format(sudoku, ch))
            goto error;
    }

    else
        goto error;

    return true;

error:
    fprintf(stderr, "invalid input\n");
    return false;
}

void print(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 3; i++) {

        printf(LINE);

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {

                if (k % 3 == 0)
                    printf("| ");

                unsigned int bitset = sudoku[i * 3 + j][k];

                if (bitset == 0)
                    printf("! ");
                else if (bitset_is_unique(bitset))
                    printf("%d ", bitset_next(bitset, 0));
                else
                    printf(". ");
            }

            printf("|\n");
        }
    }
    printf(LINE);
}
