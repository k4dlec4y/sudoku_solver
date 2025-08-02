#include <stdbool.h>
#include <stdio.h>
#include "sudoku.h"
#include "auxiliary.h"
#include "input_output.h"

unsigned int row_drop_with_memory(unsigned int sudoku[9][9],
                                  int row, int number)
{
    unsigned int dropped = 0;

    for (int i = 0; i < 9; ++i) {

        unsigned int cur_bitset = sudoku[row][i];
        if (bitset_is_unique(cur_bitset))
            continue;

        if (bitset_is_set(cur_bitset, number)) {
            sudoku[row][i] = bitset_drop(cur_bitset, number);
            dropped |= num_to_bitset(i + 1);
        }
    }

    return dropped;
}

void row_restore(unsigned int sudoku[9][9], int row,
                 int number, unsigned int dropped)
{
    unsigned int bs_number = num_to_bitset(number);

    for (int i = 0; i < 9; ++i) {
        if (bitset_is_set(dropped, i + 1)) {
            sudoku[row][i] |= bs_number;
        }
    }
}

unsigned int col_drop_with_memory(unsigned int sudoku[9][9],
                                  int col, int number)
{
    unsigned int dropped = 0;

    for (int i = 0; i < 9; ++i) {

        unsigned int cur_bitset = sudoku[i][col];
        if (bitset_is_unique(cur_bitset))
            continue;

        if (bitset_is_set(cur_bitset, number)) {
            sudoku[i][col] = bitset_drop(cur_bitset, number);
            dropped |= num_to_bitset(i + 1);
        }
    }

    return dropped;
}

void col_restore(unsigned int sudoku[9][9], int col,
                 int number, unsigned int dropped)
{
    unsigned int bs_number = num_to_bitset(number);

    for (int i = 0; i < 9; ++i) {
        if (bitset_is_set(dropped, i + 1)) {
            sudoku[i][col] |= bs_number;
        }
    }
}

unsigned int box_drop_with_memory(unsigned int sudoku[9][9],
                                  int row, int col, int number)
{
    unsigned int dropped = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {

            unsigned int cur_bitset = sudoku[row + i][col + j];
            if (bitset_is_unique(cur_bitset))
                continue;

            if (bitset_is_set(cur_bitset, number)) {
                sudoku[row + i][col + j] = bitset_drop(cur_bitset, number);
                dropped |= num_to_bitset(3 * i + j + 1);
            }
        }
    }

    return dropped;
}

void box_restore(unsigned int sudoku[9][9], int row, int col,
                 int number, unsigned int dropped)
{
    unsigned int bs_number = num_to_bitset(number);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {

            if (bitset_is_set(dropped, 3 * i + j + 1)) {
                sudoku[row + i][col + j] |= bs_number;
            }
        }
    }
}

bool generic_solve(unsigned int sudoku[9][9], int index)
{
    if (!is_valid(sudoku))
        return false;

    if (index >= 81) {
        return !needs_solving(sudoku);
    }

    int row = index / 9;
    int col = index % 9;
    int cur_bitset = sudoku[row][col];

    int number = 0;
    while ((number = bitset_next(cur_bitset, number)) != -1) {

        sudoku[row][col] = num_to_bitset(number);
        unsigned int row_drop = row_drop_with_memory(sudoku, row, number),
                     col_drop = col_drop_with_memory(sudoku, col, number),
                     box_drop = box_drop_with_memory(sudoku, row / 3 * 3,
                                                     col / 3 * 3, number);

        if (generic_solve(sudoku, index + 1))
            return true;

        box_restore(sudoku, row / 3 * 3, col / 3 * 3, number, box_drop);
        col_restore(sudoku, col, number, col_drop);
        row_restore(sudoku, row, number, row_drop);
        sudoku[row][col] = cur_bitset;
    }

    return false;
}
