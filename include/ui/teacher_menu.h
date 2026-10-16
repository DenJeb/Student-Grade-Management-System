// ===== 教师主菜单 =====
#pragma once
#include <string>
#include <vector>
#include "user.h"


void teacherMenu(const User& user); // 教师主菜单

// 成绩录入/修改界面（教师与管理员共用，classIds 为可操作的班级编号列表）
void scoreEntryMenu(const std::vector<std::string>& classIds); // 按班级+科目逐人录入成绩
void scoreEditMenu(const std::vector<std::string>& classIds);  // 按班级+科目修改成绩
