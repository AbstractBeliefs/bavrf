%{
#include <stdio.h>
#include "program_sequence.h"
#include "bf.parse.h"
%}

%option outfile="bf.lex.c" header-file="bf.lex.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%%
\+      { return TOKEN_ADD; }
-       { return TOKEN_SUB; }
\<      { return TOKEN_LEFT;}
\>      { return TOKEN_RIGHT; }
\[      { return TOKEN_LOOPSTART; }
\]      { return TOKEN_LOOPEND; }
\.      { return TOKEN_OUT; }
,       { return TOKEN_IN; }
.       { }
%%
