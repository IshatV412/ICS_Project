%{
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%

"|"                     { return EOL; }

[ \t\r]+                ;    // Ignore spaces and tabs
\n                      { yylineno++; } // Track new lines
"//".*                  ; //single-line comments 

"if"                    { return IF; }
"then"                  { return THEN; }
"else"                  { return ELSE; }
"return"                { return RETURN; }
"create"                { return CREATE; }
"as"                    { return AS; }
"of"                    { return OF; }
"show"                  { return SHOW; }
"ask"                   { return ASK; }
"loop"                  { return LOOP; }
"from"                  { return FROM; }
"to"                    { return TO; }
"while"                 { return WHILE; }
"next"                  { return NEXT; }
"leave"                 { return LEAVE; }
"let"                   { return LET; }
"generate"              { return GENERATE; }
"call"                  { return CALL; }
"and"                   { return AND; }
"or"                    { return OR; }
"insert"                { return INSERT; }
"set"                   { return SET; }
"get"                   { return GET; }
"search"                { return SEARCH; }
"sort"                  { return SORT; }
"delete"                { return DELETE; }
"run"                   { return RUN; }


"integer"               { yylval.str = strdup("integer"); return INT_TYPE; }
"character"             { yylval.str = strdup("character"); return CHAR_TYPE; }
"float"                 { yylval.str = strdup("float"); return FLOAT_TYPE; }
"string"                { yylval.str = strdup("string"); return STRING_TYPE; }
"list"                  { yylval.str = strdup("list"); return LIST_TYPE; }
"pointer"               { yylval.str = strdup("pointer"); return POINTER; }
"linkedlist"            { yylval.str = strdup("linkedlist"); return LINKEDLIST; }
"dictionary"            { yylval.str = strdup("dictionary"); return DICTIONARY; }
"null"                  { yylval.str = strdup("null"); return NULL_TYPE; }
"boolean"               { yylval.str = strdup("boolean"); return BOOLEAN; }


"=="                    { return EQ; }
"!="                    { return NEQ; }
">="                    { return GTE; }
"<="                    { return LTE; }
">"                     { return GT; }
"<"                     { return LT; }
"="                     { return ASSIGN; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MULT; }
"/"                     { return DIV; }
"%"                     { return PERCENT; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"["                     { return LSQUARE; }
"]"                     { return RSQUARE; }
","                     { return COMMA; }
"&"                     { return AMPERSAND; }


[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFIER; }
[0-9]+\.[0-9]+          { yylval.float_val = atof(yytext); return FLOAT; }
[0-9]+                  { yylval.int_val = atoi(yytext); return INTEGER; }
'[^\\']'                { yylval.char_val = yytext[1]; return CHAR; }

\"[^\"]*\"              { yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str) - 1] = '\0'; return STRING; }

. { printf("Unrecognized token: %s\n", yytext); }
%%

int yywrap() { return 1; }
