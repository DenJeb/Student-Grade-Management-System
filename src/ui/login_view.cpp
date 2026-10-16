// ===== 登录界面 =====
#include "login_view.h"
#include "auth_service.h"
#include "console.h"
#include <iostream>


// 登录界面：循环读账号密码，成功返回登录用户，失败提示后重试
User loginView(){
    while(true){
        clearScreen();
        std::cout << "========== 学生成绩管理系统登录 ==========\n";
        std::string account = inputString("账号: ");
        std::string password = inputString("密码: ");
        User user;
        if(login(account, password, user)){
            std::cout << "登录成功，欢迎 " << user.getAccount() << "\n";
            pause();
            return user;
        }
        std::cout << "账号或密码错误，或账号已被禁用\n";
        pause();
    }
}
