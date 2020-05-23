#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

static int is_user_valid(PUSER puser);

static PUSER_OPERATIONS g_user_ops = NULL;
void user_ops_register(PUSER_OPERATIONS ops) {
	if (NULL == ops) {
		return;
	}

	g_user_ops = ops;
}

PUSER init_user(char *username, char *password) {
	if (NULL == username || NULL == password) {
		printf("init_user error: username or password is NULL\n");
		return NULL;
	}

	PUSER puser = (PUSER)malloc(sizeof(USER));
	memset(puser, 0, sizeof(USER));
	strncpy(puser->username, username, USERNAME_LEN - 1);
	strncpy(puser->password, password, PASSWORD_LEN - 1);	

	return puser;
}

char *get_username(PUSER puser) {
	if (!is_user_valid(puser)) {
                return "";
        }

	return puser->username;
}

void set_username(PUSER puser, char *username) {
	if (!is_user_valid(puser) || NULL == username) {
                return;
        }

	memset(puser->username, 0, USERNAME_LEN);
	strncpy(puser->username, username, USERNAME_LEN - 1);
}

int check_password(PUSER puser, char *check_pwd) {
	if (!is_user_valid(puser) || NULL == check_pwd) {
                return 0;
        }
	
	char *dealed_pwd = check_pwd;
	if (NULL != g_user_ops) {
		dealed_pwd = g_user_ops->pwd_deal(dealed_pwd);
		if (NULL == dealed_pwd) {
			return 0;
		}
	}

	printf("check password is %s\n", dealed_pwd);
	return 0 == strncmp(puser->password, 
			dealed_pwd, 
			PASSWORD_LEN);	
}

void set_password(PUSER puser, char *pwd) {
	if (!is_user_valid(puser) || NULL == pwd) {
                return;
        }

	char *dealed_pwd = pwd;
        if (NULL != g_user_ops) {
                dealed_pwd = g_user_ops->pwd_deal(pwd);
                if (NULL == dealed_pwd) {
                        return;
                }
        }
       
	memset(puser->password, 0, PASSWORD_LEN);
        strncpy(puser->password, 
		dealed_pwd, 
		PASSWORD_LEN - 1);
	printf("password set to %s\n", puser->password);
}

void destory_user(PUSER puser) {
	if (!is_user_valid(puser)) {
		return;
	}

	free(puser);
	puser = NULL;
}

static int is_user_valid(PUSER puser) {
	if (NULL == puser) {
                return 0;
        } else {
		return 1;
	}
}



