/**@<keywords.c>::**/
#include <string.h>
#include <keywords.h>

char *keyword[]={
  "begin",
  "if",
  "then",
  "else",
  "while",
  "do",
  "repeat",
  "until",
  "of",
  "var",
  "array",
  "integer",
  "real",
  "double",
  "char",
  "string",
  "boolean",
  "program",
  "procedure",
  "function",
  "div",
  "mod",
  "or",
  "and",
  "not",
  "true",
  "false",
  "null",
  "end"
};

int iskeyword(char const *identifier)
{
  int token;
  for(token=BEGIN;token<END;token++){
    if(strcmp(keyword[token-BEGIN],identifier)==0)return token;
  }
  return 0;
}

const char * getkeyword(int id)
{
  int token;
  for(token=BEGIN;token<END;token++){
    if (token == id)
    {
      return keyword[token - BEGIN];
    }
  }
  return "";
}