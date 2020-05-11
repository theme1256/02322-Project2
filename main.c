#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1000

// Suppression for Clion warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void findRegister(char *rtn, char *ptr);
void decStringToBinary(char *rtn, char *ptr);

int main() {
    printf("Hello, World!\n");

    // Init variables
    char input[MAX];
    char original[MAX];
    char output[MAX];
    char empty[] = "";
    char delim[] = " ,\n";
    char test[] = "";

    // Init infinite loop
    while (1) {
        strcpy(output, empty);
        // Get input from stdin and make a copy for later use
        printf("Input an LC3 assembly instruction:");
        fgets(input, MAX, stdin);
        strcpy(original, input);

        // Split input by space and comma and remove trailing \n
        char *ptr = strtok(input, delim);

        /* Try to find which of the known commands */
        if (strcmp(ptr, "ADD") == 0) {
            printf("Found ADD\n");
            strcat(output, "0001");
            // Move pointer to next split, should be DR
            ptr = strtok(NULL, delim);
            // Try to find out if it is R1-R7
            findRegister(test, ptr);
            if (strcmp(test, "") == 0) {
                printf("Didn't find a register, try again\n");
                continue;
            }
            // Add the binary equivalent to output
            strcat(output, test);
            // Move pointer to next split, should be SR1
            ptr = strtok(NULL, delim);
            // Try to find out if it is R1-R7
            findRegister(test, ptr);
            if (strcmp(test, "") == 0) {
                printf("Didn't find a register, try again\n");
                continue;
            }
            // Add the binary equivalent to output
            strcat(output, test);
            // Move pointer to next split, should be SR2 or imm5
            ptr = strtok(NULL, delim);
            // Try to find out if it is number or register next
            findRegister(test, ptr);
            if (strcmp(test, "") == 0) {
                // Not a register, must be imm5, add a 1 to output
                strcat(output, "1");
                // Do a conversion from string with decimal number to binary string
                char bin[5];
                decStringToBinary(bin, ptr);
                printf("Converting: %s to binary: %s\n", ptr, bin);
                strcat(output, bin);
            } else {
                // It was a register, add to output
                strcat(output, "000");
                strcat(output, test);
            }
        } else if (strcmp(ptr, "NOT") == 0) {
            printf("Found NOT\n");
            strcat(output, "1001");
            ptr = strtok(NULL, delim);
        } else if (strcmp(ptr, "BR") == 0) {
            printf("Found BR\n");
            strcat(output, "0000");
            ptr = strtok(NULL, delim);
        } else if (strcmp(ptr, "LD") == 0) {
            printf("Found BR\n");
            strcat(output, "0010");
            ptr = strtok(NULL, delim);
        } else if (strcmp(ptr, "LDR") == 0) {
            printf("Found BR\n");
            strcat(output, "0110");
            ptr = strtok(NULL, delim);
        } else if (strcmp(ptr, "ST") == 0) {
            printf("Found BR\n");
            strcat(output, "0011");
            ptr = strtok(NULL, delim);
        } else {
            printf("Didn't recognize instruction, try again\n");
            continue;
        }
        /**/

        /* This loop is used to debug the string-splitting
        while (ptr != NULL) {
            printf("'%s'\n", ptr);
            ptr = strtok(NULL, delim);
        }
        /**/

        // Print the original command and the binary equivalent
        printf("You entered: %s", original);
        printf("Binary equivalent: %s\n", output);
    }
    return 0;
}

void findRegister(char *rtn, char *ptr) {
    strcpy(rtn, "");
    if (strcmp(ptr, "R1") == 0) {
        printf("Found R1\n");
        strcat(rtn, "001");
    } else if (strcmp(ptr, "R2") == 0) {
        printf("Found R2\n");
        strcat(rtn, "010");
    } else if (strcmp(ptr, "R3") == 0) {
        printf("Found R3\n");
        strcat(rtn, "011");
    } else if (strcmp(ptr, "R4") == 0) {
        printf("Found R4\n");
        strcat(rtn, "100");
    } else if (strcmp(ptr, "R5") == 0) {
        printf("Found R5\n");
        strcat(rtn, "101");
    } else if (strcmp(ptr, "R6") == 0) {
        printf("Found R6\n");
        strcat(rtn, "110");
    } else if (strcmp(ptr, "R7") == 0) {
        printf("Found R7\n");
        strcat(rtn, "111");
    }
}

void decStringToBinary(char *rtn, char *ptr) {
    strcpy(rtn, "");
    int a[5] = {0}, n = 0, i, x;
    // Convert the string to an integer
    sscanf(&ptr[1], "%d", &n);
    // Math to create an integer array with 1's and 0's
    for (i = 4; n > 0; i--) {
        a[i] = n % 2;
        n = n/2;
    }
    // Converting the int-array to chars and appending to return-value
    for (i = 0; i < 5; i++) {
        if (a[i] == 1)
            strcat(rtn, "1");
        else
            strcat(rtn, "0");
    }
}

// Suppression for Clion warnings
#pragma clang diagnostic pop