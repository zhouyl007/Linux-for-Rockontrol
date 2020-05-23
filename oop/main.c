#include <string.h>
#include <stdio.h>
#include "user.h"

static char *password_deal(char *pwd) {
	if (NULL == pwd) {
		return NULL;
	}

	if (0 == strncmp("654321", pwd, PASSWORD_LEN)) {
		return "123456";
	}

	return pwd;
}

static USER_OPERATIONS g_user_ops = {
	.pwd_deal = password_deal
};

int main(void) {
	user_ops_register(&g_user_ops);

	PUSER puser = init_user("yjp", "123456");
	if (NULL == puser) {
		printf("init user error!\n");
		return 1;
	}

	printf("init username: %s\n", get_username(puser));
	printf("change username\n");
	set_username(puser, "yjp1");
	printf("now username: %s\n", get_username(puser));

	printf("check password: %d\n", check_password(puser, "123456"));
	printf("change password\n");
	set_password(puser, "654321");
	printf("now check password: %d\n", check_password(puser, "123456"));

	destory_user(puser);

	return 0;
}



