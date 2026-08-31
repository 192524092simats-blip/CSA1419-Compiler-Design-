%{
#include <stdio.h>
#include <string.h>

int keywords = 0, identifiers = 0;
%}

%%
"int"|"void"|"main"|"printf"|"include"   { printf("%s is a keyword\n", yytext); keywords++; }
"stdio.h"                                { printf("%s is a standard library\n", yytext); }
[0-9]+                                   { printf("%s is a number\n", yytext); }
\".*\"                                   { printf("%s is a string literal\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                   { printf("%s is a identifier\n", yytext); identifiers++; }
[ \t\n]                                  ;   /* ignore spaces */
.                                        ;   /* ignore others */
%%

int main()
{
    printf("Enter input:\n");
    yylex();

    printf("number of identifiers = %d\n", identifiers);
    printf("number of keywords = %d\n", keywords);

    return 0;
}

int yywrap()
{
    return 1;
}