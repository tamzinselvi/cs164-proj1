
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison GLR parsers in C
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.
   
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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1




/* Copy the first part of user declarations.  */

/* Line 172 of glr.c  */
#line 81 "parser.y"

  #include <string>
  #include "apyc.h"

  using namespace std;

  extern int yylex2 ();
  static int yylex ();
  static void yyerror (const char*);

  #define YYLTYPE int
  #define YYLLOC_DEFAULT(Current, Rhs, N) \
      do if (N) { \
         Current = YYRHSLOC (Rhs, 1); \
      } else { \
         Current = YYRHSLOC (Rhs, 0); \
      } while (0)

  static ASTList* makeList ();
  static ASTList* makeList (AST*);
  static ASTList* makeListNonNull (AST*);
  static ASTList* addItem (ASTList*, AST*);
  static ASTList* addItem (AST* item, ASTList* L);
  static ASTList* addNonNullItem (ASTList*, AST*);
  static ASTList* append (ASTList*, ASTList*);
  
  static AST* makeSuite (int, ASTList*);
  static AST* makeComparison (ASTList*);
  static ASTList* addComparison (ASTList*, const char*, AST*);

  static AST* binop (AST*, const char*, AST*);
  static AST* unop (int, const char*, AST*);

  static void pushContext (int stmtType0, ...);
  static void checkContext (int stmtType, int loc);
  static void popContext ();

  AST* theProgram;

/* Line 172 of glr.c  */
#line 121 "parser.y"


    /* Define the line numbers maintained by the parser to be simple 
     * integer line numbers (of the beginning of a construct). */
    #define YYLTYPE int
    /* By default, set the line number of a nonterminal symbol from that
     * of the first right-hand side symbol in the production that
     * produces it, or that of the lookahead for empty productions. */
    #define YYLLOC_DEFAULT(Current, Rhs, N) \
        do if (N) { \
           Current = YYRHSLOC (Rhs, 1); \
        } else { \
           Current = YYRHSLOC (Rhs, 0); \
        } while (0)



/* Line 172 of glr.c  */
#line 118 "parser.cc"




/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FLOAT = 258,
     ID = 259,
     INT = 260,
     STRING = 261,
     NOTEQ = 262,
     MODEQ = 263,
     ANDEQ = 264,
     EXP = 265,
     EXPEQ = 266,
     MULTEQ = 267,
     ADDEQ = 268,
     SUBEQ = 269,
     FLDIV = 270,
     LSH = 271,
     RSH = 272,
     LSHEQ = 273,
     LTEQ = 274,
     EQEQ = 275,
     GTEQ = 276,
     RSHEQ = 277,
     XOREQ = 278,
     OREQ = 279,
     DIVEQ = 280,
     FLDIVEQ = 281,
     COLONCOLON = 282,
     AND = 283,
     BREAK = 284,
     CLASS = 285,
     CONTINUE = 286,
     DEF = 287,
     ELIF = 288,
     ELSE = 289,
     EXCEPT = 290,
     FOR = 291,
     FROM = 292,
     GLOBAL = 293,
     IF = 294,
     IMPORT = 295,
     IN = 296,
     IS = 297,
     LAMBDA = 298,
     NOT = 299,
     OR = 300,
     PASS = 301,
     PRINT = 302,
     RAISE = 303,
     RETURN = 304,
     TRY = 305,
     WHILE = 306,
     DEDENT = 307,
     INDENT = 308,
     NEWLINE = 309,
     UNARY_NOT = 310
   };
#endif


#ifndef YYSTYPE
typedef union YYSTYPE
{

/* Line 214 of glr.c  */
#line 140 "parser.y"

  string* String;
  AST* Node;
  vector<AST*>* List;
  const char* CString;



/* Line 214 of glr.c  */
#line 201 "parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{

  int first_line;
  int first_column;
  int last_line;
  int last_column;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template,
   here we set the default value of $$ to a zeroed-out value.
   Since the default value is undefined, this behavior is
   technically correct.  */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */


/* Line 243 of glr.c  */
#line 251 "parser.cc"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(env) setjmp (env)
# define YYLONGJMP(env, val) longjmp (env, val)
#endif

/*-----------------.
| GCC extensions.  |
`-----------------*/

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5) || __STRICT_ANSI__)
#  define __attribute__(Spec) /* empty */
# endif
#endif

#define YYOPTIONAL_LOC(Name) Name

#ifndef YYASSERT
# define YYASSERT(condition) ((void) ((condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNRULES -- Number of states.  */
#define YYNSTATES  300
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 8
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    65,    60,     2,
      71,    72,    63,    61,    69,    62,    67,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    70,    68,
       7,    77,     8,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    76,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,    58,    74,    66,     2,     2,     2,
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
       5,     6,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    11,    13,    16,    19,
      23,    25,    28,    30,    34,    36,    38,    40,    42,    45,
      47,    50,    53,    58,    61,    63,    67,    72,    75,    80,
      83,    86,    88,    91,    93,    95,    97,    99,   101,   103,
     105,   107,   109,   111,   113,   115,   118,   122,   127,   129,
     131,   136,   142,   144,   146,   150,   154,   157,   159,   164,
     168,   172,   177,   181,   185,   189,   193,   197,   201,   203,
     207,   211,   215,   219,   223,   227,   231,   235,   239,   243,
     247,   250,   253,   256,   260,   261,   263,   265,   269,   271,
     272,   275,   278,   281,   283,   285,   288,   293,   298,   302,
     305,   309,   313,   317,   321,   323,   325,   327,   329,   331,
     333,   335,   337,   340,   344,   349,   356,   358,   360,   362,
     365,   369,   373,   375,   379,   383,   387,   391,   393,   395,
     397,   399,   403,   404,   407,   411,   415,   419,   421,   423,
     425,   427,   429,   431,   438,   440,   446,   447,   451,   452,
     459,   468,   469,   475,   476,   480,   486,   491,   498,   501,
     502,   503,   512,   514,   516,   520,   522,   523,   526,   527,
     536,   537
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const short int yyrhs[] =
{
      79,     0,    -1,    56,    79,    -1,    -1,    80,    81,    -1,
      -1,    82,    -1,    81,    82,    -1,    83,    56,    -1,    83,
      68,    56,    -1,   115,    -1,     1,    56,    -1,    84,    -1,
      83,    68,    84,    -1,    90,    -1,    48,    -1,    31,    -1,
      33,    -1,    51,   100,    -1,    51,    -1,    50,    94,    -1,
      42,   130,    -1,    39,   129,    42,   131,    -1,    40,   130,
      -1,   114,    -1,   110,    86,   100,    -1,    49,    85,    69,
      98,    -1,    49,    98,    -1,    49,    85,    69,    96,    -1,
      49,    85,    -1,    49,    96,    -1,    49,    -1,    19,    90,
      -1,    15,    -1,    16,    -1,    14,    -1,    27,    -1,    28,
      -1,    10,    -1,    13,    -1,    20,    -1,    24,    -1,    26,
      -1,    11,    -1,    25,    -1,    83,    56,    -1,    83,    68,
      56,    -1,    56,    55,    81,    54,    -1,    87,    -1,    87,
      -1,    45,   132,    70,    90,    -1,    91,    41,    91,    36,
      90,    -1,    91,    -1,    92,    -1,    91,    47,    91,    -1,
      91,    30,    91,    -1,    46,    91,    -1,    93,    -1,    92,
      46,    43,    93,    -1,    92,    43,    93,    -1,    92,    44,
      93,    -1,    92,    44,    46,    93,    -1,    92,     7,    93,
      -1,    92,     8,    93,    -1,    92,    21,    93,    -1,    92,
      23,    93,    -1,    92,    22,    93,    -1,    92,     9,    93,
      -1,   102,    -1,    93,    58,    93,    -1,    93,    59,    93,
      -1,    93,    60,    93,    -1,    93,    18,    93,    -1,    93,
      19,    93,    -1,    93,    61,    93,    -1,    93,    62,    93,
      -1,    93,    63,    93,    -1,    93,    64,    93,    -1,    93,
      65,    93,    -1,    93,    17,    93,    -1,    62,    93,    -1,
      61,    93,    -1,    66,    93,    -1,    93,    12,    93,    -1,
      -1,    90,    -1,    90,    -1,    95,    69,    90,    -1,    95,
      -1,    -1,    95,   135,    -1,    95,    69,    -1,    95,   135,
      -1,    90,    -1,   101,    -1,    90,    69,    -1,    90,    69,
      95,   135,    -1,   102,    71,    99,    72,    -1,   102,    71,
      72,    -1,    71,    72,    -1,    71,   101,    72,    -1,    73,
     112,    74,    -1,    75,    97,    76,    -1,    71,    90,    72,
      -1,   104,    -1,   105,    -1,   106,    -1,   129,    -1,     5,
      -1,     3,    -1,   103,    -1,     6,    -1,   103,     6,    -1,
     102,    67,   129,    -1,   102,    75,    90,    76,    -1,   102,
      75,    94,    70,    94,    76,    -1,   110,    -1,   108,    -1,
     109,    -1,   110,    69,    -1,   110,    69,   110,    -1,   110,
      69,   109,    -1,   129,    -1,   129,    29,   129,    -1,    71,
     107,    72,    -1,    75,   110,    76,    -1,    75,   108,    76,
      -1,   104,    -1,   105,    -1,   106,    -1,   113,    -1,   111,
      69,   113,    -1,    -1,   111,   135,    -1,    90,    70,    90,
      -1,   107,    77,   100,    -1,   107,    77,   114,    -1,   116,
      -1,   120,    -1,   121,    -1,   123,    -1,   127,    -1,   133,
      -1,    41,    90,    70,   119,    88,   117,    -1,   118,    -1,
      35,    90,    70,    88,   117,    -1,    -1,    36,    70,    88,
      -1,    -1,    53,    90,    70,   122,    88,   118,    -1,    38,
     107,    43,   100,    70,   122,    88,   118,    -1,    -1,    52,
      70,   124,    88,   125,    -1,    -1,    37,    70,    88,    -1,
      37,    90,   126,    70,    88,    -1,   125,    37,    70,    88,
      -1,   125,    37,    90,   126,    70,    88,    -1,    69,   129,
      -1,    -1,    -1,    34,   129,    71,   132,    72,    70,   128,
      89,    -1,     4,    -1,   129,    -1,   130,    69,   129,    -1,
     130,    -1,    -1,   130,   135,    -1,    -1,    32,   129,    71,
     129,    72,    70,   134,    89,    -1,    -1,    69,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   172,   172,   173,   173,   175,   179,   180,   184,   185,
     186,   187,   191,   192,   197,   198,   199,   201,   203,   205,
     207,   208,   210,   213,   214,   215,   219,   221,   222,   224,
     227,   229,   235,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   240,   240,   240,   244,   245,   246,   249,   252,
     256,   258,   260,   264,   266,   267,   268,   273,   274,   276,
     278,   280,   282,   284,   286,   288,   290,   292,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   316,   317,   321,   322,   326,   330,
     331,   335,   339,   343,   344,   348,   349,   354,   356,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   374,   375,   382,   386,   390,   395,   396,   400,   404,
     405,   406,   410,   411,   412,   413,   414,   415,   416,   417,
     421,   422,   426,   427,   431,   435,   437,   442,   443,   444,
     445,   446,   447,   450,   455,   456,   461,   462,   465,   468,
     473,   479,   484,   488,   491,   493,   495,   497,   502,   503,
     508,   507,   515,   519,   520,   524,   528,   529,   534,   533,
     541,   543
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FLOAT", "ID", "INT", "STRING", "'<'",
  "'>'", "\"!=\"", "\"%=\"", "\"&=\"", "\"**\"", "\"**=\"", "\"*=\"",
  "\"+=\"", "\"-=\"", "\"//\"", "\"<<\"", "\">>\"", "\"<<=\"", "\"<=\"",
  "\"==\"", "\">=\"", "\">>=\"", "\"^=\"", "\"|=\"", "\"/=\"", "\"//=\"",
  "\"::\"", "\"and\"", "\"break\"", "\"class\"", "\"continue\"", "\"def\"",
  "\"elif\"", "\"else\"", "\"except\"", "\"for\"", "\"from\"",
  "\"global\"", "\"if\"", "\"import\"", "\"in\"", "\"is\"", "\"lambda\"",
  "\"not\"", "\"or\"", "\"pass\"", "\"print\"", "\"raise\"", "\"return\"",
  "\"try\"", "\"while\"", "DEDENT", "INDENT", "NEWLINE", "UNARY_NOT",
  "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'.'",
  "';'", "','", "':'", "'('", "')'", "'{'", "'}'", "'['", "']'", "'='",
  "$accept", "program", "$@1", "stmts", "stmt", "simple_stmts",
  "simple_stmt", "print_target", "augmented_assign_op", "stmt_block",
  "suite", "block", "expr", "or_test", "comparisons", "term", "expr0",
  "exprs", "expr_list", "exprs0", "expr_list_comma", "expr_list_opt_comma",
  "expr_or_tuple", "tuple", "primary", "strings", "attributeref",
  "subscription", "slicing", "lhs", "target_list", "targets", "target",
  "pairs", "pairs0", "pair", "assignment", "compound_stmt", "if_stmt",
  "if_tail", "else_part", "if_context", "while_stmt", "for_stmt",
  "loop_context", "try_stmt", "try_context", "except_clauses",
  "target_opt", "def_stmt", "$@2", "id", "ids", "id_list", "id_list0",
  "class_stmt", "$@3", "opt_comma", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    78,    79,    80,    79,    79,    81,    81,    82,    82,
      82,    82,    83,    83,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    87,    88,    89,
      90,    90,    90,    91,    91,    91,    91,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    95,    95,    96,    97,
      97,    98,    99,   100,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   103,   103,   104,   105,   106,   107,   107,   108,   109,
     109,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     111,   111,   112,   112,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   116,   117,   117,   118,   118,   119,   120,
     121,   122,   123,   124,   125,   125,   125,   125,   126,   126,
     128,   127,   129,   130,   130,   131,   132,   132,   134,   133,
     135,   135
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     0,     2,     0,     1,     2,     2,     3,
       1,     2,     1,     3,     1,     1,     1,     1,     2,     1,
       2,     2,     4,     2,     1,     3,     4,     2,     4,     2,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     4,     1,     1,
       4,     5,     1,     1,     3,     3,     2,     1,     4,     3,
       3,     4,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     0,     1,     1,     3,     1,     0,
       2,     2,     2,     1,     1,     2,     4,     4,     3,     2,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     4,     6,     1,     1,     1,     2,
       3,     3,     1,     3,     3,     3,     3,     1,     1,     1,
       1,     3,     0,     2,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     6,     1,     5,     0,     3,     0,     6,
       8,     0,     5,     0,     3,     5,     4,     6,     2,     0,
       0,     8,     1,     1,     3,     1,     0,     2,     0,     8,
       0,     1
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
static const unsigned char yydefact[] =
{
       3,     3,     0,     0,     2,     1,     0,   109,   162,   108,
     111,    16,     0,    17,     0,     0,     0,     0,     0,     0,
     166,     0,    15,    31,    84,    19,     0,     0,     0,     0,
       0,     0,   132,    89,     0,     6,     0,    12,    14,    52,
      53,    57,    68,   110,   104,   105,   106,     0,   117,   118,
     116,    24,    10,   137,   138,   139,   140,   141,   107,   142,
      11,     0,     0,     0,     0,   116,     0,   163,    23,     0,
      89,     0,   104,   105,   106,   107,    21,   170,     0,    56,
       0,    29,    86,    88,    30,    27,    85,    20,    93,    18,
      94,   153,     0,    81,    80,    82,    99,     0,     0,     0,
       0,   170,     0,   130,   170,     0,     0,     0,     7,     8,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,   112,     0,
      38,    43,    39,    35,    33,    34,    40,    41,    44,    42,
      36,    37,   119,     0,     0,     0,   166,     0,     0,     0,
     148,   171,   167,     0,    32,     0,    91,    95,     0,   151,
     103,   100,   124,     0,   171,   133,   101,   171,    90,   102,
     126,   125,     9,    13,    55,     0,    54,    62,    63,    67,
      64,    66,    65,    59,     0,    60,     0,    83,    79,    72,
      73,    69,    70,    71,    74,    75,    76,    77,    78,   113,
      98,   170,     0,    85,     0,   135,   136,   121,   120,    25,
     123,     0,     0,     0,   165,    22,   164,     0,    50,    28,
      26,    87,   170,     0,     0,    48,     0,     0,   134,   131,
       0,    61,    58,    92,    97,   114,    84,     0,     0,   151,
     146,    96,     0,    45,     0,     0,   152,   146,    51,     0,
     168,   160,     0,     0,     0,   143,   144,     0,    46,     0,
     159,     0,   149,   115,     0,     0,   146,     0,     0,    47,
     154,     0,     0,     0,   159,    49,   169,   161,   150,     0,
     147,   158,     0,   156,     0,   146,   155,     0,   145,   157
};

/* YYPDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,     2,     3,    34,    35,   234,    37,    81,   153,   235,
     236,   286,    38,    39,    40,    41,    87,    83,    84,   105,
      85,   212,    89,    90,    42,    43,    72,    73,    74,    47,
      48,    49,    50,   101,   102,   103,    51,    52,    53,   265,
     266,   227,    54,    55,   237,    56,   168,   256,   282,    57,
     275,    75,    77,   225,    78,    59,   274,   162
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -238
static const short int yypact[] =
{
      18,    18,    38,   567,  -238,  -238,   -12,  -238,  -238,  -238,
    -238,  -238,    43,  -238,    43,    52,    43,    43,   823,    43,
      43,   241,  -238,   740,   823,   823,   -16,   823,   867,   867,
     867,    47,   823,   829,   389,  -238,   -22,  -238,  -238,    -5,
     464,   145,   154,    53,   941,   961,  1029,    -1,  -238,  -238,
      57,  -238,  -238,  -238,  -238,  -238,  -238,  -238,   921,  -238,
    -238,    15,    20,   154,    61,    26,    68,  -238,    34,   408,
     823,    35,  -238,  -238,  -238,  -238,    34,    42,    45,  -238,
     823,    62,  -238,    65,  -238,  -238,  -238,  -238,    66,  -238,
    -238,  -238,    51,   100,   100,   100,  -238,   -43,    67,    69,
      59,    79,    40,  -238,    81,    78,    83,    -7,  -238,  -238,
     618,   241,   241,   241,   867,   867,   867,   867,   867,   867,
     867,   846,    90,   867,   867,   867,   867,   867,   867,   867,
     867,   867,   867,   867,   867,    43,   516,   823,  -238,   829,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,    52,   823,    43,    43,    43,   823,    43,    43,
    -238,    43,  -238,   823,  -238,   823,   823,   823,   667,  -238,
    -238,  -238,  -238,   823,   823,  -238,  -238,   823,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,    13,   138,   145,   145,   145,
     145,   145,   145,   145,   867,   145,   867,   100,   100,   155,
     155,  1002,  1017,  1056,   149,   149,   100,   100,   100,  -238,
    -238,    81,    98,    95,   125,  -238,  -238,  -238,    26,  -238,
    -238,   124,   127,   130,    34,  -238,  -238,   667,  -238,  -238,
    -238,  -238,    81,   142,    19,  -238,   164,   667,  -238,  -238,
     823,   145,   145,  -238,  -238,  -238,   823,   141,   152,  -238,
      44,  -238,   567,  -238,   716,   748,   189,   191,  -238,   156,
    -238,  -238,   667,   823,   158,  -238,  -238,   494,  -238,   667,
     161,   792,  -238,  -238,   667,   667,   191,   163,   667,  -238,
    -238,    43,   166,   667,   161,  -238,  -238,  -238,  -238,   667,
    -238,  -238,   667,  -238,   167,    44,  -238,   667,  -238,  -238
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -238,   237,  -238,   -11,   -32,     1,  -109,  -238,  -238,  -173,
      64,   -36,   339,   -13,  -238,    60,  -122,   -30,    75,  -238,
      77,  -238,  -116,    -4,   -10,  -238,    30,    63,   113,    17,
     210,    96,    -9,  -238,  -238,    76,   116,  -238,  -238,   -37,
    -237,  -238,  -238,  -238,    11,  -238,  -238,  -238,   -23,  -238,
    -238,    -3,     2,  -238,   106,  -238,  -238,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -130
static const short int yytable[] =
{
      58,   183,   108,   104,    36,    63,    65,   175,    79,    61,
     178,    62,    58,    66,    67,   214,    67,    67,    -5,    68,
     272,    76,    65,   215,   107,   111,   167,    98,    58,   170,
      58,    58,    64,    44,   109,    36,   112,   219,     5,   288,
     104,   223,   113,   111,    60,    44,   110,     8,    99,   240,
       7,     8,     9,    10,    91,     7,     8,     9,    10,   138,
     113,    44,   152,    44,    44,    98,    45,   140,   141,   181,
     142,   143,   144,   145,     1,   253,   139,   146,    45,   263,
     264,   147,   148,   149,   150,   151,   155,   254,    93,    94,
      95,   156,    20,    21,    45,   152,    45,    45,   184,   185,
     186,   285,   285,   159,   157,   160,   211,    58,    28,    29,
     158,   161,   123,    30,   176,   163,    46,   243,    31,    96,
      32,   169,    33,    31,   259,    32,   152,    33,    46,   173,
      65,   165,   209,   196,   166,   167,    58,   232,   251,   171,
      44,   172,    63,   218,    46,   183,    46,    46,   174,    58,
     177,   220,   221,    67,   179,    67,   226,   123,   226,   180,
     224,   123,   124,   125,   126,    58,   124,   123,   111,    44,
     244,   245,   124,    45,   187,   188,   189,   190,   191,   192,
     193,   195,    44,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   246,   247,   252,    44,   248,
     249,   255,    45,   127,   128,   129,   130,   131,   132,   133,
     134,   260,   132,   133,   134,    45,   130,   131,   132,   133,
     134,   135,   261,    46,    58,   136,   271,   264,   278,   137,
     281,    45,   273,   289,    58,   108,   292,   297,     4,   287,
     229,   267,   230,   106,     7,     8,     9,    10,   217,    58,
     239,    58,    46,    36,   241,   216,   242,    44,   298,    58,
     262,   294,   222,     0,    58,    46,    58,    44,    36,     0,
       0,    58,    58,     0,     0,    58,     0,     0,   291,     0,
      58,    46,    44,     0,    44,     0,    58,    21,     0,    58,
      45,   250,    44,     0,    58,     0,     0,    44,     0,    44,
      45,   257,    28,    29,    44,    44,     0,    30,    44,     0,
       0,     0,    69,    44,    32,    45,    70,    45,     0,    44,
       0,     0,    44,     0,     0,    45,   276,    44,     0,     0,
      45,     0,    45,   280,     0,     0,     0,    45,    45,     0,
      46,    45,   290,     0,     0,     0,    45,   293,     0,     0,
      46,     0,    45,   295,     0,    45,   296,    71,     0,     0,
      45,   299,    82,    86,    88,    46,    92,    46,     0,     0,
      97,   100,    82,     0,     0,    46,     0,     0,     0,     0,
      46,     0,    46,     0,     0,     0,     0,    46,    46,    -4,
       6,    46,     7,     8,     9,    10,    46,     0,     0,     0,
       0,     0,    46,     0,     0,    46,     0,     0,    97,    82,
      46,     7,     8,     9,    10,     0,     0,     0,     0,   164,
      11,    12,    13,    14,     0,     0,     0,    15,    16,    17,
      18,    19,     0,     0,    20,    21,     0,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
      28,    29,     0,    20,    21,    30,     0,     0,     0,     0,
      31,     0,    32,     0,    33,     0,     0,     0,     0,    28,
      29,   114,   115,   116,    30,    82,   213,     0,    88,    69,
      96,    32,     0,    70,     0,   117,   118,   119,     0,     0,
       0,     0,    88,     0,     0,     6,    88,     7,     8,     9,
      10,     0,   228,     0,    82,   231,    82,   120,   121,     0,
     122,     0,   238,   100,     0,     0,   231,     0,     0,     7,
       8,     9,    10,     0,     0,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,     0,     0,    20,
      21,     0,    22,    23,    24,    25,    26,    27,   279,     0,
       0,     0,     0,     0,     0,    28,    29,     0,     0,     0,
      30,    20,    21,     0,     0,    31,     0,    32,     6,    33,
       7,     8,     9,    10,     0,     0,     0,    28,    29,   258,
       0,     0,    30,     0,     0,    86,     0,    69,   210,    32,
       0,    70,     0,     0,   270,     0,     0,     0,    11,    12,
      13,    14,   277,     0,     0,    15,    16,    17,    18,    19,
     284,     0,    20,    21,     0,    22,    23,    24,    25,    26,
      27,     7,     8,     9,    10,     0,     0,     0,    28,    29,
       0,     0,     0,    30,     0,     0,     0,     0,    31,     0,
      32,     0,    33,     0,     0,     0,     0,     0,     0,    11,
       0,    13,     0,     0,     0,     0,     0,    16,    17,     0,
      19,     0,     0,    20,    21,     0,    22,    23,    24,    25,
       7,     8,     9,    10,   182,     0,     0,     0,     0,    28,
      29,     0,     0,     0,    30,     0,     0,     0,     0,    31,
       0,    32,     0,    33,     0,     0,     0,     0,    11,     0,
      13,     0,     0,     0,     0,     0,    16,    17,     0,    19,
       0,     0,    20,    21,     0,    22,    23,    24,    25,     7,
       8,     9,    10,   233,     0,     0,     0,     0,    28,    29,
       0,     0,     0,    30,     0,     0,     0,     0,    31,     0,
      32,     0,    33,     7,     8,     9,    10,    11,     0,    13,
       0,     7,     8,     9,    10,    16,    17,     0,    19,    80,
       0,    20,    21,     0,    22,    23,    24,    25,     0,     0,
       0,     0,   268,     0,     0,     0,     0,    28,    29,     0,
       0,     0,    30,     0,     0,    20,    21,    31,     0,    32,
       0,    33,     0,    20,    21,     7,     8,     9,    10,     0,
       0,    28,    29,     0,     0,     0,    30,     0,     0,    28,
      29,    69,     0,    32,    30,    70,     0,     0,   269,    69,
       0,    32,     0,    70,     0,     0,     7,     8,     9,    10,
       0,     0,     7,     8,     9,    10,     0,    20,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,    10,    28,    29,     0,     0,     0,    30,     0,
       0,     0,   283,    69,     0,    32,     0,    70,    20,    21,
       7,     8,     9,    10,    20,    21,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,     0,     0,     0,    30,
      28,    29,   194,     0,    69,    30,    32,     0,    70,     0,
      31,     0,    32,     0,    33,     0,     0,    28,    29,     0,
       0,     0,    30,     0,     0,     0,     0,    69,     0,    32,
       0,    70,     0,     0,     0,     0,     0,     0,    28,    29,
       0,  -122,  -122,    30,  -122,  -122,  -122,  -122,    69,     0,
      32,  -122,    70,     0,     0,  -122,  -122,  -122,  -122,  -122,
     154,  -127,  -127,     0,  -127,  -127,  -127,  -127,     0,     0,
       0,  -127,     0,     0,  -107,  -127,  -127,  -127,  -127,  -127,
       0,  -128,  -128,     0,  -128,  -128,  -128,  -128,     0,     0,
       0,  -128,     0,     0,  -104,  -128,  -128,  -128,  -128,  -128,
    -107,     0,     0,  -107,     0,     0,     0,  -107,  -122,     0,
       0,     0,     0,     0,  -105,     0,     0,     0,     0,     0,
    -104,     0,     0,  -104,   123,     0,     0,  -104,  -127,   124,
     125,   126,     0,     0,     0,     0,     0,     0,     0,   123,
    -105,     0,     0,  -105,   124,   125,   126,  -105,  -128,  -129,
    -129,     0,  -129,  -129,  -129,  -129,     0,     0,     0,  -129,
       0,     0,     0,  -129,  -129,  -129,  -129,  -129,     0,     0,
       0,   128,   129,   130,   131,   132,   133,   134,   123,     0,
       0,     0,  -106,   124,   125,   126,     0,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -106,     0,
       0,  -106,     0,     0,     0,  -106,  -129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
      27,     0,     0,    29,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     9,     0,     0,     0,     0,     0,
       3,     0,     0,     5,     0,     0,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,    13,     0,     0,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
       0,    21,     0,     0,     0,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   127,     0,   127,     0,   127,     0,   127,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   122,     0,   122,     0,   122,
       0,   122,     0
};

static const short int yycheck[] =
{
       3,   110,    34,    33,     3,    15,    15,   101,    21,    12,
     104,    14,    15,    16,    17,   137,    19,    20,     0,    17,
     257,    19,    31,   139,    33,    30,    69,    31,    31,    72,
      33,    34,    15,     3,    56,    34,    41,   153,     0,   276,
      70,   157,    47,    30,    56,    15,    68,     4,    31,    36,
       3,     4,     5,     6,    70,     3,     4,     5,     6,     6,
      47,    31,    69,    33,    34,    69,     3,    10,    11,    76,
      13,    14,    15,    16,    56,    56,    77,    20,    15,    35,
      36,    24,    25,    26,    27,    28,    71,    68,    28,    29,
      30,    71,    45,    46,    31,    69,    33,    34,   111,   112,
     113,   274,   275,    69,    43,    70,   136,   110,    61,    62,
      42,    69,    12,    66,    74,    70,     3,   211,    71,    72,
      73,    70,    75,    71,   246,    73,    69,    75,    15,    70,
     139,    69,   135,    43,    69,    69,   139,   167,   232,    72,
     110,    72,   152,   152,    31,   254,    33,    34,    69,   152,
      69,   154,   155,   156,    76,   158,   159,    12,   161,    76,
     158,    12,    17,    18,    19,   168,    17,    12,    30,   139,
      72,    76,    17,   110,   114,   115,   116,   117,   118,   119,
     120,   121,   152,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    70,    72,    55,   168,    72,
      70,    37,   139,    58,    59,    60,    61,    62,    63,    64,
      65,    70,    63,    64,    65,   152,    61,    62,    63,    64,
      65,    67,    70,   110,   227,    71,    37,    36,    70,    75,
      69,   168,    76,    70,   237,   267,    70,    70,     1,   275,
     165,   252,   165,    33,     3,     4,     5,     6,   152,   252,
     174,   254,   139,   252,   194,   139,   196,   227,   295,   262,
     249,   284,   156,    -1,   267,   152,   269,   237,   267,    -1,
      -1,   274,   275,    -1,    -1,   278,    -1,    -1,   281,    -1,
     283,   168,   252,    -1,   254,    -1,   289,    46,    -1,   292,
     227,   227,   262,    -1,   297,    -1,    -1,   267,    -1,   269,
     237,   237,    61,    62,   274,   275,    -1,    66,   278,    -1,
      -1,    -1,    71,   283,    73,   252,    75,   254,    -1,   289,
      -1,    -1,   292,    -1,    -1,   262,   262,   297,    -1,    -1,
     267,    -1,   269,   269,    -1,    -1,    -1,   274,   275,    -1,
     227,   278,   278,    -1,    -1,    -1,   283,   283,    -1,    -1,
     237,    -1,   289,   289,    -1,   292,   292,    18,    -1,    -1,
     297,   297,    23,    24,    25,   252,    27,   254,    -1,    -1,
      31,    32,    33,    -1,    -1,   262,    -1,    -1,    -1,    -1,
     267,    -1,   269,    -1,    -1,    -1,    -1,   274,   275,     0,
       1,   278,     3,     4,     5,     6,   283,    -1,    -1,    -1,
      -1,    -1,   289,    -1,    -1,   292,    -1,    -1,    69,    70,
     297,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    80,
      31,    32,    33,    34,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    -1,    -1,    45,    46,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    45,    46,    66,    -1,    -1,    -1,    -1,
      71,    -1,    73,    -1,    75,    -1,    -1,    -1,    -1,    61,
      62,     7,     8,     9,    66,   136,   137,    -1,   139,    71,
      72,    73,    -1,    75,    -1,    21,    22,    23,    -1,    -1,
      -1,    -1,   153,    -1,    -1,     1,   157,     3,     4,     5,
       6,    -1,   163,    -1,   165,   166,   167,    43,    44,    -1,
      46,    -1,   173,   174,    -1,    -1,   177,    -1,    -1,     3,
       4,     5,     6,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    -1,    -1,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      66,    45,    46,    -1,    -1,    71,    -1,    73,     1,    75,
       3,     4,     5,     6,    -1,    -1,    -1,    61,    62,   240,
      -1,    -1,    66,    -1,    -1,   246,    -1,    71,    72,    73,
      -1,    75,    -1,    -1,   255,    -1,    -1,    -1,    31,    32,
      33,    34,   263,    -1,    -1,    38,    39,    40,    41,    42,
     271,    -1,    45,    46,    -1,    48,    49,    50,    51,    52,
      53,     3,     4,     5,     6,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,
      73,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,
      42,    -1,    -1,    45,    46,    -1,    48,    49,    50,    51,
       3,     4,     5,     6,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,
      -1,    73,    -1,    75,    -1,    -1,    -1,    -1,    31,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,
      -1,    -1,    45,    46,    -1,    48,    49,    50,    51,     3,
       4,     5,     6,    56,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,
      73,    -1,    75,     3,     4,     5,     6,    31,    -1,    33,
      -1,     3,     4,     5,     6,    39,    40,    -1,    42,    19,
      -1,    45,    46,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    61,    62,    -1,
      -1,    -1,    66,    -1,    -1,    45,    46,    71,    -1,    73,
      -1,    75,    -1,    45,    46,     3,     4,     5,     6,    -1,
      -1,    61,    62,    -1,    -1,    -1,    66,    -1,    -1,    61,
      62,    71,    -1,    73,    66,    75,    -1,    -1,    70,    71,
      -1,    73,    -1,    75,    -1,    -1,     3,     4,     5,     6,
      -1,    -1,     3,     4,     5,     6,    -1,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    61,    62,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    70,    71,    -1,    73,    -1,    75,    45,    46,
       3,     4,     5,     6,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    66,
      61,    62,    46,    -1,    71,    66,    73,    -1,    75,    -1,
      71,    -1,    73,    -1,    75,    -1,    -1,    61,    62,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,    73,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    10,    11,    66,    13,    14,    15,    16,    71,    -1,
      73,    20,    75,    -1,    -1,    24,    25,    26,    27,    28,
      29,    10,    11,    -1,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    -1,    -1,    43,    24,    25,    26,    27,    28,
      -1,    10,    11,    -1,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    -1,    -1,    43,    24,    25,    26,    27,    28,
      69,    -1,    -1,    72,    -1,    -1,    -1,    76,    77,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    72,    12,    -1,    -1,    76,    77,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      69,    -1,    -1,    72,    17,    18,    19,    76,    77,    10,
      11,    -1,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    65,    12,    -1,
      -1,    -1,    43,    17,    18,    19,    -1,    60,    61,    62,
      63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    72,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    56,    79,    80,    79,     0,     1,     3,     4,     5,
       6,    31,    32,    33,    34,    38,    39,    40,    41,    42,
      45,    46,    48,    49,    50,    51,    52,    53,    61,    62,
      66,    71,    73,    75,    81,    82,    83,    84,    90,    91,
      92,    93,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   114,   115,   116,   120,   121,   123,   127,   129,   133,
      56,   129,   129,   102,   107,   110,   129,   129,   130,    71,
      75,    90,   104,   105,   106,   129,   130,   130,   132,    91,
      19,    85,    90,    95,    96,    98,    90,    94,    90,   100,
     101,    70,    90,    93,    93,    93,    72,    90,   101,   107,
      90,   111,   112,   113,    95,    97,   108,   110,    82,    56,
      68,    30,    41,    47,     7,     8,     9,    21,    22,    23,
      43,    44,    46,    12,    17,    18,    19,    58,    59,    60,
      61,    62,    63,    64,    65,    67,    71,    75,     6,    77,
      10,    11,    13,    14,    15,    16,    20,    24,    25,    26,
      27,    28,    69,    86,    29,    71,    71,    43,    42,    69,
      70,    69,   135,    70,    90,    69,    69,    69,   124,    70,
      72,    72,    72,    70,    69,   135,    74,    69,   135,    76,
      76,    76,    56,    84,    91,    91,    91,    93,    93,    93,
      93,    93,    93,    93,    46,    93,    43,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,   129,
      72,    95,    99,    90,    94,   100,   114,   109,   110,   100,
     129,   129,   132,   100,   130,   131,   129,   119,    90,    96,
      98,    90,    95,    56,    83,    87,    88,   122,    90,   113,
      36,    93,    93,   135,    72,    76,    70,    72,    72,    70,
      88,   135,    55,    56,    68,    37,   125,    88,    90,    94,
      70,    70,   122,    35,    36,   117,   118,    81,    56,    70,
      90,    37,   118,    76,   134,   128,    88,    90,    70,    54,
      88,    69,   126,    70,    90,    87,    89,    89,   118,    70,
      88,   129,    70,    88,   126,    88,    88,    70,   117,    88
};


/* Prevent warning if -Wmissing-prototypes.  */
int yyparse (void);

/* Error token number */
#define YYTERROR 1

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */


#define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))							\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))

/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# define YY_LOCATION_PRINT(File, Loc)			\
    fprintf (File, "%d.%d-%d.%d",			\
	     (Loc).first_line, (Loc).first_column,	\
	     (Loc).last_line,  (Loc).last_column)
#endif


#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#define YYLEX yylex ()

YYSTYPE yylval;

YYLTYPE yylloc;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)							     \
   do { YYRESULTTAG yyflag = YYE; if (yyflag != yyok) return yyflag; }	     \
   while (YYID (0))

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			    \
do {									    \
  if (yydebug)								    \
    {									    \
      YYFPRINTF (stderr, "%s ", Title);					    \
      yy_symbol_print (stderr, Type,					    \
		       Value, Location);  \
      YYFPRINTF (stderr, "\n");						    \
    }									    \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
# if (! defined __cplusplus \
      || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	  && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL))
#  define YYSTACKEXPANDABLE 1
# else
#  define YYSTACKEXPANDABLE 0
# endif
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)			\
  do {							\
    if (Yystack->yyspaceLeft < YYHEADROOM)		\
      yyexpandGLRStack (Yystack);			\
  } while (YYID (0))
#else
# define YY_RESERVE_GLRSTACK(Yystack)			\
  do {							\
    if (Yystack->yyspaceLeft < YYHEADROOM)		\
      yyMemoryExhausted (Yystack);			\
  } while (YYID (0))
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef short int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the first token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static void yyFail (yyGLRStack* yystackp, const char* yymsg)
  __attribute__ ((__noreturn__));
static void
yyFail (yyGLRStack* yystackp, const char* yymsg)
{
  if (yymsg != NULL)
    yyerror (yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static void yyMemoryExhausted (yyGLRStack* yystackp)
  __attribute__ ((__noreturn__));
static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) __attribute__ ((__unused__));
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  yyGLRState* s;
  int i;
  s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
      YYASSERT (s->yyresolved);
      yyvsp[i].yystate.yyresolved = yytrue;
      yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     __attribute__ ((__unused__));
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
/*ARGSUSED*/ static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
	      YYSTYPE* yyvalp,
	      YYLTYPE* YYOPTIONAL_LOC (yylocp),
	      yyGLRStack* yystackp
	      )
{
  yybool yynormal __attribute__ ((__unused__)) =
    (yystackp->yysplitPoint == NULL);
  int yylow;
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)						     \
  return yyerror (YY_("syntax error: cannot back up")),     \
	 yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
        case 3:

/* Line 936 of glr.c  */
#line 173 "parser.y"
    { pushContext (+DEF, +CLASS, +IMPORT, 0); ;}
    break;

  case 4:

/* Line 936 of glr.c  */
#line 174 "parser.y"
    { theProgram = makeModule (0, (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 5:

/* Line 936 of glr.c  */
#line 175 "parser.y"
    { theProgram = makeModule (0, makeList ()); ;}
    break;

  case 7:

/* Line 936 of glr.c  */
#line 180 "parser.y"
    { ((*yyvalp).List) = append ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 8:

/* Line 936 of glr.c  */
#line 184 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List); ;}
    break;

  case 9:

/* Line 936 of glr.c  */
#line 185 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List); ;}
    break;

  case 10:

/* Line 936 of glr.c  */
#line 186 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 11:

/* Line 936 of glr.c  */
#line 187 "parser.y"
    { ((*yyvalp).List) = makeList (); ;}
    break;

  case 12:

/* Line 936 of glr.c  */
#line 191 "parser.y"
    { ((*yyvalp).List) = makeListNonNull ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 13:

/* Line 936 of glr.c  */
#line 193 "parser.y"
    { ((*yyvalp).List) = addNonNullItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 15:

/* Line 936 of glr.c  */
#line 198 "parser.y"
    { ((*yyvalp).Node) = NULL; ;}
    break;

  case 16:

/* Line 936 of glr.c  */
#line 199 "parser.y"
    { checkContext (BREAK, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)); 
                                      ((*yyvalp).Node) = makeBreak ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)); ;}
    break;

  case 17:

/* Line 936 of glr.c  */
#line 201 "parser.y"
    { checkContext (CONTINUE, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc));
                                      ((*yyvalp).Node) = makeContinue ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)); ;}
    break;

  case 18:

/* Line 936 of glr.c  */
#line 203 "parser.y"
    { checkContext (RETURN, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc));
                                      ((*yyvalp).Node) = makeReturn ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 19:

/* Line 936 of glr.c  */
#line 205 "parser.y"
    { checkContext (RETURN, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc));
                                      ((*yyvalp).Node) = makeReturn ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), NULL); ;}
    break;

  case 20:

/* Line 936 of glr.c  */
#line 207 "parser.y"
    { ((*yyvalp).Node) = makeRaise ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 21:

/* Line 936 of glr.c  */
#line 208 "parser.y"
    { checkContext (IMPORT, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc));
	  	   		      ((*yyvalp).Node) = makeImportModule ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 22:

/* Line 936 of glr.c  */
#line 211 "parser.y"
    { checkContext (IMPORT, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc)); 
	                              ((*yyvalp).Node) = makeImportFrom ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 23:

/* Line 936 of glr.c  */
#line 213 "parser.y"
    { ((*yyvalp).Node) = makeGlobal ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 25:

/* Line 936 of glr.c  */
#line 216 "parser.y"
    { ((*yyvalp).Node) = makeAugAssign ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), 
                                                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), makeId ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.CString)), 
                                                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 26:

/* Line 936 of glr.c  */
#line 220 "parser.y"
    { ((*yyvalp).Node) = makePrint ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 27:

/* Line 936 of glr.c  */
#line 221 "parser.y"
    { ((*yyvalp).Node) = makePrint ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 28:

/* Line 936 of glr.c  */
#line 223 "parser.y"
    { ((*yyvalp).Node) = makePrintln ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 29:

/* Line 936 of glr.c  */
#line 225 "parser.y"
    { ((*yyvalp).Node) = makePrintln ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node), 
                                            makeExprList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), makeList ())); ;}
    break;

  case 30:

/* Line 936 of glr.c  */
#line 228 "parser.y"
    { ((*yyvalp).Node) = makePrintln ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 31:

/* Line 936 of glr.c  */
#line 230 "parser.y"
    { ((*yyvalp).Node) = makePrintln ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), NULL, 
                                            makeExprList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), makeList ())); ;}
    break;

  case 32:

/* Line 936 of glr.c  */
#line 235 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 45:

/* Line 936 of glr.c  */
#line 244 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List); (*yylocp) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc); ;}
    break;

  case 46:

/* Line 936 of glr.c  */
#line 245 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List); (*yylocp) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc); ;}
    break;

  case 47:

/* Line 936 of glr.c  */
#line 246 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.List); (*yylocp) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (4))].yystate.yyloc); ;}
    break;

  case 48:

/* Line 936 of glr.c  */
#line 249 "parser.y"
    { ((*yyvalp).Node) = makeSuite ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 49:

/* Line 936 of glr.c  */
#line 252 "parser.y"
    { ((*yyvalp).Node) = makeBlock ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 50:

/* Line 936 of glr.c  */
#line 257 "parser.y"
    { ((*yyvalp).Node) = makeLambda ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 51:

/* Line 936 of glr.c  */
#line 259 "parser.y"
    { ((*yyvalp).Node) = makeIfExpr ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (5))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (5))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (5))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (5))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 53:

/* Line 936 of glr.c  */
#line 265 "parser.y"
    { ((*yyvalp).Node) = makeComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 54:

/* Line 936 of glr.c  */
#line 266 "parser.y"
    { ((*yyvalp).Node) = makeOr ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 55:

/* Line 936 of glr.c  */
#line 267 "parser.y"
    { ((*yyvalp).Node) = makeAnd ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 56:

/* Line 936 of glr.c  */
#line 269 "parser.y"
    { ((*yyvalp).Node) = unop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), "not", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 57:

/* Line 936 of glr.c  */
#line 273 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 58:

/* Line 936 of glr.c  */
#line 275 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.List), "notin", (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 59:

/* Line 936 of glr.c  */
#line 277 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), "in", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 60:

/* Line 936 of glr.c  */
#line 279 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), "is", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 61:

/* Line 936 of glr.c  */
#line 281 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.List), "isnot", (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 62:

/* Line 936 of glr.c  */
#line 283 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), "<", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 63:

/* Line 936 of glr.c  */
#line 285 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), ">", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 64:

/* Line 936 of glr.c  */
#line 287 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), "<=", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 65:

/* Line 936 of glr.c  */
#line 289 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), ">=", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 66:

/* Line 936 of glr.c  */
#line 291 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), "==", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 67:

/* Line 936 of glr.c  */
#line 293 "parser.y"
    { ((*yyvalp).List) = addComparison ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), "!=", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 69:

/* Line 936 of glr.c  */
#line 298 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "|", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 70:

/* Line 936 of glr.c  */
#line 299 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "^", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 71:

/* Line 936 of glr.c  */
#line 300 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "&", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 72:

/* Line 936 of glr.c  */
#line 301 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "<<", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 73:

/* Line 936 of glr.c  */
#line 302 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), ">>", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 74:

/* Line 936 of glr.c  */
#line 303 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "+", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 75:

/* Line 936 of glr.c  */
#line 304 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "-", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 76:

/* Line 936 of glr.c  */
#line 305 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "*", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 77:

/* Line 936 of glr.c  */
#line 306 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "/", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 78:

/* Line 936 of glr.c  */
#line 307 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "%", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 79:

/* Line 936 of glr.c  */
#line 308 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "//", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 80:

/* Line 936 of glr.c  */
#line 309 "parser.y"
    { ((*yyvalp).Node) = unop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), "-", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 81:

/* Line 936 of glr.c  */
#line 310 "parser.y"
    { ((*yyvalp).Node) = unop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), "+", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 82:

/* Line 936 of glr.c  */
#line 311 "parser.y"
    { ((*yyvalp).Node) = unop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), "~", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 83:

/* Line 936 of glr.c  */
#line 312 "parser.y"
    { ((*yyvalp).Node) = binop ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), "**", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 84:

/* Line 936 of glr.c  */
#line 316 "parser.y"
    { ((*yyvalp).Node) = NULL; ;}
    break;

  case 86:

/* Line 936 of glr.c  */
#line 321 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 87:

/* Line 936 of glr.c  */
#line 322 "parser.y"
    { ((*yyvalp).List) = addItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 88:

/* Line 936 of glr.c  */
#line 326 "parser.y"
    { ((*yyvalp).Node) = makeExprList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 89:

/* Line 936 of glr.c  */
#line 330 "parser.y"
    { ((*yyvalp).List) = makeList (); ;}
    break;

  case 90:

/* Line 936 of glr.c  */
#line 331 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List); ;}
    break;

  case 91:

/* Line 936 of glr.c  */
#line 335 "parser.y"
    { ((*yyvalp).Node) = makeExprList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 92:

/* Line 936 of glr.c  */
#line 339 "parser.y"
    { ((*yyvalp).Node) = makeExprList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 95:

/* Line 936 of glr.c  */
#line 348 "parser.y"
    { ((*yyvalp).Node) = makeTuple ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.Node))); ;}
    break;

  case 96:

/* Line 936 of glr.c  */
#line 350 "parser.y"
    { ((*yyvalp).Node) = makeTuple ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 97:

/* Line 936 of glr.c  */
#line 355 "parser.y"
    { ((*yyvalp).Node) = makeCall ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 98:

/* Line 936 of glr.c  */
#line 357 "parser.y"
    { ((*yyvalp).Node) = makeCall ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), 
                                             makeExprList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc))); ;}
    break;

  case 99:

/* Line 936 of glr.c  */
#line 359 "parser.y"
    { ((*yyvalp).Node) = makeTuple ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc)); ;}
    break;

  case 100:

/* Line 936 of glr.c  */
#line 360 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 101:

/* Line 936 of glr.c  */
#line 361 "parser.y"
    { ((*yyvalp).Node) = makeDictDisplay ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 102:

/* Line 936 of glr.c  */
#line 362 "parser.y"
    { ((*yyvalp).Node) = makeListDisplay ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 103:

/* Line 936 of glr.c  */
#line 363 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 108:

/* Line 936 of glr.c  */
#line 368 "parser.y"
    { ((*yyvalp).Node) = makeIntLiteral ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.String)); ;}
    break;

  case 109:

/* Line 936 of glr.c  */
#line 369 "parser.y"
    { ((*yyvalp).Node) = makeFloatLiteral ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.String)); ;}
    break;

  case 110:

/* Line 936 of glr.c  */
#line 370 "parser.y"
    { ((*yyvalp).Node) = makeStringLiteral ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.String)); ;}
    break;

  case 112:

/* Line 936 of glr.c  */
#line 375 "parser.y"
    { (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.String)->insert ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.String)->size ()-1, *(((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.String), 1, 
                                              (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.String)->size ()-2); 
                                  delete (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.String);
                                  ((*yyvalp).String) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.String); ;}
    break;

  case 113:

/* Line 936 of glr.c  */
#line 382 "parser.y"
    { ((*yyvalp).Node) = makeAttributeRef ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 114:

/* Line 936 of glr.c  */
#line 386 "parser.y"
    { ((*yyvalp).Node) = makeSubscription ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 115:

/* Line 936 of glr.c  */
#line 391 "parser.y"
    { ((*yyvalp).Node) = makeSlicing ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (6))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (6))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 118:

/* Line 936 of glr.c  */
#line 400 "parser.y"
    { ((*yyvalp).Node) = makeTargetList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 119:

/* Line 936 of glr.c  */
#line 404 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 120:

/* Line 936 of glr.c  */
#line 405 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node)); addItem (((*yyvalp).List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 121:

/* Line 936 of glr.c  */
#line 406 "parser.y"
    { ((*yyvalp).List) = addItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 123:

/* Line 936 of glr.c  */
#line 411 "parser.y"
    { ((*yyvalp).Node) = makeTypedId ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 124:

/* Line 936 of glr.c  */
#line 412 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 125:

/* Line 936 of glr.c  */
#line 413 "parser.y"
    { ((*yyvalp).Node) = makeTargetList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.Node))); ;}
    break;

  case 126:

/* Line 936 of glr.c  */
#line 414 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 130:

/* Line 936 of glr.c  */
#line 421 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 131:

/* Line 936 of glr.c  */
#line 422 "parser.y"
    { ((*yyvalp).List) = addItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 132:

/* Line 936 of glr.c  */
#line 426 "parser.y"
    { ((*yyvalp).List) = makeList (); ;}
    break;

  case 133:

/* Line 936 of glr.c  */
#line 427 "parser.y"
    { ((*yyvalp).List) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List); ;}
    break;

  case 134:

/* Line 936 of glr.c  */
#line 431 "parser.y"
    { ((*yyvalp).Node) = makePair ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 135:

/* Line 936 of glr.c  */
#line 436 "parser.y"
    { ((*yyvalp).Node) = makeAssign ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 136:

/* Line 936 of glr.c  */
#line 438 "parser.y"
    { ((*yyvalp).Node) = makeAssign ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 143:

/* Line 936 of glr.c  */
#line 451 "parser.y"
    { ((*yyvalp).Node) = makeIf ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (6))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (6))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((6) - (6))].yystate.yysemantics.yysval.Node)); popContext (); ;}
    break;

  case 145:

/* Line 936 of glr.c  */
#line 457 "parser.y"
    { ((*yyvalp).Node) = makeIf ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (5))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (5))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (5))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (5))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 146:

/* Line 936 of glr.c  */
#line 461 "parser.y"
    { ((*yyvalp).Node) = NULL; ;}
    break;

  case 147:

/* Line 936 of glr.c  */
#line 462 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 148:

/* Line 936 of glr.c  */
#line 465 "parser.y"
    { pushContext (-CLASS, -IMPORT, -DEF, 0); ;}
    break;

  case 149:

/* Line 936 of glr.c  */
#line 469 "parser.y"
    { ((*yyvalp).Node) = makeWhile ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (6))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (6))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((6) - (6))].yystate.yysemantics.yysval.Node)); popContext (); ;}
    break;

  case 150:

/* Line 936 of glr.c  */
#line 475 "parser.y"
    { ((*yyvalp).Node) = makeFor ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (8))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((7) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((8) - (8))].yystate.yysemantics.yysval.Node)); popContext (); ;}
    break;

  case 151:

/* Line 936 of glr.c  */
#line 479 "parser.y"
    { pushContext (-CLASS, -IMPORT, -DEF, 
	     	       	 	      +BREAK, +CONTINUE, 0); ;}
    break;

  case 152:

/* Line 936 of glr.c  */
#line 485 "parser.y"
    { ((*yyvalp).Node) = makeTry ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (5))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (5))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (5))].yystate.yysemantics.yysval.List)); popContext (); ;}
    break;

  case 153:

/* Line 936 of glr.c  */
#line 488 "parser.y"
    { pushContext (-DEF, -CLASS, -IMPORT, 0); ;}
    break;

  case 154:

/* Line 936 of glr.c  */
#line 492 "parser.y"
    { ((*yyvalp).List) = addItem (addItem (makeList (NULL), NULL), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 155:

/* Line 936 of glr.c  */
#line 494 "parser.y"
    { ((*yyvalp).List) = addItem (addItem (makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (5))].yystate.yysemantics.yysval.Node)), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (5))].yystate.yysemantics.yysval.Node)), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (5))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 156:

/* Line 936 of glr.c  */
#line 496 "parser.y"
    { ((*yyvalp).List) = addItem (addItem (addItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.List), NULL), NULL), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 157:

/* Line 936 of glr.c  */
#line 498 "parser.y"
    { ((*yyvalp).List) = addItem (addItem (addItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yysemantics.yysval.List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (6))].yystate.yysemantics.yysval.Node)), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (6))].yystate.yysemantics.yysval.Node)), (((yyGLRStackItem const *)yyvsp)[YYFILL ((6) - (6))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 158:

/* Line 936 of glr.c  */
#line 502 "parser.y"
    { ((*yyvalp).Node) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.Node); ;}
    break;

  case 159:

/* Line 936 of glr.c  */
#line 503 "parser.y"
    { ((*yyvalp).Node) = NULL; ;}
    break;

  case 160:

/* Line 936 of glr.c  */
#line 508 "parser.y"
    { checkContext (DEF, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yyloc));
		  pushContext (-BREAK, -CONTINUE, +RETURN, -CLASS, -IMPORT, 0); ;}
    break;

  case 161:

/* Line 936 of glr.c  */
#line 510 "parser.y"
    { ((*yyvalp).Node) = makeDef ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (8))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((8) - (8))].yystate.yysemantics.yysval.Node)); popContext (); ;}
    break;

  case 162:

/* Line 936 of glr.c  */
#line 515 "parser.y"
    { ((*yyvalp).Node) = makeId ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.String)); ;}
    break;

  case 163:

/* Line 936 of glr.c  */
#line 519 "parser.y"
    { ((*yyvalp).List) = makeList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 164:

/* Line 936 of glr.c  */
#line 520 "parser.y"
    { ((*yyvalp).List) = addItem ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.List), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.Node)); ;}
    break;

  case 165:

/* Line 936 of glr.c  */
#line 524 "parser.y"
    { ((*yyvalp).Node) = makeIdList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 166:

/* Line 936 of glr.c  */
#line 528 "parser.y"
    { ((*yyvalp).Node) = makeIdList (yylloc, makeList ()); ;}
    break;

  case 167:

/* Line 936 of glr.c  */
#line 529 "parser.y"
    { ((*yyvalp).Node) = makeIdList ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.List)); ;}
    break;

  case 168:

/* Line 936 of glr.c  */
#line 534 "parser.y"
    { checkContext (CLASS, (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yyloc)); 
	        pushContext (+DEF, -RETURN, -BREAK, -CONTINUE, 
			     -CLASS, -IMPORT, 0); ;}
    break;

  case 169:

/* Line 936 of glr.c  */
#line 537 "parser.y"
    { ((*yyvalp).Node) = makeClass ((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (8))].yystate.yyloc), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (8))].yystate.yysemantics.yysval.Node), (((yyGLRStackItem const *)yyvsp)[YYFILL ((8) - (8))].yystate.yysemantics.yysval.Node)); 
	    			  popContext (); ;}
    break;



/* Line 936 of glr.c  */
#line 2527 "parser.cc"
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


/*ARGSUSED*/ static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {
      
      default: break;
    }
}

			      /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
		&yys->yysemantics.yysval, &yys->yyloc);
  else
    {
#if YYDEBUG
      if (yydebug)
	{
	  if (yys->yysemantics.yyfirstVal)
	    YYFPRINTF (stderr, "%s unresolved ", yymsg);
	  else
	    YYFPRINTF (stderr, "%s incomplete ", yymsg);
	  yy_symbol_print (stderr, yystos[yys->yylrState],
			   NULL, &yys->yyloc);
	  YYFPRINTF (stderr, "\n");
	}
#endif

      if (yys->yysemantics.yyfirstVal)
	{
	  yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
	  yyGLRState *yyrh;
	  int yyn;
	  for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
	       yyn > 0;
	       yyrh = yyrh->yypred, yyn -= 1)
	    yydestroyGLRState (yymsg, yyrh);
	}
    }
}

/** Left-hand-side symbol for rule #RULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yyis_pact_ninf(yystate) \
  ((yystate) == YYPACT_NINF)

/** True iff LR state STATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yyis_pact_ninf (yypact[yystate]);
}

/** The default reduction for STATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yyis_table_ninf(yytable_value) \
  YYID (0)

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *CONFLICTS to a pointer into yyconfl to 0-terminated list of
 *  conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
		int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yyis_table_ninf (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yylhs)
{
  int yyr;
  yyr = yypgoto[yylhs - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yylhs - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

				/* GLRStates */

/** Return a fresh GLRStackItem.  Callers should call
 * YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 * headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  RULENUM on the semantic values in RHS to the list of
 *  alternative actions for STATE.  Assumes that RHS comes from
 *  stack #K of *STACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
		     yyGLRState* rhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  yynewOption->yystate = rhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

				/* GLRStacks */

/** Initialize SET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = NULL;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize STACK to a single empty stack, with total maximum
 *  capacity for all stacks of SIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = NULL;
  yystackp->yylastDeleted = NULL;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If STACK is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yysize, yynewSize;
  size_t yyn;
  yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
	{
	  yyGLRState* yys0 = &yyp0->yystate;
	  yyGLRState* yys1 = &yyp1->yystate;
	  if (yys0->yypred != NULL)
	    yys1->yypred =
	      YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
	  if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != NULL)
	    yys1->yysemantics.yyfirstVal =
	      YYRELOC(yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
	}
      else
	{
	  yySemanticOption* yyv0 = &yyp0->yyoption;
	  yySemanticOption* yyv1 = &yyp1->yyoption;
	  if (yyv0->yystate != NULL)
	    yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
	  if (yyv0->yynext != NULL)
	    yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
	}
    }
  if (yystackp->yysplitPoint != NULL)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
				 yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != NULL)
      yystackp->yytops.yystates[yyn] =
	YYRELOC (yystackp->yyitems, yynewItems,
		 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that S is a GLRState somewhere on STACK, update the
 *  splitpoint of STACK, if needed, so that it is at least as deep as
 *  S.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != NULL && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #K in STACK.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != NULL)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = NULL;
}

/** Undelete the last stack that was marked as deleted.  Can only be
    done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == NULL || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = NULL;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == NULL)
	{
	  if (yyi == yyj)
	    {
	      YYDPRINTF ((stderr, "Removing dead stacks.\n"));
	    }
	  yystackp->yytops.yysize -= 1;
	}
      else
	{
	  yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
	  /* In the current implementation, it's unnecessary to copy
	     yystackp->yytops.yylookaheadNeeds[yyi] since, after
	     yyremoveDeletes returns, the parser immediately either enters
	     deterministic operation or shifts a token.  However, it doesn't
	     hurt, and the code might evolve to need it.  */
	  yystackp->yytops.yylookaheadNeeds[yyj] =
	    yystackp->yytops.yylookaheadNeeds[yyi];
	  if (yyj != yyi)
	    {
	      YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
			  (unsigned long int) yyi, (unsigned long int) yyj));
	    }
	  yyj += 1;
	}
      yyi += 1;
    }
}

/** Shift to a new state on stack #K of STACK, corresponding to LR state
 * LRSTATE, at input position POSN, with (resolved) semantic value SVAL.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
	    size_t yyposn,
	    YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #K of YYSTACK, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
		 size_t yyposn, yyGLRState* rhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = NULL;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, rhs, yyrule);
}

/** Pop the symbols consumed by reduction #RULE from the top of stack
 *  #K of STACK, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *VALP to the resulting value,
 *  and *LOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
	    YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == NULL)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* rhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      return yyuserAction (yyrule, yynrhs, rhs,
			   yyvalp, yylocp, yystackp);
    }
  else
    {
      /* At present, doAction is never called in nondeterministic
       * mode, so this branch is never taken.  It is here in
       * anticipation of a future feature that will allow immediate
       * evaluation of selected actions in nondeterministic mode.  */
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
	= yystackp->yytops.yystates[yyk];
      if (yynrhs == 0)
	/* Set default location.  */
	yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
	{
	  yys = yys->yypred;
	  YYASSERT (yys);
	}
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
			   yyvalp, yylocp, yystackp);
    }
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)		\
do {					\
  if (yydebug)				\
    yy_reduce_print Args;		\
} while (YYID (0))

/*----------------------------------------------------------.
| Report that the RULE is going to be reduced on stack #K.  |
`----------------------------------------------------------*/

/*ARGSUSED*/ static inline void
yy_reduce_print (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
		 YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  int yynrhs = yyrhsLength (yyrule);
  yybool yynormal __attribute__ ((__unused__)) =
    (yystackp->yysplitPoint == NULL);
  yyGLRStackItem* yyvsp = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
  int yylow = 1;
  int yyi;
  YYUSE (yyvalp);
  YYUSE (yylocp);
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
	     (unsigned long int) yyk, yyrule - 1,
	     (unsigned long int) yyrline[yyrule]);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yysemantics.yysval)
		       , &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)		       );
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop items off stack #K of STACK according to grammar rule RULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with RULE and store its value with the
 *  newly pushed state, if FORCEEVAL or if STACK is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #K from
 *  the STACK.  In this case, the (necessarily deferred) semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
	     yybool yyforceEval)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == NULL)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YY_REDUCE_PRINT ((yystackp, yyk, yyrule, &yysval, &yyloc));
      YYCHK (yydoAction (yystackp, yyk, yyrule, &yysval,
			 &yyloc));
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
		  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
				 yylhsNonterm (yyrule)),
		  yyposn, &yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
	   0 < yyn; yyn -= 1)
	{
	  yys = yys->yypred;
	  YYASSERT (yys);
	}
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
		  "Reduced stack %lu by rule #%d; action deferred.  Now in state %d.\n",
		  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
	if (yyi != yyk && yystackp->yytops.yystates[yyi] != NULL)
	  {
	    yyGLRState* yyp, *yysplit = yystackp->yysplitPoint;
	    yyp = yystackp->yytops.yystates[yyi];
	    while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
	      {
		if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
		  {
		    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
		    yymarkStackDeleted (yystackp, yyk);
		    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
				(unsigned long int) yyk,
				(unsigned long int) yyi));
		    return yyok;
		  }
		yyp = yyp->yypred;
	      }
	  }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == NULL)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = NULL;

      if (yystackp->yytops.yycapacity
	  > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
	yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
	(yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
				  (yystackp->yytops.yycapacity
				   * sizeof yynewStates[0]));
      if (yynewStates == NULL)
	yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
	(yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
			     (yystackp->yytops.yycapacity
			      * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == NULL)
	yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff Y0 and Y1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
	   yyn = yyrhsLength (yyy0->yyrule);
	   yyn > 0;
	   yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
	if (yys0->yyposn != yys1->yyposn)
	  return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (Y0,Y1), destructively merge the
 *  alternative semantic values for the RHS-symbols of Y1 and Y0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
	break;
      else if (yys0->yyresolved)
	{
	  yys1->yyresolved = yytrue;
	  yys1->yysemantics.yysval = yys0->yysemantics.yysval;
	}
      else if (yys1->yyresolved)
	{
	  yys0->yyresolved = yytrue;
	  yys0->yysemantics.yysval = yys1->yysemantics.yysval;
	}
      else
	{
	  yySemanticOption** yyz0p;
	  yySemanticOption* yyz1;
	  yyz0p = &yys0->yysemantics.yyfirstVal;
	  yyz1 = yys1->yysemantics.yyfirstVal;
	  while (YYID (yytrue))
	    {
	      if (yyz1 == *yyz0p || yyz1 == NULL)
		break;
	      else if (*yyz0p == NULL)
		{
		  *yyz0p = yyz1;
		  break;
		}
	      else if (*yyz0p < yyz1)
		{
		  yySemanticOption* yyz = *yyz0p;
		  *yyz0p = yyz1;
		  yyz1 = yyz1->yynext;
		  (*yyz0p)->yynext = yyz;
		}
	      yyz0p = &(*yyz0p)->yynext;
	    }
	  yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
	}
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
	return 0;
      else
	return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
				   yyGLRStack* yystackp);


/** Resolve the previous N states starting at and including state S.  If result
 *  != yyok, some states may have been left unresolved possibly with empty
 *  semantic option chains.  Regardless of whether result = yyok, each state
 *  has been left with consistent data so that yydestroyGLRState can be invoked
 *  if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
		 yyGLRStack* yystackp)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp));
      if (! yys->yyresolved)
	YYCHK (yyresolveValue (yys, yystackp));
    }
  return yyok;
}

/** Resolve the states for the RHS of OPT, perform its user action, and return
 *  the semantic value and location.  Regardless of whether result = yyok, all
 *  RHS states have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
		 YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs;
  int yychar_current;
  YYSTYPE yylval_current;
  YYLTYPE yylloc_current;
  YYRESULTTAG yyflag;

  yynrhs = yyrhsLength (yyopt->yyrule);
  yyflag = yyresolveStates (yyopt->yystate, yynrhs, yystackp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
	yydestroyGLRState ("Cleanup: popping", yys);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  yychar_current = yychar;
  yylval_current = yylval;
  yylloc_current = yylloc;
  yychar = yyopt->yyrawchar;
  yylval = yyopt->yyval;
  yylloc = yyopt->yyloc;
  yyflag = yyuserAction (yyopt->yyrule, yynrhs,
			   yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
			   yyvalp, yylocp, yystackp);
  yychar = yychar_current;
  yylval = yylval_current;
  yylloc = yylloc_current;
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == NULL)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
	       (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
	{
	  if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
	    YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]));
	  else
	    YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]),
		       (unsigned long int) (yystates[yyi - 1]->yyposn + 1),
		       (unsigned long int) yystates[yyi]->yyposn);
	}
      else
	yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

/*ARGSUSED*/ static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
		   yySemanticOption* yyx1)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (YY_("syntax is ambiguous"));
  return yyabort;
}

/** Starting at and including state S1, resolve the location for each of the
 *  previous N1 states that is unresolved.  The first semantic option of a state
 *  is always chosen.  */
static void
yyresolveLocations (yyGLRState* yys1, int yyn1,
		    yyGLRStack *yystackp)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp);
      if (!yys1->yyresolved)
	{
	  yySemanticOption *yyoption;
	  yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
	  int yynrhs;
	  int yychar_current;
	  YYSTYPE yylval_current;
	  YYLTYPE yylloc_current;
	  yyoption = yys1->yysemantics.yyfirstVal;
	  YYASSERT (yyoption != NULL);
	  yynrhs = yyrhsLength (yyoption->yyrule);
	  if (yynrhs > 0)
	    {
	      yyGLRState *yys;
	      int yyn;
	      yyresolveLocations (yyoption->yystate, yynrhs,
				  yystackp);
	      for (yys = yyoption->yystate, yyn = yynrhs;
		   yyn > 0;
		   yys = yys->yypred, yyn -= 1)
		yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
	    }
	  else
	    {
	      /* Both yyresolveAction and yyresolveLocations traverse the GSS
		 in reverse rightmost order.  It is only necessary to invoke
		 yyresolveLocations on a subforest for which yyresolveAction
		 would have been invoked next had an ambiguity not been
		 detected.  Thus the location of the previous state (but not
		 necessarily the previous state itself) is guaranteed to be
		 resolved already.  */
	      yyGLRState *yyprevious = yyoption->yystate;
	      yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
	    }
	  yychar_current = yychar;
	  yylval_current = yylval;
	  yylloc_current = yylloc;
	  yychar = yyoption->yyrawchar;
	  yylval = yyoption->yyval;
	  yylloc = yyoption->yyloc;
	  YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
	  yychar = yychar_current;
	  yylval = yylval_current;
	  yylloc = yylloc_current;
	}
    }
}

/** Resolve the ambiguity represented in state S, perform the indicated
 *  actions, and set the semantic value of S.  If result != yyok, the chain of
 *  semantic options in S has been cleared instead or it has been left
 *  unmodified except that redundant options may have been removed.  Regardless
 *  of whether result = yyok, S has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest;
  yySemanticOption** yypp;
  yybool yymerge;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  yybest = yyoptionList;
  yymerge = yyfalse;
  for (yypp = &yyoptionList->yynext; *yypp != NULL; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
	{
	  yymergeOptionSets (yybest, yyp);
	  *yypp = yyp->yynext;
	}
      else
	{
	  switch (yypreference (yybest, yyp))
	    {
	    case 0:
	      yyresolveLocations (yys, 1, yystackp);
	      return yyreportAmbiguity (yybest, yyp);
	      break;
	    case 1:
	      yymerge = yytrue;
	      break;
	    case 2:
	      break;
	    case 3:
	      yybest = yyp;
	      yymerge = yyfalse;
	      break;
	    default:
	      /* This cannot happen so it is not worth a YYASSERT (yyfalse),
		 but some compilers complain if the default case is
		 omitted.  */
	      break;
	    }
	  yypp = &yyp->yynext;
	}
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval,
				yylocp);
      if (yyflag == yyok)
	for (yyp = yybest->yynext; yyp != NULL; yyp = yyp->yynext)
	  {
	    if (yyprec == yydprec[yyp->yyrule])
	      {
		YYSTYPE yysval_other;
		YYLTYPE yydummy;
		yyflag = yyresolveAction (yyp, yystackp, &yysval_other,
					  &yydummy);
		if (yyflag != yyok)
		  {
		    yydestruct ("Cleanup: discarding incompletely merged value for",
				yystos[yys->yylrState],
				&yysval, yylocp);
		    break;
		  }
		yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
	      }
	  }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = NULL;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp)
{
  if (yystackp->yysplitPoint != NULL)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
	   yys != yystackp->yysplitPoint;
	   yys = yys->yypred, yyn += 1)
	continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
			     ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == NULL)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = NULL;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = NULL;
  yystackp->yylastDeleted = NULL;

  while (yyr != NULL)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
		   size_t yyposn)
{
  int yyaction;
  const short int* yyconflicts;
  yyRuleNum yyrule;

  while (yystackp->yytops.yystates[yyk] != NULL)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
		  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
	{
	  yyrule = yydefaultAction (yystate);
	  if (yyrule == 0)
	    {
	      YYDPRINTF ((stderr, "Stack %lu dies.\n",
			  (unsigned long int) yyk));
	      yymarkStackDeleted (yystackp, yyk);
	      return yyok;
	    }
	  YYCHK (yyglrReduce (yystackp, yyk, yyrule, yyfalse));
	}
      else
	{
	  yySymbol yytoken;
	  yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
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

	  yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

	  while (*yyconflicts != 0)
	    {
	      size_t yynewStack = yysplitStack (yystackp, yyk);
	      YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
			  (unsigned long int) yynewStack,
			  (unsigned long int) yyk));
	      YYCHK (yyglrReduce (yystackp, yynewStack,
				  *yyconflicts, yyfalse));
	      YYCHK (yyprocessOneStack (yystackp, yynewStack,
					yyposn));
	      yyconflicts += 1;
	    }

	  if (yyisShiftAction (yyaction))
	    break;
	  else if (yyisErrorAction (yyaction))
	    {
	      YYDPRINTF ((stderr, "Stack %lu dies.\n",
			  (unsigned long int) yyk));
	      yymarkStackDeleted (yystackp, yyk);
	      break;
	    }
	  else
	    YYCHK (yyglrReduce (yystackp, yyk, -yyaction,
				yyfalse));
	}
    }
  return yyok;
}

/*ARGSUSED*/ static void
yyreportSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState == 0)
    {
#if YYERROR_VERBOSE
      int yyn;
      yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      if (YYPACT_NINF < yyn && yyn <= YYLAST)
	{
	  yySymbol yytoken = YYTRANSLATE (yychar);
	  size_t yysize0 = yytnamerr (NULL, yytokenName (yytoken));
	  size_t yysize = yysize0;
	  size_t yysize1;
	  yybool yysize_overflow = yyfalse;
	  char* yymsg = NULL;
	  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn + 1;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytokenName (yytoken);
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytokenName (yyx);
		yysize1 = yysize + yytnamerr (NULL, yytokenName (yyx));
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + strlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow)
	    yymsg = (char *) YYMALLOC (yysize);

	  if (yymsg)
	    {
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYFREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      yyMemoryExhausted (yystackp);
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
      yynerrs += 1;
    }
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
/*ARGSUSED*/ static void
yyrecoverSyntaxError (yyGLRStack* yystackp)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (YYID (yytrue))
      {
	yySymbol yytoken;
	if (yychar == YYEOF)
	  yyFail (yystackp, NULL);
	if (yychar != YYEMPTY)
	  {
	    /* We throw away the lookahead, but the error range
	       of the shifted error token must take it into account.  */
	    yyGLRState *yys = yystackp->yytops.yystates[0];
	    yyGLRStackItem yyerror_range[3];
	    yyerror_range[1].yystate.yyloc = yys->yyloc;
	    yyerror_range[2].yystate.yyloc = yylloc;
	    YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
	    yytoken = YYTRANSLATE (yychar);
	    yydestruct ("Error: discarding",
			yytoken, &yylval, &yylloc);
	  }
	YYDPRINTF ((stderr, "Reading a token: "));
	yychar = YYLEX;
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
	yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
	if (yyis_pact_ninf (yyj))
	  return;
	yyj += yytoken;
	if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
	  {
	    if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
	      return;
	  }
	else if (yytable[yyj] != 0 && ! yyis_table_ninf (yytable[yyj]))
	  return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != NULL)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, NULL);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != NULL)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yyis_pact_ninf (yyj))
	{
	  yyj += YYTERROR;
	  if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
	      && yyisShiftAction (yytable[yyj]))
	    {
	      /* Shift the error token having adjusted its location.  */
	      YYLTYPE yyerrloc;
	      yystackp->yyerror_range[2].yystate.yyloc = yylloc;
	      YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
	      YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
			       &yylval, &yyerrloc);
	      yyglrShift (yystackp, 0, yytable[yyj],
			  yys->yyposn, &yylval, &yyerrloc);
	      yys = yystackp->yytops.yystates[0];
	      break;
	    }
	}
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != NULL)
	yydestroyGLRState ("Error: popping", yys);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == NULL)
    yyFail (yystackp, NULL);
}

#define YYCHK1(YYE)							     \
  do {									     \
    switch (YYE) {							     \
    case yyok:								     \
      break;								     \
    case yyabort:							     \
      goto yyabortlab;							     \
    case yyaccept:							     \
      goto yyacceptlab;							     \
    case yyerr:								     \
      goto yyuser_error;						     \
    default:								     \
      goto yybuglab;							     \
    }									     \
  } while (YYID (0))


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

#if YYLTYPE_IS_TRIVIAL
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif


  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (YYID (yytrue))
    {
      /* For efficiency, we have two loops, the first of which is
	 specialized to deterministic operation (single stack, no
	 potential ambiguity).  */
      /* Standard mode */
      while (YYID (yytrue))
	{
	  yyRuleNum yyrule;
	  int yyaction;
	  const short int* yyconflicts;

	  yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
	  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
	  if (yystate == YYFINAL)
	    goto yyacceptlab;
	  if (yyisDefaultedState (yystate))
	    {
	      yyrule = yydefaultAction (yystate);
	      if (yyrule == 0)
		{
		  yystack.yyerror_range[1].yystate.yyloc = yylloc;
		  yyreportSyntaxError (&yystack);
		  goto yyuser_error;
		}
	      YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
	    }
	  else
	    {
	      yySymbol yytoken;
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

	      yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
	      if (*yyconflicts != 0)
		break;
	      if (yyisShiftAction (yyaction))
		{
		  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
		  yychar = YYEMPTY;
		  yyposn += 1;
		  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
		  if (0 < yystack.yyerrState)
		    yystack.yyerrState -= 1;
		}
	      else if (yyisErrorAction (yyaction))
		{
		  yystack.yyerror_range[1].yystate.yyloc = yylloc;
		  yyreportSyntaxError (&yystack);
		  goto yyuser_error;
		}
	      else
		YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
	    }
	}

      while (YYID (yytrue))
	{
	  yySymbol yytoken_to_shift;
	  size_t yys;

	  for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
	    yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

	  /* yyprocessOneStack returns one of three things:

	      - An error flag.  If the caller is yyprocessOneStack, it
		immediately returns as well.  When the caller is finally
		yyparse, it jumps to an error label via YYCHK1.

	      - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
		(&yystack, yys), which sets the top state of yys to NULL.  Thus,
		yyparse's following invocation of yyremoveDeletes will remove
		the stack.

	      - yyok, when ready to shift a token.

	     Except in the first case, yyparse will invoke yyremoveDeletes and
	     then shift the next token onto all remaining stacks.  This
	     synchronization of the shift (that is, after all preceding
	     reductions on all stacks) helps prevent double destructor calls
	     on yylval in the event of memory exhaustion.  */

	  for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
	    YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn));
	  yyremoveDeletes (&yystack);
	  if (yystack.yytops.yysize == 0)
	    {
	      yyundeleteLastStack (&yystack);
	      if (yystack.yytops.yysize == 0)
		yyFail (&yystack, YY_("syntax error"));
	      YYCHK1 (yyresolveStack (&yystack));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yystack.yyerror_range[1].yystate.yyloc = yylloc;
	      yyreportSyntaxError (&yystack);
	      goto yyuser_error;
	    }

	  /* If any yyglrShift call fails, it will fail after shifting.  Thus,
	     a copy of yylval will already be on stack 0 in the event of a
	     failure in the following loop.  Thus, yychar is set to YYEMPTY
	     before the loop to make sure the user destructor for yylval isn't
	     called twice.  */
	  yytoken_to_shift = YYTRANSLATE (yychar);
	  yychar = YYEMPTY;
	  yyposn += 1;
	  for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
	    {
	      int yyaction;
	      const short int* yyconflicts;
	      yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
	      yygetLRActions (yystate, yytoken_to_shift, &yyaction,
			      &yyconflicts);
	      /* Note that yyconflicts were handled by yyprocessOneStack.  */
	      YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
	      YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
	      yyglrShift (&yystack, yys, yyaction, yyposn,
			  &yylval, &yylloc);
	      YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
			  (unsigned long int) yys,
			  yystack.yytops.yystates[yys]->yylrState));
	    }

	  if (yystack.yytops.yysize == 1)
	    {
	      YYCHK1 (yyresolveStack (&yystack));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yycompressStack (&yystack);
	      break;
	    }
	}
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
		YYTRANSLATE (yychar),
		&yylval, &yylloc);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
	{
	  size_t yysize = yystack.yytops.yysize;
	  size_t yyk;
	  for (yyk = 0; yyk < yysize; yyk += 1)
	    if (yystates[yyk])
	      {
		while (yystates[yyk])
		  {
		    yyGLRState *yys = yystates[yyk];
		    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
		    if (yys->yypred != NULL)
		      yydestroyGLRState ("Cleanup: popping", yys);
		    yystates[yyk] = yys->yypred;
		    yystack.yynextFree -= 1;
		    yystack.yyspaceLeft += 1;
		  }
		break;
	      }
	}
      yyfreeGLRStack (&yystack);
    }

  /* Make sure YYID is used.  */
  return YYID (yyresult);
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void yypstack (yyGLRStack* yystackp, size_t yyk)
  __attribute__ ((__unused__));
static void yypdumpstack (yyGLRStack* yystackp) __attribute__ ((__unused__));

static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == NULL)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)							     \
    ((YYX) == NULL ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
	{
	  YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
		     yyp->yystate.yyresolved, yyp->yystate.yylrState,
		     (unsigned long int) yyp->yystate.yyposn,
		     (long int) YYINDEX (yyp->yystate.yypred));
	  if (! yyp->yystate.yyresolved)
	    YYFPRINTF (stderr, ", firstVal: %ld",
		       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
	}
      else
	{
	  YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
		     yyp->yyoption.yyrule - 1,
		     (long int) YYINDEX (yyp->yyoption.yystate),
		     (long int) YYINDEX (yyp->yyoption.yynext));
	}
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
	       (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif



/* Line 2634 of glr.c  */
#line 546 "parser.y"


#include <set>
#include <stack>
#include <cstdarg>

using namespace std;

/** The stack of sets of allowed tokens in current syntactic context. */
static stack< set<int> > contextStack;

bool debugParser;


#include "lexer.cc"

/* AST convenience routines. */

/** A new empty list of AST*s. */
static ASTList*
makeList ()
{
    return new ASTList ();
}

/** A new list of AST*s initially containing ITEM. */
static ASTList*
makeList (AST* item)
{
    return addItem (makeList (), item);
}


/** A new list of AST*s initially containing ITEM, if it is non-null, and
 *  otherwise empty. */
static ASTList*
makeListNonNull (AST* item)
{
    ASTList* r = new ASTList ();
    if (item != NULL)
        r->push_back (item);
    return r;
}

/** Adds ITEM to the end of L and returns L. */
static ASTList*
addItem (ASTList* L, AST* item)
{
    L->push_back (item);
    return L;
}

/** Adds ITEM to the front of L and returns L. */
static ASTList*
addItem (AST* item, ASTList* L)
{
    L->insert (L->begin (), item);
    return L;
}

/** Adds ITEM to the end of L if ITEM is non-null.  Returns L. */
static ASTList*
addNonNullItem (ASTList* L, AST* item)
{
    if (item == NULL)
        return L;
    else 
        return addItem (L, item);
}

/** A node representing a statement or sequence of statements, L.  If L is
 *  empty, uses DEFAULTLINE as the source position. */
static AST*
makeSuite (int defaultLine, ASTList* L) {
    if (L->size () == 1) {
         AST* r = L->at (0);
         delete L;
         return r;
    } else if (L->size () == 0)
         return makeStmtList (defaultLine, L);
    else
         return makeStmtList (L->at (0)->line (), L);
}

/** The result of appending L0 and L1 (destructively).  Either deletes or
 *  returns its operands. */
static ASTList*
append (ASTList* L0, ASTList* L1)
{
    if (L0->size () == 0) {
        delete L0;
        return L1;
    } else {
        L0->insert (L0->end (), L1->begin (), L1->end ());
        delete L1;
        return L0;
    }
}

/** A binary operator node for operands E0 and E1 and operator OP. */
static AST*
binop (AST* e0, const char* op, AST* e1)
{
    return makeBinop (e0->line (), e0,
                 makeId (e0->line (), new string (op)), e1);
}

/** A unary operator node for operand E1 and operator OP, with source
 *  position LINE. */
static AST*
unop (int line, const char* op, AST* e1)
{
    return makeUnop (line, makeId (line, new string (op)), e1);
}

/** Turn COMPS into a comparison node if contains multiple members.  Otherwise,
 *  coerce to its first item. */
static AST*
makeComparison (ASTList* comps)
{
    if (comps->size () == 1) {
        AST* result = comps->at (0);
        delete comps;
        return result;
    } else 
        return makeComparison (comps->at (0)->line (), comps);
}
 
/** Add OP EXPR to end of a comparison list, where OP is the name of a
 *  comparison operator. */
static ASTList*
addComparison (ASTList* comps, const char* op, AST* expr)
{
    return addItem (addItem (comps, makeId (expr->line (), op)), expr);
}
 
/** Push a new context on the statement context stack, specifying 
 *  the set of statement types allowed in the current syntactic
 *  context.  The allowed statements in the new context are
 *  those allowed in the previous context, modified by the arguments 
 *  STMTTYPE0, etc.  Each STMTTYPE is a token category from among
 *  DEF, CLASS, RETURN, CONTINUE, BREAK, or its negation.  A negative 
 *  value indicates a token type to be removed from the allowable
 *  contexts (if present); a positive value indicates a token type to
 *  be added. Terminate the list of values with 0. */
static void
pushContext (int stmtType0, ...)
{
    va_list ap;
    if (contextStack.empty ())
        contextStack.push (set<int>());
    else
        contextStack.push (contextStack.top ());
    
    va_start (ap, stmtType0);
    for (int type = stmtType0; type != 0; type = va_arg (ap, int)) {
      if (type > 0)
	contextStack.top ().insert (type);
      else
	contextStack.top ().erase (-type);
    }
}

/** Restore previous set of allowed constructs (before last pushContext). */
static void
popContext ()
{
    contextStack.pop ();
}

/** Flags an error at location LOC if STMTTYPE is not among the currently 
 *  allowed contexts. */
static void
checkContext (int stmtType, int loc) 
{
    if (contextStack.empty ())
	return;
    if (contextStack.top ().find (stmtType) == contextStack.top ().end ())

	Error (loc, "statement may not occur in this context");
}

static void
yyerror (const char* msg) {
   Error (yylloc, "%s", msg);
}

void
parse (FILE* f)
{
    if (debugParser)
        yydebug = 1;
    initLexer (f);
    yyparse ();
}


