#include <stdio.h>
#include <time.h>

int main() {
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
    printf("");
    scanf("%d %d %d", &future_year, &future_month, &future_day);
    days = (future_year - year) * 365 + (future_month - month) * 30 + (future_day - day);
    printf(" %d \n", days);
    struct tm future_tm = {0};
    future_tm.tm_year = future_year - 1900;
    future_tm.tm_mon = future_month - 1;
    future_tm.tm_mday = future_day;
    mktime(&future_tm);
    printf(" %d\n", future_tm.tm_wday);
    return 0;
}