/*
代码功能：
（1）计算未来天数和星期:输入未来某天的日期，输出距今天还有多少天，是星期几。
（2）打印年历：输入一个年份，将该年的日历按下面图示格式输出到文件 cal.txt 中。
要求每行同时打印 3 个月。每月 1 号是星期几可以利用蔡勒公式计算，百度下该公式。
（3）打印月历：输入年月，输出该月的日历，可以参考年历中月份的格式。

小组成员：
李思俊（负责主函数和（3）打印月历）
武艺仰（负责（2）打印年历）
曹启航（负责（1）计算未来天数和星期）

合作方式：使用 vs code 编码，使用 gcc 编译运行，使用 GitHub进行云端交流与合作

GitHub 地址：https://github.com/togedrinker/C_homework

*/

#define _CRT_SECURE_NO_WARNINGS 1 // 避免vs中 scanf 报错
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	// 声明函数
	void is_loopYear(int *, int *);
	bool isLeapYear(int);
	void print_month(int *, int *, int *, int *);
	int ZellerCongruence(int, int, int);
	void print_year_calendar(int);
	void calculateDateDifference(void);
	void printCalendar(int, FILE *);
	int twice(void);

	// 将终端设置为 UTF-8 来显示中文
	system("chcp 65001");

	while (1)
	{
		int choice;

		printf("\n\t\t\t万年历\t\t\t\n\n");

		printf("\t\t1. 查找某一天的位置\n");
		printf("\t\t2. 查找所在年的日历\n");
		printf("\t\t3. 打印月历\n");
		printf("\t\t4. 结束\n");
		printf("请输入您想要执行的操作：");
		scanf("%d", &choice);

		if (choice == 2)
		{
			twice();
		}
		else if (choice == 1)
		{
			calculateDateDifference(); // 计算未来天数和星期
		}
		else if (choice == 3)
		{
			int year = 0;
			int month = 0;
			// 输入要查询的年份和月份
			printf("请输入年份:");
			scanf("%d", &year);
			printf("请输入月份:");
			scanf("%d", &month);

			// 判断闰年
			int day = 0;
			is_loopYear(&year, &day);

			// 判断月数
			int day1 = 0;
			print_month(&year, &month, &day1, &day);
		}
		else if (choice == 4)
		{
			printf("欢迎使用！下次再见！\n");
			return 0;
		}
		else{
			printf("输入有误，请重新输入。");
		}
		printf("请按回车继续！\n");
		system("pause");
		system("cls");
	}
	return 0;
}

void calculateDateDifference()
{
	time_t t;
	struct tm *now;
	int year, month, day;
	int future_year, future_month, future_day;
	int days;

	time(&t);
	now = localtime(&t);
	year = now->tm_year + 1900;
	month = now->tm_mon + 1;
	day = now->tm_mday;

	printf("现在的时间是: %d 年 %02d 月 %02d 日\n", year, month, day);

	printf("请输入未来时间 (某年 某月 某日): ");
	scanf("%d %d %d", &future_year, &future_month, &future_day);

	days = (future_year - year) * 365 + (future_month - month) * 30 + (future_day - day);

	printf("距离今天的时间差: %d\n", days);

	struct tm future_tm = {0};
	future_tm.tm_year = future_year - 1900;
	future_tm.tm_mon = future_month - 1;
	future_tm.tm_mday = future_day;
	mktime(&future_tm);
	if (future_tm.tm_wday == 0)
	{
		future_tm.tm_wday = 7;
	}

	printf("是星期: %d\n", future_tm.tm_wday);
}

// 蔡勒公式计算星期几
int ZellerCongruence(int year, int month, int day)
{
	if (month < 3)
	{
		month += 12;
		year--;
	}
	int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	return h;
}

/*
功能：判断当年是否是闰年
year：输入年份
day：一年总天数
*/
void is_loopYear(int *year, int *day)
{
	for (int i = 1900; i < *year; i++) // 将输入年之前的年份天数求和
	{
		// 判断是否为闰年
		if ((i % 4 == 0 && i % 100 == 0) || (i % 400 == 0))
		{
			*day += 366;
		}
		else
		{
			*day += 365;
		}
	}
}

/*
功能：判断并输出某年某月的月历。
year：输入年份。
month：输入月份。
day1：当月天数
day：一年总天数
*/
void print_month(int *year, int *month, int *day1, int *day)
{
	printf("一\t二\t三\t四\t五\t六\t日\n");

	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 每月天数，索引从1开始

	// 判断是否为闰年，更新二月的天数
	if (((*year % 4 == 0 && *year % 100 != 0) || *year % 400 == 0))
	{
		daysInMonth[2] = 29; // 闰年二月有29天
	}

	for (int m = 1; m <= *month; m++)
	{
		*day1 = daysInMonth[m]; // 获取当前月的天数

		if (m < *month)
		{
			*day += *day1; // 将当前月天数累加到总天数中
		}
	}
	int t = *day % 7;

	for (int i = 0; i < t; i++)
	{
		printf("\t");
	}

	for (int i = 1; i <= *day1; i++)
	{
		printf("%d\t", i);
		if ((i + *day) % 7 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int zellerFormula(int day, int month, int year)
{
	if (month < 3)
	{
		month += 12;
		year--;
	}
	int century = year / 100;
	int a = year % 100;
	int h = (day + 2 * month + 3 * (month + 1) / 5 + a + a / 4 + century / 4 - 2 * century + 1) % 7;
	if (h < 0)
		h = h + 7;
	return h;
}

void printCalendar(int year, FILE *file)
{
	fprintf(file, "%48d\n", year);
	const char *weekdays[] = {"日", "一", "二", "三", "四", "五", "六"};
	const char *months[] = {"一月", "二月", "三月", "四月", "五月", "六月",
							"七月", "八月", "九月", "十月", "十一月", "十二月"};
	int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30,
						 31, 31, 30, 31, 30, 31};

	for (int m = 0; m < 12; m += 3)
	{

		for (int i = 0; i < 3; i++)
		{
			fprintf(file, "%20s", months[m + i]);
			if (i < 2)
			{
				fprintf(file, "\t\t");
			}
		}
		fprintf(file, "\n");
		for (int i = 0; i < 3; i++)
		{
			fprintf(file, "Sun Mon Tue Wed Tur Fri Sat");
			if (i < 2)
			{
				fprintf(file, "\t");
			}
		}
		fprintf(file, "\n");
		int firstDayWeeks[3];
		for (int i = 0; i < 3 && m + i < 12; i++)
		{
			firstDayWeeks[i] = zellerFormula(1, m + i + 1, year);
		}
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
							firstDayWeeks[i] = -1;
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
							fprintf(file, "    ");
						}
					}
				}
				else
				{
					for (int weekday = 0; weekday < 7; weekday++)
					{
						fprintf(file, "    ");
					}
				}

				if (i < 2)
				{
					fprintf(file, "\t");
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
	printf("完成打印，文件名为\"cal.txt\"，请复制文件绝对路径，输入到浏览器导航栏查看网页。\n");
	printf("注意：文件不支持记事本打开，请使用浏览器进行查看！");
	return 0;
}