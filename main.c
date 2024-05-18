/*
代码功能：

小组成员：

合作方式：

GitHub 地址：

*/

#define _CRT_SECURE_NO_WARNINGS 1 // 避免vs中scanf报错
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
功能：判断当年是否是闰年。
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
	for (int m = 1; m <= *month; m++)
	{
		switch (m)
		{
		case 4:
		case 6:
		case 9:
		case 11:
			*day1 = 30;
			break;
		case 2:
			if ((*year % 4 == 0 && *year % 100 == 0) || (*year % 400 == 0))
			{
				*day1 = 29;
			}
			else
			{
				*day1 = 28;
			}
			break;
		default:
			*day1 = 31;
			break;
		}
		if (m < *month)
		{
			*day += *day1; // 将输入年中的每月统计到总天数中
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


// ____________
// |          |
// |          |
// ------------
// |     |     |

