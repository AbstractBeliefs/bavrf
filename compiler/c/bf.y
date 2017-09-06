%{
#include <stdbool.h>

#include "program_sequence.h"
#include "bf.parse.h"
#include "bf.lex.h"

int yyerror(node* *sequence, yyscan_t scanner, const char *msg) {
    printf("Aaa: %s\n", msg);
    return 0;
}
 
%}

%code requires {

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

}

%output  "bf.parse.c"
%defines "bf.parse.h"
 
%define api.pure
%define parse.error verbose
%lex-param   { yyscan_t scanner }
%parse-param { node* *sequence }
%parse-param { yyscan_t scanner }

%union {
    node* sequence;
}

%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_LEFT
%token TOKEN_RIGHT
%token TOKEN_LOOPSTART
%token TOKEN_LOOPEND
%token TOKEN_IN
%token TOKEN_OUT

%type <sequence> bf

%%

program
    : bf[B]         { *sequence = addNode(*sequence, $B); }
    | program bf[B] { *sequence = addNode(*sequence, $B); }
    ;

bf
    : TOKEN_ADD                                     { $$ = createArithmetic(1); }
    | TOKEN_SUB                                     { $$ = createArithmetic(-1); }
    | TOKEN_LEFT                                    { $$ = createNavigation(false); }
    | TOKEN_RIGHT                                   { $$ = createNavigation(true); }
    | TOKEN_LOOPSTART TOKEN_LOOPEND                 { }
    | TOKEN_LOOPSTART program[P] TOKEN_LOOPEND      { }
    | TOKEN_IN                                      { $$ = createIO(false); }
    | TOKEN_OUT                                     { $$ = createIO(true); }
    ;
 
%%
