#include<stdio.h>

void main(){
	int state[10];
	int input[10];
	int str[10];
	int x[20];
	int s, n, k=0, j,a,i,l,t,q=0,fs,b,nxt,z;
	
	printf("Enter no. states:\n");
	scanf("%d",&s);
	
	printf("Enter no. of input symbol:");
	scanf("%d",&n);
	
	for(i=0;i<s;i++){
		printf("Enter state %d:\n",i);
		scanf("%d",&state[i]);
		printf("is it a final state?(1 yes 0 no):\n");
		scanf("%d",&a);
		if(a==1){
			fs=state[i];
		}
	}
	
	printf("Enter the input symbols:\n");
	for(i=0;i<n;i++){
		scanf("%d",&input[i]);
	}
	
	printf("Enter the transition function\n");
	for(i=0;i<s;i++){
		for(j=0;j<n;j++){
			printf("(q%d%d)=q",state[i],input[j]);
			scanf("%d",&b);
			x[k]=b;
			k++;
		}
	}
	
	do{
		printf("Enter the length of string:\n");
		scanf("%d",&l);
		
		printf("Enter input string\n");
		for(i=0;i<l;i++){
			scanf("%d",&str[i]);
		}
		
		q=0;
		for(i=0;i<l;i++){
			t=0;
			while(t<n){
				if(str[i]==input[t]){
					nxt=x[n*q+t];
					
					for(j=0;j<s;j++){
						if(nxt == state[j]){
							q=j;
							break;
						}
					}
					break;
				}
				t++;
			}
		}
		
		if(state[q]==fs){
			printf("String is accepted\n");
		} else{
			printf("String is not accepted\n");
		}
		
		printf("Doyou want to continue?(1 yes 0 no):");
		scanf("%d",&z);
	} while(z==1);
}
