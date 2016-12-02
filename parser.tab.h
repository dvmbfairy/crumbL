/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_IF = 258,
    TOKEN_LPAREN = 259,
    TOKEN_RPAREN = 260,
    TOKEN_THEN = 261,
    TOKEN_ELSE = 262,
    TOKEN_FI = 263,
    TOKEN_ASSIGN = 264,
    TOKEN_SEMICOLON = 265,
    TOKEN_WHILE = 266,
    TOKEN_DO = 267,
    TOKEN_OB = 268,
    TOKEN_PRINT = 269,
    TOKEN_READSTRING = 270,
    TOKEN_READINT = 271,
    TOKEN_FUNC = 272,
    TOKEN_IDENTIFIER = 273,
    TOKEN_COMMA = 274,
    TOKEN_RET = 275,
    TOKEN_CNUF = 276,
    TOKEN_PLUS = 277,
    TOKEN_MINUS = 278,
    TOKEN_TIMES = 279,
    TOKEN_DIVIDE = 280,
    TOKEN_MODULO = 281,
    TOKEN_CONS = 282,
    TOKEN_CONCAT = 283,
    TOKEN_HD = 284,
    TOKEN_TL = 285,
    TOKEN_INT = 286,
    TOKEN_STRING = 287,
    TOKEN_NIL = 288,
    TOKEN_LT = 289,
    TOKEN_LEQ = 290,
    TOKEN_GEQ = 291,
    TOKEN_GT = 292,
    TOKEN_EQ = 293,
    TOKEN_NEQ = 294,
    TOKEN_NOT = 295,
    TOKEN_AND = 296,
    TOKEN_OR = 297,
    TOKEN_ISNIL = 298,
    TOKEN_ERROR = 299,
    TOKEN_LAZY = 300,
    EXPR = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
