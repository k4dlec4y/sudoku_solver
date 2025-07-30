#include <assert.h>
#include <stdbool.h>
#include "../include/sudoku.h"
#include "../include/auxiliary.h"

bool eliminate_row(unsigned int sudoku[9][9], int row_index)
{
    assert(row_index >= 0 && row_index < 9);

    bool eliminated = false;
    unsigned int done_numbers = row_bitset(sudoku, row_index);

    for (int i = 0; i < 9; i++) {

        unsigned int bitset = sudoku[row_index][i];
        if (bitset_is_unique(bitset))
            continue;

        int number = 0;
        while ((number = bitset_next(bitset, number)) != -1) {
            if (bitset_is_set(done_numbers, number)) {

                sudoku[row_index][i] = bitset_drop(bitset, number);
                eliminated = true;
            }
        }
    }

    return eliminated;
}

bool eliminate_col(unsigned int sudoku[9][9], int col_index)
{
    assert(col_index >= 0 && col_index < 9);

    bool eliminated = false;
    unsigned int done_numbers = col_bitset(sudoku, col_index);

    for (int i = 0; i < 9; i++) {

        unsigned int bitset = sudoku[i][col_index];
        if (bitset_is_unique(bitset))
            continue;

        int number = 0;
        while ((number = bitset_next(bitset, number)) != -1) {
            if (bitset_is_set(done_numbers, number)) {

                sudoku[i][col_index] = bitset_drop(bitset, number);
                eliminated = true;
            }
        }
    }

    return eliminated;
}

bool eliminate_box(unsigned int sudoku[9][9], int row_index, int col_index)
{
    assert(row_index >= 0 && row_index < 9);
    assert(col_index >= 0 && col_index < 9);

    bool eliminated = false;
    unsigned int done_numbers = box_bitset(sudoku, row_index, col_index);

    for (int i = row_index; i < row_index + 3; i++) {
        for (int j = col_index; j < col_index + 3; j++) {

            if (bitset_is_unique(sudoku[i][j]))
                continue;

            int number = 0;
            while ((number = bitset_next(sudoku[i][j], number)) != -1) {
                if (bitset_is_set(done_numbers, number)) {

                    sudoku[i][j] = bitset_drop(sudoku[i][j], number);
                    eliminated = true;
                }
            }
        }
    }

    return eliminated;
}

bool needs_solving(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (!bitset_is_unique(sudoku[i][j]))
                return true;
        }
    }

    return false;
}

bool is_valid(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 9; i++) {

        if (col_conflict(sudoku, i) || row_conflict(sudoku, i))
            return false;

        for (int j = 0; j < 9; j++) {

            if (sudoku[i][j] == 0x0 ||
                (j % 3 == 0 && i % 3 == 0 &&
                 box_conflict(sudoku, i, j)))
                return false;
        }
    }

    return true;
}

bool solve(unsigned int sudoku[9][9])
{
    bool eliminated = true;

    while (eliminated) {

        eliminated = false;

        for (int i = 0; i < 9; i++)
            eliminated = eliminated ||
                         eliminate_row(sudoku, i) ||
                         eliminate_col(sudoku, i);

        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 9; j += 3)
                eliminated = eliminated || eliminate_box(sudoku, i, j);
        }
    }

    return !needs_solving(sudoku);
}

// bool generic_solve(unsigned int sudoku[9][9])
// {
//     return false; // todo
// }
