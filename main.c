/*
代码功能：
（1）计算未来天数和星期:输入未来某天的日期，输出距今天还有多少天，是星期几。
（2）打印年历:输入一个年份，将该年的日历按下面图示格式输出到文件 cal.txt 中。
要求每行同时打印3个月。每月1号是星期几可以利用蔡勒公式计算，百度下该公式。
（3）打印月历:输入年月，输出该月的日历，可以参考年历中月份的格式。

小组成员：
李思俊（负责主函数和（3）打印月历）
武艺仰（负责（2）打印年历）
曹启航（负责（1）计算未来天数和星期）

合作方式：使用vs code编码，使用gcc编译运行，使用github进行云端交流与合作
>>>>>>> Stashed changes

GitHub 地址：https://github.com/togedrinker/C_homework

*/

#define _CRT_SECURE_NO_WARNINGS 1 // 避免vs中 scanf 报错
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// 声明函数
	void is_loopYear(int *, int *);
	void print_month(int *, int *, int *, int *);
	
	// 将终端设置为 UTF-8 来显示中文
	system("chcp 65001");

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

	return 0;
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
