CC = g++
CFLAGS = -g -Wall -std=c++0x
INC=-. ./ast
INC_PARAMS=$(foreach d, $(INC), -I$d)

OBJs =   Expression.o SymbolTable.o frontend.o AstRead.o AstNil.o AstList.o AstUnOp.o AstBranch.o AstExpressionList.o AstIdentifierList.o AstBinOp.o  AstIdentifier.o AstInt.o AstLambda.o AstLet.o AstString.o
LEXER_OBJS = lex.yy.o
PARSER_OBJS = lex.yy.o parser.tab.o
INTERPRETER_OBJS = lex.yy.o parser.tab.o

default: parser

lexer: ${LEXER_OBJS} ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${LEXER_OBJS} ${OBJs} -o lexer -lfl

lex.yy.c: lexer.l parser-defs.h
	flex -i lexer.l

parser: ${PARSER_OBJS} ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${PARSER_OBJS} ${OBJs} -o parser -lfl

interpreter: ${INTERPRETER_OBJS} ${OBJS}
	${CC} ${CFLAGS} ${INC_PARAMS} ${INTERPRETER_OBJS} ${OBJs} -o interpreter -lfl

frontend.o:	frontend.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c frontend.cpp
	
SymbolTable.o:	SymbolTable.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c SymbolTable.cpp 

Expression.o:	ast/*.h ast/*.cpp #ast/Expression.cpp ast/Expression.h ast/AstString.cpp ast/AstString.h
	${CC} ${CFLAGS} ${INC_PARAMS} -c ast/*.cpp 


clean:
	rm -f l-type-inference  *.o  parser.output

depend:
	makedepend -I. *.c
