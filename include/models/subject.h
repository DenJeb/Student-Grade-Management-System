// ===== 科目信息结构 =====
#pragma once
#include <string>


struct Subject{
    std::string id;   // 科目ID
    std::string name; // 科目名称
    int credit;       // 学分
};