/**@<parser.h>::**/

void mypas (void);
void programID (void);
void declarations(void);
void varspecs(void);
void typespec(void);
void idstmt(void);
void idvalue(void);
void exprlist(void);
void blockstmt(void);
void sbpspecs(void);

extern int lookahead;
void match(int expected);
extern gettoken(FILE *);
extern FILE *target;