%{
#include "parser-defs.h"

/*
 * Dummy parser to output tokens for PA1
 */

int yylex();
extern int yy_scan_string(const char* c);
int yyerror(const char* p)
{ 
  if(parser_error_fn != NULL) {
    parser_error_fn("At line " + int_to_string(curr_lineno) + ": " + string(p));
  }
  return 1;
};

 



%}
/* BISON Declarations */
%token 
TOKEN_READSTRING 
TOKEN_READINT 
TOKEN_PRINT 
TOKEN_ISNIL
TOKEN_HD 
TOKEN_TL 
TOKEN_CONS 
TOKEN_NIL 
TOKEN_CONCAT
TOKEN_PLUS 
TOKEN_MINUS 
TOKEN_IDENTIFIER 
TOKEN_TIMES 
TOKEN_DIVIDE 
TOKEN_INT
TOKEN_LPAREN 
TOKEN_RPAREN 
TOKEN_AND 
TOKEN_OR 
TOKEN_EQ 
TOKEN_NEQ 
TOKEN_GT 
TOKEN_GEQ 
TOKEN_LT 
TOKEN_LEQ 
TOKEN_IF 
TOKEN_THEN 
TOKEN_ELSE 
TOKEN_COMMA 
TOKEN_STRING 
TOKEN_ERROR 
TOKEN_FI
TOKEN_FUNC
TOKEN_CNUF
TOKEN_WHILE
TOKEN_DO
TOKEN_OB
TOKEN_NOT
TOKEN_RET
TOKEN_ASSIGN
TOKEN_MODULO
TOKEN_SEMICOLON
TOKEN_LAZY





%%




input:   
input TOKEN_READSTRING
{
	cout << "TOKEN_READSTRING" << endl;
}
|
input TOKEN_READINT
{
	cout << "TOKEN_READINT" << endl;
}
|
input TOKEN_PRINT 
{
	cout << "TOKEN_PRINT" << endl;
}
|
input TOKEN_ISNIL
{
	cout << "TOKEN_ISNIL" << endl;
}
|
input TOKEN_HD
{
	cout << "TOKEN_HD" << endl;
}
| 
input TOKEN_TL 
{
	cout << "TOKEN_TL" << endl;
}
|
input TOKEN_CONS
{
	cout << "TOKEN_CONS" << endl;
}
|
input TOKEN_NIL
{
	cout << "TOKEN_NIL" << endl;
}
|
input TOKEN_CONCAT
      {
      cout << "TOKEN_CONCAT" << endl;
      }

|
input TOKEN_PLUS
      {
      cout << "TOKEN_PLUS" << endl;
      }
  | 
 input TOKEN_MINUS
      {
      cout << "TOKEN_MINUS" << endl;
      }
|
input TOKEN_IDENTIFIER
{
	string lexeme = GET_LEXEME($2);
	cout << "TOKEN_IDENTIFIER: " << lexeme << endl;
}
| 
 input TOKEN_TIMES
      {
      cout << "TOKEN_TIMES" << endl;
      }
|
 input TOKEN_DIVIDE
      {
      cout << "TOKEN_DIVIDE" << endl;
      }
|
input TOKEN_INT 
{
	string lexeme = GET_LEXEME($2);
	cout << "TOKEN_INT: " << lexeme << endl;
}
|
input TOKEN_LPAREN
{
	cout << "TOKEN_LPAREN" << endl;
}
|
input TOKEN_RPAREN 
{
	cout << "TOKEN_RPAREN" << endl;
}
|
input TOKEN_AND 
{
	cout << "TOKEN_AND" << endl;
}
|
input TOKEN_OR 
{
	cout << "TOKEN_OR" << endl;
}
|
input TOKEN_EQ 
{
	cout << "TOKEN_EQ" << endl;
}
| input TOKEN_NEQ 
{
	cout << "TOKEN_NEQ" << endl;
}
|
input TOKEN_GT
{
	cout << "TOKEN_GT" << endl;
}
|
input TOKEN_GEQ
{
	cout << "TOKEN_GEQ" << endl;
}
|
input TOKEN_LT
{
	cout << "TOKEN_LT" << endl;
}
|
input TOKEN_LEQ
{
	cout << "TOKEN_LEQ" << endl;
}
|
input TOKEN_IF 
{
	cout << "TOKEN_IF" << endl;
}
| 
input TOKEN_THEN
{
	cout << "TOKEN_THEN" << endl;
}
| 
input TOKEN_ELSE
{
	cout << "TOKEN_ELSE" << endl;
}
|
input TOKEN_COMMA
{
	cout << "TOKEN_COMMA" << endl;
}
|
input TOKEN_STRING
{
	string lexeme = GET_LEXEME($2);
	cout << "TOKEN_STRING: " << lexeme << endl;
}
|
input TOKEN_FI {
    cout << "TOKEN_FI" << endl;
}
|
input TOKEN_FUNC {
    cout << "TOKEN_FUNC" << endl;
}
|
input TOKEN_CNUF {
    cout << "TOKEN_CNUF" << endl;
}
|
input TOKEN_WHILE {
    cout << "TOKEN_WHILE" << endl;
}
|
input TOKEN_DO {
    cout << "TOKEN_DO" << endl;
}
|
input TOKEN_OB {
    cout << "TOKEN_OB" << endl;
}
|
input TOKEN_NOT {
    cout << "TOKEN_NOT" << endl;
}
|
input TOKEN_RET {
    cout << "TOKEN_RET" << endl;
}
|
input TOKEN_ASSIGN {
    cout << "TOKEN_ASSIGN" << endl;
}
|
input TOKEN_MODULO {
    cout << "TOKEN_MODULO" << endl;
}
|
input TOKEN_SEMICOLON {
    cout << "TOKEN_SEMICOLON" << endl;
}
|
input TOKEN_LAZY {
    cout << "TOKEN_LAZY" << endl;
}
|
input TOKEN_ERROR
      {
    
      yyerror("Lexing Error");
      YYERROR;
      }

| 
{

}
