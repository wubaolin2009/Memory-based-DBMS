/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "gram.y"

#include<stdio.h>
#include<string.h>
#include<vector>
using std::vector;
#include"lex_defines.h"



int yyerror(char *msg);
int yylex();

extern DataTable g_table_result;



/* Line 268 of yacc.c  */
#line 88 "gram.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SELECT = 258,
     FROM = 259,
     ID = 260,
     SEPARATER = 261,
     STMT_END = 262,
     AS = 263,
     PERIOD = 264,
     LT = 265,
     ST = 266,
     EQ = 267,
     INTEGER = 268,
     REALNUM = 269,
     WHERE = 270,
     AND = 271,
     OR = 272,
     DISTINCT = 273,
     ASC = 274,
     DESC = 275,
     SORT = 276,
     BY = 277,
     CREATE = 278,
     TABLE = 279,
     LGB = 280,
     RGB = 281,
     LSB = 282,
     RSB = 283,
     PK = 284,
     NOT = 285,
     COLUMN_NULL = 286,
     TYPE_FLOAT = 287,
     TYPE_INTEGER = 288,
     TYPE_VARCHAR = 289,
     TYPE_CHAR = 290,
     INSERT = 291,
     INTO = 292,
     VALUES = 293,
     SET = 294,
     DELETE = 295,
     UPDATE = 296,
     INDEX = 297,
     ON = 298,
     FK = 299,
     REF = 300,
     BEGIN_TR = 301,
     END_TR = 302,
     TRANSACTION = 303,
     CMD_HELP = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 179 "gram.cpp"

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
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   129

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    17,    20,
      29,    37,    39,    41,    43,    45,    47,    51,    53,    55,
      59,    62,    66,    68,    72,    74,    78,    82,    85,    88,
      89,    92,    94,    98,   100,   102,   104,   106,   108,   110,
     114,   118,   122,   123,   128,   129,   131,   133,   141,   145,
     147,   153,   155,   157,   162,   167,   168,   171,   173,   174,
     179,   180,   182,   191,   195,   197,   199,   201,   203,   210,
     214,   220
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    55,    -1,    53,    -1,    54,    -1,    52,
      -1,    49,    -1,    46,    48,     5,    -1,    47,    48,    -1,
       3,    18,    58,     4,    56,    60,    65,     7,    -1,     3,
      58,     4,    56,    60,    65,     7,    -1,    67,    -1,    74,
      -1,    79,    -1,    77,    -1,    80,    -1,    56,     6,    57,
      -1,    57,    -1,     5,    -1,     5,     8,     5,    -1,     5,
       5,    -1,    58,     6,    59,    -1,    59,    -1,     5,     9,
       5,    -1,     5,    -1,     5,     8,     5,    -1,    59,     8,
       5,    -1,    59,     5,    -1,     5,     5,    -1,    -1,    15,
      64,    -1,     5,    -1,     5,     9,     5,    -1,    10,    -1,
      12,    -1,    11,    -1,    13,    -1,    14,    -1,    61,    -1,
      61,    62,    63,    -1,    64,    16,    64,    -1,    64,    17,
      64,    -1,    -1,    21,    22,    58,    66,    -1,    -1,    19,
      -1,    20,    -1,    23,    24,     5,    25,    68,    26,     7,
      -1,    68,     6,    69,    -1,    69,    -1,     5,    70,    71,
      73,    72,    -1,    33,    -1,    32,    -1,    34,    27,    13,
      28,    -1,    35,    27,    13,    28,    -1,    -1,    30,    31,
      -1,    31,    -1,    -1,    44,    45,     5,     5,    -1,    -1,
      29,    -1,    36,    37,     5,    38,    27,    75,    28,     7,
      -1,    75,     6,    76,    -1,    76,    -1,    13,    -1,    14,
      -1,     5,    -1,    41,     5,    39,    78,    60,     7,    -1,
      61,    62,    63,    -1,    40,     4,     5,    60,     7,    -1,
      23,    42,    43,     5,     5,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    23,    23,    24,    25,    26,    28,    29,    31,    34,
      35,    36,    37,    38,    39,    40,    42,    45,    50,    52,
      54,    57,    60,    68,    70,    72,    74,    76,    78,    83,
      84,    87,    88,    90,    91,    92,    94,    97,   100,   111,
     115,   118,   121,   122,   124,   125,   126,   128,   130,   131,
     133,   167,   168,   169,   170,   172,   173,   174,   176,   177,
     179,   180,   182,   184,   185,   187,   188,   189,   191,   193,
     197,   199
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "FROM", "ID", "SEPARATER",
  "STMT_END", "AS", "PERIOD", "LT", "ST", "EQ", "INTEGER", "REALNUM",
  "WHERE", "AND", "OR", "DISTINCT", "ASC", "DESC", "SORT", "BY", "CREATE",
  "TABLE", "LGB", "RGB", "LSB", "RSB", "PK", "NOT", "COLUMN_NULL",
  "TYPE_FLOAT", "TYPE_INTEGER", "TYPE_VARCHAR", "TYPE_CHAR", "INSERT",
  "INTO", "VALUES", "SET", "DELETE", "UPDATE", "INDEX", "ON", "FK", "REF",
  "BEGIN_TR", "END_TR", "TRANSACTION", "CMD_HELP", "$accept", "command",
  "help_cmd", "transaction_begin", "transaction_end", "declaration",
  "from_list", "from_val", "attr_list", "attr_name", "where_clause",
  "attr_name_in_where", "operator_in_where", "operand2_in_where",
  "condition", "sort_clause", "sort_order", "create_clause",
  "column_info_list", "column_info", "column_type", "column_null_info",
  "fk_info", "pk_info", "insert_clause", "id_list", "data_value",
  "update_clause", "update_column_value", "delete_clause",
  "create_index_clause", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    52,    53,    54,    55,
      55,    55,    55,    55,    55,    55,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    66,    66,    66,    67,    68,    68,
      69,    70,    70,    70,    70,    71,    71,    71,    72,    72,
      73,    73,    74,    75,    75,    76,    76,    76,    77,    78,
      79,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     2,     8,
       7,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       2,     3,     1,     3,     1,     3,     3,     2,     2,     0,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     4,     0,     1,     1,     7,     3,     1,
       5,     1,     1,     4,     4,     0,     2,     1,     0,     4,
       0,     1,     8,     3,     1,     1,     1,     1,     6,     3,
       5,     6
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       5,     3,     4,     2,    11,    12,    14,    13,    15,    24,
       0,     0,    22,     0,     0,     0,     0,     0,     0,     8,
       1,    28,     0,     0,     0,     0,     0,    27,     0,     0,
       0,     0,    29,     0,     7,    25,    23,     0,    18,    29,
      17,    21,    26,     0,     0,     0,     0,     0,    31,     0,
      29,    29,    20,     0,     0,    42,     0,     0,    49,     0,
       0,     0,    30,    70,     0,    33,    35,    34,     0,     0,
      42,    19,    16,     0,     0,    52,    51,     0,     0,    55,
       0,     0,    71,    67,    65,    66,     0,    64,     0,     0,
       0,    32,    36,    37,    38,    69,    68,     0,     0,    10,
       0,     0,     0,    57,    60,    48,    47,     0,     0,    39,
      40,    41,     9,    44,     0,     0,    56,    61,    58,    63,
      62,    45,    46,    43,    53,    54,     0,    50,     0,     0,
      59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    49,    50,    21,    22,
      57,    71,    78,   105,    72,    84,   133,    14,    67,    68,
      89,   114,   137,   128,    15,    96,    97,    16,    60,    17,
      18
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -43
static const yytype_int8 yypact[] =
{
      -1,     3,   -19,    10,    49,    50,    13,    14,   -43,    63,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,     5,
      59,    28,    23,    60,    26,    61,    62,    29,    65,   -43,
     -43,   -43,    66,    67,    48,    68,    59,   -43,    69,    51,
      70,    40,    64,    72,   -43,   -43,   -43,    68,    25,     1,
     -43,    23,   -43,    75,    76,    55,    72,    77,    74,    39,
      64,     1,   -43,    80,    68,    71,     9,    -2,   -43,    79,
       4,    39,    -5,   -43,    82,   -43,   -43,   -43,    24,    83,
      71,   -43,   -43,    73,    84,   -43,   -43,    78,    81,    27,
      75,    86,   -43,   -43,   -43,   -43,    -3,   -43,    24,    72,
      72,   -43,   -43,   -43,   -43,   -43,   -43,    87,    59,   -43,
      85,    88,    58,   -43,    89,   -43,   -43,     4,    90,   -43,
      -5,    -5,   -43,     0,    91,    92,   -43,   -43,    52,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,    54,   -43,    95,    97,
     -43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -43,   -43,   -43,   -43,    56,    42,   -20,    93,
     -34,   -42,    33,    11,   -40,    30,   -43,   -43,   -43,    17,
     -43,   -43,   -43,   -43,   -43,   -43,    -6,   -43,   -43,   -43,
     -43
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      34,    59,     1,   117,    90,    23,    36,    64,    19,    93,
      31,    99,   100,    32,    33,    65,    56,    94,    95,   131,
     132,    20,     2,    24,    91,   118,    79,    80,    37,    58,
      62,    38,    35,    63,    36,     3,   104,   102,   103,     4,
       5,    85,    86,    87,    88,     6,     7,    25,     8,    75,
      76,    77,    47,    26,    36,    27,   104,   112,   113,   120,
     121,    28,    29,    30,    19,    39,    41,    42,    43,    40,
      44,    45,    46,    48,    52,    54,    53,    58,    55,    56,
      66,    69,    70,    74,    73,    81,    92,   101,   123,   126,
     106,   109,    83,   116,   122,   108,   136,   130,   124,   138,
     139,   125,   140,    61,    98,   110,    82,   115,   111,   119,
     107,   129,     0,     0,     0,     0,     0,     0,   127,   134,
     135,     0,     0,     0,     0,     0,     0,     0,     0,    51
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-43))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      20,    43,     3,     6,     6,    24,     6,     6,     5,     5,
       5,    16,    17,     8,     9,    49,    15,    13,    14,    19,
      20,    18,    23,    42,    26,    28,    60,    61,     5,     5,
       5,     8,     4,     8,     6,    36,    78,    13,    14,    40,
      41,    32,    33,    34,    35,    46,    47,    37,    49,    10,
      11,    12,     4,     4,     6,     5,    98,    30,    31,    99,
     100,    48,    48,     0,     5,     5,     5,     5,    39,    43,
       5,     5,     5,     5,     5,     5,    25,     5,    38,    15,
       5,     5,    27,     9,     7,     5,     7,     5,   108,    31,
       7,     7,    21,     7,     7,    22,    44,     7,    13,    45,
       5,    13,     5,    47,    71,    27,    64,    90,    27,    98,
      80,   117,    -1,    -1,    -1,    -1,    -1,    -1,    29,    28,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    23,    36,    40,    41,    46,    47,    49,    51,
      52,    53,    54,    55,    67,    74,    77,    79,    80,     5,
      18,    58,    59,    24,    42,    37,     4,     5,    48,    48,
       0,     5,     8,     9,    58,     4,     6,     5,     8,     5,
      43,     5,     5,    39,     5,     5,     5,     4,     5,    56,
      57,    59,     5,    25,     5,    38,    15,    60,     5,    61,
      78,    56,     5,     8,     6,    60,     5,    68,    69,     5,
      27,    61,    64,     7,     9,    10,    11,    12,    62,    60,
      60,     5,    57,    21,    65,    32,    33,    34,    35,    70,
       6,    26,     7,     5,    13,    14,    75,    76,    62,    16,
      17,     5,    13,    14,    61,    63,     7,    65,    22,     7,
      27,    27,    30,    31,    71,    69,     7,     6,    28,    63,
      64,    64,     7,    58,    13,    13,    31,    29,    73,    76,
       7,    19,    20,    66,    28,    28,    44,    72,    45,     5,
       5
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
#endif


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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  *++yyvsp = yylval;

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

/* Line 1806 of yacc.c  */
#line 23 "gram.y"
    {return 0;}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 28 "gram.y"
    { (yyval).MakeHelp(); return 9;}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 29 "gram.y"
    {Simple_Log::StartTransaction( (string)(yyvsp[(3) - (3)]) ); return 0;}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 31 "gram.y"
    {Simple_Log::EndTransaction();return 0;}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 34 "gram.y"
    {g_table_result = (yyval).MakeSelectNode((yyvsp[(3) - (8)]),(yyvsp[(5) - (8)]),(yyvsp[(6) - (8)]),(yyvsp[(7) - (8)]),1);return 0;}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 35 "gram.y"
    {g_table_result = (yyval).MakeSelectNode((yyvsp[(2) - (7)]),(yyvsp[(4) - (7)]),(yyvsp[(5) - (7)]),(yyvsp[(6) - (7)]),0);return 0;}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 42 "gram.y"
    {
											(yyval).AppendNameEntry((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
										  }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 45 "gram.y"
    {
					(yyval)= (vector<NameEntry>*)(yyvsp[(1) - (1)]);
					
				}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 50 "gram.y"
    {  NameEntry tmp_entry((yyvsp[(1) - (1)]),"");
				(yyval)=&tmp_entry;}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 52 "gram.y"
    { NameEntry tmp_entry((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); 
				(yyval)=&tmp_entry;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 54 "gram.y"
    { NameEntry tmp_entry((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])); 
				(yyval)=&tmp_entry;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 57 "gram.y"
    {
											(yyval).AppendAttrEntry((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]).GetAttr());
										  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 60 "gram.y"
    {
					Attribute attr = (yyval).GetAttr();
					vector<Attribute> new_attrs;
					new_attrs.push_back(attr);
					(yyval) = &new_attrs;
				 }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 68 "gram.y"
    { NameEntry tmp_entry((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); Attribute new_attr(tmp_entry,""); 
						  (yyval).SetAttr(new_attr);}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 70 "gram.y"
    {  NameEntry tmp_entry("",(yyvsp[(1) - (1)])); Attribute new_attr(tmp_entry,"");
				(yyval).SetAttr(new_attr);}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 72 "gram.y"
    { NameEntry tmp_entry("",(yyvsp[(1) - (3)])); Attribute new_attr(tmp_entry,(yyvsp[(3) - (3)])); 
				(yyval).SetAttr(new_attr);}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 74 "gram.y"
    { NameEntry tmp_entry = (yyvsp[(1) - (3)]).GetAttr().GetName(); Attribute new_attr(tmp_entry,(yyvsp[(3) - (3)])); 
				(yyval).SetAttr(new_attr);}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 76 "gram.y"
    { NameEntry tmp_entry = (yyvsp[(1) - (2)]).GetAttr().GetName(); Attribute new_attr(tmp_entry,(yyvsp[(2) - (2)])); 
				(yyval).SetAttr(new_attr);}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 78 "gram.y"
    { NameEntry tmp_entry("",(yyvsp[(1) - (2)])); Attribute new_attr(tmp_entry,(yyvsp[(2) - (2)])); 
				(yyval).SetAttr(new_attr);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 83 "gram.y"
    {(yyval).SetAvailable(false);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 84 "gram.y"
    {(yyval)=(yyvsp[(2) - (2)]);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 87 "gram.y"
    { NameEntry new_entry("",(yyvsp[(1) - (1)])); (yyval).SetSimpleExprOperand1(new_entry);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 88 "gram.y"
    {NameEntry new_entry((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); (yyval).SetSimpleExprOperand1(new_entry);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 90 "gram.y"
    {(yyval).SetSimpleOperator(SimpleExpr::LargeThan);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 91 "gram.y"
    {(yyval).SetSimpleOperator(SimpleExpr::Equal);}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 92 "gram.y"
    {(yyval).SetSimpleOperator(SimpleExpr::SmallThan);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 94 "gram.y"
    { SimpleExpr::SecondOperand operand2; 
							 operand2.iVal = (yyvsp[(1) - (1)]); operand2.oper_type = SimpleExpr::IntValue;
							 (yyval).SetSimpleExprOperand2(operand2);}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 97 "gram.y"
    { SimpleExpr::SecondOperand operand2; 
				 operand2.dVal = (yyvsp[(1) - (1)]); operand2.oper_type = SimpleExpr::RealValue;
				 (yyval).SetSimpleExprOperand2(operand2);}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 100 "gram.y"
    { SimpleExpr::SecondOperand operand2; 
						   operand2.name_entry = (yyvsp[(1) - (1)]).GetSimpleExprOperand1(); 
						   if( operand2.name_entry.GetSecondName()[0] == 39)
						  	{	operand2.oper_type == SimpleExpr::StrValue;operand2.strVal= operand2.name_entry.GetSecondName(); }
						   else
								operand2.oper_type = SimpleExpr::AttrName;
								
						   (yyval).SetSimpleExprOperand2(operand2);
						   }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 111 "gram.y"
    { SimpleExpr new_expr((yyvsp[(1) - (3)]).GetSimpleExprOperand1(),(yyvsp[(3) - (3)]).GetSimpleExprOperand2(),(yyvsp[(2) - (3)]).GetSimpleOperator());
																    Conditions new_cond( new_expr); (yyval)=new_cond;}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 115 "gram.y"
    { Conditions cond2 = (yyvsp[(3) - (3)]); Conditions::ConditionOperator oper = Conditions::conditionAND;
								Conditions cond1 = (yyvsp[(1) - (3)]); cond1.AppendCondition(oper,&cond2); (yyval) = cond1;}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 118 "gram.y"
    { Conditions cond2 = (yyvsp[(3) - (3)]); Conditions::ConditionOperator oper = Conditions::conditionOR;
								Conditions cond1 = (yyvsp[(1) - (3)]); cond1.AppendCondition(oper,&cond2); (yyval) = cond1;}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 121 "gram.y"
    {(yyval).SetAvailable(false);}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 122 "gram.y"
    { (yyval)=(yyvsp[(3) - (4)]); (yyval)=(int)(yyvsp[(4) - (4)]);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 124 "gram.y"
    {(yyval)=1;}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 125 "gram.y"
    {(yyval)=1;}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 126 "gram.y"
    {(yyval)=2;}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 128 "gram.y"
    { (yyval).MakeCreateTable((yyvsp[(3) - (7)]),(yyvsp[(5) - (7)]));  return 1;}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 130 "gram.y"
    {(yyval).AppendColumnInfo((yyvsp[(1) - (3)]).GetColumnInfo(),(yyvsp[(3) - (3)]).GetColumnInfo() );}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 131 "gram.y"
    {(yyval).AppendColumnInfo((yyvsp[(1) - (1)]).GetColumnInfo() ); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 133 "gram.y"
    { ColumnInfo info; info.name=(string)(yyvsp[(1) - (5)]); string type = (string)(yyvsp[(2) - (5)]);
																		if(type == "int")
																		{
																			info.type = DataColumn::COLUMN_TYPE_INTEGER;
																		}
																		if(type == "float")
																		{
																			info.type = DataColumn::COLUMN_TYPE_REAL;
																		}
																		if(type == "varchar")
																		{
																			info.type = DataColumn::COLUMN_TYPE_VARCHAR;
																			info.append_val = (yyvsp[(2) - (5)]);
																		}
																		if(type == "char")
																		{
																			info.type = DataColumn::COLUMN_TYPE_CHAR;
																			info.append_val = (yyvsp[(2) - (5)]);
																		}
																		info.b_null = (int)(yyvsp[(3) - (5)]) == 1;
																		info.b_pk = (int)(yyvsp[(4) - (5)]) == 1;
																		info.b_fk = (int)(yyvsp[(5) - (5)]) == 1;
																		if(info.b_fk)
																		{
																			
																			info.fk_table_name = (yyvsp[(5) - (5)]).m_fk_info.ref_table_name;
																			info.fk_col_name = (yyvsp[(5) - (5)]).m_fk_info.ref_col_name;
																		
																		}
																		vector<ColumnInfo> infos; infos.push_back(info);
																		(yyval).AppendColumnInfo(infos);
																	  }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 167 "gram.y"
    {(yyval)="int";}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 168 "gram.y"
    {(yyval)="float";}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 169 "gram.y"
    {(yyval)="varchar"; (yyval)=(int)(yyvsp[(3) - (4)]);}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 170 "gram.y"
    {(yyval)="char"; (yyval)=(int)(yyvsp[(3) - (4)]);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 172 "gram.y"
    {(yyval)=0;}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 173 "gram.y"
    {(yyval)=0;}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 174 "gram.y"
    {(yyval)=1;}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 176 "gram.y"
    {(yyval)=0;}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 177 "gram.y"
    { (yyval)=1; Fk_Info info; info.ref_table_name=(string)(yyvsp[(3) - (4)]); info.ref_col_name=(string)(yyvsp[(4) - (4)]); (yyval).m_fk_info=info; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 179 "gram.y"
    {(yyval) = 0;}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 180 "gram.y"
    {(yyval) = 1;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 182 "gram.y"
    { (yyval).MakeInsert((yyvsp[(3) - (8)]),(yyvsp[(6) - (8)])); return 2;}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 184 "gram.y"
    {(yyval).AppendValue((yyvsp[(1) - (3)]).GetValue(),(yyvsp[(3) - (3)]).GetValue() ); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 185 "gram.y"
    {(yyval).SetValue((yyvsp[(1) - (1)]).GetValue() ); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 187 "gram.y"
    {(yyval).AppendValue((int)(yyvsp[(1) - (1)]) ); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 188 "gram.y"
    {(yyval).AppendValue( (double)(yyvsp[(1) - (1)])) ;}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 189 "gram.y"
    {(yyval).AppendValue( (string)(yyvsp[(1) - (1)]) ); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 191 "gram.y"
    {(yyval).MakeUpdate((yyvsp[(2) - (6)]),(yyvsp[(4) - (6)]),(yyvsp[(5) - (6)])); return 3; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 193 "gram.y"
    { SimpleExpr new_expr((yyvsp[(1) - (3)]).GetSimpleExprOperand1(),(yyvsp[(3) - (3)]).GetSimpleExprOperand2(),(yyvsp[(2) - (3)]).GetSimpleOperator());
																    Conditions new_cond( new_expr); (yyval)=new_cond;}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 197 "gram.y"
    {(yyval).MakeDelete((yyvsp[(3) - (5)]),(yyvsp[(4) - (5)]));  return 4;}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 199 "gram.y"
    { (yyval).CreateIndex((yyvsp[(4) - (6)]),(yyvsp[(5) - (6)])); return 5; }
    break;



/* Line 1806 of yacc.c  */
#line 2034 "gram.cpp"
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 2067 of yacc.c  */
#line 202 "gram.y"
   

int yyerror(char *msg)
{
printf("Error encountered: %s \n", msg);
return 0;

}
