#ifndef USER_H
#define USER_H

#define USERNAME_LEN 255
#define PASSWORD_LEN 255

typedef char* (*PWD_DEAL_FUNC)(char *pwd);
typedef struct {
	PWD_DEAL_FUNC pwd_deal;
} USER_OPERATIONS, *PUSER_OPERATIONS;

void user_ops_register(PUSER_OPERATIONS ops);

typedef struct {
	char username[USERNAME_LEN];
	char password[PASSWORD_LEN];
} USER, *PUSER;

PUSER init_user(char *username, char *password);

char *get_username(PUSER puser);
void set_username(PUSER puser, char *username);

int check_password(PUSER puser, char *check_pwd);
void set_password(PUSER puser, char *pwd);

void destory_user(PUSER puser);

#endif


