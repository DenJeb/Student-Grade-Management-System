// ===== 绩点、统计与排名 =====
#pragma once
#include <string>
#include <vector>


// 单科成绩明细（学生成绩单用）
struct SubjectScore{
    std::string subject_id;   // 科目编号
    std::string subject_name; // 科目名称
    int credit;               // 学分
    int score;                // 成绩
};

// 班级单科统计结果
struct ClassSubjectStat{
    std::string subject_id;   // 科目编号
    std::string subject_name; // 科目名称
    double average;           // 平均分
    int max;                  // 最高分
    int min;                  // 最低分
    int passCount;            // 及格人数（≥60）
    int failCount;            // 不及格人数（<60，未录入不算）
    int count;                // 已录入人数
    double passRate;          // 及格率（%）
};

// 排名表条目
struct StudentRankItem{
    std::string student_id;   // 学号
    std::string student_name; // 姓名
    int total;                // 总分（-1 表示无成绩）
    double average;           // 平均分
};


double scoreToGpa(int score);                                                    // 分数转绩点（分段表，见计划书 3.5）
std::vector<SubjectScore> getStudentScoreDetail(const std::string& studentId);   // 已录入成绩的明细（未录入的不出现）
int getStudentSubjectScore(const std::string& studentId, const std::string& subjectId); // 单科成绩（-1 表示未录入）
int getStudentTotal(const std::string& studentId);                               // 总分（-1 表示没有任何成绩）
double getStudentAverage(const std::string& studentId);                          // 平均分（-1 表示没有任何成绩）
double getStudentGpa(const std::string& studentId);                              // 平均绩点，学分加权（-1 表示没有任何成绩）
int getClassSize(const std::string& studentId);                                  // 同班人数（-1 表示学号不存在）
int getClassTotalRank(const std::string& studentId);                             // 班级总分排名，从 1 开始，同分并列同名次
int getClassAverageRank(const std::string& studentId);                           // 班级平均分排名
int getSubjectRank(const std::string& studentId, const std::string& subjectId);  // 单科班级排名（-1 表示未录入）

// 班级各科统计（只统计已录入，没人录过的科目不出现）
std::vector<ClassSubjectStat> getClassSubjectStats(const std::string& classId);

// 班级排名表（byTotal: true 按总分、false 按平均分；ascending: 升序）
std::vector<StudentRankItem> getClassRankList(const std::string& classId, bool byTotal, bool ascending);

// 班级成绩梯队（按平均分分档，返回各档人数：优秀/良好/中等/及格/不及格）
std::vector<int> getClassTiers(const std::string& classId);
