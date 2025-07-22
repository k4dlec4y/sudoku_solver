#include "sudoku.h"
#include "auxiliary.h"

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
        if (col_conflict(sudoku, i) || row_conflict(sudoku, i))
        {
            return false;
        }
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0x0 ||
                (j % 3 == 0 && i % 3 == 0 && box_conflict(sudoku, i, j)))
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
        if (!load_in_square_format(sudoku, ch))
        {
            fprintf(stderr, "invalid input\n");
            return false;
        }
    }
    else if(ch >= '0' && ch <= '9')
    {
        if (!load_in_line_format(sudoku, ch))
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
