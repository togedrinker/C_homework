#include <stdio.h>

const char *months[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

void printOneMonth(int year, int month, FILE *file) {
    // Implementation of the function
    // You can keep the existing implementation here

    fprintf(file, "      %s %d\n", months[month], year);
    fprintf(file, " Su Mo Tu We Th Fr Sa\n");
    // Rest of the function remains the same as before
}

void printYear(int year, FILE *file) {
    // Implementation of the function
    // You can keep the existing implementation here

    int month;
    for (month = 1; month <= 12; month += 3) {
        printOneMonth(year, month, file);
        fprintf(file, "  ");
        printOneMonth(year, month + 1, file);
        fprintf(file, "  ");
        printOneMonth(year, month + 2, file);
        fprintf(file, "\n\n");
    }
}

int main() {
    int year;
    FILE *file; // Define file pointer

    // Open the file in write mode
    file = fopen("calendar.txt", "w");

    if (file == NULL) {
        printf("Error opening file! Exiting...");
        return 1;
    }

    printf("Enter year: ");
    scanf("%d", &year);

    // Write output to file
    printYear(year, file);

    // Close the file
    fclose(file);

    return 0;
}