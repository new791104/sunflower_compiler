/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_SUNFLOWER_TAB_H_INCLUDED
#define YY_YY_SUNFLOWER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
enum yytokentype
{
   IDENTIFIER = 258,
   INTCONST = 259,
   INITIAL = 260,
   SPACE = 261,
   OTHERS = 262,
   ADD = 263,
   SUB = 264,
   MUL = 265,
   DIV = 266,
   MOD = 267,
   GIVE = 268,
   EQUAL = 269,
   NEQUAL = 270,
   GREATER = 271,
   GEQUAL = 272,
   SMALLER = 273,
   SEQUAL = 274,
   LEFTBRACKET = 275,
   RIGHTBRACKET = 276,
   AND = 277,
   BEGIN_ = 278,
   DO = 279,
   ELSE = 280,
   END = 281,
   ENDIF = 282,
   ENDWHILE = 283,
   EXIT = 284,
   IF = 285,
   SET = 286,
   NOT = 287,
   OR = 288,
   PROGRAM = 289,
   READ = 290,
   THEN = 291,
   VAR = 292,
   WHILE = 293,
   WRITE = 294
};
#endif
typedef struct branch_type
{
   char *reg;
   char *label_stmt;
   char *label_else;
   int isAnd; /*isAnd 代表上一個邏輯運算為: 1.And 2.Or 3.沒有邏輯運算*/
   int last_addr;
} branch_type;

#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE {
/* Line 2058 of yacc.c  */
#line 30 "sunflower.y"

   float floatVal;
   int intVal;
   char *str;
   branch_type branch;

/* Line 2058 of yacc.c  */
#line 104 "sunflower.tab.h"
} YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define yystype YYSTYPE /* obsolescent; will be withdrawn */
#define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse(void *YYPARSE_PARAM);
#else
int yyparse();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse(void);
#else
int yyparse();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SUNFLOWER_TAB_H_INCLUDED  */
