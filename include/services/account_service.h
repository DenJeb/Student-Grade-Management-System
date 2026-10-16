// ===== 管理员账号管理 =====
#pragma once
#include <string>
#include <vector>
#include "user.h"


bool addAccount(const std::string& account, const std::string& password, Role role); // 新增账号（账号已存在则失败）
bool deleteAccount(const std::string& account);                                      // 删除账号
bool setAccountActive(const std::string& account, bool active);                      // 禁用/启用账号
bool resetPassword(const std::string& account, const std::string& newPassword);      // 重置密码
std::vector<User> getUsersByRole(Role role);                                         // 按角色查账号列表
