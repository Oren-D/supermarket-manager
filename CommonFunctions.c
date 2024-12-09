#include "exe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void capitalizeString(char* str) {
    int i = 0;
    int capitalize_next = 1;

    while (str[i]) {
        if (isspace(str[i]) || str[i] == '#') {
            capitalize_next = 1;
        }
        else if (capitalize_next) {
            str[i] = toupper(str[i]);
            capitalize_next = 0;
        }
        else {
            str[i] = tolower(str[i]);
        }
        i++;
    }
}
int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    else {
        return 0;
    }
}
int isValidDate(int day, int month, int year) {
    time_t t = time(NULL);
    struct tm currentTime = *localtime(&t);

    int currentYear = currentTime.tm_year + 1900;
    int currentMonth = currentTime.tm_mon + 1;
    int currentDay = currentTime.tm_mday;

    if (year > currentYear || (year == currentYear && month > currentMonth) ||
        (year == currentYear && month == currentMonth && day > currentDay)) {
        return 0;
    }


    if (month < 1 || month > 12) {
        return 0;
    }

    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (day < 1 || day > 31) {
            return 0;
        }
        break;
    case 4: case 6: case 9: case 11:
        if (day < 1 || day > 30) {
            return 0;
        }
        break;
    case 2:
        if (isLeapYear(year)) {
            if (day < 1 || day > 29) {
                return 0;
            }
        }
        else {
            if (day < 1 || day > 28) {
                return 0;
            }
        }
        break;
    default:
        return 0;
    }

    return 1;
}
int isValidDateForOrder(int day, int month, int year) {
    time_t t = time(NULL);
    struct tm currentTime = *localtime(&t);

    int currentYear = currentTime.tm_year + 1900;
    int currentMonth = currentTime.tm_mon + 1;
    int currentDay = currentTime.tm_mday;

    if (year < currentYear ||
        (year == currentYear && month < currentMonth) ||
        (year == currentYear && month == currentMonth && day < currentDay)) {
        return 0;
    }

    if (month < 1 || month > 12) {
        return 0;
    }

    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (day < 1 || day > 31) {
            return 0;
        }
        break;
    case 4: case 6: case 9: case 11:
        if (day < 1 || day > 30) {
            return 0;
        }
        break;
    case 2:
        if (isLeapYear(year)) {
            if (day < 1 || day > 29) {
                return 0;
            }
        }
        else {
            if (day < 1 || day > 28) {
                return 0;
            }
        }
        break;
    default:
        return 0;
    }

    return 1;
}
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void iterateOverArray(void** array, int size, void (*action)(void*)) {
    for (int i = 0; i < size; i++) {
        printf("%d. ", i+1);
        action(array[i]);
    }
    printf("\n");

}
int strcasecmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}