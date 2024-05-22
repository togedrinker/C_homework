#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// 判断是否为闰年
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 蔡勒公式计算星期几（0=星期日，1=星期一，...，6=星期六）
int zellerFormula(int day, int month, int year)
{
    if (month < 3)
    {
        month += 12;
        year--;
    }
    int century = year / 100;
    int a = year % 100;
    int h = (day + (13 * (month + 1)) / 5 + a + a / 4 + century / 4 - 2 * century) % 7;
    if (h < 0) // 确保结果为非负数
        h = h + 7;
    return h;
}

void printCalendar(int year, FILE *file) {
    const wchar_t *weekdays[] = {"日", "一", "二", "三", "四", "五", "六"};
    const wchar_t *months[] = {"一月", "二月", "三月", "四月", "五月", "六月",
                            "七月", "八月", "九月", "十月", "十一月", "十二月"};
    int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    for (int m = 0; m < 12; m += 3) {
        // 打印月份标题
        for (int i = 0; i < 3; i++) {
            fprintf(file, "%25s", months[m + i]);
            if (i < 2) {
                fprintf(file, "\t\t"); // 调整月份间的分隔空间
            }
        }
        fprintf(file, "\n");

        // 打印星期标题
        for (int week = 0; week < 3; week++) {
            fprintf(file, " ");
            for (int w = 0; w < 7; w++) {
                fprintf(file, "%4s ", weekdays[w]);
            }
            if (week < 2) fprintf(file, "\t\t"); // 调整月份间的分隔空间
        }
        fprintf(file, "\n");

        // 确定每个月  的第一天是星期几
        int firstDayWeeks[3];
        for (int i = 0; i < 3 && m + i < 12; i++)
        {
            firstDayWeeks[i] = zellerFormula(1, m + i + 1, year);
        }

        // 打印日历体
        int day[3] = {1, 1, 1};
        bool monthFinished[3] = {false, false, false};

        while (!monthFinished[0] || !monthFinished[1] || !monthFinished[2])
        {
            for (int i = 0; i < 3 && m + i < 12; i++)
            {
                if (!monthFinished[i])
                {
                    for (int weekday = 0; weekday < 7; weekday++)
                    {
                        if (weekday == firstDayWeeks[i])
                        {
                            
                            fprintf(file, "%4d", day[i]);
                            day[i]++;
                            firstDayWeeks[i] = -1; // 已打印了第一天的日期，重置为-1以避免再次检测
                        }
                        else if (firstDayWeeks[i] == -1 && day[i] <= daysInMonth[m + i])
                        {
                            fprintf(file, "%4d", day[i]);
                            day[i]++;
                            if (day[i] > daysInMonth[m + i])
                            {
                                monthFinished[i] = true;
                            }
                        }
                        else
                        {
                            fprintf(file, "\t\t"); // 打印空格以对齐 -----
                        }
                    }
                }
                else
                {
                    for (int weekday = 0; weekday < 7; weekday++)
                    {
                        fprintf(file, "\t\t"); // 月份已结束，打印空格以对齐 -----
                    }
                }

                if (i < 2)
                {
                    fprintf(file, "\t"); // 分隔月份
                }
            }
            fprintf(file, "\n");
        }

        // 打印分隔线
        if (m < 9)
        {
            for (int i = 0; i < 3 && m + i < 12; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    fprintf(file, "=");
                }
                if (i < 2)
                {
                    fprintf(file, "\t"); // 分隔月份
                }
            }
            fprintf(file, "\n");
        }
    }
    }

int twice(void)
{
    // system("chcp 65001");
    int year;
    printf("请输入年份：");
    scanf("%d", &year);

    FILE *file = fopen("cal.txt", "w");
    if (file == NULL)
    {
        perror("无法打开文件");
        return 1;
    }

    printCalendar(year, file);
    fclose(file);
    printf("日历已保存到 cal.txt 文件中。\n");
    return 0;
}

// // 打印日历到文件
// void printCalendar(int year, FILE *file)
// {
//     const char *weekdays[] = {"日", "一", "二", "三", "四", "五", "六"};
//     const char *months[] = {"一月", "二月", "三月", "四月", "五月", "六月",
//                             "七月", "八月", "九月", "十月", "十一月", "十二月"};
//     int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30,
//                          31, 31, 30, 31, 30, 31};

//     fprintf(file, "    日 一 二 三 四 五 六\n");

//     for (int m = 0; m < 12; m += 3)
//     {
//         // 打印月份标题
//         for (int i = 0; i < 3; i++)
//         {
//             fprintf(file, "%8s", months[m + i]);
//             if (i < 2)
//             {
//                 fprintf(file, "\t"); // 分隔月份
//             }
//         }
//         fprintf(file, "\n");

//         // 确定每个月  的第一天是星期几
//         int firstDayWeeks[3];
//         for (int i = 0; i < 3 && m + i < 12; i++)
//         {
//             firstDayWeeks[i] = zellerFormula(1, m + i + 1, year);
//         }

//         // 打印日历体
//         int day[3] = {1, 1, 1};
//         bool monthFinished[3] = {false, false, false};

//         while (!monthFinished[0] || !monthFinished[1] || !monthFinished[2])
//         {
//             for (int i = 0; i < 3 && m + i < 12; i++)
//             {
//                 if (!monthFinished[i])
//                 {
//                     for (int weekday = 0; weekday < 7; weekday++)
//                     {
//                         if (weekday == firstDayWeeks[i])
//                         {
//                             fprintf(file, "%2d", day[i]);
//                             day[i]++;
//                             firstDayWeeks[i] = -1; // 已打印了第一天的日期，重置为-1以避免再次检测
//                         }
//                         else if (firstDayWeeks[i] == -1 && day[i] <= daysInMonth[m + i])
//                         {
//                             fprintf(file, "%2d", day[i]);
//                             day[i]++;
//                             if (day[i] > daysInMonth[m + i])
//                             {
//                                 monthFinished[i] = true;
//                             }
//                         }
//                         else
//                         {
//                             fprintf(file, "  "); // 打印空格以对齐
//                         }
//                     }
//                 }
//                 else
//                 {
//                     for (int weekday = 0; weekday < 7; weekday++)
//                     {
//                         fprintf(file, "  "); // 月份已结束，打印空格以对齐
//                     }
//                 }

//                 if (i < 2)
//                 {
//                     fprintf(file, "\t"); // 分隔月份
//                 }
//             }
//             fprintf(file, "\n");
//         }

//         // 打印分隔线
//         if (m < 9)
//         {
//             for (int i = 0; i < 3 && m + i < 12; i++)
//             {
//                 for (int j = 0; j < 8; j++)
//                 {
//                     fprintf(file, "=");
//                 }
//                 if (i < 2)
//                 {
//                     fprintf(file, "\t"); // 分隔月份
//                 }
//             }
//             fprintf(file, "\n");
//         }
//     }
// }

