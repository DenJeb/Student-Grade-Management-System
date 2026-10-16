// ===== 成绩录入、修改与校验 =====
#pragma once
#include <string>
#include "score.h"


bool findScore(const std::string& studentId, const std::string& subjectId, Score& out); // 查一条成绩（找不到返回 false）
void saveScore(const std::string& studentId, const std::string& subjectId, int score); // 录入或修改：已有则覆盖，没有则新增
