// ===== 用户基类：账号、密码、角色、状态 =====
#pragma once
#include <string>


// 角色枚举
enum class Role{
    Student, // 学生
    Teacher, // 教师
    Admin    // 管理员
};

// 角色与 CSV 文本互转（"student"/"teacher"/"admin"）
std::string roleToString(Role role);
Role stringToRole(const std::string& text);

// 用户基类
class User{
public:
    User();
    User(std::string account, std::string password, Role role, bool active, std::string create_time);

    // 获取器
    std::string getAccount() const;
    std::string getPassword() const;
    Role getRole() const;
    bool getActive() const;
    std::string getCreateTime() const;

    // 设置器
    void setAccount(std::string account);
    void setPassword(std::string password);

private:
    std::string account;     // 账号
    std::string password;    // 密码
    Role role;               // 角色
    bool active;             // 状态
    std::string create_time; // 创建时间
};