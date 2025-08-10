#ifndef GENERIC_SOLVE_H
#define GENERIC_SOLVE_H

#include <stdbool.h>

/**
 * @file  generic_solve.h
 *
 * This header contains everything related to the backtracking part of
 * the program.
 */

/**
 * @brief  Drops a number from non-unique cells of the row and returns a bitset
 *         of cells from which the number was indeed dropped.
 *
 * @param sudoku  2D array of digit bitsets
 * @param row     index of the processed row
 * @param number  a number to be dropped
 * 
 * @return  a bitset of cells in which the number was present before the call
 */
unsigned int row_drop_with_memory(unsigned int sudoku[9][9],
                                  int row, int number);

/**
 * @brief  Adds the number back to the cells of the row from which it was
 *         dropped.
 * 
 * @param sudoku   2D array of digit bitsets
 * @param row      index of the processed row
 * @param number   the number to be restored
 * @param dropped  a bitset of cells which originally contained the number
 */
void row_restore(unsigned int sudoku[9][9], int row,
                 int number, unsigned int dropped);

/**
 * @brief  Drops a number from non-unique cells of the col and returns a bitset
 *         of cells from which the number was indeed dropped.
 *
 * @param sudoku  2D array of digit bitsets
 * @param col     index of the processed col
 * @param number  a number to be dropped
 * 
 * @return  a bitset of cells in which the number was present before the call
 */

unsigned int col_drop_with_memory(unsigned int sudoku[9][9],
                                  int col, int number);

/**
 * @brief  Adds the number back to the cells of the col from which it was
 *         dropped.
 * 
 * @param sudoku   2D array of digit bitsets
 * @param col      index of the processed col
 * @param number   the number to be restored
 * @param dropped  a bitset of cells which originally contained the number
 */
void col_restore(unsigned int sudoku[9][9], int col,
                 int number, unsigned int dropped);

/**
 * @brief  Drops a number from non-unique cells of the box and returns a bitset
 *         of cells from which the number was indeed dropped.
 *
 * @param sudoku  2D array of digit bitsets
 * @param row     row index of the processed box
 * @param col     col index of the processed box
 * @param number  a number to be dropped
 * 
 * @return  a bitset of cells in which the number was present before the call
 */
unsigned int box_drop_with_memory(unsigned int sudoku[9][9],
                                  int row, int col, int number);

/**
 * @brief  Adds the number back to the cells of the box from which it was
 *         dropped.
 * 
 * @param sudoku   2D array of digit bitsets
 * @param row      row index of the processed box
 * @param col      col index of the processed box
 * @param number   the number to be restored
 * @param dropped  a bitset of cells which originally contained the number
 */
void box_restore(unsigned int sudoku[9][9], int row, int col,
                 int number, unsigned int dropped);

/**
 * @brief  Completes the sudoku by using backtracking.
 *
 * @param sudoku  2D array of digit bitsets
 * @param index   index of current sudoku cell
 * 
 * @note  Always call this function with index = 0,
 *        higher indices are used only in recursive calls.
 * 
 * @note  Index 0 is the most top left cell.
 * 
 * @return  true, if sudoku was solved, false otherwise
 */
bool generic_solve(unsigned int sudoku[9][9], int index);

#endif  // GENERIC_SOLVE_H
