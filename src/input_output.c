#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/auxiliary.h"
#include "../include/input_output.h"

static const unsigned int FULL_BITSET = 0x1ff;
static const unsigned int LINE_LEN = 26;

static const char LINE[] = "+=======+=======+=======+\n";
static const char NUMBER_LINE[] = "| x x x | x x x | x x x |\n";

int load_in_line_format(FILE *file, unsigned int sudoku[9][9], int ch)
{
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {

            if (ch == '0')
                sudoku[i][j] = FULL_BITSET; 

            else if (ch >= '1' && ch <= '9')
                sudoku[i][j] = num_to_bitset(ch - '0');

            else {
                printf(" - expected char from '0' to '9', "
                       "got %c instead\n", ch);
                return -1;
            }

            ch = fgetc(file);
        }
    }

    return ch == '\n' || ch == EOF ? 0 : -1;
}

int load_number_lines(FILE *file, unsigned int sudoku[9][9], int count)
{
    int ch;

    for (size_t j = 0; j < 3 * LINE_LEN; ++j) {

        ch = fgetc(file);

        if (ch == NUMBER_LINE[j % 26] && ch != 'x')
            continue;

        if ('x' == NUMBER_LINE[j % 26]) {

            unsigned int cell;

            if (ch >= '1' && ch <= '9')
                cell = num_to_bitset(ch - '0');
    
            else if (ch == '.' || ch == '0')
                cell = FULL_BITSET;

            else {
                printf(" - expected char from '0' to '9' or '.', "
                       "got %c instead\n", ch);
                return count;
            }

            sudoku[count / 9][count % 9] = cell;
            ++count;
            continue;
        }

        printf(" - expected '%c', got %c instead\n", NUMBER_LINE[j % 26], ch);
        return count;
    }

    return count;
}

int load_in_square_format(FILE *file, unsigned int sudoku[9][9], int ch)
{
    int count = 0;

    for (int i = 0; i < 4; i++) {

        for (size_t j = 0; j < LINE_LEN - 1; j++) {
            if (ch != LINE[j]) {

                printf(" - expected '%c', got %c instead\n", LINE[j], ch);
                return -1;
            }

            ch = fgetc(file);
        }

        if (i == 3)  // in this if the function ends
            return ch == '\n' || ch == EOF ? 0 : -1;

        if (ch != '\n') {
            printf(" - expected new line, got %c instead\n", ch);
            return -1;
        }

        count = load_number_lines(file, sudoku, count);
        if (count % 27 != 0)
            return -1;

        ch = fgetc(file);
    }

    assert(false);
}

int load(FILE *file, unsigned int sudoku[9][9])
{
    int ch = fgetc(file);

    if (ch == '+')
        return load_in_square_format(file, sudoku, ch);
    
    else if (ch >= '0' && ch <= '9')
        return load_in_line_format(file, sudoku, ch);

    else if (ch == EOF) {
        puts(" + no more sudoku to load");
        return 1;
    }

    puts(" - sudoku starts with unexpected character");
    return -1;
}

void print(FILE *file, unsigned int sudoku[9][9])
{
    for (int i = 0; i < 3; i++) {

        fprintf(file, LINE);

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {

                if (k % 3 == 0)
                    fprintf(file, "| ");

                unsigned int bitset = sudoku[i * 3 + j][k];

                if (bitset == 0)
                    fprintf(file, "! ");
                else if (bitset_is_unique(bitset))
                    fprintf(file, "%d ", bitset_next(bitset, 0));
                else
                    fprintf(file, ". ");
            }

            fprintf(file, "|\n");
        }
    }
    fprintf(file, LINE);
}
