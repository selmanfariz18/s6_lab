#include <stdio.h>
#include <string.h>

// Global variables
int k = 0, z = 0, i = 0, j = 0, c = 0; // Counters and flags
char a[16], ac[20], stk[15], act[10]; // Input string, action string, stack, and action message

// Function prototypes
void check(); // Function to check and perform reductions

// Main function
int main() {
    // Display the grammar rules
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");

    // Prompt user for input string
    puts("Enter input string: ");
    fgets(a, sizeof(a), stdin); // Use fgets to read the input string
    a[strcspn(a, "\n")] = '\0'; // Remove the newline character if present

    c = strlen(a); // Get the length of the input string
    strcpy(act, "SHIFT->"); // Initialize action message
    puts("stack \t input \t action"); // Print header for output

    // Parsing loop
    for (k = 0, i = 0, j = 0; j < c; k++, i++, j++) {
        // Check for identifier 'id' (assumed to be 'i' followed by 'd')
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j]; // Push 'i'
            stk[i + 1] = a[j + 1]; // Push 'd'
            stk[i + 2] = '\0'; // Null-terminate stack
            a[j] = ' '; // Replace in input string to signify processing
            a[j + 1] = ' '; // Replace next character as well
            printf("\n$%s\t%s$\t%sid", stk, a, act); // Print current state
            check(); // Check for reductions
        } else {
            stk[i] = a[j]; // Push current symbol to stack
            stk[i + 1] = '\0'; // Null-terminate stack
            a[j] = ' '; // Replace in input string
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act); // Print current state
            check(); // Check for reductions
        }
    }

    // Acceptance check
    if (j == c && i == 1 && stk[i] == '\0') {
        printf("\nAccept\n"); // Accepted if conditions are met
    } else {
        printf("\nReject\n"); // Rejected otherwise
    }

    return 0;
}

// Function to perform reduction based on grammar rules
void check() {
    strcpy(ac, "REDUCE TO E"); // Set action for reduction
    // Check for 'id' and reduce it to 'E'
    for (z = 0; z < c; z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E'; // Reduce 'id' to 'E'
            stk[z + 1] = '\0'; // Null-terminate stack
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Print reduction action
            j++; // Increment input index
        }
    }

    // Check for production E -> E + E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E'; // Reduce 'E + E' to 'E'
            stk[z + 1] = '\0'; // Null-terminate stack
            stk[z + 2] = '\0'; // Null-terminate next symbol
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Print reduction action
            i = i - 2; // Adjust stack index
        }
    }

    // Check for production E -> E * E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E'; // Reduce 'E * E' to 'E'
            stk[z + 1] = '\0'; // Null-terminate stack
            stk[z + 1] = '\0'; // Null-terminate next symbol
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Print reduction action
            i = i - 2; // Adjust stack index
        }
    }

    // Check for production E -> ( E )
    for (z = 0; z < c; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E'; // Reduce '(E)' to 'E'
            stk[z + 1] = '\0'; // Null-terminate stack
            stk[z + 1] = '\0'; // Null-terminate next symbol
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Print reduction action
            i = i - 2; // Adjust stack index
        }
    }
}

