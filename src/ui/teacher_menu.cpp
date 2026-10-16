// ===== 教师主菜单 =====
#include "teacher_menu.h"
#include "auth_service.h"
#include "console.h"
#include <iostream>


void teacherMenu(const User& user){
    while(true){
        clearScreen();
        printMenu("教师主菜单", {"修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 2);

        if(choice == 1){
            // 修改密码
            std::string oldPwd = inputString("请输入原密码: ");
            std::string newPwd = inputString("请输入新密码: ");
            if(changePassword(user.getAccount(), oldPwd, newPwd)){
                std::cout << "修改成功\n";
            }else{
                std::cout << "原密码错误，修改失败\n";
            }
            pause();
        }else{
            break; // 退出登录
        }
    }
}
