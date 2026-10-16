// ===== 报表导出与备份恢复 =====
#pragma once
#include <string>


// 导出学生个人成绩报表，返回文件路径（失败返回空串）；subjectId 为空 = 全部科目
std::string exportStudentReport(const std::string& studentId, const std::string& subjectId);

// 教师批量导出班级报表（学生信息/成绩单/排名表/统计报表），返回成功导出的文件数
int exportClassReports(const std::string& classId);

// 全量备份 data/ 到 backup/
bool backupAllData();

// 从 backup/ 恢复覆盖 data/
bool restoreAllData();
