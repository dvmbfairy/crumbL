/* Carolyn Tran - carolyn.tran@outlook.com,
   Raymond Chee - rjchee@utexas.edu */

%{
#include "parser-defs.h"

int yylex();
extern int yy_scan_string(const char* c);
int yyerror(const char* p)
{ 
  if(parser_error_fn != NULL) {
    parser_error_fn("At line " + int_to_string(curr_lineno) + ": " + string(p));
  }
  return 1;
};

AstIdentifier* getIdentifier(Expression* token)
{
  string lexeme = GET_LEXEME(token);
  return AstIdentifier::make(lexeme);
}

%}
/* BISON Declarations */
%token 
TOKEN_IF
TOKEN_LPAREN
TOKEN_RPAREN
TOKEN_THEN
TOKEN_ELSE
TOKEN_FI
TOKEN_ASSIGN
TOKEN_SEMICOLON
TOKEN_WHILE
TOKEN_DO
TOKEN_OB
TOKEN_PRINT
TOKEN_FUNC
TOKEN_IDENTIFIER
TOKEN_COMMA
TOKEN_RET
TOKEN_CNUF
TOKEN_PLUS
TOKEN_MINUS
TOKEN_TIMES
TOKEN_DIVIDE
TOKEN_MODULO
TOKEN_CONS
TOKEN_CONCAT
TOKEN_HD
TOKEN_TL
TOKEN_INT
TOKEN_STRING
TOKEN_NIL
TOKEN_LT
TOKEN_LEQ
TOKEN_GEQ
TOKEN_GT
TOKEN_EQ
TOKEN_NEQ
TOKEN_NOT
TOKEN_AND
TOKEN_OR
TOKEN_ISNIL
TOKEN_ERROR



%nonassoc EXPR
%nonassoc TOKEN_ELSE
%nonassoc TOKEN_PRINT
%left TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_GT TOKEN_LEQ TOKEN_GEQ
%left TOKEN_AND TOKEN_OR
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_TIMES TOKEN_DIVIDE
%nonassoc TOKEN_ISNIL
%right TOKEN_CONS
%nonassoc TOKEN_HD TOKEN_TL


%%


program: %empty {}
|
program statement
{
  Expression* first = $1;
  Expression* next = $2;
  if (first == NULL) {
    res_expr = $2;
  } else {
    first -> set_next_exp(next);
  }
  $$ = $2;
}

statement:
TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON
{
  $$ = AstAssign::make(getIdentifier($1), $3);
}

expression: TOKEN_INT 
{
  	string lexeme = GET_LEXEME($1);
  	long int val = string_to_int(lexeme);
  	Expression* e = AstInt::make(val);
  	$$ = e;
}
|
TOKEN_STRING 
{
  string lexeme = GET_LEXEME($1);
    Expression* e = AstString::make(lexeme);
    $$ = e;
}
|
TOKEN_IDENTIFIER
{
  $$ = getIdentifier($1);
}
|
expression TOKEN_PLUS expression 
{
  $$ = AstBinOp::make(PLUS, $1, $3);
}
|
TOKEN_ERROR 
{
   // do not change the error rule
   string lexeme = GET_LEXEME($1);
   string error = "Lexing error: ";
   if(lexeme != "") error += lexeme;
   yyerror(error.c_str());
   YYERROR;
}