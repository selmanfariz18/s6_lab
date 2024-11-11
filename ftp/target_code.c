#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isp(char item);
void output(char item);
void push(char item);
char pop(void);

char infix[20];
char postfix[20];
char stack[20];
int top = 0;
int z = 0;
int pc = 0x5000;

int main() {
    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove newline character

    int l = strlen(infix);
    push('#');

    for (int i = 0; i < l; i++) {
        char item = infix[i];

        if (isalpha(item)) {
            output(item);
        } else if (item == '+' || item == '-' || item == '*' || item == '/' || item == '^') {
            while (isp(stack[top]) >= isp(item)) {
                output(pop());
            }
            push(item);
        } else if (item == '(') {
            push(item);
        } else if (item == ')') {
            while ((item = pop()) != '(') {
                output(item);
            }
        }
    }

    while (stack[top] != '#') {
        output(pop());
    }

    postfix[z] = '\0';
    printf("Postfix expression: %s\n", postfix);

    printf("8085 Code Generation:\n");
    for (int i = 0; i < z; i++) {
        if (isalpha(postfix[i])) {
            printf("%04x MVI A, %c\n", pc, postfix[i]);
            pc += 2;
            printf("%04x PUSH A\n", pc);
            pc += 1;
        } else {
            printf("%04x POP B\n", pc);
            pc += 1;
            printf("%04x POP A\n", pc);
            pc += 1;

            if (postfix[i] == '+') {
                printf("%04x ADD B\n", pc);
            } else if (postfix[i] == '-') {
                printf("%04x SUB B\n", pc);
            } else if (postfix[i] == '*') {
                printf("%04x MOV C, A\n", pc);
                pc += 1;
                printf("%04x MVI A, 0\n", pc);
                pc += 2;
                printf("%04x ADD B\n", pc);
            } else if (postfix[i] == '/') {
                printf("%04x MOV C, A\n", pc);
                pc += 1;
                printf("%04x MVI A, 0\n", pc);
                pc += 2;
                printf("%04x ADD B\n", pc);
            }
            printf("%04x PUSH A\n", pc);
            pc += 1;
        }
    }

    return 0;
}

int isp(char item) {
    if (item == '+' || item == '-') return 1;
    if (item == '*' || item == '/') return 2;
    if (item == '^') return 3;
    return 0;
}

void output(char item) {
    postfix[z++] = item;
}

void push(char item) {
    stack[++top] = item;
}

char pop(void) {
    return stack[top--];
}
