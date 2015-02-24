typedef struct _symbol_table_ {
    char            symbol[MAXIDLEN + 1];
    int             objtype;
    char            offset[MAXIDLEN + 1];
    char            paddle[4096];
} SYMTAB;

extern SYMTAB   symtab[MAXTBENTRIES];

extern int      symtab_nextentry;

void		symtab_cat(char const *newsymbol);
int             symtab_lookup(char const *query);
