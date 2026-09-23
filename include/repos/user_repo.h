// ===== 账号与登录记录读写 =====
#pragma once
#include <string>
#include <vector>
#include "user.h"


std::vector<User> loadUsers(); // 读取 account.csv 文件
void saveUsers(const std::vector<User>& users); // 写入 account.csv 文件
std::vector<std::string> loadLoginRecords(); // 读取 login_records.csv 文件
void appendLoginRecords(const std::string& account, const std::string& time, const std::string& result); // 追加登录记录