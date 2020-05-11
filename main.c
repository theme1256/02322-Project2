#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Suppression for Clion warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
    printf("Hello, World!\n");

    // Init variables
    char input[MAX];
    char original[MAX];
    char output[MAX];
    char empty[] = "";
    char delim[] = " \n";

    // Init infinite loop
    while (1) {
        strcpy(output, empty);
        // Get input from stdin and make a copy for later use
        printf("Enter a value:");
        fgets(input, MAX, stdin);
        strcpy(original, input);

        // Split input by space and remove trailing \n
        char *ptr = strtok(input, delim);

        // Try to find ont of the known commands
        if (strcmp(ptr, "ADD") == 0) {
            printf("Found ADD\n");
            strcat(output, "0001");
        } else if (strcmp(ptr, "NOT") == 0) {
            printf("Found NOT\n");
            strcat(output, "1001");
        } else if (strcmp(ptr, "BR") == 0) {
            printf("Found BR\n");
            strcat(output, "0000");
        } else if (strcmp(ptr, "LD") == 0) {
            printf("Found BR\n");
            strcat(output, "0010");
        } else if (strcmp(ptr, "LDR") == 0) {
            printf("Found BR\n");
            strcat(output, "0110");
        } else if (strcmp(ptr, "ST") == 0) {
            printf("Found BR\n");
            strcat(output, "0011");
        } else {
            printf("Didn't recognize instruction, try again\n");
            continue;
        }

        // This loop is used to debug the string-splitting
        /*while (ptr != NULL) {
            printf("'%s'\n", ptr);
            ptr = strtok(NULL, delim);
        }*/

        // Print the original command and the binary equivalent
        printf("You entered: %s", original);
        printf("Binary equivalent: %s\n", output);
    }
    return 0;
}

// Suppression for Clion warnings
#pragma clang diagnostic pop