/**@<parser.c>::**/

#include <parser.h>
#include "../Compiladores/MyPas_integral/keywords.h"
#include "../../projects/Aula121614-03/parser.h"
#include <string.h>

/* MyPas:: My very simplified Pascal */

/* LL(1)-Grammar:
 * 
 * mypas -> programID declarations blockstmt '.'
 * 
 * programID -> [ PROGRAM ID ';' ]
 * 
 * declarations -> varspecs sbpspecs
 * 
 * varspecs -> { VAR ID {',' ID} ':' typespec ';' }
 * 
 * typespec -> INTEGER | BOOLEAN | REAL | DOUBLE | CHAR | STRING
 *           | ARRAY '[' decimal { ',' decimal } ']' of typespec
 * 
 * sbpspecs -> FUNCTION ID [ '(' parmlist ')' ] : typespec ';' declarations blockstmt ';'
 *           | PROCEDURE ID [ '(' parmlist ')' ] ';' declarations blockstmt ';'
 * 
 * parmlist -> formparm { ';' formparm }
 * 
 * formparm -> [ VAR ] ID {',' ID} ':' typespec
 * 
 * 
 * blockstmt -> BEGIN stmtlist END
 * 
 * stmtlist -> stmt { ';' stmt }
 * 
 * stmt -> blockstmt | ifstmt | whilestmt | repstmt | idstmt
 * 
 * ifstmt -> IF expr THEN stmt [ ELSE stmt ]
 * 
 * expr -> simpexpr [ relop simpexpr ]
 * 
 * relop = '>'['='] | '<'[ ['='|'>'] ] | '='
 * 
 * simpexpr -> negate term { addop term }
 * 
 * negate -> [ '-' | NOT ]
 * 
 * addop -> '+' | '-' | OR
 * 
 * term -> fact { mulop fact }
 * 
 * mulop -> '*' | '/' | DIV | MOD | AND
 * 
 * fact -> constant | idstmt | '(' expr ')'
 * 
 * constant -> num | string | TRUE | FALSE | NULL | char
 * 
 * char -> \'[.]\'
 * 
 * num -> decimal | fltpoint
 * 
 * decimal -> '0' | ['1'-'9']{digit}
 * 
 * fltpoint -> decimal E [ ['+'|'-'] ] digit {digit} 
 *           | (decimal [ '.' {dgigit} ] | '.'digit {digit})  [ E [ ['+'|'-'] ] digit {digit} ]
 * 
 * digit -> ['0'-'9']
 * 
 * string -> \' {[^\']} \'
 * 
 * whilestmt -> WHILE expr DO stmt
 * 
 * repstmt -> REPEAT stmtlist UNTIL expr
 * 
 * idstmt -> assgmnt | procedcall
 * 
 * assgmnt -> variable ":=" expr
 * 
 * variable -> ID { '[' exprlist ']' }
 * 
 * exprlist -> expr { ',' expr }
 * 
 * procedcall -> ID [ '(' exprlist ')' ]
 * 
 */ 


/* mypas -> programID declarations blockstmt '.' */
void mypas (void) 
{
  programID();
  declarations();
  blockstmt();
  match('.');
}
/* programID -> [ PROGRAM ID ';' ] */
void programID (void)
{
  if(lookahead==PROGRAM){
    match (PROGRAM); match (ID); match (';');
}
/* declarations -> varspecs sbpspecs */
void declarations(void)
{
  varspecs(); sbpspecs();
}
/* varspecs -> { VAR ID {',' ID} ':' typespec ';' } */
void varspecs(void)
{
  while(lookahead==VAR){
    match(VAR);match(ID);
    while(lookahead==','){
      match(','); match(ID);
    }
    match(':');typespec();match(';');
  }
}
/* typespec -> INTEGER | BOOLEAN | REAL | DOUBLE | CHAR | STRING
 *           | ARRAY '[' decimal { ',' decimal } ']' OF typespec
 */
void typespec(void)
{
  switch(lookahead){
    case INTEGER: 
    case BOOLEAN: 
    case REAL: 
    case DOUBLE: 
    case CHAR: 
    case STRING:
      lookahead = gettoken(target);
      break;
    case ARRAY:
      match(ARRAY);match('[');
      decimal(); 
      while(lookahead==',') {
        match(','); decimal();
      }
      match(']');
      match(OF); 
      typespec();
  }
}
/* sbpspecs -> FUNCTION ID [ '(' parmlist ')' ] : typespec ';' declarations blockstmt ';'
 *           | PROCEDURE ID [ '(' parmlist ')' ] ';' declarations blockstmt ';'
 * 
 * parmlist -> formparm { ';' formparm }
 * 
 * formparm -> [ VAR ] ID {',' ID} ':' typespec
 * 
 * 
 * blockstmt -> BEGIN stmtlist END
 * 
 * stmtlist -> stmt { ';' stmt }
 * 
 * stmt -> blockstmt | ifstmt | whilestmt | repstmt | idstmt
 * 
 * ifstmt -> IF expr THEN stmt [ ELSE stmt ]
 * 
 * expr -> simpexpr [ relop simpexpr ]
 * 
 * relop = '>'['='] | '<'[ ['='|'>'] ] | '='
 * 
 * simpexpr -> negate term { addop term }
 * 
 * negate -> [ '-' | NOT ]
 * 
 * addop -> '+' | '-' | OR
 * 
 * term -> fact { mulop fact }
 * 
 * mulop -> '*' | '/' | DIV | MOD | AND
 * 
 * fact -> constant | idvalue | '(' expr ')'
 * 
 /* constant -> num | string | TRUE | FALSE | NIL | char*/
 void constant(void)
 {
   switch(lookahead)
   {
     case TRUE:
       match(TRUE);
   }
 }
 
 /* character -> \'[.]\'*/ 
 void character(void)
 {
   match('\'');
   
   if(strlen(lookahead)==1) match(lookahead);
   
   match('\'');
 }
 
 /* num -> decimal | fltpoint */
 void num(void)
 {
   
 }
 
 /* decimal -> '0' | ['1'-'9']{digit}*/ 
 /*fltpoint -> decimal E [ ['+'|'-'] ] digit {digit} 
 *           | (decimal [ '.' {dgigit} ] | '.'digit {digit})  [ E [ ['+'|'-'] ] digit {digit} ] */
 void fltpoint(void)
 {
   
 }

 /*digit -> ['0'-'9']*/ 
 void digit(void)
 {
   if(lookahead>='0' && lookahead<='9')
     match(lookahead);
 }
 
 /* string -> \' {[^\']} \' */
 void string(void)
 {
   match('\'');
   
   while(lookahead != '\'')
     match(lookahead);
   
   match('\'');
 }
 
 /* whilestmt -> WHILE expr DO stmt */
 void whilestmt(void)
 {
   match(WHILE); expr(); match(DO); stmt();
 }
 
 /* repstmt -> REPEAT stmtlist UNTIL expr */
 void repstmt(void)
 {
   match(REPEAT); stmtlist(); match(UNTIL); expr();
 }
 
 /* idstmt -> assgmnt | procedcall */
void idstmt(void)
{
  int isarray = 0;
  match(ID);
  isarray = (lookahead == '[');
  while(lookahead=='['){
    match('['); exprlist(); match(']');
  }
  if(lookahead==COLONEQ){
    match(COLONEQ); expr();
  } else if (isarray == 0 && lookahead == '('){
    match('('); exprlist(); match(')');
  } else if (isarray) {
    match(COLONEQ);
  }
}
void idvalue(void)
{
  int isarray = 0;
  match(ID);
  isarray = (lookahead == '[');
  while(lookahead=='['){
    match('['); exprlist(); match(']');
  }
  if(lookahead==COLONEQ){
    match(COLONEQ); expr();
  } else if (isarray == 0 && lookahead == '('){
    match('('); exprlist(); match(')');
  }
}
/* exprlist -> expr { ',' expr } */
void exprlist(void)
{
  expr();
  while(lookahead==','){
    match(',');expr();
  }
}