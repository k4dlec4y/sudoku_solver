#ifndef AUXILIARY_H
#define AUXILIARY_H

/**
 * @brief  Converts a number to it's bitset representation in sudoku/
 * 
 * @param number  integer from 1 to 9
 */
unsigned int num_to_bitset(int number);

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
unsigned int bitset_drop(unsigned int original, int number);

/**
 * @brief  Check whether given number is present in the set.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param query     number which should be checked for presence
 *
 * @return          true if set, false otherwise
 */
bool bitset_is_set(unsigned int original, int query);

/**
 * @brief  Check whether given cell has a unique value assigned.
 *
 * @param original  bitset to check for single vs. multiple values.
 *
 * @return          true if set, false otherwise
 */
bool bitset_is_unique(unsigned int original);

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
int bitset_next(unsigned int bitset, int previous);

/**
 * @brief Compute the bitset of all done numbers in the box.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index of the top most row in box, one of 0, 3, 6
 * @param col_index of the left most column in box, one of 0, 3, 6
 */
int box_bitset(unsigned int sudoku[9][9], int row_index, int col_index);

/**
 * @brief Compute the bitset of all done numbers in the row.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index
 */
int row_bitset(unsigned int sudoku[9][9], int row_index);

/**
 * @brief Compute the bitset of all done numbers in the col.
 *
 * @param sudoku 2D array of digit bitsets
 * @param col_index
 */
int col_bitset(unsigned int sudoku[9][9], int col_index);

/**
 * @brief Checks, whether there is a conflict in the box.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index of the top most most row in box, one of 0, 3, 6
 * @param col_index of the left most column in box, one of 0, 3, 6
 */
bool box_conflict(unsigned int sudoku[9][9],
                  int row_index, int col_index);

/**
 * @brief Checks, whether there is a conflict in the row.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index
 */
bool row_conflict(unsigned int sudoku[9][9], int row_index);

/**
 * @brief Checks, whether there is a conflict in the col.
 *
 * @param sudoku 2D array of digit bitsets
 * @param col_index
 */
bool col_conflict(unsigned int sudoku[9][9], int col_index);

#endif // AUXILIARY_H
