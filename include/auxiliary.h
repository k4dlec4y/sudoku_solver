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
static unsigned int bitset_drop(unsigned int original, int number);

/**
 * @brief  Check whether given number is present in the set.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param query     number which should be checked for presence
 *
 * @return          true if set, false otherwise
 */
static bool bitset_is_set(unsigned int original, int query);

/**
 * @brief  Check whether given cell has a unique value assigned.
 *
 * @param original  bitset to check for single vs. multiple values.
 *
 * @return          true if set, false otherwise
 */
static bool bitset_is_unique(unsigned int original);

/**
 * @brief Return next number present in bit set.
 *
 * This function encapsulates a bit ands, ors and whatever
 * other bit operations, that would flood the toplevel code
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
static int bitset_next(unsigned int bitset, int previous);

/**
 * @brief Compute the bitset of all done numbers in the box.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index of the top most row in box, one of 0, 3, 6
 * @param col_index of the left most column in box, one of 0, 3, 6
 */
static int box_bitset(unsigned int sudoku[9][9], int row_index, int col_index);

/**
 * @brief Compute the bitset of all done numbers in the row.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index
 */
static int row_bitset(unsigned int sudoku[9][9], int row_index);

/**
 * @brief Compute the bitset of all done numbers in the col.
 *
 * @param sudoku 2D array of digit bitsets
 * @param col_index
 */
static int col_bitset(unsigned int sudoku[9][9], int col_index);

static bool duplicate_in_box_bitset(unsigned int sudoku[9][9],
                                    int row_index, int col_index);

static bool duplicate_in_row_bitset(unsigned int sudoku[9][9], int row_index);

static bool duplicate_in_col_bitset(unsigned int sudoku[9][9], int col_index);

static bool load_sudoku_line(unsigned int sudoku[9][9], int ch);

static int check_char_square(unsigned int sudoku[9][9], int count);

static bool load_sudoku_square(unsigned int sudoku[9][9], int ch);
