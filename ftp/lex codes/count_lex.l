%{
    #include<stdio.h>
    int lines=0;
    int words=0;
    int chars=0;
%}
%%
[a-z|A-Z|0-9] {chars++;}
" " {words++;}
"\n" {lines++;chars++;words;}
%%
int main(int argc, char *argv[])
{
    //yyin=fopen(argv[1],"r");
    yylex();
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);
    return 0;
}
