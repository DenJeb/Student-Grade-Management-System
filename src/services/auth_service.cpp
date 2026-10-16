// ===== 登录认证、修改密码、登录记录 =====
#include "auth_service.h"
#include "user_repo.h"
#include <ctime>


// 登录：账号密码正确且未被禁用才算成功，成功和失败都记一条登录记录
bool login(const std::string& account, const std::string& password, User& user){
    for(const User& u : loadUsers()){
        if(u.getAccount() == account){
            if(u.getPassword() == password && u.getActive()){
                user = u;
                appendLoginRecords(account, currentTime(), "成功");
                return true;
            }
            appendLoginRecords(account, currentTime(), "失败");
            return false;
        }
    }
    appendLoginRecords(account, currentTime(), "失败"); // 账号不存在也记一条
    return false;
}

// 修改密码：找到账号且原密码正确才改
bool changePassword(const std::string& account, const std::string& oldPassword, const std::string& newPassword){
    std::vector<User> users = loadUsers();
    for(User& u : users){
        if(u.getAccount() == account){
            if(u.getPassword() != oldPassword) return false;
            u.setPassword(newPassword);
            saveUsers(users);
            return true;
        }
    }
    return false;
}

// 查询某账号的登录记录
std::vector<std::string> getLoginRecords(const std::string& account){
    std::vector<std::string> records;
    for(const std::string& r : loadLoginRecords()){
        if(r.find(account + ",") == 0) records.push_back(r); // 按账号开头匹配
    }
    return records;
}

// 当前时间，格式 YYYY-MM-DD HH:MM
std::string currentTime(){
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", t);
    return std::string(buf);
}
