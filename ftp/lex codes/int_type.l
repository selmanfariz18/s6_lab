%{
    #include<stdio.h>
%}
%%
[\t];
[0-9]+\.[0-9]+ {printf("Found a floating point number %s \n",yytext);}
[0-9]+ {printf("Found an integer number %s \n", yytext);}
[a-zA-Z0-9]+ {printf("Found a string %s \n",yytext);}
%%
int main()
{
    yylex();
}
