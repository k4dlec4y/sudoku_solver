#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sudoku.h"
#include "../include/input_output.h"

int solve_file(unsigned int sudoku[9][9],
               FILE *file_in, FILE *file_out)
{
    for (int i = 1;; ++i) {
        printf(" = loading %d. sudoku\n", i);
        if (!load(file_in, sudoku))
            return 0;

        printf(" = solving %d. sudoku\n", i);
        if (!solve(sudoku))
            printf(" - could not solve with eliminations only\n");
        else
            printf(" + sudoku solved with eliminations only\n");

        print(file_out, sudoku);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int sudoku[9][9];

    if (argc == 1)
        return solve_file(sudoku, stdin, stdout);

    int rv = 0;

    FILE *file_in;
    FILE *file_out;

    for (int i = 1; i < argc; ++i) {

        file_in = fopen(argv[i], "r");
        if (!file_in) {
            fprintf(stderr, "could not open file %s for reading\n",
                    argv[i]);
            continue;
        }

        char *file_out_name = calloc(strlen(argv[i]) + 5,
                                     sizeof(char));
        if (!file_out_name) {
            fprintf(stderr, "insufficient memory\n");
            goto cleanup;
        }

        strcpy(file_out_name, argv[i]);
        strcat(file_out_name, ".out");

        file_out = fopen(file_out_name, "w");
        if (!file_out) {
            fprintf(stderr, "could not open file %s for writing\n",
                    file_out_name);
            goto cleanup;
        }

        printf("solving file %s\n", argv[i]);
        if (solve_file(sudoku, file_in, file_out) != 0)
            rv = -1;

cleanup:
        if (file_out_name)
            free(file_out_name);
        if (file_in)
            fclose(file_in);
        if (file_out)
            fclose(file_out);

        if (i < argc - 1)
            putchar('\n');
    }

    return rv;
}
