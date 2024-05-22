#include <stdio.h>
#include <stdlib.h>

int run(int year)
{

    // 判断该年是闰年还是平年
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 366;
    }
    else
    {
        return 365;
    }
}

int main()
{
    system("chcp 65001");
    // 菜单
    printf("\t\t\t万年历\t\t\t\n");
    printf("\t\t1.@查找所在年的日历@\n");
    printf("\t\t2.@查找某一天的位置@\n");
    printf("\t\t     3.@退出@\n");
    printf("请输入您想要执行的操作：");

    int year;
    int m;
    int day;
    int a = 1900;
    int t;
    int sum = 0;
    int b;
    int c;
    int d;
    int e;
    int r;
    int f;
    int g = 0;
    int h;
    int nian;

    // 每个月的天数
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (run(year) == 366)
    {
        month[1] = 29;
    }

    // 选择进行的操作
    scanf("%d", &t);

    // 1.@查找所在年的日历@
    if (t == 1)
    {
        printf("请输入您想要查日历的所在年份：");
        scanf("%d", &year);

        // 计算该年1月1日到1900年1月1日的距离
        for (a = 1900; a < year; a++)
        {
            sum += run(a);
        }

        // 求一月一号是星期几
        e = b = sum % 7;
        printf("%d", b);
        // 输出日历
        for (c = 0; c < 12; c++)
        {

            printf("                     %d月\n", c + 1);
            printf("    一    二    三    四    五    六    日\n");
            printf("    **************************************\n");

            for (d = 1; d <= month[c]; d++)
            {
                for (b; b > 0; b--)
                {
                    printf("      ");
                }
                // 补齐一位数与二位数相差一个空格，使输出变得美观
                if (d < 10)
                {
                    printf("     %d", d);
                }
                else
                {
                    printf("    %d", d);
                }
                // 输出满一周换行
                if ((e + d) % 7 == 0)
                {
                    printf("\n");
                }
            }
            e += month[c];
            b = e % 7;
            printf("\n\n");
        }
    }

    // 2.@查找某一天的位置@
    if (t == 2)
    {
        printf("请输入您想要查询的日期（年 月 日）：");
        scanf("%d %d %d", &nian, &m, &r);

        // 算出该天到1900年1月1日的距离
        for (f = 1900; f < nian; f++)
        {
            sum += run(f);
        }
        for (g = 0; g < m - 1; g++)
        {
            sum += month[g];
        }

        // 求1月1日是星期几
        h = sum % 7;

        // 输出日历
        printf("                     %d月\n", m);
        printf("    一    二    三    四    五    六    日\n");
        printf("    **************************************\n");
        for (h; h > 0; h--)
        {
            printf("      ");
        }
        for (h = 1; h <= month[m - 1]; h++)
        {

            // 输出时补齐一位数与两位数的空格，并用if语句在所求日期前标上星号�
            if (h < 10 && h != r)
            {
                printf("     %d", h);
            }
            else if (h >= 10 && h != r)
            {
                printf("    %d", h);
            }
            else if (h < 10 && h == r)
            {
                printf("    *%d", h);
            }
            else
            {
                printf("   *%d", h);
            }
            // 输出满一个星期时换行
            if ((h + month[m - 1]) % 7 == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
    }

    // 3.@退出@
    else
    {
        return 0;
    }

    // 防止闪退
    system("pause");

    return 0;
}