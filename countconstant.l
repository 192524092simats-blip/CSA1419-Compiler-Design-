%{
#include <stdio.h>
int cons = 0;
%}

digit [0-9]

%%

{digit}+   { cons++; printf("%s is a constant\n", yytext); }
.|\n       { }

%%

int yywrap(void) {
    return 1;
}

int main(void)
{
    FILE *f;
    char file[20];

    printf("Enter File Name : ");
    scanf("%s", file);

    f = fopen(file, "r");
    if (f == NULL) {
        printf("File not found\n");
        return 1;
    }

    yyin = f;
    yylex();

    printf("Number of Constants : %d\n", cons);
    fclose(yyin);
}
