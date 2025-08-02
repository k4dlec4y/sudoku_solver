#include <assert.h>
#include <stdbool.h>
#include "../include/sudoku.h"
#include "../include/auxiliary.h"

bool eliminate_row(unsigned int sudoku[9][9], int row)
{
    assert(row >= 0 && row < 9);

    bool eliminated = false;
    unsigned int unique_numbers = row_bitset(sudoku, row);

    for (int i = 0; i < 9; i++) {

        unsigned int bitset = sudoku[row][i];
        if (bitset_is_unique(bitset))
            continue;

        int number = 0;
        while ((number = bitset_next(bitset, number)) != -1) {
            if (bitset_is_set(unique_numbers, number)) {

                sudoku[row][i] = bitset_drop(sudoku[row][i], number);
                eliminated = true;
            }
        }
    }

    return eliminated;
}

bool eliminate_col(unsigned int sudoku[9][9], int col)
{
    assert(col >= 0 && col < 9);

    bool eliminated = false;
    unsigned int unique_numbers = col_bitset(sudoku, col);

    for (int i = 0; i < 9; i++) {

        unsigned int bitset = sudoku[i][col];
        if (bitset_is_unique(bitset))
            continue;

        int number = 0;
        while ((number = bitset_next(bitset, number)) != -1) {
            if (bitset_is_set(unique_numbers, number)) {

                sudoku[i][col] = bitset_drop(sudoku[i][col], number);
                eliminated = true;
            }
        }
    }

    return eliminated;
}

bool eliminate_box(unsigned int sudoku[9][9], int row, int col)
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    bool eliminated = false;
    unsigned int unique_numbers = box_bitset(sudoku, row, col);

    for (int i = row; i < row + 3; i++) {
        for (int j = col; j < col + 3; j++) {

            if (bitset_is_unique(sudoku[i][j]))
                continue;

            int number = 0;
            while ((number = bitset_next(sudoku[i][j], number)) != -1) {
                if (bitset_is_set(unique_numbers, number)) {

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
                (i % 3 == 0 && j % 3 == 0 && box_conflict(sudoku, i, j)))
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
