#include<stdio.h>
#include<string.h>
#include<ctype.h>

void E();
void Eprime();
void T();
void Tprime();
void F();

char input[10];
int i=0,error=0;

void E(){
	T();
	Eprime();
}

void Eprime(){
	if(input[i]=='+'){
		i++;
		T();
		Eprime();
	}
}

void T(){
	F();
	Tprime();
}

void Tprime(){
	if(input[i]=='*'){
		i++;
		F();
		Tprime();
	}
}

void F(){
	if(input[i]=='('){
		i++;
		E();
		if(input[i]==')'){
			i++;
		}
	}
	else if(isalpha(input[i])){
		i++;
		while(isalnum(input[i])||input[i]=='_'){
			i++;
		}
	}
	else error=1;
}

void main(){
	printf("Enter arithmetic expression:");
	//fgets(input,sizeof(input),stdin);
	scanf("%s",&input);
	puts(input);
	E();
	printf("%d\t%d\n",i,strlen(input));
	if(strlen(input)==i && error==0)
		printf("Accepted");
	else
		printf("Rejected");
}
