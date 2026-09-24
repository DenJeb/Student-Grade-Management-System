// ===== 科目数据读写 =====
#pragma once
#include <vector>
#include "subject.h"


std::vector<Subject> loadSubjects(); // 读取 subjects.csv
void saveSubjects(const std::vector<Subject>& subjects); // 写入 subjects.csv
