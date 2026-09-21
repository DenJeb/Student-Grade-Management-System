// ===== 数字与区间校验 =====
#pragma once
#include <string>


bool isInt(const std::string& text);       // 判断字符串是否为纯整数
bool isNumber(const std::string& text);    // 判断字符串是否为整数
bool inRange(int value, int min, int max); // 判断值是否在 [min, max] 内