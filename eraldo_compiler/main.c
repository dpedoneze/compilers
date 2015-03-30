/**@<main.c>::**/

#include <stdio.h>
#include <stdlib.h>
#include <main.h>

#define MISSING_FILE    -2
#define CANNOT_OPEN_FILE    -3

extern FILE *object;
FILE *target;

const char *filename;

int main(int argc, char const *argv[])
{
    if (argc <= 1) 
    {
        fprintf(stderr, "%s: missing file name... exiting\n", argv[0]);

        exit(MISSING_FILE);
    }

    filename = argv[1];

    target = fopen(argv[1], "r");

    if (target == NULL) 
    {
        fprintf(stderr, "%s: cannot open target %s... exiting\n", argv[0], argv[1]);
        exit(CANNOT_OPEN_FILE);
    }
    
    object = stdout;
    start();
    printf("\n");
    return 0;
}