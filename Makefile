CC = g++
CFLAGS = -g -Wall -std=c++0x
INC=-. ./ast
INC_PARAMS=$(foreach d, $(INC), -I$d)

OBJs =   parser.tab.o lex.yy.o Expression.o SymbolTable.o frontend.o Evaluator.o AstNil.o AstList.o AstUnOp.o AstBranch.o AstFunctionCall.o AstFunc.o AstWhile.o AstAssign.o AstCallList.o AstParameterList.o AstBinOp.o  AstIdentifier.o AstInt.o AstString.o


default: lexer parser interpreter

lexer: ${OBJs}
	cp lexer.l lexer_test/lexer.l && cd lexer_test && make && cp lexer ../

lex.yy.c: lexer.l parser-defs.h
	flex -i lexer.l

parser: ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o parser -lfl

parser.tab.c: parser.y parser-defs.h
	bison -dv parser.y

interpreter: ${OBJS}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o crumbl-interpreter -lfl


operational_semantics.pdf: operational_semantics.tex
	pdflatex operational_semantics.tex

pdf: operational_semantics.pdf
	xpdf operational_semantics.pdf

frontend.o:	frontend.cpp Evaluator.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c frontend.cpp Evaluator.cpp
	
SymbolTable.o:	SymbolTable.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c SymbolTable.cpp 

Expression.o:	ast/*.h ast/*.cpp #ast/Expression.cpp ast/Expression.h ast/AstString.cpp ast/AstString.h
	${CC} ${CFLAGS} ${INC_PARAMS} -c ast/*.cpp 

# test lexer: run the test for the lexer
tl: lexer
	./lexer test.L

# test parser: run the test for the parser
tp: parser
	./parser -ast test.L

# test interpreter: run the test for the interpreter
ti: interpreter
	./crumbl-interpreter test.L

clean:
	rm -f crumbl-interpreter lexer lex.yy.c parser *.o parser.tab.[ch] parser.output *.aux *.log

depend:
	makedepend -I. *.c
