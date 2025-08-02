#ifndef GENERIC_SOLVE_H
#define GENERIC_SOLVE_H

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
bool generic_solve(unsigned int sudoku[9][9], int index);

#endif  // GENERIC_SOLVE_H
