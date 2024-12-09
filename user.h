#ifndef USER_H
#define USER_H

typedef struct {
    char username[50];
    char password[50];
} User;

User* createUser(const char* username, const char* password);
void printUser(User* user);

#endif // USER_H
