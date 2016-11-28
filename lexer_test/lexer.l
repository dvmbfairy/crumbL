/*
angela may xie amx@cs.utexas.edu
sarah wang sarahgw@cs.utexas.edu
*/


%{
#include "parser-defs.h"
#include "parser.tab.h"

/*
 * You may want to use this string to assemble the lexeme
 * of string constants by adding the current matched character from yytext to it.
 * You can do this as buffer += yytext;
 */
string buffer;


/*
 * You may want to track the comment nesting depth with this variable.
 */
int comment_depth = 0;

int curr_line = 1;
%}


%option noyywrap

WHITESPACE [ \t\f\r\v]+
NEWLINE [\n]
COMMA [,]
DIGIT [0-9]
LETTER [a-z]
ID [a-z_][a-z0-9_]*
PLUS [+]
MINUS [-]
STAR "*"
DIVIDE [/]
MODULO [%]
LPAREN [(]
RPAREN [)]
AND [&]
OR [|]
EQUALS [=]
LESS_THAN [<]
GREATER_THAN [>]
DOUBLE_QUOTE ["]
EXCLAMATION [!]
POUND [#]
AT [@]
DOT [.]
SEMICOLON [;]
 
%x STRING
%x COMMENT 

%%

<INITIAL>{LPAREN}{STAR} {
    comment_depth++;
    BEGIN(COMMENT);
}

<INITIAL>{STAR}{RPAREN} {
    curr_lineno = curr_line;
	SET_LEXEME(yytext);
	return TOKEN_ERROR;
}

<COMMENT>{LPAREN}{STAR} {
    comment_depth++;
}

<COMMENT>{STAR}{RPAREN} {
    comment_depth--;
    if (comment_depth == 0) {
        BEGIN(INITIAL);
    }
}

<COMMENT>. {
    /* Do nothing */
}

<COMMENT><<EOF>> {
    curr_lineno = curr_line;
	SET_LEXEME(yytext);
	return TOKEN_ERROR;
}

<INITIAL>{DOUBLE_QUOTE} {
    BEGIN(STRING);
	buffer = "";
}

<STRING>{DOUBLE_QUOTE} {
	SET_LEXEME(buffer);
    BEGIN(INITIAL);
	return TOKEN_STRING;
}

<STRING>{NEWLINE} {
    buffer += yytext;
    curr_line++;
}

<STRING>. {
    buffer += yytext;
}

<STRING><<EOF>> {
    curr_lineno = curr_line;
	SET_LEXEME(yytext);
	return TOKEN_ERROR;
}

{WHITESPACE} {
    /* Do nothing */
}

<INITIAL,COMMENT>{NEWLINE} {
    /* Do nothing, but increment line numbers */
    curr_line++;
}

{COMMA} {
    return TOKEN_COMMA;
}

print {
    return TOKEN_PRINT;
}

isnil {
    return TOKEN_ISNIL;
}

nil {
    return TOKEN_NIL;
}

if {
    return TOKEN_IF;
}

fi {
    return TOKEN_FI;
}

then {
    return TOKEN_THEN;
}

else {
    return TOKEN_ELSE;
}

func {
    return TOKEN_FUNC;
}

cnuf {
    return TOKEN_CNUF;
}

while {
    return TOKEN_WHILE;
}

do {
    return TOKEN_DO;
}

ob {
    return TOKEN_OB;
}

and {
    return TOKEN_AND;
}

or {
    return TOKEN_OR;
}

not {
    return TOKEN_NOT;
}

ret {
    return TOKEN_RET;
}

lazy {
    return TOKEN_LAZY;
}

{EQUALS} {
    return TOKEN_ASSIGN;
}

{LPAREN} {
	return TOKEN_LPAREN;
}

{RPAREN} {
	return TOKEN_RPAREN;
}

{STAR} {
    return TOKEN_TIMES;
}

{PLUS} {
    return TOKEN_PLUS;
}

{MINUS} {
    return TOKEN_MINUS;
}

{DIVIDE} {
    return TOKEN_DIVIDE;
}

{MODULO} {
    return TOKEN_MODULO;
}

{EQUALS}{EQUALS} {
    return TOKEN_EQ;
}

{EXCLAMATION}{EQUALS} {
    return TOKEN_NEQ;
}

{LESS_THAN}{EQUALS} {
    return TOKEN_LEQ;
}

{LESS_THAN} {
    return TOKEN_LT;
}

{GREATER_THAN}{EQUALS} {
    return TOKEN_GEQ;
}

{GREATER_THAN} {
    return TOKEN_GT;
}

{EXCLAMATION} {
    return TOKEN_HD;
}

{POUND} {
    return TOKEN_TL;
}

{AT} {
    return TOKEN_CONS;
}

{SEMICOLON} {
    return TOKEN_SEMICOLON;
}

{DIGIT}+ {
    SET_LEXEME(yytext);
    return TOKEN_INT;
}

{ID} {
    SET_LEXEME(yytext);
    return TOKEN_IDENTIFIER;
}

. {
  /* Leave this rule at the end of our lexer to "eat up" all illegal strings */
  	curr_lineno = curr_line;
	SET_LEXEME(yytext);
	return TOKEN_ERROR;
}
