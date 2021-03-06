/**@<keywords.h>::**/

enum {
  BEGIN = 16384,
  IF,
  THEN,
  ELSE,
  WHILE,
  DO,
  REPEAT,
  UNTIL,
  OF,
  VAR,
  ARRAY,
  INTEGER,
  REAL,
  DOUBLE,
  CHAR,
  STRING,
  BOOLEAN,
  PROGRAM,
  PROCEDURE,
  FUNCTION,
  DIV,
  MOD,
  OR,
  AND,
  NOT,
  TRUE,
  FALSE,
  END
};


int iskeyword(const char *identifier);
const char * getkeyword(int id);