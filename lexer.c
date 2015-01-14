/**@<lexer.c>::**/
#include <stdio.h>
#include <ctype.h>
#include <lexer.h>
#include <tokens.h>
#include <keywords.h>

int isID(FILE *target)
{
  char lexeme[1024];
  int letter = getc(target);
  int i = 0;
  if(isalpha(lexeme[i]=letter)){
    int symbol;
    i++;
    while(isalnum(lexeme[i] = symbol = getc(target))) i++;
    lexeme[i] = 0;
    ungetc(symbol,target);
    if(i=iskeyword(lexeme))return i;
    return ID;
  }
  ungetc(letter,target);
  return 0;
}

int isTEXT(FILE* target)
{
  int symbol = getc(target);
  
  if(symbol=='\'')
  {
    int backslash=0;
    while(symbol=getc(target) != '\'' || backslash)
    {
      backslash = (!backslash && symbol == '\\');
    }
  }
  
  ungetc(symbol,target);
  
  return 0;
}

int isNUMBER(FILE* target)
{
  /* regex: ['1'-'9']['0'-'9']* | '0' */
  int symbol = getc(target);
  int numtype = UINT;
  if(isdigit(symbol)) {
    if(symbol=='0') {
          if(symbol=='.') {
	    numtype = FLTP;
            while(isdigit(symbol=getc(target)));
            ungetc(symbol,target);
          }
          return numtype;
    }
    while(isdigit(symbol=getc(target)));
    if(symbol=='.')
      numtype = FLTP;
      while(isdigit(symbol=getc(target)));
    ungetc(symbol,target);
    return numtype;
  } else if(symbol=='.') {
    if(isdigit(symbol=getc(target))) {
      numtype = FLTP;
      while(isdigit(symbol=getc(target)));
    }
  }
  
  /*
   * IMPLEMENTAR PARTE EXPONENCIAL
   * 
   * [E [('+'|'-')] digit {digit}
  */
  
  ungetc(symbol,target);
  return 0;
}

int isCOLONEQ(FILE* target)
{
  int symbol = getc(target);
  
  if(symbol == ':')
  {
    if(symbol=getc(target)=='=')
      return COLONEQ;
  }
  
  ungetc(symbol,target);
  return 0;
}

int skipspaces(FILE* target)
{
  int symbol;
  while(isspace(symbol=getc(target)));
  if(symbol == EOF) return EOF;
  ungetc(symbol,target);
  return 0;
}

/** lexer-to-parser interface **/
int gettoken(FILE* target)
{
  int token;
  if(token = skipspaces(target)) return token;
  if(token = isID(target)) return token;
  if(token = isDECIMAL(target)) return token;
  if(token = isTEXT(target)) return token;
  if(token = isCOLONEQ(target)) return token;
  return getc(target);
}
