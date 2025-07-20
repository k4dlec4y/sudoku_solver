# sudoku_solver

## Table of Contents
- [Introduction](#introduction)
- [Overview](#overview)
- [Usage](#usage)
- [License](#license)
- [Author](#author)

## Introduction

This is a refactored version of one of my first university projects in C, which I originally wrote a year ago. The goal of this refactoring is to apply what I’ve learned over the past year and to get better at reading and understanding "unfamiliar" code (one year is a long time). We were given a `main.c` file to start with, but in this refactored version, I’ll be writing my own main so that the project feels fully like my own work.

## Overview

This program is a solver for the popular game Sudoku, which most people are likely familiar with. It accepts input in two different formats and tries to solve the puzzle in two main steps:

**Elimination** – based on known numbers from the input, the program removes impossible values from each cell.

**Backtracking** – once elimination can't progress further, it uses backtracking to find the correct solution.

The Sudoku grid is stored as a right-angle `unsigned int[9][9]` array. Each `unsigned int` represents a set of possible values for that cell. More technical details, including input formats and how to run the program, can be found in the Usage section.

## Usage

The program will accept input via standard input or a file, and display the solved grid on the console. Full instructions will be added once the new `main.c` is complete.

## License

This project is licensed under the MIT License – see the LICENSE file for details.

## Author

Created by Matúš Kadlecay - https://github.com/k4dlec4y