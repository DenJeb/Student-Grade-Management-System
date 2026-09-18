// ===== 学生用户类：学号、个人资料 =====
#include "student_user.h"


// 默认构造函数：创建一个学生用户
StudentUser::StudentUser() : User("", "", Role::Student, true, ""){}

// 获取器
std::string StudentUser::getStudentName() const{ return name; }
std::string StudentUser::getStudentGender() const{ return gender; }
std::string StudentUser::getStudentGrade() const{ return grade; }
std::string StudentUser::getStudentClass() const{ return class_name; }
std::string StudentUser::getStudentContact() const{ return contact; }

// 设置器
void StudentUser::setStudentName(std::string name){ this->name = name; }
void StudentUser::setStudentGender(std::string gender){ this->gender = gender; }
void StudentUser::setStudentGrade(std::string grade){ this->grade = grade; }
void StudentUser::setStudentClass(std::string class_name){ this->class_name = class_name; }
void StudentUser::setStudentContact(std::string contact){ this->contact = contact; }