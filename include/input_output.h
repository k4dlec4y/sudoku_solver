#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

/**
 * @brief Loads sudoku from stdin in single line format.
 * 
 * @note This function prints on stderr, if wrong format was encountered.
 *
 * @param file FILE * of input file, from which is sudoku loaded
 * @param sudoku 2D array of digit bitsets
 * @param ch already loaded char, based on which the format was decided
 *
 * @return true, if the input is in the correct format
 */
bool load_in_line_format(FILE *file,
                         unsigned int sudoku[9][9], int ch);

/**
 * @brief Loads 3 sets of consecutive number lines, when loading sudoku
 *        in square format. Also checks the format.
 * 
 * @note This function prints on stderr, if wrong format was encountered.
 *
 * @param file FILE * of input file, from which is sudoku loaded
 * @param sudoku 2D array of digit bitsets
 * @param count of already loaded numbers into sudoku
 * 
 * @return count of loaded chars, should be % 27 == 0 for success
 */
int load_number_lines(FILE *file,
                      unsigned int sudoku[9][9], int count);

/**
 * @brief Loads sudoku from stdin in square format.
 * 
 * @note This function prints on stderr, if wrong format was encountered.
 *
 * @param file FILE * of input file, from which is sudoku loaded
 * @param sudoku 2D array of digit bitsets
 * @param ch already loaded char, based on which the format was decided
 *
 * @return true, if the input is in the correct format
 */
bool load_in_square_format(FILE *file,
                           unsigned int sudoku[9][9], int ch);

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
 * @param file FILE * of input file, from which is sudoku loaded
 * @param sudoku 2D array to store digit bitsets, passed in undefined state
 *
 * @return true if sudoku was successfuly loaded, false otherwise;
 * also returns false for EOF
 */
bool load(FILE *file, unsigned int sudoku[9][9]);

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
 * @param file FILE * of output file, where is sudoku printed
 * @param sudoku 2D array of digit bitsets
 */
void print(FILE *file, unsigned int sudoku[9][9]);

#endif  // INPUT_OUTPUT_H
