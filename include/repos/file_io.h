// ===== 通用文件读写 =====
#pragma once
#include <string>
#include <vector>


std::vector<std::string> readLine(const std::string& path);                      // 读取文件行列表
void writeLines(const std::string& path, const std::vector<std::string>& lines); // 写文件
void appendLine(const std::string& path, const std::string& line);               // 追加一行
std::vector<std::string> split(const std::string& s, char delimiter);            // 按分隔符拆分字符串
std::string join(const std::vector<std::string>& fields, char delimiter);        // 按分隔符合并字符串