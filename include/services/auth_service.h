// ===== 登录认证、修改密码、登录记录 =====
#pragma once
#include <string>
#include <vector>
#include "user.h"


bool login(const std::string& account, const std::string& password, User& user);       // 登录：成功把用户写入 user 并返回 true，失败返回 false
bool changePassword(const std::string& account, const std::string& oldPassword, const std::string& newPassword); // 修改密码：原密码正确才生效
std::vector<std::string> getLoginRecords(const std::string& account);                  // 查询某账号的登录记录
std::string currentTime();                                                             // 当前时间，格式 YYYY-MM-DD HH:MM
