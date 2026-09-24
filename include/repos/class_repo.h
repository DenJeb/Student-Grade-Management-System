// ===== 班级数据读写 =====
#pragma once
#include <vector>
#include "class_info.h"


std::vector<ClassInfo> loadClasses(); // 读取 classes.csv
void saveClasses(const std::vector<ClassInfo>& classes); // 写入 classes.csv