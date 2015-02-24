/**@<keywords.c>::**/
#include <string.h>
#include <keywords.h>
#include <tokens.h>

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
  "end"
};

char *type[] = {
  "id", 
  "unsigned integer",
  "floating point",
  "text",
  ":="
};


char * gettypes(int id){
  int token;
  for (token = ID; token < COLONEQ; token++){
    if(token == id){
      return type[token - ID];
    }
  }
  return "keyword-not-found";
}

int iskeyword(char const *identifier)
{
  int token;
  for(token=BEGIN;token<=END;token++){
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
  return gettypes(id);
}
