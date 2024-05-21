#include <stdio.h>

// 蔡勒公式计算星期几
int ZellerCongruence(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    return h;
}

// 打印年历
void print_year_calendar(int year) {
    FILE *fp = fopen("cal.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "Year Calendar: %d\n", year);

    for (int month = 1; month <= 12; month++) {
        fprintf(fp, "---------------------\n");
        fprintf(fp, "|      Month %2d     |\n", month);
        fprintf(fp, "---------------------\n");
        fprintf(fp, "Sun Mon Tue Wed Thu Fri Sat\n");

        int startDay = ZellerCongruence(year, month, 1);
        int daysInMonth = (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) ? 29 : 28;
        int day = 1;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (i == 0 && j < startDay) {
                    fprintf(fp, "    ");
                } else if (day <= daysInMonth) {
                    fprintf(fp, "%4d", day);
                    day++;
                } else {
                    fprintf(fp, "    ");
                }
            }
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
}

int main() {
    int year;

    // 输入年份
    printf("请输入年份：");
    scanf("%d", &year);

    print_year_calendar(year); // 打印年历到文件cal.txt

    return 0;
}