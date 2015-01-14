/**@<lexer.h>**/

#define BUFFER_SIZE 1024

int isIDENTIFIER(FILE *target);
int isDECIMAL(FILE *target);
int gettoken(FILE *target);
int skipspaces(FILE *target);
extern int iskeyword(char const *identifier);


