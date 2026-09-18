// ===== 教师用户类：工号、所辖班级 =====
#include "teacher_user.h"


// 构造函数
TeacherUser::TeacherUser() : User("", "", Role::Teacher, true, ""){}

// 获取器
std::string TeacherUser::getTeacherName() const{ return name; }
std::string TeacherUser::getTeacherContact() const{ return contact; }

// 设置器
void TeacherUser::setTeacherName(std::string name){ this->name = name; }
void TeacherUser::setTeacherContact(std::string contact){ this->contact = contact; }