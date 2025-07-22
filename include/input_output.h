#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

/**
 * @brief Loads sudoku from stdin in single line format.
 *
 * @param sudoku 2D array of digit bitsets
 * @param ch already loaded char, based on which the format was decided
 *
 * @return true, if the input was in the right format
 */
bool load_in_line_format(unsigned int sudoku[9][9], int ch);

/**
 * @brief Loads 3 sets of consecutive number lines, when loading sudoku
 *        in square format. Also checks the format.
 *
 * @param sudoku 2D array of digit bitsets
 * @param count of already loaded numbers into sudoku
 * 
 * @return count of last loaded char 
 */
int load_number_lines(unsigned int sudoku[9][9], int count);

/**
 * @brief Loads sudoku from stdin in square format.
 *
 * @param sudoku 2D array of digit bitsets
 * @param ch already loaded char, based on which the format was decided
 *
 * @return true, if the input was in the right format
 */
bool load_in_square_format(unsigned int sudoku[9][9], int ch);

/**
 * @brief Load the sudoku from STDIN.
 *
 * The digits are read from left to right and from top to bottom,
 * just as common english text. Zero is interpreted as an unknown
 * digit, i.e. a full digit bitset and NOT an empty set (000000000).
 *
 * @example
 * 000456789000123456000789123312000967697000845845000312231574000968231000574968000
 *
 * @note In case of invalid input, prints one line message
 * on STDERR and returns false. In such case, the sudoku is in undefined state,
 * and might contain partialy loaded sudoku.
 *
 * @note The exact format is described in readme file.
 *
 * @param sudoku 2D array to store digit bitsets, passed in undefined state.
 *
 * @return true if sudoku was successfuly loaded, false otherwise.
 */
bool load(unsigned int sudoku[9][9]);

/**
 * @brief Prints sudoku to STDOUT in grid with highlighted boxes.
 *
 * The X in the grid are substituted by respective digit or '.' if unknown.
 * If no digit can be placed to the cell, '!' is printed instead.
 *
 * @verbatim
 * +=======+=======+=======+
 * | X X X | X X X | X X X |
 * | X X X | X X X | X X X |
 * | X X X | X X X | X X X |
 * +=======+=======+=======+
 * | X X X | X X X | X X X |
 * | X X X | X X X | X X X |
 * | X X X | X X X | X X X |
 * +=======+=======+=======+
 * | X X X | X X X | X X X |
 * | X X X | X X X | X X X |
 * | X X X | X X X | X X X |
 * +=======+=======+=======+
 * @endverbatim
 *
 * @param sudoku 2D array of digit bitsets
 */
void print(unsigned int sudoku[9][9]);

#endif  // INPUT_OUTPUT_H
