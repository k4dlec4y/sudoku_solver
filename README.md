# sudoku_solver

## Table of Contents
- [Introduction](#introduction)
- [Overview](#overview)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [License](#license)
- [Author](#author)

## Introduction
This is a refactored version of one of my first university projects in C, which I originally wrote a year ago. The goal of this refactoring is to apply what I’ve learned over the past year and to get better at reading and understanding "unfamiliar" code (one year is a long time). We were given a `main.c` file to start with, but in this refactored version, I’ll be writing my own main so that the project feels fully like my own work.

## Overview
This program is a solver for the popular game Sudoku, which most people are likely familiar with. It accepts input in two different formats and tries to solve the puzzle in two main steps:

**Elimination** – based on known numbers from the input, the program removes impossible values from each cell.  
**Backtracking** – once elimination can't progress further, it uses backtracking to find the correct solution.

The Sudoku grid is stored as a right-angle `unsigned int[9][9]` array. Each `unsigned int` represents a set of possible values for that cell. More technical details, including input formats and how to run the program, can be found in the Usage section.

## Requirements
- GCC with C99 support
- make
- Tested on Linux (Fedora 42)

## Installation
```bash
git clone https://github.com/k4dlec4y/sudoku_solver
cd sudoku_solver
make
```

## Usage
Run the executable with `./build/sudoku file1 file2 ...`.

The program accepts one or more files as command-line arguments. For each input file `file`, it generates output file `file.out` inside the same directory. Solved Sudoku puzzles will be printed to corresponding `file.out`. Each input file may contain multiple Sudoku puzzles separated by a single `\n`. The last Sudoku of the file does not need to be followed by `\n`. If no input files are provided, it uses `STDIN` as an input file and `STDOUT` as an output file.

### Single line format of Sudoku
This format is pretty simple. It is represented by single line of exactly 81 characters ranging from '0' to '9' where '0' represents an empty cell (FULL_BITSET in sudoku grid representation) and digits from '1' to '9' represent pre-filled (known) values.

Example:  
```
530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

### Square format of Sudoku
This format is also used for output files. It consists of square grid divided into 9 boxes where '0' or '.' represents an empty cell (FULL_BITSET in sudoku grid representation) and digits from '1' to '9' represent pre-filled (known) values.

Example:  
```
+=======+=======+=======+  
| . . . | 4 5 6 | 7 8 9 |  
| . . . | 1 2 3 | 4 5 6 |  
| . . . | 7 8 9 | 1 2 3 |  
+=======+=======+=======+  
| 3 1 2 | 0 0 0 | 9 6 7 |  
| 6 9 7 | 0 0 0 | 8 4 5 |  
| 8 4 5 | 0 0 0 | 3 1 2 |  
+=======+=======+=======+  
| 2 3 1 | 5 7 4 | . . . |  
| 9 6 8 | 2 3 1 | . . . |  
| 5 7 4 | 9 6 8 | . . . |  
+=======+=======+=======+
```

Both formats can be used inside the same file. For whole input files examples, see `tests/sudoku01.txt` and `tests/sudoku02.txt`. The program prints information about file processing to `STDOUT`.

Example:
```bash
build/sudoku tests/sudoku01.txt tests/sudoku02.txt 
solving file tests/sudoku01.txt
 = loading 1. sudoku
 = solving 1. sudoku
 + sudoku solved with eliminations only
 = loading 2. sudoku
 = solving 2. sudoku
 + sudoku solved with generic solve
 = loading 3. sudoku
 - expected char from '0' to '9' or '.', got x instead

solving file tests/sudoku02.txt
 = loading 1. sudoku
 = solving 1. sudoku
 + sudoku solved with eliminations only
 = loading 2. sudoku
 - there is a conflict in the sudoku
 = loading 3. sudoku
 = solving 3. sudoku
 + sudoku solved with generic solve
 = loading 4. sudoku
 + no more sudoku to load
```

## Testing

To run the tests, execute `make tests` inside the project directory. Note that the tests for `sudoku01.txt` and `sudoku02.txt` may fail even if the program is correct; if solver implementation is changed, it may find different valid solution first.

## License

This project is licensed under the MIT License – see the LICENSE file for details.

## Author

Created by Matúš Kadlecay - https://github.com/k4dlec4y
