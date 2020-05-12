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
void decStringToBinary(char *rtn, char *ptr, int length, int offset);

int main() {
    // Init variables
    char in_file[32];
    char out_file[32];
    FILE *f_i, *f_o;
    char input[MAX];
    char output[MAX];
    char empty[] = "";
    char delim[] = " ,\n";
    char test[] = "";

    // Init infinite loop
    while (1) {
        // Get filename from user
        printf("Input filename (without .asm):");
        fgets(in_file, MAX, stdin);

        // Compose filenames for in put out files
        strcpy(out_file, in_file);
        strcat(in_file, ".asm");
        strcat(out_file, ".bin");

        // Open files in read and write mode
        f_i = fopen(in_file, "r");
        f_o = fopen(out_file, "w");

        // Loop through entire input-file
        while (fgets(input, MAX, f_i)) {
            // Clear output
            strcpy(output, empty);

            // Split input by space and comma and remove trailing \n
            char *ptr = strtok(input, delim);

            /* Try to find which of the known commands */
            if (strcmp(ptr, "ADD") == 0) {
                printf("Found ADD, converting to 0001\n");
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
                    decStringToBinary(bin, ptr, 5, 1);
                    printf("Converting: %s to binary: %s\n", ptr, bin);
                    strcat(output, bin);
                } else {
                    // It was a register, add to output
                    strcat(output, "000");
                    strcat(output, test);
                }
            }
            else if (strcmp(ptr, "NOT") == 0) {
                printf("Found NOT, converting to 1001\n");
                strcat(output, "1001");
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
                // Move pointer to next split, should be SR
                ptr = strtok(NULL, delim);
                // Try to find out if it is R1-R7
                findRegister(test, ptr);
                if (strcmp(test, "") == 0) {
                    printf("Didn't find a register, try again\n");
                    continue;
                }
                // Add the binary equivalent to output
                strcat(output, test);
                // Add 6 ones
                strcat(output, "111111");
            }
            else if (strstr(ptr, "BR") != NULL) {
                printf("Found BR, converting to 0000\n");
                strcat(output, "0000");
                // check for flags n, z and/or p and add a 1 or 0
                if (strchr(ptr, 'n') != NULL) {
                    strcat(output, "1");
                } else {
                    strcat(output, "0");
                }
                if (strchr(ptr, 'z') != NULL) {
                    strcat(output, "1");
                } else {
                    strcat(output, "0");
                }
                if (strchr(ptr, 'p') != NULL) {
                    strcat(output, "1");
                } else {
                    strcat(output, "0");
                }
                // Move pointer to next split, should be a label or an offset
                ptr = strtok(NULL, delim);
                if (strchr(ptr, '#') != NULL) {
                    // It's an offset, convert to binary
                    char bin[9];
                    decStringToBinary(bin, ptr, 9, 1);
                    printf("Converting: %s to binary: %s\n", ptr, bin);
                    strcat(output, bin);
                } else {
                    // It's a label
                    printf("Labels are not supported\n");
                    continue;
                }
            }
            else if (strcmp(ptr, "LD") == 0) {
                printf("Found LD, converting to 0010\n");
                strcat(output, "0010");
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
                // Move pointer to next word, should be an offset
                ptr = strtok(NULL, delim);
                if (strchr(ptr, '#') != NULL) {
                    // It's a value, convert to binary and add to output
                    char bin[9];
                    decStringToBinary(bin, ptr, 9, 1);
                    printf("Converting: %s to binary: %s\n", ptr, bin);
                    strcat(output, bin);
                } else {
                    // It's a label
                    printf("Labels are not supported\n");
                    continue;
                }
            }
            else if (strcmp(ptr, "LDR") == 0) {
                printf("Found LDR, converting to 0110\n");
                strcat(output, "0110");
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
                // Move pointer to next word, should be a register
                ptr = strtok(NULL, delim);
                findRegister(test, ptr);
                if (strcmp(test, "") == 0) {
                    printf("Didn't find a register, try again\n");
                    continue;
                }
                // Add the binary equivalent to output
                strcat(output, test);
                // Move pointer to next word, should be an offset
                ptr = strtok(NULL, delim);
                if (strchr(ptr, '#') != NULL) {
                    // It's a value, convert to binary and add to output
                    char bin[9];
                    decStringToBinary(bin, ptr, 9, 1);
                    printf("Converting: %s to binary: %s\n", ptr, bin);
                    strcat(output, bin);
                } else {
                    // It's a label
                    printf("Labels are not supported\n");
                    continue;
                }
            }
            else if (strcmp(ptr, "ST") == 0) {
                printf("Found ST, converting to 0011\n");
                strcat(output, "0011");
                // Move pointer to next split, should be SR
                ptr = strtok(NULL, delim);
                // Try to find out if it is R1-R7
                findRegister(test, ptr);
                if (strcmp(test, "") == 0) {
                    printf("Didn't find a register, try again\n");
                    continue;
                }
                // Add the binary equivalent to output
                strcat(output, test);
                // Move pointer to next word, should be an offset
                ptr = strtok(NULL, delim);
                if (strchr(ptr, '#') != NULL) {
                    // It's a value, convert to binary and add to output
                    char bin[9];
                    decStringToBinary(bin, ptr, 9, 1);
                    printf("Converting: %s to binary: %s\n", ptr, bin);
                    strcat(output, bin);
                } else {
                    // It's a label
                    printf("Labels are not supported\n");
                    continue;
                }
            }
            else {
                printf("Didn't recognize instruction, try again\n");
                continue;
            }
            /**/

            // Write binary to file
            fputc(output, f_o);
        }
        fclose(f_i);
        fclose(f_o);
    }
    return 0;
}

void findRegister(char *rtn, char *ptr) {
    strcpy(rtn, "");
    if (strcmp(ptr, "R0") == 0) {
        printf("Found R0, converting to 000\n");
        strcat(rtn, "000");
    } else if (strcmp(ptr, "R1") == 0) {
        printf("Found R1, converting to 001\n");
        strcat(rtn, "001");
    } else if (strcmp(ptr, "R2") == 0) {
        printf("Found R2, converting to 010\n");
        strcat(rtn, "010");
    } else if (strcmp(ptr, "R3") == 0) {
        printf("Found R3, converting to 011\n");
        strcat(rtn, "011");
    } else if (strcmp(ptr, "R4") == 0) {
        printf("Found R4, converting to 100\n");
        strcat(rtn, "100");
    } else if (strcmp(ptr, "R5") == 0) {
        printf("Found R5, converting to 101\n");
        strcat(rtn, "101");
    } else if (strcmp(ptr, "R6") == 0) {
        printf("Found R6, converting to 110\n");
        strcat(rtn, "110");
    } else if (strcmp(ptr, "R7") == 0) {
        printf("Found R7, converting to 111\n");
        strcat(rtn, "111");
    }
}

void decToBinary(char *rtn, int n, int length, int neg) {
    // a is set to length 11, because that's the longest binary number needed
    int a[11] = {0}, i;
    if (neg == 1)
        n--;
    // Math to create an integer array with 1's and 0's
    for (i = length-1; n > 0; i--) {
        a[i] = n % 2;
        n = n/2;
    }
    // Converting the int-array to chars and appending to return-value
    for (i = 0; i < length; i++) {
        if (i == 0 && neg == 0) // First bit has to be 0, because it's positive
            strcat(rtn, "0");
        else if (i == 0 && neg == 1) // First bit has to be 1, because it's negative
            strcat(rtn, "1");
        else if (a[i] == 1)
            strcat(rtn, "1");
        else
            strcat(rtn, "0");
    }
}

void decStringToBinary(char *rtn, char *ptr, int length, int offset) {
    strcpy(rtn, "");
    int n = 0;
    // Convert the string to an integer
    if (strchr(ptr, '-') != NULL) {
        // It's a negative number, read as positive
        sscanf(&ptr[offset+1], "%d", &n);
        decToBinary(rtn, n, length, 1);
    } else {
        // It's a positive number
        sscanf(&ptr[offset], "%d", &n);
        decToBinary(rtn, n, length, 0);
    }
}

// Suppression for Clion warnings
#pragma clang diagnostic pop