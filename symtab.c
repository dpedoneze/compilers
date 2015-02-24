#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <tokens.h>
#include <symtab.h>

SYMTAB          symtab[MAXTBENTRIES];

int             symtab_nextentry;

void
symtab_cat(char const *newsymbol)
{
    if (symtab_lookup(newsymbol) < 0) {
        if (symtab_nextentry < MAXTBENTRIES) {
            strcpy(symtab[symtab_nextentry].symbol, newsymbol);
            symtab_nextentry++;
        } else {
            fprintf(stderr,
                    "maximum symbol entries exceeded... exiting\n");
            exit(-4);
        }
    }else{
      fprintf(stderr, "%s already declared... exiting\n", newsymbol);
      exit(-3);
    }
}

int
symtab_lookup(char const *query)
{
    int             i;
    for (i = symtab_nextentry - 1; i > -1; i--) {
        if (strcmp(symtab[i].symbol, query) == 0)
            break;
    }
    return i;
}
