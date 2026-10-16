// ===== 程序入口：启动、加载、分发 =====
#include "login_view.h"
#include "student_menu.h"
#include "teacher_menu.h"
#include "admin_menu.h"
#include "user.h"


int main(){
    User user = loginView(); // 登录

    // 按角色分发菜单
    if(user.getRole() == Role::Student)      studentMenu(user);
    else if(user.getRole() == Role::Teacher) teacherMenu(user);
    else                                     adminMenu(user);
    return 0;
}
