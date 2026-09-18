// ===== 超级管理员用户类 =====
#include "admin_user.h"


// 构造函数
AdminUser::AdminUser() : User("", "", Role::Admin, true, ""){}