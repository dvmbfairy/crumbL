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

AstFunc* getFunc(Expression* formal, Expression* body)
{
  assert(formal->get_type() == AST_PARAMETER_LIST);
  AstParameterList* list = static_cast<AstParameterList*>(formal);
  return AstFunc::make(list, body);
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
%left TOKEN_PLUS TOKEN_MINUS TOKEN_CONCAT
%left TOKEN_TIMES TOKEN_DIVIDE TOKEN_MODULO
%nonassoc TOKEN_ISNIL
%right TOKEN_CONS
%nonassoc TOKEN_HD TOKEN_TL
%nonassoc TOKEN_NOT

%%


program: %empty {
  $$ = NULL;
}
|
program statement
{
  Expression* first = $1;
  Expression* next = $2;
  if (first == NULL) {
    res_expr = $2;
    $$ = $2;
  } else {
    Expression* last = first;
    while (last -> get_next_exp() != NULL) {
      last = last -> get_next_exp();
    }
    last -> set_next_exp(next);
    $$ = $1;
  }
}


statement:
TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON
{
  $$ = AstAssign::make(getIdentifier($1), $3);
}
|
TOKEN_PRINT TOKEN_LPAREN expression TOKEN_RPAREN TOKEN_SEMICOLON
{
  $$ = AstUnOp::make(PRINT, $3);
}
|
TOKEN_IF TOKEN_LPAREN conditional TOKEN_RPAREN TOKEN_THEN program TOKEN_ELSE program TOKEN_FI
{
  $$ = AstBranch::make($3, $6, $8);
}



expression:
TOKEN_INT 
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
expression TOKEN_MINUS expression 
{
  $$ = AstBinOp::make(MINUS, $1, $3);
}
|
expression TOKEN_TIMES expression 
{
  $$ = AstBinOp::make(TIMES, $1, $3);
}
|
expression TOKEN_DIVIDE expression 
{
  $$ = AstBinOp::make(DIVIDE, $1, $3);
}
|
expression TOKEN_MODULO expression 
{
  $$ = AstBinOp::make(MODULO, $1, $3);
}
|
expression TOKEN_CONS expression 
{
  $$ = AstBinOp::make(CONS, $1, $3);
}
|
expression TOKEN_CONCAT expression 
{
  $$ = AstBinOp::make(CONCAT, $1, $3); 
}
|
TOKEN_HD expression
{
  $$ = AstUnOp::make(HD, $2);
}
|
TOKEN_TL expression
{
  $$ = AstUnOp::make(TL, $2);
}
|
TOKEN_NIL
{
  $$ = AstNil::make();
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


conditional:
expression TOKEN_EQ expression 
{
  $$ = AstBinOp::make(EQ, $1, $3);
}
|
expression TOKEN_NEQ expression 
{
  $$ = AstBinOp::make(NEQ, $1, $3);
}
|
expression TOKEN_LT expression 
{
  $$ = AstBinOp::make(LT, $1, $3);
}
|
expression TOKEN_LEQ expression 
{
  $$ = AstBinOp::make(LEQ, $1, $3);
}
|
expression TOKEN_GT expression 
{
  $$ = AstBinOp::make(GT, $1, $3);
}
|
expression TOKEN_GEQ expression 
{
  $$ = AstBinOp::make(GEQ, $1, $3);
}
|
TOKEN_NOT conditional
{
  $$ = AstUnOp::make(NOT, $2);
}
|
conditional TOKEN_AND conditional 
{
  $$ = AstBinOp::make(AND, $1, $3);
}
|
conditional TOKEN_OR conditional 
{
  $$ = AstBinOp::make(OR, $1, $3);
}
