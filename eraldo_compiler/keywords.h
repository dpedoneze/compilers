/**@<keywords.h>::**/

enum {
    BEGIN = 0x10000,
    IF,
    THEN,
    ELSE,
    WHILE,
    DO,
    REPEAT,
    UNTIL,
    DIV,
    MOD,
    OR,
    AND,
    NOT,
    TRUE,
    FALSE,
    PROGRAM,
    VAR,
    INTEGER,
    REAL,
    DOUBLE,
    CHAR,
    TEXT,
    BOOLEAN,
    ARRAY,
    OF,
    PROCEDURE,
    FUNCTION,
    WRITE,
    WRITELN,
    READLN,
    END
};

extern char *keyword[];
int iskeyword(char const *identifier);