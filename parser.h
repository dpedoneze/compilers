/**@<parser.h>::**/
#include <stdio.h>
#include <constants.h>

void mypas (void);
void programID (void);
void declarations (void);
void varspecs(void);
int isbuiltin(void);
void typespec(void);
void formparm(void);
void parmlist(void);
void sbpspecs(void);
void blockstmt(void);
void stmtlist(void);
void stmt(void);
void ifstmt(void);
void expr(void);
int isrelop(void);
void simpexpr(void);
void negate(void);
int isaddop(void);
void term(void);
int ismulop(void);
void fact(void);
void constant(void);
void number(void);
void digit(void);
void whilestmt(void);
void repstmt(void);
void idstmt(void);
void idvalue(void);
void exprlist(void);
void start();

void match(int expected);

extern int lookahead;
extern gettoken(FILE *);
extern FILE *target;
extern char lexeme[];

