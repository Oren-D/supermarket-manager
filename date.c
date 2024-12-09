#include <stdio.h>
#include "date.h"

Date createDate(int day, int month, int year) {
    Date date;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

void printDate(Date date) {
    printf("%02d/%02d/%d\n", date.day, date.month, date.year);
}
