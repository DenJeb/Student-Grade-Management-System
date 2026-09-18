// ===== 用户基类：账号、密码、角色、状态 =====
#include "user.h"


// 默认构造函数：创建一个学生用户
User::User()
    : role(Role::Student)
    , active(true)
{}

// 构造函数：创建一个用户
User::User(std::string account, std::string password, Role role, bool active, std::string create_time)
    : account(account)
    , password(password)
    , role(role)
    , active(active)
    , create_time(create_time)
{}

// 获取器
std::string User::getAccount() const{ return account; }
std::string User::getPassword() const{ return password; }
Role User::getRole() const{ return role; }
bool User::getActive() const{ return active; }
std::string User::getCreateTime() const{ return create_time; }

// 设置器
void User::setAccount(std::string account){ this->account = account; }
void User::setPassword(std::string password){ this->password = password; }

// 角色与 CSV 文本互转（"student"/"teacher"/"admin"）
std::string roleToString(Role role){
    switch(role){
        case Role::Student: return "student";
        case Role::Teacher: return "teacher";
        case Role::Admin:   return "admin";
    }
    return "student"; // 默认返回学生角色
}

Role stringToRole(const std::string& text){
    if(text == "student") return Role::Student;
    if(text == "teacher") return Role::Teacher;
    if(text == "admin")   return Role::Admin;
    return Role::Student; // 默认返回学生角色
}