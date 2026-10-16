// ===== 学生主菜单 =====
#include "student_menu.h"
#include "auth_service.h"
#include "console.h"
#include <iostream>
#include <vector>


void studentMenu(const User& user){
    while(true){
        clearScreen();
        printMenu("学生主菜单", {"查看登录记录", "修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 3);

        if(choice == 1){
            // 查看登录记录
            std::vector<std::string> records = getLoginRecords(user.getAccount());
            if(records.empty()){
                std::cout << "暂无登录记录\n";
            }else{
                for(const std::string& r : records){
                    std::cout << r << "\n";
                }
            }
            pause();
        }else if(choice == 2){
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
