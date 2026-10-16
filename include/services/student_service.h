// ===== 学生、班级、科目维护 =====
#pragma once
#include <string>
#include <vector>
#include "student_user.h"
#include "class_info.h"
#include "subject.h"


// ---- 学生 ----
std::vector<StudentUser> getAllStudents();                              // 全部学生列表
std::vector<StudentUser> searchStudents(const std::string& keyword);     // 模糊检索（学号/姓名包含关键字）
bool findStudent(const std::string& account, StudentUser& out);         // 按学号查找，找到写入 out
bool addStudent(const StudentUser& s);                                  // 新增学生（学号已存在则失败）
bool deleteStudent(const std::string& account);                         // 删除学生
bool updateStudent(const std::string& account, const StudentUser& s);   // 按学号更新学生信息

// ---- 教师边界 ----
std::vector<std::string> getTeacherClassIds(const std::string& teacherId);  // 教师所辖班级编号列表
bool teacherOwnsStudent(const std::string& teacherId, const std::string& account); // 教师是否管辖该学生
std::vector<StudentUser> teacherSearchStudents(const std::string& keyword, const std::string& teacherId); // 教师检索（仅所辖班级）

// ---- 班级 ----
std::vector<ClassInfo> getAllClasses();                                 // 全部班级
bool findClass(const std::string& id, ClassInfo& out);                  // 按编号查找
bool addClass(const ClassInfo& c);                                      // 新增（编号已存在则失败）
bool deleteClass(const std::string& id);                                // 删除
bool updateClass(const std::string& id, const ClassInfo& c);            // 按编号更新（含班主任关联）

// ---- 科目 ----
std::vector<Subject> getAllSubjects();                                  // 全部科目
bool findSubject(const std::string& id, Subject& out);                  // 按编号查找
bool addSubject(const Subject& s);                                      // 新增（编号已存在则失败）
bool deleteSubject(const std::string& id);                              // 删除
bool updateSubject(const std::string& id, const Subject& s);            // 按编号更新
