INCLUDEDIR=./
CFLAGS=-g -I$(INCLUDEDIR)

objs=		main.o\
		lexer.o\
		keywords.o\
		parser.o\
		pseudocode.o\
		symtab.o

mypas: $(objs)
	$(CC) -o $@  $^

clean:
	$(RM) $(objs)

mostlyclean: clean
	$(RM) *~
