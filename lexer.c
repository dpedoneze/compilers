/**@<lexer.c>::**/
#include <stdio.h>
#include <ctype.h>
#include <lexer.h>
#include <tokens.h>
#include <keywords.h>

char lexeme[BUFFER_SIZE];

int isID(FILE *target)
{
  int letter = getc(target);
  int i = 0;
  if(isalpha(lexeme[i]=letter)){
    int symbol;
    i++;
    while(isalnum(lexeme[i] = symbol = getc(target))) i++;
    lexeme[i] = 0;
    ungetc(symbol,target);
    if((i = iskeyword(lexeme)))return i;
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
    while((symbol=getc(target)) != '\'' || backslash)
    {
      if(symbol == EOF) return EOF;
      backslash = (!backslash && symbol == '\\');
    }

    return TEXT;
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
    while(isdigit(symbol)) symbol=getc(target);
    if(symbol=='.')
    {
      numtype = FLTP;
      while(isdigit(symbol=getc(target)));
    }
    ungetc(symbol,target);
    return numtype;
  }
  else if(symbol == '.') {
    if(isdigit(symbol=getc(target))) {
      numtype = FLTP;
      while(isdigit(symbol=getc(target)));
      ungetc(symbol,target);
      return numtype;
    }
    ungetc(symbol,target);
    symbol = '.';
  }

  ungetc(symbol,target);
  return 0;
}

  /*
   * IMPLEMENTAR PARTE EXPONENCIAL
   *
   * [E [('+'|'-')] digit {digit}
  */
int isSCIENTIFIC(FILE * target)
{
  int i = 0;

  if(toupper(lexeme[i] = getc(target)) == 'E')
  {
    i++;
    if((lexeme[i]=getc(target)) == '+' || lexeme[i] == '-')
    {
      i++;

      if(!isdigit(lexeme[i] = getc(target)))
      {
	  ungetc(lexeme[2],target);
	  ungetc(lexeme[1],target);
	  ungetc(lexeme[0],target);
	  return 0;
      }
    }

    if(isdigit(lexeme[i]))
    {
      while(isdigit(lexeme[i]=getc(target)));

      ungetc(lexeme[i],target);
      return 1;
    }
     ungetc(lexeme[1],target);
  }

  ungetc(lexeme[0],target);
  return 0;
}

int isCOLONEQ(FILE* target)
{
  int symbol = getc(target);

  if(symbol == ':')
  {
    if((symbol = getc(target)) == '=')
      return COLONEQ;

    ungetc(symbol,target);
    symbol = ':';
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
  if((token = skipspaces(target))) return token;
  if((token = isID(target))) return token;
  if((token = isNUMBER(target))){
    if(isSCIENTIFIC(target))
    {
      return FLTP;
    }
    return token;
  }
  if((token = isTEXT(target))) return token;
  if((token = isCOLONEQ(target))) return token;
  return getc(target);
}
