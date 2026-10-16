// ===== 报表导出与备份恢复 =====
#include "export_service.h"
#include "student_service.h"
#include "stats_service.h"
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <vector>


// 导出学生个人成绩报表到 export/ 目录，带 BOM（Excel 打开中文不乱码）
std::string exportStudentReport(const std::string& studentId, const std::string& subjectId){
    StudentUser s;
    if(!findStudent(studentId, s)) return "";

    std::vector<SubjectScore> detail = getStudentScoreDetail(studentId);
    if(detail.empty()) return ""; // 没有成绩，无可导出

    std::filesystem::create_directories("export"); // 导出目录不存在则创建
    std::string path = "export/成绩报表_" + studentId + ".csv";

    std::ofstream out(path, std::ios::binary);
    if(!out) return "";
    out << "\xEF\xBB\xBF"; // BOM
    out << "姓名," << s.getStudentName() << "\n";
    out << "科目编号,科目名称,学分,成绩\n";

    for(const SubjectScore& d : detail){
        if(!subjectId.empty() && d.subject_id != subjectId) continue; // 单科筛选
        out << d.subject_id << "," << d.subject_name << "," << d.credit << "," << d.score << "\n";
    }

    // 全部科目才附带汇总
    if(subjectId.empty()){
        out << std::fixed << std::setprecision(1);
        out << "总分," << getStudentTotal(studentId) << "\n";
        out << "平均分," << getStudentAverage(studentId) << "\n";
        out << std::setprecision(2);
        out << "平均绩点," << getStudentGpa(studentId) << "\n";
    }
    return path;
}

// 教师批量导出班级报表：学生信息/成绩单/排名表/统计报表 四份，规范命名存 export/
int exportClassReports(const std::string& classId){
    std::vector<StudentUser> students;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() == classId) students.push_back(s);
    }
    if(students.empty()) return 0;

    std::filesystem::create_directories("export");
    int count = 0;

    // 1. 学生信息表
    {
        std::ofstream out("export/学生信息_" + classId + ".csv", std::ios::binary);
        if(out){
            out << "\xEF\xBB\xBF";
            out << "学号,姓名,性别,年级,班级,联系方式\n";
            for(const StudentUser& s : students){
                out << s.getAccount() << "," << s.getStudentName() << ","
                    << s.getStudentGender() << "," << s.getStudentGrade() << ","
                    << s.getStudentClass() << "," << s.getStudentContact() << "\n";
            }
            count++;
        }
    }

    // 2. 全科成绩单（未录入留空）
    {
        std::ofstream out("export/成绩单_" + classId + ".csv", std::ios::binary);
        if(out){
            out << "\xEF\xBB\xBF";
            std::vector<Subject> subjects = getAllSubjects();
            out << "学号,姓名";
            for(const Subject& sub : subjects) out << "," << sub.name;
            out << "\n";
            for(const StudentUser& s : students){
                out << s.getAccount() << "," << s.getStudentName();
                for(const Subject& sub : subjects){
                    int score = getStudentSubjectScore(s.getAccount(), sub.id);
                    out << "," << (score < 0 ? "" : std::to_string(score));
                }
                out << "\n";
            }
            count++;
        }
    }

    // 3. 排名表（按总分从高到低）
    {
        std::ofstream out("export/排名表_" + classId + ".csv", std::ios::binary);
        if(out){
            out << "\xEF\xBB\xBF";
            out << "名次,学号,姓名,总分,平均分\n";
            std::vector<StudentRankItem> list = getClassRankList(classId, true, false);
            for(size_t i = 0; i < list.size(); i++){
                out << i + 1 << "," << list[i].student_id << "," << list[i].student_name << ","
                    << list[i].total << "," << std::fixed << std::setprecision(2) << list[i].average << "\n";
            }
            count++;
        }
    }

    // 4. 统计报表
    {
        std::ofstream out("export/统计报表_" + classId + ".csv", std::ios::binary);
        if(out){
            out << "\xEF\xBB\xBF";
            out << "科目,平均分,最高分,最低分,及格人数,不及格人数,及格率(%)\n";
            for(const ClassSubjectStat& st : getClassSubjectStats(classId)){
                out << st.subject_name << "," << std::fixed << std::setprecision(1) << st.average << ","
                    << st.max << "," << st.min << ","
                    << st.passCount << "," << st.failCount << ","
                    << st.passRate << "\n";
            }
            count++;
        }
    }

    return count;
}

// 全量备份 data/ 到 backup/
bool backupAllData(){
    std::filesystem::create_directories("backup");
    bool ok = true;
    std::error_code ec;
    const char* files[] = {"accounts.csv", "students.csv", "teachers.csv", "classes.csv", "subjects.csv", "scores.csv", "login_records.csv"};
    for(const char* f : files){
        std::filesystem::copy_file(std::string("data/") + f, std::string("backup/") + f,
                                   std::filesystem::copy_options::overwrite_existing, ec);
        if(ec) ok = false;
    }
    return ok;
}

// 从 backup/ 恢复覆盖 data/
bool restoreAllData(){
    bool ok = true;
    std::error_code ec;
    const char* files[] = {"accounts.csv", "students.csv", "teachers.csv", "classes.csv", "subjects.csv", "scores.csv", "login_records.csv"};
    for(const char* f : files){
        std::filesystem::copy_file(std::string("backup/") + f, std::string("data/") + f,
                                   std::filesystem::copy_options::overwrite_existing, ec);
        if(ec) ok = false;
    }
    return ok;
}
