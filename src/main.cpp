// ===== 程序入口：启动、加载、分发 =====
#include "user_repo.h"
#include "student_repo.h"
#include "class_repo.h"
#include "subject_repo.h"
#include "score_repo.h"
#include "user.h"
#include <iostream>
#include <vector>


int main(){
    // 加载全部数据
    std::vector<User> users = loadUsers();
    std::vector<StudentUser> students = loadStudents();
    std::vector<ClassInfo> classes = loadClasses();
    std::vector<Subject> subjects = loadSubjects();
    std::vector<Score> scores = loadScores();
    std::vector<std::string> records = loadLoginRecords();

    // 打印验证：数据能进能出
    std::cout << "==================== 账号 ====================\n";
    for(const User& u : users){
        std::cout << u.getAccount() << " | "
                  << u.getPassword() << " | "
                  << roleToString(u.getRole()) << " | "
                  << u.getActive() << " | "
                  << u.getCreateTime() << "\n";
    }

    std::cout << "==================== 学生 ====================\n";
    for(const StudentUser& s : students){
        std::cout << s.getAccount() << " | "
                  << s.getStudentName() << " | "
                  << s.getStudentGender() << " | "
                  << s.getStudentGrade() << " | "
                  << s.getStudentClass() << " | "
                  << s.getStudentContact() << "\n";
    }

    std::cout << "==================== 班级 ====================\n";
    for(const ClassInfo& c : classes){
        std::cout << c.id << " | "
                  << c.grade << " | "
                  << c.teacher_id << "\n";
    }

    std::cout << "==================== 科目 ====================\n";
    for(const Subject& s : subjects){
        std::cout << s.id << " | "
                  << s.name << " | "
                  << s.credit << "\n";
    }

    std::cout << "==================== 成绩 ====================\n";
    for(const Score& s : scores){
        std::cout << s.student_id << " | "
                  << s.subject_id << " | "
                  << s.score << "\n";
    }

    std::cout << "================== 登录记录 ==================\n";
    for(const std::string& r : records){
        std::cout << r << "\n";
    }

    return 0;
}
