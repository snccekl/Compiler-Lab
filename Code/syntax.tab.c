/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./syntax.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "lex.yy.c"
    extern int yylineno;
    extern Node* Root;
    extern int error;

    void yyerror(char const *msg){
        if(strcmp(msg,"syntax error") == 0){
            printf("Error type B at Line %d: %s\n", yylineno,msg);
        }
    }

#line 87 "./syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_SEMI = 6,                       /* SEMI  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 8,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 9,                      /* RELOP  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_STAR = 12,                      /* STAR  */
  YYSYMBOL_DIV = 13,                       /* DIV  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_DOT = 16,                       /* DOT  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_TYPE = 18,                      /* TYPE  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_LB = 21,                        /* LB  */
  YYSYMBOL_RB = 22,                        /* RB  */
  YYSYMBOL_LC = 23,                        /* LC  */
  YYSYMBOL_RC = 24,                        /* RC  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_UMINUS = 30,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 31,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_Program = 33,                   /* Program  */
  YYSYMBOL_ExtDefList = 34,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 35,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 36,                /* ExtDecList  */
  YYSYMBOL_Specifier = 37,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 38,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 39,                    /* OptTag  */
  YYSYMBOL_Tag = 40,                       /* Tag  */
  YYSYMBOL_VarDec = 41,                    /* VarDec  */
  YYSYMBOL_FunDec = 42,                    /* FunDec  */
  YYSYMBOL_VarList = 43,                   /* VarList  */
  YYSYMBOL_ParamDec = 44,                  /* ParamDec  */
  YYSYMBOL_CompSt = 45,                    /* CompSt  */
  YYSYMBOL_StmtList = 46,                  /* StmtList  */
  YYSYMBOL_Stmt = 47,                      /* Stmt  */
  YYSYMBOL_DefList = 48,                   /* DefList  */
  YYSYMBOL_Def = 49,                       /* Def  */
  YYSYMBOL_DecList = 50,                   /* DecList  */
  YYSYMBOL_Dec = 51,                       /* Dec  */
  YYSYMBOL_Exp = 52,                       /* Exp  */
  YYSYMBOL_Args = 53                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    39,    39,    40,    43,    44,    47,    48,    49,    50,
      53,    54,    58,    59,    62,    63,    64,    67,    68,    71,
      75,    76,    77,    80,    81,    82,    85,    86,    87,    90,
      91,    94,    95,    98,    99,   102,   103,   104,   105,   106,
     107,   108,   112,   113,   116,   119,   120,   123,   124,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   148,   149
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV",
  "AND", "OR", "DOT", "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "UMINUS", "LOWER_THAN_ELSE",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-68)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,     6,   -56,     3,    15,   -56,    37,   166,   -56,    -7,
      -5,   -56,   -56,   -56,   -56,   106,     5,   -56,    42,    -2,
      12,    74,   101,   -56,    45,    50,   -56,    40,   -56,    45,
      52,    40,    29,   -56,    45,    41,    70,   -56,   -56,   -56,
      63,    67,    31,    68,    80,   -56,   -56,    79,   -56,    55,
     -56,   197,   -56,   -56,    69,   157,   157,   157,   157,    84,
      92,   -56,    93,    67,   169,   157,   -56,    45,   -56,   146,
     -56,    -9,    -9,   241,   183,   157,   157,   -56,   -56,   -56,
     157,   157,   157,   157,   157,   157,   157,   157,   115,   157,
     283,   -56,   -56,   212,   110,   -56,   -56,   255,   269,   283,
     316,   102,   102,    -9,    -9,   309,   296,   -56,   226,   157,
     -56,    78,   105,   -56,   -56,   127,    97,   -56,   105,   105,
     -56,   -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    12,    18,     0,     2,     0,     0,    13,    19,
       0,    15,     1,    16,     4,     9,    20,     7,     0,    10,
       0,     0,     0,     6,     0,     0,    32,     0,     8,     0,
       0,     0,    16,    24,     0,     0,    27,    22,    20,    11,
       0,     0,    47,     0,    45,    14,    42,    29,    23,     0,
      21,    32,    65,    66,    64,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,    44,     0,    26,     0,
      67,    58,    59,     0,     0,     0,     0,    31,    33,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,    46,    61,    69,     0,    57,    37,     0,     0,    49,
      52,    53,    54,    55,    56,    50,    51,    63,     0,     0,
      60,     0,     0,    62,    68,    32,    38,    41,     0,     0,
      40,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -56,   -56,   132,   -56,   120,    11,   -56,   -56,   -56,   -25,
     -56,   107,   -56,   134,    96,    34,   142,   -56,   103,   -56,
     -55,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    18,    29,     8,    10,    11,    19,
      20,    35,    36,    61,    62,    63,    30,    31,    43,    44,
      64,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    72,    73,    74,    42,    24,    -3,    88,     9,    47,
      90,     7,    89,    26,    93,    12,   -17,     7,    21,    25,
      97,    98,    -5,     1,    22,    99,   100,   101,   102,   103,
     104,   105,   106,    34,   108,    27,   -30,    -5,    13,    65,
       2,    13,    42,   -43,   -43,   -43,    37,     3,    23,   -28,
      38,   -43,    25,    40,    93,     2,    32,   -43,     2,   -43,
      34,    48,     3,   -43,   -43,     3,   -43,   -43,    51,   -43,
      52,    53,    54,     2,    66,    13,    45,    49,    55,   115,
       3,    52,    53,    54,    56,    50,    57,    67,    69,    55,
      27,   -34,     2,    58,    59,    56,    60,    57,   -43,     3,
      25,    27,    32,    75,    58,    59,    51,    60,    52,    53,
      54,    76,   -22,   -22,    84,    85,    55,    77,    88,     2,
     107,    33,    56,    89,    57,   119,     3,   -22,    27,   -25,
     110,    58,    59,   -67,    60,   -67,   -67,   -67,    14,   -67,
     -67,   -67,   -67,   -67,    39,   116,   117,    70,   -67,    52,
      53,    54,   120,   121,    28,   118,    68,    55,    70,    78,
      52,    53,    54,    56,     0,    57,    92,    15,    55,    41,
      91,    16,    17,    46,    56,    79,    57,    80,    81,    82,
      83,    84,    85,    86,    87,    88,   114,     0,     0,    96,
      89,    80,    81,    82,    83,    84,    85,    86,    87,    88,
       0,     0,     0,   -67,    89,   -67,   -67,   -67,     0,   -67,
     -67,   -67,   -67,   -67,     0,     0,     0,     0,   -67,   109,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     0,
       0,     0,     0,    89,    80,    81,    82,    83,    84,    85,
      86,    87,    88,     0,     0,     0,     0,    89,   113,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     0,     0,
       0,    95,    89,    80,    81,    82,    83,    84,    85,    86,
      87,    88,     0,     0,     0,   111,    89,    80,    81,    82,
      83,    84,    85,    86,    87,    88,     0,     0,     0,   112,
      89,    80,    81,    82,    83,    84,    85,    86,    87,    88,
       0,     0,     0,     0,    89,    81,    82,    83,    84,    85,
      86,     0,    88,     0,     0,     0,     0,    89,    81,    82,
      83,    84,    85,     0,     0,    88,    82,    83,    84,    85,
      89,     0,    88,     0,     0,     0,     0,    89
};

static const yytype_int8 yycheck[] =
{
      55,    56,    57,    58,    29,     7,     0,    16,     5,    34,
      65,     0,    21,     1,    69,     0,    23,     6,    23,    21,
      75,    76,     0,     1,    19,    80,    81,    82,    83,    84,
      85,    86,    87,    22,    89,    23,     7,     0,     1,     8,
      18,     1,    67,     3,     4,     5,     1,    25,     6,    20,
       5,    11,    21,     3,   109,    18,     1,    17,    18,    19,
      49,    20,    25,    23,    24,    25,    26,    27,     1,    29,
       3,     4,     5,    18,     6,     1,    24,     7,    11,     1,
      25,     3,     4,     5,    17,    22,    19,     7,    19,    11,
      23,    24,    18,    26,    27,    17,    29,    19,    24,    25,
      21,    23,     1,    19,    26,    27,     1,    29,     3,     4,
       5,    19,     6,     7,    12,    13,    11,    24,    16,    18,
       5,    20,    17,    21,    19,    28,    25,    21,    23,    23,
      20,    26,    27,     6,    29,     8,     9,    10,     6,    12,
      13,    14,    15,    16,    24,   111,   112,     1,    21,     3,
       4,     5,   118,   119,    20,    28,    49,    11,     1,    63,
       3,     4,     5,    17,    -1,    19,    20,     1,    11,    27,
      67,     5,     6,    31,    17,     6,    19,     8,     9,    10,
      11,    12,    13,    14,    15,    16,   109,    -1,    -1,     6,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,     6,    21,     8,     9,    10,    -1,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    21,    22,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    21,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    -1,    -1,    -1,    21,     9,    10,
      11,    12,    13,    -1,    -1,    16,    10,    11,    12,    13,
      21,    -1,    16,    -1,    -1,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    25,    33,    34,    35,    37,    38,     5,
      39,    40,     0,     1,    34,     1,     5,     6,    36,    41,
      42,    23,    19,     6,     7,    21,     1,    23,    45,    37,
      48,    49,     1,    20,    37,    43,    44,     1,     5,    36,
       3,    48,    41,    50,    51,    24,    48,    41,    20,     7,
      22,     1,     3,     4,     5,    11,    17,    19,    26,    27,
      29,    45,    46,    47,    52,     8,     6,     7,    43,    19,
       1,    52,    52,    52,    52,    19,    19,    24,    46,     6,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    21,
      52,    50,    20,    52,    53,    20,     6,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,     5,    52,     7,
      20,    20,    20,    22,    53,     1,    47,    47,    28,    28,
      47,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    33,    34,    34,    35,    35,    35,    35,
      36,    36,    37,    37,    38,    38,    38,    39,    39,    40,
      41,    41,    41,    42,    42,    42,    43,    43,    43,    44,
      44,    45,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     3,     2,     3,     2,
       1,     3,     1,     1,     5,     2,     1,     1,     0,     1,
       1,     4,     1,     4,     3,     1,     3,     1,     1,     2,
       1,     4,     1,     2,     0,     2,     1,     3,     5,     7,
       7,     5,     2,     0,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     3,     4,     3,     1,     1,     1,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Program: ExtDefList  */
#line 39 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Program",""); addNode((yyval.node), 1, (yyvsp[0].node)); Root = (yyval.node);}
#line 1246 "./syntax.tab.c"
    break;

  case 3: /* Program: error  */
#line 40 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1252 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 43 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ExtDefList",""); addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1258 "./syntax.tab.c"
    break;

  case 5: /* ExtDefList: %empty  */
#line 44 "./syntax.y"
                                                {(yyval.node) = NULL;}
#line 1264 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier ExtDecList SEMI  */
#line 47 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ExtDef","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1270 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier SEMI  */
#line 48 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ExtDef","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1276 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier FunDec CompSt  */
#line 49 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ExtDef","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1282 "./syntax.tab.c"
    break;

  case 9: /* ExtDef: Specifier error  */
#line 50 "./syntax.y"
                                                {error++;yyerror("Syntax error.");}
#line 1288 "./syntax.tab.c"
    break;

  case 10: /* ExtDecList: VarDec  */
#line 53 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ExtDecList","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1294 "./syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 54 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ExtDecList","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1300 "./syntax.tab.c"
    break;

  case 12: /* Specifier: TYPE  */
#line 58 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Specifier","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1306 "./syntax.tab.c"
    break;

  case 13: /* Specifier: StructSpecifier  */
#line 59 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Specifier","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1312 "./syntax.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 62 "./syntax.y"
                                                {(yyval.node) = createNode(1, "StructSpecifier","");addNode((yyval.node), 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1318 "./syntax.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT Tag  */
#line 63 "./syntax.y"
                                                {(yyval.node) = createNode(1, "StructSpecifier","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1324 "./syntax.tab.c"
    break;

  case 17: /* OptTag: ID  */
#line 67 "./syntax.y"
                                                {(yyval.node) = createNode(1, "OptTag","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1330 "./syntax.tab.c"
    break;

  case 18: /* OptTag: %empty  */
#line 68 "./syntax.y"
                                                {(yyval.node) = NULL;}
#line 1336 "./syntax.tab.c"
    break;

  case 19: /* Tag: ID  */
#line 71 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Tag","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1342 "./syntax.tab.c"
    break;

  case 20: /* VarDec: ID  */
#line 75 "./syntax.y"
                                                {(yyval.node) = createNode(1, "VarDec","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1348 "./syntax.tab.c"
    break;

  case 21: /* VarDec: VarDec LB INT RB  */
#line 76 "./syntax.y"
                                                {(yyval.node) = createNode(1, "VarDec","");addNode((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1354 "./syntax.tab.c"
    break;

  case 22: /* VarDec: error  */
#line 77 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1360 "./syntax.tab.c"
    break;

  case 23: /* FunDec: ID LP VarList RP  */
#line 80 "./syntax.y"
                                                {(yyval.node) = createNode(1, "FunDec","");addNode((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1366 "./syntax.tab.c"
    break;

  case 24: /* FunDec: ID LP RP  */
#line 81 "./syntax.y"
                                                {(yyval.node) = createNode(1, "FunDec","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1372 "./syntax.tab.c"
    break;

  case 25: /* FunDec: error  */
#line 82 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1378 "./syntax.tab.c"
    break;

  case 26: /* VarList: ParamDec COMMA VarList  */
#line 85 "./syntax.y"
                                                {(yyval.node) = createNode(1, "VarList","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1384 "./syntax.tab.c"
    break;

  case 27: /* VarList: ParamDec  */
#line 86 "./syntax.y"
                                                {(yyval.node) = createNode(1, "VarList","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1390 "./syntax.tab.c"
    break;

  case 28: /* VarList: error  */
#line 87 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1396 "./syntax.tab.c"
    break;

  case 29: /* ParamDec: Specifier VarDec  */
#line 90 "./syntax.y"
                                                {(yyval.node) = createNode(1, "ParamDec","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1402 "./syntax.tab.c"
    break;

  case 30: /* ParamDec: error  */
#line 91 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1408 "./syntax.tab.c"
    break;

  case 31: /* CompSt: LC DefList StmtList RC  */
#line 94 "./syntax.y"
                                                {(yyval.node) = createNode(1, "CompSt","");addNode((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1414 "./syntax.tab.c"
    break;

  case 32: /* CompSt: error  */
#line 95 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1420 "./syntax.tab.c"
    break;

  case 33: /* StmtList: Stmt StmtList  */
#line 98 "./syntax.y"
                                                {(yyval.node) = createNode(1, "StmtList","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1426 "./syntax.tab.c"
    break;

  case 34: /* StmtList: %empty  */
#line 99 "./syntax.y"
                                                {(yyval.node) = NULL;}
#line 1432 "./syntax.tab.c"
    break;

  case 35: /* Stmt: Exp SEMI  */
#line 102 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Stmt","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1438 "./syntax.tab.c"
    break;

  case 36: /* Stmt: CompSt  */
#line 103 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Stmt","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1444 "./syntax.tab.c"
    break;

  case 37: /* Stmt: RETURN Exp SEMI  */
#line 104 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Stmt","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1450 "./syntax.tab.c"
    break;

  case 38: /* Stmt: IF LP Exp RP Stmt  */
#line 105 "./syntax.y"
                                                          {(yyval.node) = createNode(1, "Stmt","");addNode((yyval.node), 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1456 "./syntax.tab.c"
    break;

  case 39: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 106 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Stmt","");addNode((yyval.node), 7, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1462 "./syntax.tab.c"
    break;

  case 40: /* Stmt: IF LP Exp RP error ELSE Stmt  */
#line 107 "./syntax.y"
                                                {error++;yyerror("Missing \";\".");}
#line 1468 "./syntax.tab.c"
    break;

  case 41: /* Stmt: WHILE LP Exp RP Stmt  */
#line 108 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Stmt","");addNode((yyval.node), 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1474 "./syntax.tab.c"
    break;

  case 42: /* DefList: Def DefList  */
#line 112 "./syntax.y"
                                                {(yyval.node) = createNode(1, "DefList","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1480 "./syntax.tab.c"
    break;

  case 43: /* DefList: %empty  */
#line 113 "./syntax.y"
                                                {(yyval.node) = NULL;}
#line 1486 "./syntax.tab.c"
    break;

  case 44: /* Def: Specifier DecList SEMI  */
#line 116 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Def","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1492 "./syntax.tab.c"
    break;

  case 45: /* DecList: Dec  */
#line 119 "./syntax.y"
                                                {(yyval.node) = createNode(1, "DecList","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1498 "./syntax.tab.c"
    break;

  case 46: /* DecList: Dec COMMA DecList  */
#line 120 "./syntax.y"
                                                {(yyval.node) = createNode(1, "DecList","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1504 "./syntax.tab.c"
    break;

  case 47: /* Dec: VarDec  */
#line 123 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Dec","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1510 "./syntax.tab.c"
    break;

  case 48: /* Dec: VarDec ASSIGNOP Exp  */
#line 124 "./syntax.y"
                                                {(yyval.node) = createNode(1, "Dec","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1516 "./syntax.tab.c"
    break;

  case 49: /* Exp: Exp ASSIGNOP Exp  */
#line 127 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1522 "./syntax.tab.c"
    break;

  case 50: /* Exp: Exp AND Exp  */
#line 128 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1528 "./syntax.tab.c"
    break;

  case 51: /* Exp: Exp OR Exp  */
#line 129 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1534 "./syntax.tab.c"
    break;

  case 52: /* Exp: Exp RELOP Exp  */
#line 130 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1540 "./syntax.tab.c"
    break;

  case 53: /* Exp: Exp PLUS Exp  */
#line 131 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1546 "./syntax.tab.c"
    break;

  case 54: /* Exp: Exp MINUS Exp  */
#line 132 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1552 "./syntax.tab.c"
    break;

  case 55: /* Exp: Exp STAR Exp  */
#line 133 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1558 "./syntax.tab.c"
    break;

  case 56: /* Exp: Exp DIV Exp  */
#line 134 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1564 "./syntax.tab.c"
    break;

  case 57: /* Exp: LP Exp RP  */
#line 135 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1570 "./syntax.tab.c"
    break;

  case 58: /* Exp: MINUS Exp  */
#line 136 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1576 "./syntax.tab.c"
    break;

  case 59: /* Exp: NOT Exp  */
#line 137 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1582 "./syntax.tab.c"
    break;

  case 60: /* Exp: ID LP Args RP  */
#line 138 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1588 "./syntax.tab.c"
    break;

  case 61: /* Exp: ID LP RP  */
#line 139 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1594 "./syntax.tab.c"
    break;

  case 62: /* Exp: Exp LB Exp RB  */
#line 140 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1600 "./syntax.tab.c"
    break;

  case 63: /* Exp: Exp DOT ID  */
#line 141 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1606 "./syntax.tab.c"
    break;

  case 64: /* Exp: ID  */
#line 142 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1612 "./syntax.tab.c"
    break;

  case 65: /* Exp: INT  */
#line 143 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1618 "./syntax.tab.c"
    break;

  case 66: /* Exp: FLOAT  */
#line 144 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Exp","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1624 "./syntax.tab.c"
    break;

  case 67: /* Exp: error  */
#line 145 "./syntax.y"
                                                {error++;yyerror("error");}
#line 1630 "./syntax.tab.c"
    break;

  case 68: /* Args: Exp COMMA Args  */
#line 148 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Args","");addNode((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1636 "./syntax.tab.c"
    break;

  case 69: /* Args: Exp  */
#line 149 "./syntax.y"
                                                {(yyval.node)=createNode(1, "Args","");addNode((yyval.node), 1, (yyvsp[0].node));}
#line 1642 "./syntax.tab.c"
    break;


#line 1646 "./syntax.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 152 "./syntax.y"
