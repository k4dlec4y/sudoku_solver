#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/auxiliary.h"

void num_to_bitset_test(void)
{
    assert(num_to_bitset(3) == 0b100);
    assert(num_to_bitset(1) == 0b1);
    assert(num_to_bitset(9) == 0b100000000);
}

void bitset_drop_test(void)
{
    assert(bitset_drop(0b111, 2) == 0b101);
    assert(bitset_drop(0b110, 1) == 0b110);
    assert(bitset_drop(0b111111111, 9) == 0b011111111);
}

void bitset_is_set_test(void)
{
    assert(bitset_is_set(0b100, 3));
    assert(!bitset_is_set(0b01100, 5));
    assert(bitset_is_set(0b100000000, 9));
}

void bitset_is_unique_test(void)
{
    assert(bitset_is_unique(0b100));
    assert(!bitset_is_unique(0b110));
    assert(bitset_is_unique(0b001));
    assert(bitset_is_unique(0b100000000));
    assert(!bitset_is_unique(0b100001000));
}

void bitset_next_test(void)
{
    unsigned int bitset = 0b100110011;
    int results[] = {1, 2, 5, 6, 9, -1};
    int result = 0;

    for (int i = 0; i < 6; ++i) {
        assert((result = bitset_next(bitset, result)) == results[i]);
    }

    assert(bitset_next(0U, 0) == -1);
}

void box_bitset_test(unsigned int sudoku[9][9])
{
    sudoku[0][0] = 0b1;  // 1
    sudoku[0][1] = 0b11;
    sudoku[0][2] = 0b11;

    sudoku[1][0] = 0b10;  // 2
    sudoku[1][1] = 0b11;
    sudoku[1][2] = 0b10000;  // 5

    sudoku[2][0] = 0b110000;
    sudoku[2][1] = 0b11;
    sudoku[2][2] = 0b100000000;  // 9

    assert(box_bitset(sudoku, 0, 0) == 0b100010011);
}

void row_bitset_test(unsigned int sudoku[9][9])
{
    sudoku[1][0] = 0b1;  // 1
    sudoku[1][1] = 0b11;
    sudoku[1][2] = 0b11;

    sudoku[1][3] = 0b100;  // 3
    sudoku[1][4] = 0b11;
    sudoku[1][5] = 0b100000;  // 6

    sudoku[1][6] = 0b110000;
    sudoku[1][7] = 0b11;
    sudoku[1][8] = 0b100000000;  // 9

    assert(row_bitset(sudoku, 1) == 0b100100101);
}

void col_bitset_test(unsigned int sudoku[9][9])
{
    sudoku[0][2] = 0b1;  // 1
    sudoku[1][2] = 0b11;
    sudoku[2][2] = 0b11;

    sudoku[3][2] = 0b10;  // 2
    sudoku[4][2] = 0b11;
    sudoku[5][2] = 0b100000;  // 6

    sudoku[6][2] = 0b110000;
    sudoku[7][2] = 0b11;
    sudoku[8][2] = 0b100000000;  // 9

    assert(col_bitset(sudoku, 2) == 0b100100011);
}

void box_conflict_test(unsigned int sudoku[9][9])
{
    sudoku[0][0] = 0b1;  // 1
    sudoku[0][1] = 0b11;
    sudoku[0][2] = 0b11;

    sudoku[1][0] = 0b10;  // 2
    sudoku[1][1] = 0b11;
    sudoku[1][2] = 0b10000;  // 5

    sudoku[2][0] = 0b110000;
    sudoku[2][1] = 0b11;
    sudoku[2][2] = 0b100000000;  // 9

    assert(!box_conflict(sudoku, 0, 0));
    sudoku[2][1] = 0b100000000;  // 9
    assert(box_conflict(sudoku, 0, 0));
}

void row_conflict_test(unsigned int sudoku[9][9])
{
    sudoku[1][0] = 0b1;  // 1
    sudoku[1][1] = 0b11;
    sudoku[1][2] = 0b11;

    sudoku[1][3] = 0b100;  // 3
    sudoku[1][4] = 0b11;
    sudoku[1][5] = 0b100000;  // 6

    sudoku[1][6] = 0b110000;
    sudoku[1][7] = 0b11;
    sudoku[1][8] = 0b100000000;  // 9

    assert(!row_conflict(sudoku, 1));
    sudoku[1][4] = 0b100000;
    assert(row_conflict(sudoku, 1));
}

void col_conflict_test(unsigned int sudoku[9][9])
{
    sudoku[0][2] = 0b1;  // 1
    sudoku[1][2] = 0b11;
    sudoku[2][2] = 0b11;

    sudoku[3][2] = 0b10;  // 2
    sudoku[4][2] = 0b11;
    sudoku[5][2] = 0b10000;  // 6

    sudoku[6][2] = 0b110000;
    sudoku[7][2] = 0b11;
    sudoku[8][2] = 0b100000000;  // 9

    assert(!col_conflict(sudoku, 2));
    sudoku[4][2] = 0b1;
    assert(col_conflict(sudoku, 2));
}

int main(void)
{
    bitset_drop_test();
    bitset_is_set_test();
    bitset_is_unique_test();
    bitset_next_test();

    unsigned int sudoku[9][9];
    box_bitset_test(sudoku);
    row_bitset_test(sudoku);
    col_bitset_test(sudoku);
    box_conflict_test(sudoku);
    row_conflict_test(sudoku);
    col_conflict_test(sudoku);

    puts("test of auxiliary functions passed");
    return 0;
}