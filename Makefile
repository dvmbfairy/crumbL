CC = g++
CFLAGS = -g -Wall -std=c++0x
INC=-. ./ast
INC_PARAMS=$(foreach d, $(INC), -I$d)

OBJs =   parser.tab.o lex.yy.o Expression.o SymbolTable.o frontend.o AstNil.o AstList.o AstUnOp.o AstBranch.o AstAssign.o AstIdentifierList.o AstBinOp.o  AstIdentifier.o AstInt.o AstString.o

default: parser

lexer: ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o lexer -lfl

lex.yy.c: lexer.l parser-defs.h
	flex -i lexer.l

parser: ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o parser -lfl

parser.tab.c: parser.y parser-defs.h
	bison -dv parser.y

interpreter: ${OBJS}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o crumbl-interpreter -lfl

frontend.o:	frontend.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c frontend.cpp
	
SymbolTable.o:	SymbolTable.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c SymbolTable.cpp 

Expression.o:	ast/*.h ast/*.cpp #ast/Expression.cpp ast/Expression.h ast/AstString.cpp ast/AstString.h
	${CC} ${CFLAGS} ${INC_PARAMS} -c ast/*.cpp 

tp:
	./parser -ast test.L

clean:
	rm -f crumbl-interpreter lexer parser *.o parser.tab.[ch] parser.output

depend:
	makedepend -I. *.c
