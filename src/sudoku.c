#include "sudoku.h"

const unsigned int FULL_BITSET = 0x1ff;
const unsigned int LINE_LEN = 26;
const unsigned int ROWS = 3;
const char LINE[] = "+=======+=======+=======+";
const char NUMBER_LINE[] = "| x x x | x x x | x x x |\n";

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


/* ************************************************************** *
 *                 Adwised auxiliary functionns                   *
 * ************************************************************** */

/**
 * @brief  Drop number from bit set.
 *
 * For detailed description, see bitset_add.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param number    to be dropped from the set
 *
 * @return          new value of the cell without the number included
 */
static unsigned int bitset_drop(unsigned int original, int number) {
    if (number < 1 || number > 9)
    {
        return 0;
    }
    return original & (~(0x1 << (number - 1)));
}

/**
 * @brief  Check whether given number is present in the set.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param query     number which should be checked for presence
 *
 * @return          true if set, false otherwise
 */
static bool bitset_is_set(unsigned int original, int query) {
    if (query < 1 || query > 9)
    {
        return false;
    }
	return ((original >> (query - 1)) & 0x1) == 0x1;
}

/**
 * @brief  Check whether given cell has a unique value assigned.
 *
 * @param original  bitset to check for single vs. multiple values.
 *
 * @return          true if set, false otherwise
 */
static bool bitset_is_unique(unsigned int original) {
    bool found = false;
	for (int i = 0; i < 9; ++i)
    {
        if (((original >> i) & 0x1) == 0x1)
        {
            if (found)
            {
                return false;
            }
            found = true;
        }
    }
    return found;
}

/**
 * @brief Return next number present in bit set.
 *
 * This function encapsulates a bit ands, ors and whatever
 * other bint operations, that would flood the toplevel code
 * with implementation details.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param previous  last known number present, 0 for start
 *
 * @return          * next (higher) number than argument if such
                    such is present.
 *                  * -1 otherwise
 *
 * @note The value previous might not be in the bitset
 */
static int bitset_next(unsigned int bitset, int previous) {
    ++previous;
    while (previous < 10)
    {
        if (((bitset >> (previous - 1)) & 0x1) == 0x1)
        {
            return previous;
        }
        ++previous;
    }
    return -1;
}

/**
 * @brief Compute the bitset of all done numbers in the box.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index of the top most row in box, one of 0, 3, 6
 * @param col_index of the left most column in box, one of 0, 3, 6
 */
static int box_bitset(unsigned int sudoku[9][9], int row_index, int col_index) {
    int done = 0x00;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            unsigned int bitset = sudoku[row_index + i][col_index + j];
            if (bitset_is_unique(bitset))
            {
                done |= (0x1 << (bitset_next(bitset, 0) - 1));
            }
        }
    }
    return done;
}

/**
 * @brief Compute the bitset of all done numbers in the row.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index
 */
static int row_bitset(unsigned int sudoku[9][9], int row_index) {
    int done = 0x00;
    for (int i = 0; i < 9; ++i)
    {
        unsigned int bitset = sudoku[row_index][i];
        if (bitset_is_unique(bitset))
        {
            done |= (0x1 << (bitset_next(bitset, 0) - 1));
        }
    }
    return done;
}

/**
 * @brief Compute the bitset of all done numbers in the col.
 *
 * @param sudoku 2D array of digit bitsets
 * @param col_index
 */
static int col_bitset(unsigned int sudoku[9][9], int col_index) {
    int done = 0x00;
    for (int i = 0; i < 9; ++i)
    {
        unsigned int bitset = sudoku[i][col_index];
        if (bitset_is_unique(bitset))
        {
            done |= (0x1 << (bitset_next(bitset, 0) - 1));
        }
    }
    return done;
}

static bool duplicate_in_box_bitset(unsigned int sudoku[9][9], int row_index, int col_index) {
    int done = 0x00;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            unsigned int bitset = sudoku[row_index + i][col_index + j];
            if (bitset_is_unique(bitset))
            {
                int num_in_bitset = (0x1 << (bitset_next(bitset, 0) - 1));
                if ((done & num_in_bitset) > 0)
                {
                    return true;
                }
                done |= num_in_bitset;
            }
        }
    }
    return false;
}

static bool duplicate_in_row_bitset(unsigned int sudoku[9][9], int row_index) {
    int done = 0x00;
    for (int i = 0; i < 9; ++i)
    {
        unsigned int bitset = sudoku[row_index][i];
        if (bitset_is_unique(bitset))
        {
            int num_in_bitset = (0x1 << (bitset_next(bitset, 0) - 1));
            if ((done & num_in_bitset) > 0)
            {
                return true;
            }
            done |= num_in_bitset;
        }
    }
    return false;
}

static bool duplicate_in_col_bitset(unsigned int sudoku[9][9], int col_index) {
    int done = 0x00;
    for (int i = 0; i < 9; ++i)
    {
        unsigned int bitset = sudoku[i][col_index];
        if (bitset_is_unique(bitset))
        {
            int num_in_bitset = (0x1 << (bitset_next(bitset, 0) - 1));
            if ((done & num_in_bitset) > 0)
            {
                return true;
            }
            done |= num_in_bitset;
        }
    }
    return false;
}

static bool load_sudoku_line(unsigned int sudoku[9][9], int ch)
{
    for (int count = 0; count < 81; count++)
    {
        if (ch == '0')
        {
            sudoku[count / 9][count % 9] = FULL_BITSET; 
        }
        else if (ch <= '9' && ch >= '1')
        {
            sudoku[count / 9][count % 9] = 0x1 << (((int)ch - '0') - 1);
        }
        else
        {
            return false;
        }
        ch = getchar();
    }
    return ch == '\n' || ch == EOF;
}

static int check_char_square(unsigned int sudoku[9][9], int count)
{
    int ch;
    for (size_t j = 0; j < ROWS * LINE_LEN; j++)
    {
        ch = getchar();
        if (ch == NUMBER_LINE[j % 26] && ch != 'x')
        {
            continue;
        }
        else if ('x' == NUMBER_LINE[j % 26])
        {
            if (ch <= '9' && ch >= '1')
            {
                sudoku[count / 9][count % 9] = 0x1 << (((int)ch - '0') - 1);
                count++;
                continue;
            }
            if (ch == '.' || ch == '0')
            {
                sudoku[count / 9][count % 9] = FULL_BITSET;
                count++;
                continue;
            }
        }
        return count;
    }
    return count;
}

static bool load_sudoku_square(unsigned int sudoku[9][9], int ch)
{
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < LINE_LEN - 1; j++)
        {
            if (ch != LINE[j])
            {
                return false;
            }
            ch = getchar();
        }

        // in this if the function ends
        if (i == 3)
        {
            return ch == '\n';
        }
        if (ch != '\n')
        {
            return false;
        }

        count = check_char_square(sudoku, count);
        if (count % 27 != 0)
        {
            return false;
        }
        ch = getchar();
    }
    return false;
}
