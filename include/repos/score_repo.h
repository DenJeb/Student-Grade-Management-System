// ===== 成绩数据读写 =====
#pragma once
#include <vector>
#include "score.h"


std::vector<Score> loadScores(); // 读取 scores.csv
void saveScores(const std::vector<Score>& scores); // 写入 scores.csv