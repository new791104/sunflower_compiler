/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "sunflower.y"

/*
*   sunflower 語法分析
*/
#include <stdio.h>
#include <string.h>
#include "sunflower.tab.h"

extern int yylex();
extern FILE *yyin;
extern FILE *yyout;
extern char *exception_array;
extern char *combineStr(char*, char*);
extern char *getReg();
extern void putReg(char*);
extern char *makeAluInstr(char*, char*, char*, char*, char*);
extern char *makeIdentifierInstr(char*, char*, char*);
extern char *makeBranchInstr(char *text, char *op, char *rs, char *rt, char *label_stmt, char *label_else);
extern char *newLabel();
extern char *makebooleanTermInstr(char *text, branch_type branch);
extern char *deleteLine(char *text, int addr);
extern char *formatLabel(char *label);
extern char *doNEG(char*);
extern int countLines(char *text);
extern char *substr(char *dest, char *src, int start, int cnt);
extern char *insertInstr(char *text, char *mid, int addr);
extern char *findLastLine(char *text);
extern int findLastLineAddr(char *text);
extern void debugMode(char* text, int flag);

char *data = "\t.data";
char *text = "\n\t.text\nmain:";

/* Line 371 of yacc.c  */
#line 102 "sunflower.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 203 "sunflower.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   92

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  37
/* YYNRULES -- Number of states.  */
#define YYNSTATES  76

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    10,    14,    15,    18,    19,    24,    30,
      38,    44,    47,    50,    52,    56,    58,    62,    64,    67,
      69,    73,    77,    81,    85,    89,    93,    97,   101,   103,
     107,   111,   115,   117,   120,   122,   124,   126
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    34,     3,    23,    42,    43,    26,    -1,
      42,    37,     3,    -1,    -1,    43,    44,    -1,    -1,    31,
       3,    13,    49,    -1,    30,    45,    36,    43,    27,    -1,
      30,    45,    36,    43,    25,    43,    27,    -1,    38,    45,
      24,    43,    28,    -1,    35,     3,    -1,    39,    49,    -1,
      29,    -1,    45,    33,    46,    -1,    46,    -1,    46,    22,
      47,    -1,    47,    -1,    32,    47,    -1,    48,    -1,    49,
      14,    49,    -1,    49,    15,    49,    -1,    49,    16,    49,
      -1,    49,    17,    49,    -1,    49,    18,    49,    -1,    49,
      19,    49,    -1,    49,     8,    50,    -1,    49,     9,    50,
      -1,    50,    -1,    50,    10,    51,    -1,    50,    11,    51,
      -1,    50,    12,    51,    -1,    51,    -1,     9,    51,    -1,
      52,    -1,     4,    -1,     3,    -1,    20,    49,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    46,    46,    59,    66,    69,    75,    80,    89,    99,
     118,   135,   146,   154,   161,   180,   209,   223,   232,   239,
     248,   259,   270,   281,   292,   303,   316,   322,   328,   334,
     340,   346,   352,   358,   365,   371,   379,   386
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INTCONST", "INITIAL",
  "SPACE", "OTHERS", "ADD", "SUB", "MUL", "DIV", "MOD", "GIVE", "EQUAL",
  "NEQUAL", "GREATER", "GEQUAL", "SMALLER", "SEQUAL", "LEFTBRACKET",
  "RIGHTBRACKET", "AND", "BEGIN_", "DO", "ELSE", "END", "ENDIF",
  "ENDWHILE", "EXIT", "IF", "SET", "NOT", "OR", "PROGRAM", "READ", "THEN",
  "VAR", "WHILE", "WRITE", "$accept", "program", "declarations",
  "statements", "statement", "booleanExpression", "booleanTerm",
  "booleanFactor", "relationExpression", "arithmeticExpression",
  "arithmeticTerm", "arithmeticFactor", "primaryExpression", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    44,    44,    44,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    49,    49,    49,    50,
      50,    50,    50,    51,    51,    52,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     3,     0,     2,     0,     4,     5,     7,
       5,     2,     2,     1,     3,     1,     3,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     1,     2,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     6,     0,     0,     3,
       2,    13,     0,     0,     0,     0,     0,     5,    36,    35,
       0,     0,     0,     0,    15,    17,    19,     0,    28,    32,
      34,     0,    11,     0,    12,    33,     0,    18,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    37,    14,     0,    16,    26,    27,
      20,    21,    22,    23,    24,    25,    29,    30,    31,     7,
       0,     6,     8,    10,     0,     9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     6,     8,    17,    23,    24,    25,    26,    27,
      28,    29,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -39
static const yytype_int8 yypact[] =
{
     -25,    18,    34,     1,   -39,   -39,     5,    45,   -13,   -39,
     -39,   -39,     3,    58,    64,     3,    37,   -39,   -39,   -39,
      37,    37,     3,   -22,    51,   -39,   -39,    61,    42,   -39,
     -39,    72,   -39,   -14,    -5,   -39,    35,   -39,     3,   -39,
       3,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,   -39,   -39,    51,    20,   -39,    42,    42,
      -5,    -5,    -5,    -5,    -5,    -5,   -39,   -39,   -39,    -5,
      53,   -39,   -39,   -39,    33,   -39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   -39,   -38,   -39,    59,    48,   -20,   -39,   -16,
      24,   -12,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      34,    56,    37,    41,    42,    36,    18,    19,    35,     1,
      53,    38,    20,    10,    39,    70,    11,    12,    13,    38,
      57,     3,    14,    21,     5,    15,    16,    60,    61,    62,
      63,    64,    65,    74,     4,    22,    69,    66,    67,    68,
      18,    19,     7,    41,    42,    71,    20,    72,     9,    11,
      12,    13,    49,    50,    51,    14,    54,    21,    15,    16,
      75,    31,    11,    12,    13,    58,    59,    32,    14,    41,
      42,    15,    16,    40,    33,    43,    44,    45,    46,    47,
      48,    73,    11,    12,    13,    52,    55,     0,    14,     0,
       0,    15,    16
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-39)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      16,    39,    22,     8,     9,    21,     3,     4,    20,    34,
      24,    33,     9,    26,    36,    53,    29,    30,    31,    33,
      40,     3,    35,    20,    23,    38,    39,    43,    44,    45,
      46,    47,    48,    71,     0,    32,    52,    49,    50,    51,
       3,     4,    37,     8,     9,    25,     9,    27,     3,    29,
      30,    31,    10,    11,    12,    35,    21,    20,    38,    39,
      27,     3,    29,    30,    31,    41,    42,     3,    35,     8,
       9,    38,    39,    22,    15,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    31,    13,    38,    -1,    35,    -1,
      -1,    38,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    41,     3,     0,    23,    42,    37,    43,     3,
      26,    29,    30,    31,    35,    38,    39,    44,     3,     4,
       9,    20,    32,    45,    46,    47,    48,    49,    50,    51,
      52,     3,     3,    45,    49,    51,    49,    47,    33,    36,
      22,     8,     9,    14,    15,    16,    17,    18,    19,    10,
      11,    12,    13,    24,    21,    46,    43,    47,    50,    50,
      49,    49,    49,    49,    49,    49,    51,    51,    51,    49,
      43,    25,    27,    28,    43,    27
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 46 "sunflower.y"
    { 
        char *finish = "\n\tli $v0, 10\n\tsyscall";
        printf("program -> Program Identifier Begin declarations statements End\n");
        printf("\nLexical errors: \n%s", exception_array);    
        fwrite(data, 1, strlen(data), yyout);
        fwrite(text, 1, strlen(text), yyout);
        fwrite(finish, 1, strlen(finish), yyout);
        free(data);
        free(text);
        free(finish);
    }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 59 "sunflower.y"
    { 
        printf("declarations -> declarations Var Identifier\n");
        char *result = "\n";
        result = combineStr(result, (yyvsp[(3) - (3)].stmt).var_label);
        result = combineStr(result, ":\n\t.word 0");
        data = combineStr(data, result);
    }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 66 "sunflower.y"
    { printf("declarations -> empty\n"); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 69 "sunflower.y"
    { 
        printf("statements -> statements statement\n"); 
        // text = combineStr(text, "\n# STMTS #");
        // debugMode(text, strlen(text));
        (yyval.stmt).last_addr = strlen(text);
    }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 75 "sunflower.y"
    { 
        printf("statements -> empty\n");
    }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 80 "sunflower.y"
    { 
        printf("statement -> Set Identifier = arithmeticExpression\n");
        char result[40], *rd = (yyvsp[(4) - (4)].stmt).reg, *rs = getReg(), *var_label = (yyvsp[(2) - (4)].stmt).var_label;
        snprintf(result, sizeof(result), "\n\tla %s, %s", rs, var_label);
        snprintf(result, sizeof(result), "%s\n\tsw %s, 0(%s)", result, rd, rs);
        text = combineStr(text, result);
        putReg(rs);
        putReg(rd);
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 89 "sunflower.y"
    { 
        printf("statement -> If booleanExpression Then statements EndIf\n");
        if (!(yyvsp[(2) - (5)].branch).isAnd) {
            // insert or_label_stmt
            char *mid = findLastLine((yyvsp[(2) - (5)].branch).label_stmt);
            text = insertInstr(text, mid, (yyvsp[(2) - (5)].branch).last_addr);
        }
        // add $2.label_else:
        text = combineStr(text, (yyvsp[(2) - (5)].branch).label_else);
    }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 99 "sunflower.y"
    { 
        printf("statement -> If booleanExpression Then statements Else statements EndIf\n"); 
        // 需要修正 Or insert 過後 statements 傳回的插斷點
        int insert_offset = 0;
        if (!(yyvsp[(2) - (7)].branch).isAnd) {
            // insert or_label_stmt
            char *mid = findLastLine((yyvsp[(2) - (7)].branch).label_stmt);
            text = insertInstr(text, mid, (yyvsp[(2) - (7)].branch).last_addr);
            insert_offset = strlen(mid);
        }
        // insert "\nb Lnext\n$2.label_else"
        int stmt_addr = (yyvsp[(4) - (7)].stmt).last_addr;
        char result[20], *Lnext = newLabel(), *mid;
        // debugMode("stmt_addr", stmt_addr);
        snprintf(result, sizeof(result), "\n\tb %s%s", Lnext, (yyvsp[(2) - (7)].branch).label_else);
        text = insertInstr(text, result, stmt_addr + insert_offset);
        // add Lnext:
        text = combineStr(text, formatLabel(Lnext));
    }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 118 "sunflower.y"
    { 
        printf("statement -> While booleanExpression Do statements EndWhile\n");
        if (!(yyvsp[(2) - (5)].branch).isAnd) {
            // insert or_label_stmt
            char *mid = findLastLine((yyvsp[(2) - (5)].branch).label_stmt);
            text = insertInstr(text, mid, (yyvsp[(2) - (5)].branch).last_addr);
        }
        // insert Lbegin
        char *bLabel = newLabel();
        text = insertInstr(text, formatLabel(bLabel), (yyvsp[(2) - (5)].branch).first_addr);
        // add b Lbegin
        char result[20];
        snprintf(result, sizeof(result), "\n\tb %s", bLabel);
        text = combineStr(text, result);
        // add $2.label_else:
        text = combineStr(text, (yyvsp[(2) - (5)].branch).label_else); 
    }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 135 "sunflower.y"
    { 
        printf("statement -> Read Identifier\n"); 
        char result[40], *reg = getReg();
        snprintf(result, sizeof(result), "\n\tli $v0, 5\n\tsyscall");
        text = combineStr(text, result);
        snprintf(result, sizeof(result), "\n\tla %s, %s", reg, (yyvsp[(2) - (2)].stmt).var_label);
        text = combineStr(text, result);
        snprintf(result, sizeof(result), "\n\tsw $v0, 0(%s)", reg);
        text = combineStr(text, result);
        putReg(reg);
    }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 146 "sunflower.y"
    { 
        printf("statement -> Write arithmeticExpression\n"); 
        char result[40], *reg = (yyvsp[(2) - (2)].stmt).reg;
        snprintf(result, sizeof(result), "\n\tmove $a0, %s", reg);
        text = combineStr(text, result);
        snprintf(result, sizeof(result), "\n\tli $v0, 1\n\tsyscall", reg);
        text = combineStr(text, result);
    }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 154 "sunflower.y"
    { 
        printf("statement -> Exit\n"); 
        char *finish = "\n\tli $v0, 10\n\tsyscall";
        text = combineStr(text, finish);
    }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 161 "sunflower.y"
    { 
        printf("booleanExpression -> booleanExpression Or booleanTerm\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].branch).first_addr;
        // text = combineStr(text, "\n### booleanExpression -> booleanExpression Or booleanTerm");
        char *label_else_1 = (yyvsp[(1) - (3)].branch).label_else;
        if ((yyvsp[(1) - (3)].branch).isAnd) {
            char *text_tmp = text;
            int last_line_size = strlen(findLastLine(text_tmp));
            text = deleteLine(text_tmp, (yyvsp[(1) - (3)].branch).last_addr);
            text = insertInstr(text, label_else_1, (yyvsp[(1) - (3)].branch).last_addr - last_line_size + 2);  // const(2): size of "\n\t"
            label_else_1 = "\0";
        }
        text = combineStr(text, (yyvsp[(1) - (3)].branch).label_stmt);

        (yyval.branch).last_addr = strlen(text);
        (yyval.branch).label_else = combineStr(formatLabel(label_else_1), formatLabel((yyvsp[(3) - (3)].branch).label_else));
        (yyval.branch).label_stmt = combineStr(formatLabel((yyvsp[(1) - (3)].branch).label_stmt), formatLabel((yyvsp[(3) - (3)].branch).label_stmt));
        (yyval.branch).isAnd = 0;
    }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 180 "sunflower.y"
    { 
        printf("booleanExpression -> booleanTerm\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (1)].branch).first_addr;
        // text = combineStr(text, "\n### booleanExpression -> booleanTerm");
        if ((yyvsp[(1) - (1)].branch).isAnd == 1) {
            // insert
            char *mid = (yyvsp[(1) - (1)].branch).label_stmt;
            // char *hint = combineStr(mid, "\nbooleanTerm insert HERE HAHA!!!");
            int last_addr = (yyvsp[(1) - (1)].branch).last_addr;
            text = insertInstr(text, mid, last_addr);

            (yyval.branch).last_addr = strlen(text);
        }
        else if ((yyvsp[(1) - (1)].branch).isAnd == 0) {
            text = combineStr(text, (yyvsp[(1) - (1)].branch).label_else);
            // $1.label_else = deleteLine($1.label_else, strlen($1.label_else));
            (yyval.branch).label_else = "\0";
            (yyval.branch).last_addr = strlen(text);
            // text = combineStr(text, "\n### booleanTerm");
        }
        else {
            text = combineStr(text, formatLabel((yyvsp[(1) - (1)].branch).label_stmt));
            (yyval.branch).label_stmt = formatLabel((yyvsp[(1) - (1)].branch).label_stmt);
            (yyval.branch).label_else = formatLabel((yyvsp[(1) - (1)].branch).label_else);
            (yyval.branch).last_addr = strlen(text);
        }
    }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 209 "sunflower.y"
    {
        printf("booleanTerm -> booleanTerm And booleanFactor\n");
        // text = combineStr(text, "\n### booleanTerm -> booleanTerm And booleanFactor");
        char result[20], *mid = (yyvsp[(1) - (3)].branch).label_stmt;
        int last_addr = (yyvsp[(1) - (3)].branch).last_addr;
        // insert
        text = insertInstr(text, mid, last_addr);
        
        (yyval.branch).last_addr = strlen(text);
        (yyval.branch).label_else = combineStr((yyvsp[(1) - (3)].branch).label_else, formatLabel((yyvsp[(3) - (3)].branch).label_else));
        (yyval.branch).label_stmt = formatLabel((yyvsp[(3) - (3)].branch).label_stmt);
        (yyval.branch).isAnd = 1;
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].branch).first_addr;
    }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 223 "sunflower.y"
    {
        printf("booleanTerm -> booleanFactor\n");
        (yyval.branch).last_addr = strlen(text);
        (yyval.branch).label_else = formatLabel((yyvsp[(1) - (1)].branch).label_else);
        (yyval.branch).label_stmt = formatLabel((yyvsp[(1) - (1)].branch).label_stmt);
        (yyval.branch).isAnd = -1;
    }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 232 "sunflower.y"
    { 
        printf("booleanFactor -> Not booleanFactor\n");
        // text = combineStr(text, "\n### booleanFactor -> Not booleanFactor");
        (yyval.branch).label_else = (yyvsp[(2) - (2)].branch).label_stmt;
        (yyval.branch).label_stmt = (yyvsp[(2) - (2)].branch).label_else;
        (yyval.branch).first_addr = (yyvsp[(2) - (2)].branch).first_addr;
    }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 239 "sunflower.y"
    { 
        printf("booleanFactor -> relationExpression\n");
        // text = combineStr(text, "\n### booleanFactor -> relationExpression");
        (yyval.branch).label_else = (yyvsp[(1) - (1)].branch).label_else;
        (yyval.branch).label_stmt = (yyvsp[(1) - (1)].branch).label_stmt;
        (yyval.branch).first_addr = (yyvsp[(1) - (1)].branch).first_addr;
    }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 248 "sunflower.y"
    { 
        printf("relationExpression -> arithmeticExpression == arithmeticExpression\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].stmt).first_addr;
        // text = combineStr(text, "\n### ==");        
        char result[20], *rs = (yyvsp[(1) - (3)].stmt).reg, *rt = (yyvsp[(3) - (3)].stmt).reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "beq", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        (yyval.branch).label_else = label_else;
        (yyval.branch).label_stmt = label_stmt;
    }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 259 "sunflower.y"
    { 
        printf("relationExpression -> arithmeticExpression <> arithmeticExpression\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].stmt).first_addr;
        // text = combineStr(text, "\n### <>"); 
        char result[20], *rs = (yyvsp[(1) - (3)].stmt).reg, *rt = (yyvsp[(3) - (3)].stmt).reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bne", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        (yyval.branch).label_else = label_else;
        (yyval.branch).label_stmt = label_stmt;
    }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 270 "sunflower.y"
    { 
        printf("relationExpression -> arithmeticExpression > arithmeticExpression\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].stmt).first_addr;
        // text = combineStr(text, "\n### >"); 
        char result[20], *rs = (yyvsp[(1) - (3)].stmt).reg, *rt = (yyvsp[(3) - (3)].stmt).reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bgt", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        (yyval.branch).label_else = label_else;
        (yyval.branch).label_stmt = label_stmt;
    }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 281 "sunflower.y"
    { 
        printf("relationExpression -> arithmeticExpression >= arithmeticExpression\n"); 
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].stmt).first_addr;
        // text = combineStr(text, "\n### >="); 
        char result[20], *rs = (yyvsp[(1) - (3)].stmt).reg, *rt = (yyvsp[(3) - (3)].stmt).reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bge", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        (yyval.branch).label_else = label_else;
        (yyval.branch).label_stmt = label_stmt;
    }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 292 "sunflower.y"
    { 
        printf("relationExpression -> arithmeticExpression < arithmeticExpression\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].stmt).first_addr;
        // text = combineStr(text, "\n### <");
        char result[20], *rs = (yyvsp[(1) - (3)].stmt).reg, *rt = (yyvsp[(3) - (3)].stmt).reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "blt", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        (yyval.branch).label_else = label_else;
        (yyval.branch).label_stmt = label_stmt;
    }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 303 "sunflower.y"
    { 
        printf("relationExpression -> arithmeticExpression <= arithmeticExpression\n");
        (yyval.branch).first_addr = (yyvsp[(1) - (3)].stmt).first_addr;
        // text = combineStr(text, "\n### <=");
        char result[20], *rs = (yyvsp[(1) - (3)].stmt).reg, *rt = (yyvsp[(3) - (3)].stmt).reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "ble", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        (yyval.branch).label_else = label_else;
        (yyval.branch).label_stmt = label_stmt;
    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 316 "sunflower.y"
    { 
        printf("arithmeticExpression -> arithmeticExpression + arithmeticTerm\n"); 
        text = makeAluInstr(text, "add", (yyvsp[(1) - (3)].stmt).reg, (yyvsp[(3) - (3)].stmt).reg, (yyvsp[(1) - (3)].stmt).reg);
        putReg((yyvsp[(3) - (3)].stmt).reg);
        (yyval.stmt) = (yyvsp[(1) - (3)].stmt);
    }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 322 "sunflower.y"
    { 
        printf("arithmeticExpression -> arithmeticExpression - arithmeticTerm\n");
        text = makeAluInstr(text, "sub", (yyvsp[(1) - (3)].stmt).reg, (yyvsp[(3) - (3)].stmt).reg, (yyvsp[(1) - (3)].stmt).reg);
        putReg((yyvsp[(3) - (3)].stmt).reg);
        (yyval.stmt).reg = (yyvsp[(1) - (3)].stmt).reg;
    }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 328 "sunflower.y"
    { 
        printf("arithmeticExpression -> arithmeticTerm\n");
        (yyval.stmt).reg = (yyvsp[(1) - (1)].stmt).reg;
    }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 334 "sunflower.y"
    { 
        printf("arithmeticTerm -> arithmeticTerm * arithmeticFactor\n");
        text = makeAluInstr(text, "mul", (yyvsp[(1) - (3)].stmt).reg, (yyvsp[(3) - (3)].stmt).reg, (yyvsp[(1) - (3)].stmt).reg);
        putReg((yyvsp[(3) - (3)].stmt).reg);
        (yyval.stmt).reg = (yyvsp[(1) - (3)].stmt).reg;
    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 340 "sunflower.y"
    { 
        printf("arithmeticTerm -> arithmeticTerm / arithmeticFactor\n"); 
        text = makeAluInstr(text, "div", (yyvsp[(1) - (3)].stmt).reg, (yyvsp[(3) - (3)].stmt).reg, (yyvsp[(1) - (3)].stmt).reg);
        putReg((yyvsp[(3) - (3)].stmt).reg);
        (yyval.stmt).reg = (yyvsp[(1) - (3)].stmt).reg;
    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 346 "sunflower.y"
    { 
        printf("arithmeticTerm -> arithmeticTerm % arithmeticFactor\n"); 
        text = makeAluInstr(text, "rem", (yyvsp[(1) - (3)].stmt).reg, (yyvsp[(3) - (3)].stmt).reg, (yyvsp[(1) - (3)].stmt).reg);
        putReg((yyvsp[(3) - (3)].stmt).reg);
        (yyval.stmt).reg = (yyvsp[(1) - (3)].stmt).reg;
    }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 352 "sunflower.y"
    { 
        printf("arithmeticTerm -> arithmeticFactor\n");
        (yyval.stmt).reg = (yyvsp[(1) - (1)].stmt).reg;
    }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 358 "sunflower.y"
    { 
        printf("arithmeticFactor -> arithmeticFactor\n");
        char result[20], *rd = (yyvsp[(2) - (2)].stmt).reg, *rs = (yyvsp[(2) - (2)].stmt).reg;
        snprintf(result, sizeof(result), "\n\tneg %s, %s", rd, rs);
        text = combineStr(text, result);
        (yyval.stmt).reg = (yyvsp[(2) - (2)].stmt).reg;
    }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 365 "sunflower.y"
    { 
        printf("arithmeticFactor -> primaryExpression\n");
        (yyval.stmt).reg = (yyvsp[(1) - (1)].stmt).reg;
    }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 371 "sunflower.y"
    { 
        printf("primaryExpression -> IntConst\n");
        (yyval.stmt).first_addr = strlen(text);
        char result[20], *reg = getReg(), *intconst = (yyvsp[(1) - (1)].stmt).reg;
        snprintf(result, sizeof(result), "\n\tli %s, %s", reg, intconst);
        text = combineStr(text, result);
        (yyval.stmt).reg = reg;
    }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 379 "sunflower.y"
    { 
        printf("primaryExpression -> Identifier\n");
        (yyval.stmt).first_addr = strlen(text);
        char *reg = getReg();
        text = makeIdentifierInstr(text, reg, (yyvsp[(1) - (1)].stmt).var_label);
        (yyval.stmt).reg = reg;
    }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 386 "sunflower.y"
    { 
        printf("primaryExpression -> arithmeticExpression\n");
        (yyval.stmt).first_addr = strlen(text);
        (yyval.stmt).reg = (yyvsp[(2) - (3)].stmt).reg;
    }
    break;


/* Line 1792 of yacc.c  */
#line 1960 "sunflower.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 392 "sunflower.y"


