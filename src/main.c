#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sudoku.h"
#include "../include/generic_solve.h"
#include "../include/input_output.h"

int solve_file(unsigned int sudoku[9][9], FILE *file_in, FILE *file_out)
{
    int rv = 0;

    for (int i = 1;; ++i) {

        printf(" = loading %d. sudoku\n", i);
        int fnc_rv = load(file_in, sudoku);
        if (fnc_rv == 1)  // EOF
            return rv;
        if (fnc_rv == -1)
            return -1;

        if (!is_valid(sudoku)) {
            puts(" - there is a conflict in the sudoku");
            rv = -1;
            print(file_out, sudoku);
            continue;
        }

        printf(" = solving %d. sudoku\n", i);
        if (solve(sudoku))
            puts(" + sudoku solved with eliminations only");
        else if (generic_solve(sudoku, 0))
            puts(" + sudoku solved with generic solve");
        else
            puts(" - sudoku could not be solved even with generic solve");

        print(file_out, sudoku);
    }

    return rv;
}

int main(int argc, char *argv[])
{
    unsigned int sudoku[9][9];

    if (argc == 1) {
        puts("solving from stdin");
        return solve_file(sudoku, stdin, stdout);
    }

    int rv = 0;

    FILE *file_in;
    FILE *file_out;
    char *file_out_name;

    for (int i = 1; i < argc; ++i) {

        printf("solving file %s\n", argv[i]);

        file_in = fopen(argv[i], "r");
        if (!file_in) {
            printf("could not open file %s for reading\n", argv[i]);
            continue;
        }

        size_t file_name_len = strlen(argv[i]);
        file_out_name = calloc(file_name_len + 5, sizeof(char));
        if (!file_out_name) {
            puts("insufficient memory");
            goto cleanup;
        }

        strcpy(file_out_name, argv[i]);
        strcpy(file_out_name + file_name_len, ".out");

        file_out = fopen(file_out_name, "w");
        if (!file_out) {
            printf("could not open file %s for writing\n", file_out_name);
            goto cleanup;
        }

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
