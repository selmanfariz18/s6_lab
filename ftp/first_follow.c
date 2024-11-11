#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Global variables
int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10]; // Array to hold productions and FIRST/FOLLOW sets

// Function prototypes
void follow(char c); // Function to calculate FOLLOW set
void first(char c);  // Function to calculate FIRST set

int main() {
    int i, z;          // Loop counters and control variable
    char c, ch;       // Character variables for input and control

    // Prompt user for the number of productions
    printf("Enter the no of productions:\n");
    scanf("%d", &n);
    
    // Prompt user to enter the productions
    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch); // Read each production rule

    // Loop to find FIRST and FOLLOW sets for a given non-terminal
    do {
        m = 0; // Reset m for the new calculation
        printf("Enter the elements whose FIRST & FOLLOW is to be found: ");
        scanf(" %c", &c); // Read a non-terminal character (with space to skip newline)

        // Calculate and display the FIRST set
        first(c);
        printf("First(%c) = {", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]); // Print each element in the FIRST set
        printf("}\n");

        // Reset the FIRST set array
        strcpy(f, " ");
        m = 0; // Reset m for FOLLOW calculation
        
        // Calculate and display the FOLLOW set
        follow(c);
        printf("Follow(%c) = {", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]); // Print each element in the FOLLOW set
        printf("}\n");

        // Ask if the user wants to continue
        printf("Continue (0/1)? ");
        scanf("%d%c", &z, &ch); // Read continuation option (0 or 1)
    } while (z == 1); // Repeat if user enters 1

    return 0; // Exit the program
}

// Function to calculate the FIRST set for a given non-terminal
void first(char c) {
    int k; // Loop counter
    
    // If 'c' is a terminal, add it directly to the FIRST set
    if (!isupper(c))
        f[m++] = c;

    // Loop through all productions
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) { // Check if the production starts with 'c'
            // If the production is epsilon (denoted by '$')
            if (a[k][2] == '$')
                follow(a[k][0]); // Call FOLLOW for the non-terminal
            // If the next symbol is a terminal, add it to the FIRST set
            else if (islower(a[k][2]))
                f[m++] = a[k][2];
            // If the next symbol is a non-terminal, call FIRST recursively
            else
                first(a[k][2]);
        }
    }
}

// Function to calculate the FOLLOW set for a given non-terminal
void follow(char c) {
    // If 'c' is the start symbol, add '$' to the FOLLOW set
    if (a[0][0] == c)
        f[m++] = '$';

    // Loop through all productions
    for (i = 0; i < n; i++) {
        // Loop through the production rule starting from the 3rd character
        for (j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) { // If the current symbol matches 'c'
                // If there is a next symbol, call FIRST for it
                if (a[i][j + 1] != '\0')
                    first(a[i][j + 1]);
                // If 'c' is at the end of the production and is not the start symbol
                if (a[i][j + 1] == '\0' && c != a[i][0])
                    follow(a[i][0]); // Call FOLLOW for the parent non-terminal
            }
        }
    }
}
