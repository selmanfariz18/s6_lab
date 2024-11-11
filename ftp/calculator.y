%{
#include<stdio.h>
%}
%union {int a_number;}
%start line
%type <a_number> exp term factor number digit

%%

line : exp ';' '\n' {printf("Result is %d\n",$1);}
;
exp : term {$$=$1;}
|exp '+' term {$$=$1+$3;}
|exp '-' term {$$=$1-$3;}
;
term : factor {$$=$1;}
| term '*' factor {$$=$1*$3;}
| term '/' factor {$$=$1/$3;}
;
factor : number {$$=$1;}
|'('exp')' {$$=$2;}
;
number : digit {$$=$1;}
|number digit {$$=$1*10+$2;}
;
digit : '0' {$$=0;}
|'1' {$$=1;}
|'2' {$$=2;}
|'3' {$$=3;}
|'4' {$$=4;}
|'5' {$$=5;}
|'6' {$$=6;}
|'7' {$$=7;}
|'8' {$$=8;}
|'9' {$$=9;}
;

%%

int main() {return yyparse();}
int yylex() {return getchar();}
void yyerror() {printf("error");}
