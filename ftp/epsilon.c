#include <stdio.h>
#include <string.h>

char result[20][20]; // Stores the epsilon closure results for each state
char copy[3];        // To store the current state being processed
char states[20][3];  // Array to hold the input states

void add_state(char a[3], int *i) {
    strcpy(result[*i], a); // Copy the state to the results array
    (*i)++;                // Increment the count of added states
}


void display(int n) {
    int k = 0; // Loop index
    printf("Epsilon closure of %s = { ", copy); // Print the header
    for (k = 0; k < n; k++) {
        printf(" %s", result[k]); // Print each state in the closure
    }
    printf(" }\n"); // Close the output
}

int main() {
    FILE *INPUT; // File pointer for reading input data
    INPUT = fopen("input.dat", "r"); // Open the input file for reading
    if (INPUT == NULL) { // Check if the file was opened successfully
        perror("Error opening file");
        return 1; // Exit with error code if file opening fails
    }

    char state[3]; // Variable to hold the current state being processed
    int i, n, k;   // Indices for state count and loops

    // Prompt user for the number of states and read them
    printf("Enter the number of states: ");
    scanf("%d", &n);
    printf("Enter the states:\n");
    for (k = 0; k < n; k++) {
        scanf("%s", states[k]); // Read each state into the states array
    }

    // Iterate through each state to compute its epsilon closure
    for (k = 0; k < n; k++) {
        i = 0; // Reset the index for results
        strcpy(state, states[k]); // Copy the current state
        strcpy(copy, state); // Store the state for display
        add_state(state, &i); // Add the initial state to the closure

        // Read transitions from the file until EOF
        while (1) {
            char state1[3], input[3], state2[3]; // Temporary variables for transitions
            int end = fscanf(INPUT, "%s %s %s", state1, input, state2); // Read a transition
            if (end == EOF) {
                break; // Exit if end of file is reached
            }
            // Check if the current state has an epsilon transition
            if (strcmp(state, state1) == 0 && strcmp(input, "e") == 0) {
                add_state(state2, &i); // Add the resulting state to the closure
                strcpy(state, state2); // Move to the next state
            }
        }
        display(i); // Display the epsilon closure for the current state
        rewind(INPUT); // Rewind the file pointer for the next state
    }

    fclose(INPUT); // Close the input file
    return 0; // Return success
}
