/**@<lexer.h>**/
#include <constants.h>

int isIDENTIFIER(FILE *target);
int isDECIMAL(FILE *target);
int gettoken(FILE *target);
int skipspaces(FILE *target);
extern int iskeyword(char const *identifier);
extern char lexeme[];