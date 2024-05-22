#include <stdio.h>

// Check if the year is leap year
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Get the first day of the month
int firstDayOfMonth(int year, int month)
{
    static int day_tab[2][13] = {
        {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4},
        {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}};
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + day_tab[isLeapYear(year)][month] + 1) % 7;
}

// Print month title and week title
void printMonthTitle(int year, int month)
{
    static char *months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    printf("      %s %d\n", months[month], year);
    printf(" Su Mo Tu We Th Fr Sa\n");
}

// Print one month
void printOneMonth(int year, int month)
{
    static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int weekDay, day;

    if (month == 2 && isLeapYear(year))
        days[month] = 29;

    printMonthTitle(year, month);

    weekDay = firstDayOfMonth(year, month);

    // Print spaces for days before month starts
    for (day = 0; day < weekDay; day++)
    {
        printf("   ");
    }

    // Print the days of the month
    for (day = 1; day <= days[month]; day++)
    {
        printf("%3d", day);
        if (++weekDay > 6)
        {
            weekDay = 0; // Next row
            printf("\n");
        }
    }
    if (weekDay)
        printf("\n");
    printf("\n");
}

// Print all months
// Print all months in rows of three
void printYear(int year)
{
    int month;
    for (month = 1; month <= 12; month += 3)
    {
        printOneMonth(year, month);
        printf("  ");
        printOneMonth(year, month + 1);
        printf("  ");
        printOneMonth(year, month + 2);
        printf("\n\n");
    }
}
// Main function
int main()
{
    int year;

    printf("Enter year: ");
    scanf("%d", &year);

    printYear(year);

    return 0;
}
