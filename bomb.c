/***************************************************************************
 * CS612 Bomb Lab
 * Covers CS:APP Chapter 3, Sections 3.1-3.6:
 *   data formats, registers/addressing modes, arithmetic/logical ops,
 *   condition codes, jumps, loops, switch/jump tables.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "phases.h"

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    if (argc == 1) {
        infile = stdin;
    } else if (argc == 2) {
        if (!(infile = fopen(argv[1], "r"))) {
            printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
            exit(8);
        }
    } else {
        printf("Usage: %s [<input_file>]\n", argv[0]);
        exit(8);
    }

    printf("Welcome to the CS612 bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    input = read_line();
    phase_1(input);
    phase_defused();
    printf("Phase 1 defused. How about the next one?\n");

    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2. Keep going!\n");

    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there!\n");

    input = read_line();
    phase_4(input);
    phase_defused();
    printf("Good, but this bomb has 2 more phases!\n");

    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Almost there! One more to go.\n");

    input = read_line();
    phase_6(input);
    phase_defused();

    printf("Congratulations! You've defused the bomb!\n");

    return 0;
}
