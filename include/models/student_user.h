// ===== 学生用户类：学号、个人资料 =====
#pragma once
#include "user.h"


class StudentUser : public User{
public:
    StudentUser();

    // 获取器
    std::string getStudentName() const;
    std::string getStudentGender() const;
    std::string getStudentGrade() const;
    std::string getStudentClass() const;
    std::string getStudentContact() const;

    // 设置器
    void setStudentName(std::string name);
    void setStudentGender(std::string gender);
    void setStudentGrade(std::string grade);
    void setStudentClass(std::string class_name);
    void setStudentContact(std::string contact);

private:
    std::string name;      // 姓名
    std::string gender;    // 性别
    std::string grade;     // 年级
    std::string class_name; // 班级
    std::string contact;   // 联系方式
};