// ===== 学生数据读写 =====
#pragma once
#include <vector>
#include "student_user.h"


std::vector<StudentUser> loadStudents(); // 读取 students.csv 文件
void saveStudents(const std::vector<StudentUser>& students); // 写入 students.csv 文件