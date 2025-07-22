/**
 * @file sudoku.h
 * @author PB071
 * @date 10 Feb 2024
 * @brief Sudoku - second homework of PB071 in spring semester of 2024.
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

/**
 * @brief Eliminate the possible digits in unknown squares in the row.
 *
 * E.g. for |...|456|789| the unknown squares will have
 * bitset 7 (000000111).
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index starting from 0 (leftmost) to 8 (rightmost)
 */
bool eliminate_row(unsigned int sudoku[9][9], int row_index);

/**
 * @brief Eliminate the possible digits in unknown squares in the column.
 *
 * @param sudoku 2D array of digit bitsets
 * @param col_index starting from 0 (top) to 8 (bottom)
 */
bool eliminate_col(unsigned int sudoku[9][9], int col_index);

/**
 * @brief Eliminate the possible digits in unknown squares in the box.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index of the top most row in box, one of 0, 3, 6
 * @param col_index of the left most column in box, one of 0, 3, 6
 */
bool eliminate_box(unsigned int sudoku[9][9], int row_index, int col_index);

/**
 * @brief Check if the sudoku is to be solved yet, or is allready
 * complete.
 *
 * @note Does not care about validity, just checks whether cell
 * without unique value exists!
 * @param sudoku 2D array of digit bitsets
 */
bool needs_solving(unsigned int sudoku[9][9]);

/**
 * @brief Check if the set digits do not conflict with one another.
 *
 * @note The squares that do not have set digits are not checked!
 * @param sudoku 2D array of digit bitsets
 */
bool is_valid(unsigned int sudoku[9][9]);

/**
 * @brief Solve the sudoku using elimination as much as possible
 * without guessing or backtracking.
 *
 * If you fully solve the sudoku return true, otherwise false.
 *
 * @note In case the sudoku is invalid, reports to user with one
 * line message on STDERR and returns false. The state of sudoku
 * is then not defined.
 *
 * @param sudoku 2D array of digit bitsets
 */
bool solve(unsigned int sudoku[9][9]);

/**
 * @brief Solve the sudoku first by using elimination (solve())
 * and if needed, completes it by using backtracking.
 * 
 * @note In case the sudoku is invalid, reports to user with one
 * line message on STDERR and returns false. The state of sudoku
 * is then not defined.
 *
 * @param sudoku 2D array of digit bitsets
 * 
 * @return true, if sudoku was solved, false otherwise
 */
bool generic_solve(unsigned int sudoku[9][9]);

#endif //SUDOKU_H
