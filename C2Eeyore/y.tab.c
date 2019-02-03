/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "C2Eeyore.y" /* yacc.c:339  */

#include <string.h>
#include "globals.h"
#include "util.h"
static TreeNode *savedTree;
int yydebug = 1;
int yyerror(char *);
extern int yylex(void);

#line 76 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    MAIN = 261,
    RETURN = 262,
    INT_TYPE = 263,
    AND = 264,
    OR = 265,
    EQ = 266,
    NEQ = 267,
    INT = 268,
    ID = 269
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define MAIN 261
#define RETURN 262
#define INT_TYPE 263
#define AND 264
#define OR 265
#define EQ 266
#define NEQ 267
#define INT 268
#define ID 269

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 155 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   177

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,    30,     2,     2,
      16,    17,    28,    26,    20,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    15,
      24,    21,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    18,     2,    19,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    16,    16,    19,    21,    26,    31,    36,    42,    50,
      59,    64,    69,    71,    76,    82,    84,    90,    91,    97,
     100,   102,   105,   113,   115,   118,   124,   132,   138,   140,
     142,   144,   146,   148,   150,   156,   162,   167,   176,   182,
     191,   196,   203,   210,   213,   220,   227,   234,   241,   244,
     251,   258,   261,   268,   275,   282,   285,   287,   289,   291,
     297,   303,   305,   311,   318,   323,   328,   332,   338
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "MAIN", "RETURN",
  "INT_TYPE", "AND", "OR", "EQ", "NEQ", "INT", "ID", "';'", "'('", "')'",
  "'{'", "'}'", "','", "'='", "'['", "']'", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "$accept", "root", "program", "func_decl",
  "func_def", "def_body", "def_para", "main_def", "stmt_seq", "one_stmt",
  "stmt", "ifelse_stmt", "open_stmt", "if_open", "while_open",
  "match_stmt", "while_stmt", "assign_stmt", "def_stmt", "return_stmt",
  "exp", "comp_exp", "am_exp", "tom_exp", "factor", "func", "para", "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    59,    40,    41,   123,   125,
      44,    61,    91,    93,    60,    62,    43,    45,    42,    47,
      37,    33
};
# endif

#define YYPACT_NINF -117

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-117)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,    23,   131,    21,  -117,    60,    60,  -117,    27,    35,
      50,    59,    -7,    -7,  -117,  -117,  -117,    60,    60,    71,
      49,  -117,    84,    -7,    -7,    -7,   145,    87,   130,   121,
    -117,  -117,     9,  -117,  -117,    69,    66,   101,     0,    -7,
      75,  -117,  -117,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    68,  -117,   118,   116,   104,  -117,
    -117,    42,   123,    47,   140,    87,    87,   130,   130,   130,
     130,   121,   121,  -117,  -117,  -117,    -7,    15,   143,  -117,
      64,    -7,  -117,  -117,    -7,   145,  -117,  -117,    69,   148,
     149,    -7,   126,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,   151,   152,   153,   154,   156,  -117,
     113,   102,  -117,    -7,    -7,   145,   110,  -117,  -117,  -117,
    -117,    92,  -117,  -117,   122,   124,  -117,  -117,   157,    69,
      83,    83,   150,   158,  -117,   169,  -117,  -117,   159,    83,
    -117,  -117
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    68,     0,     0,     2,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     1,     7,     6,     0,     0,    38,
       0,    57,    58,     0,     0,     0,    36,    43,    48,    51,
      55,    61,     0,     5,     4,    15,     0,     0,     0,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     0,    12,
      65,    66,     0,     0,    56,    42,    41,    44,    45,    46,
      47,    49,    50,    52,    53,    54,     0,     0,    13,    39,
       0,     0,    64,    59,     0,    37,     8,    12,    15,     0,
       0,     0,     0,    17,    16,    10,    11,    19,    28,    20,
      23,    24,    21,    30,     0,     0,     0,     0,     0,    67,
       0,     0,    14,     0,     0,    40,     0,    31,    32,    33,
      34,    38,    60,     9,     0,     0,    29,    18,     0,    15,
       0,     0,    38,     0,    25,    21,    27,    35,     0,     0,
      26,    22
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -117,  -117,   120,   -75,  -117,    89,   -85,  -117,  -117,  -108,
    -117,  -117,  -116,  -117,  -117,  -105,  -117,    41,    43,  -117,
     -11,   115,    98,   111,   -14,   -76,    96,   -35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    80,    56,     7,   116,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      61,    27,    28,    29,    30,    31,    62,    10
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    26,    32,   112,   107,    95,    21,    22,   127,    23,
      41,    42,    40,    21,    22,   136,    23,    60,    43,    44,
      24,    14,   134,   140,    25,   135,   137,    24,    63,    11,
      86,    25,    54,    87,   141,   107,    95,    73,    74,    75,
     107,     8,    17,     9,   133,   108,     8,     8,     9,     9,
      18,    43,    44,    57,   107,   107,    43,    44,     8,     8,
       9,     9,    81,   107,    19,    85,    37,    89,     1,    90,
      83,    91,    55,   110,     2,    20,   108,    55,    92,    58,
     115,   128,    93,    94,    43,    44,    89,    35,    90,    76,
      91,    55,    64,    36,    57,   128,   128,    92,    45,    46,
      38,    93,   124,   125,   128,    89,    39,    90,   129,    91,
      55,    47,    48,    89,    36,    90,    92,    91,    55,    59,
      93,   123,    43,    44,    92,    15,    16,    79,    93,   126,
      78,    43,    44,    43,    44,    77,   122,    33,    34,   130,
      82,   131,    38,    67,    68,    69,    70,    12,    13,    51,
      52,    53,    12,    13,    43,    44,    49,    50,    65,    66,
      71,    72,    84,    88,   113,   114,   117,   118,   119,   120,
     121,   132,    36,   139,    86,   138,   111,   109
};

static const yytype_uint8 yycheck[] =
{
      35,    12,    13,    88,    80,    80,    13,    14,   116,    16,
      24,    25,    23,    13,    14,   131,    16,    17,     9,    10,
      27,     0,   130,   139,    31,   130,   131,    27,    39,     6,
      15,    31,    23,    18,   139,   111,   111,    51,    52,    53,
     116,     0,    15,     0,   129,    80,     5,     6,     5,     6,
      15,     9,    10,    88,   130,   131,     9,    10,    17,    18,
      17,    18,    20,   139,    14,    76,    17,     3,     8,     5,
      23,     7,     8,    84,    14,    16,   111,     8,    14,    13,
      91,   116,    18,    19,     9,    10,     3,    16,     5,    21,
       7,     8,    17,    22,   129,   130,   131,    14,    11,    12,
      16,    18,   113,   114,   139,     3,    22,     5,    16,     7,
       8,    24,    25,     3,    22,     5,    14,     7,     8,    18,
      18,    19,     9,    10,    14,     5,     6,    23,    18,    19,
      14,     9,    10,     9,    10,    17,    23,    17,    18,    17,
      17,    17,    16,    45,    46,    47,    48,    21,    22,    28,
      29,    30,    21,    22,     9,    10,    26,    27,    43,    44,
      49,    50,    22,    20,    16,    16,    15,    15,    15,    15,
      14,    14,    22,     4,    15,    17,    87,    81
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    14,    33,    34,    35,    36,    39,    49,    50,
      59,     6,    21,    22,     0,    34,    34,    15,    15,    14,
      16,    13,    14,    16,    27,    31,    52,    53,    54,    55,
      56,    57,    52,    34,    34,    16,    22,    17,    16,    22,
      52,    56,    56,     9,    10,    11,    12,    24,    25,    26,
      27,    28,    29,    30,    23,     8,    38,    59,    13,    18,
      17,    52,    58,    52,    17,    53,    53,    54,    54,    54,
      54,    55,    55,    56,    56,    56,    21,    17,    14,    23,
      37,    20,    17,    23,    22,    52,    15,    18,    20,     3,
       5,     7,    14,    18,    19,    35,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    57,    59,    58,
      52,    37,    38,    16,    16,    52,    40,    15,    15,    15,
      15,    14,    23,    19,    52,    52,    19,    41,    59,    16,
      17,    17,    14,    38,    41,    47,    44,    47,    17,     4,
      44,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    34,    34,    34,    35,    36,
      37,    37,    37,    38,    38,    38,    39,    40,    40,    41,
      42,    42,    43,    44,    44,    45,    45,    46,    47,    47,
      47,    47,    47,    47,    47,    48,    49,    49,    50,    50,
      51,    52,    52,    52,    53,    53,    53,    53,    53,    54,
      54,    54,    55,    55,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    58,    58,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     3,     2,     2,     6,     8,
       2,     2,     0,     2,     4,     0,     7,     0,     2,     1,
       1,     1,     7,     1,     1,     5,     7,     5,     1,     3,
       1,     2,     2,     2,     2,     5,     3,     6,     2,     5,
       2,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     1,     4,
       6,     1,     2,     2,     4,     3,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 17 "C2Eeyore.y" /* yacc.c:1646  */
    { SyntaxTree = (yyvsp[0]); }
#line 1328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 20 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 22 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1343 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 27 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1352 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 32 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1361 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 37 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 43 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Def_K);
				  (yyval)->attr.def = FUNC;
				  (yyval)->child[0] = (yyvsp[-5]);
				  (yyval)->child[1] = (yyvsp[-4]);
				  (yyval)->child[2] = (yyvsp[-2]);
				}
#line 1381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 51 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Def_K);
				  (yyval)->attr.def = FUNC;
				  (yyval)->child[0] = (yyvsp[-7]);
				  (yyval)->child[1] = (yyvsp[-6]);
				  (yyval)->child[2] = (yyvsp[-4]);
				  (yyval)->child[3] = (yyvsp[-1]);
				}
#line 1393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 60 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 65 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 69 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 72 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newParaNode(Para_def);
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 77 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newParaNode(Para_def);
				  (yyval)->child[0] = (yyvsp[-3]);
				  (yyval)->child[1] = (yyvsp[-2]);
				  (yyval)->child[2] = (yyvsp[0]);
				}
#line 1436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 82 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 85 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Def_K);
				  (yyval)->attr.def = FUNC_MAIN;
				  (yyval)->child[0] = (yyvsp[-1]);
				}
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 90 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 92 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Seq_K);
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 98 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 101 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 103 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 106 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(If_K);
				  (yyval)->child[0] = (yyvsp[-4]);
				  (yyval)->child[1] = (yyvsp[-2]);
				  (yyval)->child[2] = (yyvsp[0]);
				  (yyval)->attr.IfwithElse = TRUE;
				}
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 114 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 116 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 119 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(If_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->attr.IfwithElse = FALSE;
				}
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 125 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(If_K);
				  (yyval)->child[0] = (yyvsp[-4]);
				  (yyval)->child[1] = (yyvsp[-2]);
				  (yyval)->child[2] = (yyvsp[0]);
				  (yyval)->attr.IfwithElse = TRUE;
				}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 133 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(While_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 139 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 141 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 143 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 145 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 147 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 149 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 151 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(OFunc_K);
				  (yyval)->child[0] = (yyvsp[-1])->child[0];
				  (yyval)->child[1] = (yyvsp[-1])->child[1];
				}
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 157 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(While_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 163 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Assign_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 168 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Assign_K);
				  (yyval)->child[0] = newExpNode(Array_K);
				  (yyval)->child[0]->child[0] = (yyvsp[-5]);
				  (yyval)->child[0]->child[1] = (yyvsp[-3]);
				  (yyval)->child[0]->type = Integer;
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 177 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Def_K);
				  (yyval)->attr.def = NUM;
				  (yyval)->child[0] = (yyvsp[-1]);
				  (yyval)->child[1] = (yyvsp[0]);
				}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 183 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Def_K);
				  (yyval)->attr.def = ARRAY;
				  (yyval)->child[0] = (yyvsp[-4]);
				  (yyval)->child[1] = (yyvsp[-3]);
				  (yyval)->child[2] = (yyvsp[-1]);
				}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 192 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(Return_K);
				  (yyval)->child[0] = (yyvsp[0]);
				}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 197 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Or;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 204 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = And;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 211 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 214 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Eq;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 221 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Neq;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 228 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Lt;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 235 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Gt;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 242 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 245 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Plus;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Integer;
				}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 252 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Minus;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Integer;
				}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 259 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 262 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Times;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Integer;
				}
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 269 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Over;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Integer;
				}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 276 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(DOp_K);
				  (yyval)->attr.op = Mod;
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[0]);
				  (yyval)->type = Integer;
				}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 283 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 286 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 288 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 290 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 292 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(Array_K);
				  (yyval)->child[0] = (yyvsp[-3]);
				  (yyval)->child[1] = (yyvsp[-1]);
				  (yyval)->type = Integer;
				}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 298 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(Array_K);
				  (yyval)->child[0] = (yyvsp[-4]);
				  (yyval)->child[1] = (yyvsp[-1]);
				  (yyval)->type = Integer;
				}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 304 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 306 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(SOp_K);
				  (yyval)->attr.op = Minus;
				  (yyval)->child[0] = (yyvsp[0]);
				  (yyval)->type = Integer;
				}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 312 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(SOp_K);
				  (yyval)->attr.op = Not;
				  (yyval)->child[0] = (yyvsp[0]);
				  (yyval)->type = Boolean;
				}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 319 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(Func_K);
				  (yyval)->child[0] = (yyvsp[-3]);
				  (yyval)->child[1] = (yyvsp[-1]);
				}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 324 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(Func_K);
				  (yyval)->child[0] = (yyvsp[-2]);
				}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 329 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newParaNode(Para);
				  (yyval)->child[0] = (yyvsp[0]);
				}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 333 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newParaNode(Para);
				  (yyval)->child[0] = (yyvsp[-2]);
				  (yyval)->child[1] = (yyvsp[-1]);
				}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 339 "C2Eeyore.y" /* yacc.c:1646  */
    { (yyval) = newTypeNode(Int);}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1894 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 342 "C2Eeyore.y" /* yacc.c:1906  */
 

int yyerror(char *message)
{
	fprintf(stderr, "error in line %d: %s\n", lineno, message);
	return 0;
}

int myerror(int lineno, char *message)
{
	fprintf(stderr, "error in line %d: %s\n", lineno, message);
	return 0;
}
