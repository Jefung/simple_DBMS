/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SQL_GRAM_TAB_H_INCLUDED
# define YY_YY_SQL_GRAM_TAB_H_INCLUDED
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
    TK_CREATE = 10001,
    TK_TABLE = 10002,
    TK_DROP = 10003,
    TK_INSERT = 10004,
    TK_INTO = 10005,
    TK_VALUE = 10006,
    TK_DELETE = 10007,
    TK_FROM = 10008,
    TK_WHERE = 10009,
    TK_UPDATE = 10010,
    TK_SET = 10011,
    TK_INDEX = 10012,
    TK_ON = 10013,
    TK_SELECT = 10014,
    TK_INT = 10015,
    TK_CHAR = 10016,
    NUM = 10036,
    STR = 10037,
    ID = 10038,
    TK_IS = 10017,
    TK_NULL = 10018,
    TK_NOT = 10019,
    TK_OR = 10021,
    TK_AND = 10020,
    TK_GTR = 10022,
    TK_LSS = 10023,
    TK_EQU = 10024,
    TK_LEQ = 10025,
    TK_GEQ = 10026,
    TK_ADD = 10027,
    TK_SUB = 10028,
    TK_MUL = 10029,
    TK_DIV = 10030,
    UMINUS = 10040,
    TK_LP = 10031,
    TK_RP = 10032,
    TK_COMMA = 10033,
    TK_PERIOD = 10034,
    TK_SEMICOLON = 10035
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "sql_gram.y" /* yacc.c:1909  */

	char str[100];
	int num;

#line 101 "sql_gram.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SQL_GRAM_TAB_H_INCLUDED  */
