// ===== 成绩记录结构 =====
#pragma once
#include <string>


struct Score{
    std::string student_id; // 学号
    std::string subject_id; // 科目ID
    int score;              // 成绩
};