/**@<lexer.c>::**/
#include <stdio.h>
#include <ctype.h>
#include <lexer.h>
#include <tokens.h>
#include <keywords.h>

char lexeme[BUFFER_SIZE];

int isID(FILE *target)
{
  int i = 0;
  
  if(isalpha(lexeme[i] = getc(target)))
  {
    i++;
    while(isalnum(lexeme[i] = getc(target))) i++;

    ungetc(lexeme[i],target);
    lexeme[i] = 0;
    
    if((i = iskeyword(lexeme))) return i;
    
    return ID;
  }

  ungetc(lexeme[i],target);
  return 0;
}

int isTEXT(FILE* target)
{
  int i = 0;
  lexeme[i] = getc(target);

  if(lexeme[i] == '\'')
  {
    int backslash = 0;
    i++;

    while((lexeme[i] = getc(target)) != '\'' || backslash)
    {
      if(lexeme[i] == EOF) return EOF;
      backslash = (!backslash && lexeme[i] == '\\');
      i++;
    }

    return TEXT;
  }

  ungetc(lexeme[0],target);
  return 0;
}

/* regex: ['1'-'9']['0'-'9']* | '0' */
int isNUMBER(FILE* target)
{
  int i = 0;
  lexeme[i] = getc(target);
  int numtype = UINT;

  if(isdigit(lexeme[i])) 
  {
    if(lexeme[i] == '0') 
    {
      if(lexeme[i] == '.') 
      {
        i++;
        numtype = FLTP;
        while(isdigit(lexeme[i] = getc(target)));
        ungetc(lexeme[i],target);
      }

      return numtype;
    }

    i++;
    while(isdigit(lexeme[i] = getc(target))) i++;
    
    if(lexeme[i] == '.')
    {
      numtype = FLTP;
      i++;
      while(isdigit(lexeme[i] = getc(target))) i++;
    }
    
    ungetc(lexeme[i],target);
    return numtype;
  }
  else if(lexeme[i] == '.') 
  {
    i++;
    if(isdigit(lexeme[i] = getc(target))) 
    {
      numtype = FLTP;
      i++;
      while(isdigit(lexeme[i] = getc(target))) i++;

      ungetc(lexeme[i],target);
      return numtype;
    }

    ungetc(lexeme[i],target);
  }

  ungetc(lexeme[0],target);
  return 0;
}

/* [E [('+'|'-')] digit {digit} */
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
  if((lexeme[0] = getc(target)) == ':')
  {
    if((lexeme[1] = getc(target)) == '=')
      return COLONEQ;

    ungetc(lexeme[1],target);
  }

  ungetc(lexeme[0],target);
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
