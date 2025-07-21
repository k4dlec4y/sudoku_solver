#include "sudoku.h"

static unsigned int bitset_drop(unsigned int original, int number);
static bool bitset_is_set(unsigned int original, int query);
static bool bitset_is_unique(unsigned int original);
static int bitset_next(unsigned int bitset, int previous);
static int box_bitset(unsigned int sudoku[9][9], int row_index, int col_index);
static int row_bitset(unsigned int sudoku[9][9], int row_index);
static int col_bitset(unsigned int sudoku[9][9], int col_index);
static bool duplicate_in_box_bitset(unsigned int sudoku[9][9], int row_index, int col_index);
static bool duplicate_in_row_bitset(unsigned int sudoku[9][9], int col_index);
static bool duplicate_in_col_bitset(unsigned int sudoku[9][9], int col_index);
static bool load_sudoku_line(unsigned int sudoku[9][9], int ch);
static bool load_sudoku_square(unsigned int sudoku[9][9], int ch);

/* ************************************************************** *
 *               Functions required by assignment                 *
 * ************************************************************** */

bool eliminate_row(unsigned int sudoku[9][9], int row_index)
{
    bool change = false;
    unsigned int done = row_bitset(sudoku, row_index);

    for (int i = 0; i < 9; i++)
    {
        if (bitset_is_unique(sudoku[row_index][i]))
        {
            continue;
        }

        int number = 0;
        while ((number = bitset_next(sudoku[row_index][i], number)) != -1)
        {
            if (bitset_is_set(done, number))
            {
                sudoku[row_index][i] = bitset_drop(sudoku[row_index][i], number);
                change = true;
            }
        }
    }
    return change;
}

bool eliminate_col(unsigned int sudoku[9][9], int col_index)
{
    bool change = false;
    unsigned int done = col_bitset(sudoku, col_index);

    for (int i = 0; i < 9; i++)
    {
        if (bitset_is_unique(sudoku[i][col_index]))
        {
            continue;
        }

        int number = 0;
        while ((number = bitset_next(sudoku[i][col_index], number)) != -1)
        {
            if (bitset_is_set(done, number))
            {
                sudoku[i][col_index] = bitset_drop(sudoku[i][col_index], number);
                change = true;
            }
        }
    }
    return change;
}

bool eliminate_box(unsigned int sudoku[9][9], int row_index, int col_index)
{
    bool change = false;
    row_index = (row_index / 3) * 3;  // round down to i % 3 == 0
    col_index = (col_index / 3) * 3;
    unsigned int done = box_bitset(sudoku, row_index, col_index);

    for (int i = row_index; i < row_index + 3; i++)
    {
        for (int j = col_index; j < col_index + 3; j++)
        {
            if (bitset_is_unique(sudoku[i][j]))
            {
                continue;
            }

            int number = 0;
            while ((number = bitset_next(sudoku[i][j], number)) != -1)
            {
                if (bitset_is_set(done, number))
                {
                    sudoku[i][j] = bitset_drop(sudoku[i][j], number);
                    change = true;
                }
            }
        }
    }
    return change;
}

bool needs_solving(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!bitset_is_unique(sudoku[i][j]))
            {
                return true;
            }
        }
    }
    return false;
}

bool is_valid(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if (duplicate_in_col_bitset(sudoku, i) || duplicate_in_row_bitset(sudoku, i))
        {
            return false;
        }
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0x0 ||
                (j % 3 == 0 && i % 3 == 0 && duplicate_in_box_bitset(sudoku, i, j)))
            {
                return false;
            }
        }
    }
    return true;
}

bool solve(unsigned int sudoku[9][9])
{
    bool change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < 9; i++)
        {
            change = change || eliminate_row(sudoku, i) || eliminate_col(sudoku, i);
        }
        for (int i = 0; i < 9; i += 3)
        {
            for (int j = 0; j < 9; j += 3)
            {
                change = change || eliminate_box(sudoku, i, j);
            }
        }
        if (!needs_solving(sudoku))
        {
            return true;
        }
    }
    return false;
}

bool load(unsigned int sudoku[9][9])
{
    int ch = getchar();
    if (ch == '+')
    {
        if (!load_sudoku_square(sudoku, ch))
        {
            fprintf(stderr, "invalid input\n");
            return false;
        }
    }
    else if(ch >= '0' && ch <= '9')
    {
        if (!load_sudoku_line(sudoku, ch))
        {
            fprintf(stderr, "invalid input\n");
            return false;
        }
    }
    else
    {
        fprintf(stderr, "invalid input\n");
        return false;
    }
    return true;
}

void print(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 3; i++)
    {
        printf("+=======+=======+=======+\n");
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                if (k % 3 == 0){
                    printf("| ");
                }

                unsigned int bitset = sudoku[i * 3 + j][k];
                if (bitset == 0)
                {
                    printf("! ");
                }
                else if (bitset_is_unique(bitset))
                {
                    printf("%d ", bitset_next(bitset, 0));
                }
                else
                {
                    printf(". ");
                }
            }
            printf("|\n");
        }
    }
    printf("+=======+=======+=======+\n");
}

/* ************************************************************** *
 *                              Bonus                             *
 * ************************************************************** */

#ifdef BONUS_GENERATE
void generate(unsigned int sudoku[9][9])
{
    return; // todo
}
#endif

#ifdef BONUS_GENERIC_SOLVE
bool generic_solve(unsigned int sudoku[9][9])
{
    return false; // todo
}
#endif
