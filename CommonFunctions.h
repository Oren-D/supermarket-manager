#ifndef CommonFunctions_H
#define CommonFunctions_H
void capitalizeString(char* str);
int isLeapYear(int year);
int isValidDate(int day, int month, int year);
int isValidDateForOrder(int day, int month, int year);

void clearInputBuffer();
void iterateOverArray(void** array, int size, void (*action)(void*));
int strcasecmp(const char* s1, const char* s2);

#endif





