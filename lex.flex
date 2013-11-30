%{
#include <io.h>
#include"lex_defines.h"
#include"gram.tab.h"

%}
%option noyywrap

%%
"select" {return SELECT;}
"from" {return FROM;}
"as"   {return AS;}
"where" {return WHERE;}
"and"   {return AND;}
"distinct" {return DISTINCT;}
"asc"   {return ASC;}
"desc"  {return DESC;}
"or"   {return OR;}
"sort" {return SORT;}
"by"  {return BY;}
">"	  {return LT;}
"<"	  {return ST;}
"="   {return EQ;}
"{"   {return LGB;}
"}"   {return RGB;}
"("   {return LSB;}
")"   {return RSB;}
"pk"  {return PK;}
"not" {return NOT;}
"null" {return COLUMN_NULL;}
"float" {return TYPE_FLOAT;}
"integer" {return TYPE_INTEGER;}
"varchar" {return TYPE_VARCHAR;}
"char" {return TYPE_CHAR;}
"create" {return CREATE;}
"table" {return TABLE;}
"insert" {return INSERT;}
"into" {return INTO;}
"values" {return VALUES;}
"update" {return UPDATE;}
"set" {return SET;}
"delete" {return DELETE;}
"index" {return INDEX;}
"on" {return ON;}
"fk" {return FK;}
"ref" {return REF;}
"transaction" {return TRANSACTION;}
"begin"  {return BEGIN_TR;}
"end" {return END_TR;}
"help" {return CMD_HELP;}

[1-9]+[0-9]* {yylval = atoi(yytext); return INTEGER;}
[0-9] {yylval=atoi(yytext);return INTEGER;}
[1-9]+[0-9]*[.][0-9]* {yylval = atof(yytext); return REALNUM;}
[0-9][.][0-9]*  {yylval=atof(yytext);return REALNUM;}
[.]    {return PERIOD;}
['a-zA-Z*][a-zA-Z0-9]*[']* { yylval = yytext; return ID;}
[,] {return SEPARATER;}
[ \t\n]
[;] {return STMT_END;}


%%