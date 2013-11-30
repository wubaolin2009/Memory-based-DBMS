/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
/* Tokens.  */
#define SELECT 258
#define FROM 259
#define ID 260
#define SEPARATER 261
#define STMT_END 262
#define AS 263
#define PERIOD 264
#define LT 265
#define ST 266
#define EQ 267
#define INTEGER 268
#define REALNUM 269
#define WHERE 270
#define AND 271
#define OR 272
#define DISTINCT 273
#define ASC 274
#define DESC 275
#define SORT 276
#define BY 277
#define CREATE 278
#define TABLE 279
#define LGB 280
#define RGB 281
#define LSB 282
#define RSB 283
#define PK 284
#define NOT 285
#define COLUMN_NULL 286
#define TYPE_FLOAT 287
#define TYPE_INTEGER 288
#define TYPE_VARCHAR 289
#define TYPE_CHAR 290
#define INSERT 291
#define INTO 292
#define VALUES 293
#define SET 294
#define DELETE 295
#define UPDATE 296
#define INDEX 297
#define ON 298
#define FK 299
#define REF 300
#define BEGIN_TR 301
#define END_TR 302
#define TRANSACTION 303
#define CMD_HELP 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

