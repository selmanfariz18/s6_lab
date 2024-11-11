#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isp(char item);
void output(char item);
void push(char item);
char pop(void);
void quad(void);

char exp[20];
char res[20];
char a[20];
int top = 0;
int z = 0;
int i = 0;
int l;

void main() {
    char item; // Declare item here
    char x;    // Declare x here

   printf("Enter the infix expression: ");
   fgets(exp, sizeof(exp), stdin);
   exp[strcspn(exp, "\n")] = '\0'; // Remove the newline character added by fgets
    l = strlen(exp);
    push('#');

    while ((item = exp[i]) != '\0') {
        if (isalpha(item)) {
            output(item);
        } else if (item == '+' || item == '-' || item == '*' || item == '/' || item == '^') {
            while (isp(a[top]) >= isp(item)) {
                output(pop());
            }
            push(item);
        } else if (item == '(') {
            push(item);
        } else if (item == ')') {
            while ((x = pop()) != '(') {
                output(x);
            }
        }
        i++;
    }

    while ((x = pop()) != '#') {
        output(x);
    }
    res[z] = '\0';
    printf("Postfix expression: ");
    puts(res);
    quad();
}

int isp(char item) {
    if (item == '+' || item == '-') return 1;
    else if (item == '*' || item == '/') return 2;
    else if (item == '^') return 3;
    else return 0;
}

void output(char item) {
    res[z++] = item;
}

void push(char item) {
    a[++top] = item;
}

char pop(void) {
    return a[top--];
}

void quad() {
    int i, x = 0;
    char m, n, p, temp, str1[5], str2[5];
    printf("\noperator\top1\top2\tresult\n");
    printf("-------------------------------");

    for (i = 0; i < z; i++) { // Use 'z' for the number of output items
        if (isalnum(res[i])) {
            push(res[i]);
        } else {
            if (isalpha(m = pop())) {
                str1[0] = m;
                str1[1] = '\0';
            } else {
                str1[0] = 't';
                str1[1] = m;
                str1[2] = '\0';
            }
            if (isalpha(n = pop())) {
                str2[0] = n;
                str2[1] = '\0';
            } else {
                str2[0] = '\0';
            }
            x++;
            printf("\n%c\t\t%s\t%s\tt%d\n", res[i], str2, str1, x);
            temp = x + '0';
            push(temp);
        }
    }
}
