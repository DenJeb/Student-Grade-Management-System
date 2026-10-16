// ===== 管理员主菜单 =====
#include "admin_menu.h"
#include "account_service.h"
#include "auth_service.h"
#include "console.h"
#include <iostream>
#include <vector>


void adminMenu(const User& user){
    while(true){
        clearScreen();
        printMenu("管理员主菜单", {"账号列表", "新增账号", "批量新增账号", "删除账号", "禁用/启用账号", "重置密码", "修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 8);

        if(choice == 1){
            // 账号列表（按角色筛选）
            printMenu("选择角色", {"学生", "教师", "管理员"});
            int roleChoice = inputChoice("请选择: ", 1, 3);
            Role role = (roleChoice == 1) ? Role::Student : (roleChoice == 2) ? Role::Teacher : Role::Admin;
            for(const User& u : getUsersByRole(role)){
                std::cout << u.getAccount() << " | " << roleToString(u.getRole())
                          << " | " << (u.getActive() ? "正常" : "禁用") << "\n";
            }
            pause();
        }else if(choice == 2){
            // 新增账号（学生或教师）
            printMenu("选择角色", {"学生", "教师"});
            int roleChoice = inputChoice("请选择: ", 1, 2);
            Role role = (roleChoice == 1) ? Role::Student : Role::Teacher;
            std::string account = inputString("请输入账号: ");
            std::string password = inputString("请输入初始密码: ");
            if(addAccount(account, password, role)){
                std::cout << "新增成功\n";
            }else{
                std::cout << "账号已存在，新增失败\n";
            }
            pause();
        }else if(choice == 3){
            // 批量新增账号（统一初始密码，空行结束）
            printMenu("选择角色", {"学生", "教师"});
            int roleChoice = inputChoice("请选择: ", 1, 2);
            Role role = (roleChoice == 1) ? Role::Student : Role::Teacher;
            std::string password = inputString("请输入统一初始密码: ");
            while(true){
                std::string account = inputString("请输入账号（空行结束）: ");
                if(account.empty()) break;
                if(addAccount(account, password, role)){
                    std::cout << account << " 新增成功\n";
                }else{
                    std::cout << account << " 已存在，跳过\n";
                }
            }
            pause();
        }else if(choice == 4){
            // 删除账号
            std::string account = inputString("请输入要删除的账号: ");
            if(deleteAccount(account)){
                std::cout << "删除成功\n";
            }else{
                std::cout << "账号不存在，删除失败\n";
            }
            pause();
        }else if(choice == 5){
            // 禁用/启用账号
            std::string account = inputString("请输入账号: ");
            printMenu("选择操作", {"禁用", "启用"});
            int op = inputChoice("请选择: ", 1, 2);
            bool active = (op == 2);
            if(setAccountActive(account, active)){
                std::cout << "操作成功\n";
            }else{
                std::cout << "账号不存在\n";
            }
            pause();
        }else if(choice == 6){
            // 重置密码
            std::string account = inputString("请输入账号: ");
            std::string newPwd = inputString("请输入新密码: ");
            if(resetPassword(account, newPwd)){
                std::cout << "重置成功\n";
            }else{
                std::cout << "账号不存在\n";
            }
            pause();
        }else if(choice == 7){
            // 修改自己的密码
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
