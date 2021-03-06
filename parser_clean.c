/**@<parser.c>::**/
#include <parser.h>
#include <string.h>
#include <tokens.h>
#include <keywords.h>
#include <stdlib.h>
#include <lexer.h>

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
 *
 * sbpspecs -> FUNCTION ID [ '(' parmlist ')' ] : typespec ';' declarations blockstmt ';'
 *           | PROCEDURE ID [ '(' parmlist ')' ] ';' declarations blockstmt ';'
 *
 * parmlist -> formparm { ';' formparm }
 *
 * formparm -> [ VAR ] ID {',' ID} ':' typespec
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
 * constant -> number | TEXT | TRUE | FALSE
 *
 * number -> UINT | FLTP
 *
 * whilestmt -> WHILE expr DO stmt
 *
 * repstmt -> REPEAT stmtlist UNTIL expr
 *
 * idstmt -> assgmnt | procedcall
 *
 * assgmnt -> variable ':=' expr
 *
 * variable -> ID { '[' exprlist ']' }
 *
 * exprlist -> expr { ',' expr }
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
}

/* declarations -> varspecs sbpspecs */
void declarations (void)
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

/* typespec -> INTEGER | BOOLEAN | REAL | DOUBLE | CHAR | STRING */

int typespec(void)
{
    switch(lookahead){
    case INTEGER:
    case BOOLEAN:
    case REAL:
    case DOUBLE:
    case CHAR:
    case STRING:
      match(lookahead);
      return 1;
    }
    return 0;
}

/* formparm -> [ VAR ] ID {',' ID} ':' typespec */
void formparm(void)
{
  if (lookahead == VAR){
    match(VAR);
  }
  match(ID);
  while(lookahead == ','){
    match(',');
    match(ID);
  }
  match(':');
  typespec();
}

/* parmlist -> formparm { ';' formparm } formparm */
void parmlist(void)
{
  formparm();
  while(lookahead == ','){
    match(',');
    formparm();
  }
}

/* sbpspecs -> FUNCTION ID [ '(' parmlist ')' ] : typespec ';' declarations blockstmt ';'
 *           | PROCEDURE ID [ '(' parmlist ')' ] ';' declarations blockstmt ';'
 */
void sbpspecs(void)
{
  int isfunction = (lookahead == FUNCTION);
  switch(lookahead){
    case FUNCTION: case PROCEDURE:
      match(lookahead);
      match(ID);
        if(lookahead == '(')
        {
	         match('(');
  	       parmlist();
	         match(')');
        }
        if(isfunction)
        {
	       match(':');
	       if(!isbuiltin())
         {
	         match(0);
	       }
      }
      match(';');
      declarations();
      blockstmt();
      match(';');
  }
}

 /*
 * blockstmt -> BEGIN stmtlist END
 */

void blockstmt(void)
{
  match(BEGIN);
  stmtlist();
  match(END);
}

 /* stmtlist -> stmt { ';' stmt }
 */
void stmtlist()
{
  stmt();
  while(lookahead == ';'){
    match(';');
    stmt();
  }
}

 /* stmt -> blockstmt | ifstmt | whilestmt | repstmt | idstmt
 */
void stmt()
{
  switch(lookahead){
    case BEGIN:
      blockstmt();
      break;
    case IF:
      ifstmt();
      break;
    case WHILE:
      whilestmt();
      break;
    case REPEAT:
      repstmt();
      break;
    case ID:
      idstmt();
  }
}

 /* ifstmt -> IF expr THEN stmt [ ELSE stmt ]
 */
void ifstmt(void)
{
  match(IF);
  expr();
  match(THEN);
  stmt();
  if(lookahead == ELSE){
    match(ELSE);
    stmt();
  }
}

 /* expr -> simpexpr [ relop simpexpr ]
 */
void expr(void)
{
  simpexpr();
  if(isrelop()){
    simpexpr();
  }
}

 /* relop = '>'['='] | '<'[ ['='|'>'] ] | '='
 */
int isrelop(void)
{
  switch(lookahead){
    case '>':
      match('>');
      if(lookahead == '=')
      {
            match('=');
      }
      break;
    case '<':
      match('<');
      if(lookahead == '=' || lookahead == '>')
      {
        match(lookahead);
      }
      break;
    case '=':
      match('=');
      break;
    default:
      return 0;
  }
  return 1;
}

 /* simpexpr -> negate term { addop term }
 */
void simpexpr(void)
{
  negate();
  term();
  while(isaddop()){
    term();
  }
}

 /* negate -> [ '-' | NOT ]
 */
void negate(void)
{
  switch(lookahead){
    case '-':
    case NOT:
      match(lookahead);
  }
}

 /* addop -> '+' | '-' | OR
 */
int isaddop(void)
{
  switch(lookahead){
    case '+':
    case '-':
    case OR:
      do_operation(lookahead);
      match(lookahead);
      return 1;
  }
  return 0;
}

 /* term -> fact { mulop fact }
 */
void term(void)
{
  fact();
  while(ismulop()){
    fact();
  }
}

/* mulop -> '*' | '/' | DIV | MOD | AND
 */
int ismulop(void)
{
  switch(lookahead){
    case '*':
    case '/':
    case DIV:
    case MOD:
    case AND:
      do_operation(lookahead);
      match(lookahead);
      return 1;
  }
  return 0;
}
 /* fact -> constant | idvalue | '(' expr ')'
 */
void fact(void){
  switch(lookahead){
    case ID:
      idvalue();
      break;
    case '(':
      match('(');
      expr();
      match(')');
      break;
    default:
      constant();
  }
}

 /* constant -> number | TEXT | TRUE | FALSE*/
 void constant(void)
 {
   switch(lookahead)
   {
     case TRUE:
     case FALSE:
     case TEXT:
       match(lookahead);
       break;
     default:
       number();
   }
 }

 /* number -> (UINT|FLTP) */
 void number(void)
 {
   switch(lookahead)
   {
     case UINT:
       match(UINT);
       break;
     default:
       match(FLTP);
   }
 }

 /*digit -> ['0'-'9']*/
 void digit(void)
 {
   if(lookahead>='0' && lookahead<='9')
     match(lookahead);
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
  match(ID);

  if (lookahead == COLONEQ)
  {
    match(COLONEQ); expr();
  }
  else if (lookahead == '(')
  {
    match('('); exprlist(); match(')');
  }
}

void idvalue(void)
{
  match(ID);

  if(lookahead==COLONEQ)
  {
    match(COLONEQ); expr();
  }
  else if (lookahead == '(')
  {
    match('('); exprlist(); match(')');
  }
}

/* exprlist -> expr { ',' expr } */
void exprlist(void)
{
  expr();
  while(lookahead == ','){
    match(',');expr();
  }
}

/** lexer-to-parser interface **/
int lookahead;

void match(int expected_token)
{
  if(lookahead == expected_token) {
    lookahead = gettoken(target);
  } else {
    fprintf(stderr,"token mismatch ... expected %i \"%s\" but got \"%s\" ... exiting.\n",expected_token, getkeyword(expected_token), lexeme);
    exit(ILEGALTOKEN);
  }
}

void start()
{
  lookahead = gettoken(target);

  mypas();
}
