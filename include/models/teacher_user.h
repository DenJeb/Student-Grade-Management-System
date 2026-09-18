// ===== 教师用户类：工号、所辖班级 =====
#pragma once
#include "user.h"


class TeacherUser : public User{
public:
    TeacherUser();

    // 获取器
    std::string getTeacherName() const;
    std::string getTeacherContact() const;

    // 设置器
    void setTeacherName(std::string name);
    void setTeacherContact(std::string contact);

private:
    std::string name;    // 姓名
    std::string contact; // 联系方式
};