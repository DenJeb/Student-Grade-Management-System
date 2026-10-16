// ===== 教师主菜单 =====
#include "teacher_menu.h"
#include "auth_service.h"
#include "student_service.h"
#include "score_service.h"
#include "stats_service.h"
#include "export_service.h"
#include "console.h"
#include <iostream>
#include <iomanip>
#include <vector>


// 从给定班级里选一个（成功返回 true 并写入 classId）
static bool pickClass(const std::vector<std::string>& classIds, std::string& classId){
    std::vector<ClassInfo> classes;
    for(const std::string& id : classIds){
        ClassInfo c;
        if(findClass(id, c)) classes.push_back(c);
    }
    if(classes.empty()){
        std::cout << "没有可操作的班级\n";
        pause();
        return false;
    }
    std::vector<std::string> options;
    for(const ClassInfo& c : classes) options.push_back(c.id + "（" + c.grade + "）");
    printMenu("选择班级", options);
    classId = classes[inputChoice("请选择: ", 1, (int)options.size()) - 1].id;
    return true;
}

// 选班级+科目（教师与管理员共用），成功把结果写入 classId / subjectId
static bool pickClassAndSubject(const std::vector<std::string>& classIds, std::string& classId, std::string& subjectId){
    if(!pickClass(classIds, classId)) return false;

    std::vector<Subject> subjects = getAllSubjects();
    if(subjects.empty()){
        std::cout << "没有科目，请管理员先维护科目\n";
        pause();
        return false;
    }
    std::vector<std::string> options;
    for(const Subject& s : subjects) options.push_back(s.name);
    printMenu("选择科目", options);
    subjectId = subjects[inputChoice("请选择: ", 1, (int)options.size()) - 1].id;
    return true;
}

// 按班级+科目逐人录入成绩
void scoreEntryMenu(const std::vector<std::string>& classIds){
    std::string classId, subjectId;
    if(!pickClassAndSubject(classIds, classId, subjectId)) return;

    std::vector<StudentUser> students;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() == classId) students.push_back(s);
    }
    if(students.empty()){
        std::cout << "该班级没有学生\n";
        pause();
        return;
    }

    for(const StudentUser& s : students){
        int score = inputChoice("请输入 " + s.getStudentName() + "(" + s.getAccount() + ") 的成绩(0-100): ", 0, 100);
        saveScore(s.getAccount(), subjectId, score);
    }
    std::cout << "录入完成，共 " << students.size() << " 人\n";
    pause();
}

// 按班级+科目修改成绩
void scoreEditMenu(const std::vector<std::string>& classIds){
    std::string classId, subjectId;
    if(!pickClassAndSubject(classIds, classId, subjectId)) return;

    std::vector<StudentUser> students;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() == classId) students.push_back(s);
    }
    if(students.empty()){
        std::cout << "该班级没有学生\n";
        pause();
        return;
    }

    std::vector<std::string> options;
    for(const StudentUser& s : students){
        Score sc;
        std::string cur = findScore(s.getAccount(), subjectId, sc) ? std::to_string(sc.score) : "未录入";
        options.push_back(s.getStudentName() + "（" + s.getAccount() + "）当前: " + cur);
    }
    printMenu("选择学生", options);
    int stuChoice = inputChoice("请选择: ", 1, (int)options.size());
    const StudentUser& picked = students[stuChoice - 1];

    int score = inputChoice("请输入新成绩(0-100): ", 0, 100);
    saveScore(picked.getAccount(), subjectId, score);
    std::cout << "修改成功\n";
    pause();
}


void teacherMenu(const User& user){
    while(true){
        clearScreen();
        printMenu("教师主菜单", {"查询学生", "编辑学生信息", "成绩录入", "成绩修改", "班级统计", "排名表", "梯队分布", "导出报表", "修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 10);

        if(choice == 1){
            // 模糊检索（仅所辖班级），空关键字 = 批量查看全班
            std::string keyword = inputString("请输入学号或姓名关键字（空行 = 全班）: ");
            std::vector<StudentUser> list = teacherSearchStudents(keyword, user.getAccount());
            if(list.empty()){
                std::cout << "没有找到匹配的学生（仅限所辖班级）\n";
            }else{
                for(const StudentUser& s : list){
                    std::cout << s.getAccount() << " | " << s.getStudentName() << " | "
                              << s.getStudentGender() << " | " << s.getStudentGrade() << " | "
                              << s.getStudentClass() << " | " << s.getStudentContact() << "\n";
                }
            }
            pause();
        }else if(choice == 2){
            // 编辑学生信息（仅所辖班级，无新增删除权限）
            std::string account = inputString("请输入要编辑的学生学号: ");
            if(!teacherOwnsStudent(user.getAccount(), account)){
                std::cout << "该学生不在你所辖班级，操作被拒绝\n";
                pause();
                continue;
            }
            StudentUser s;
            if(!findStudent(account, s)){
                std::cout << "学号不存在\n";
                pause();
                continue;
            }
            std::string input;
            input = inputString("姓名（空行不修改）: ");
            if(!input.empty()) s.setStudentName(input);
            input = inputString("性别（空行不修改）: ");
            if(!input.empty()) s.setStudentGender(input);
            input = inputString("年级（空行不修改）: ");
            if(!input.empty()) s.setStudentGrade(input);
            input = inputString("联系方式（空行不修改）: ");
            if(!input.empty()) s.setStudentContact(input);
            updateStudent(account, s);
            std::cout << "保存成功\n";
            pause();
        }else if(choice == 3){
            scoreEntryMenu(getTeacherClassIds(user.getAccount())); // 成绩录入（仅所辖班级）
        }else if(choice == 4){
            scoreEditMenu(getTeacherClassIds(user.getAccount()));  // 成绩修改（仅所辖班级）
        }else if(choice == 5){
            // 班级统计（各科平均/最高/最低/及格/不及格/及格率）
            std::string classId;
            if(!pickClass(getTeacherClassIds(user.getAccount()), classId)) continue;
            std::vector<ClassSubjectStat> stats = getClassSubjectStats(classId);
            if(stats.empty()){
                std::cout << "该班级还没有任何已录入成绩\n";
            }else{
                for(const ClassSubjectStat& st : stats){
                    std::cout << st.subject_name << ": 平均 " << std::fixed << std::setprecision(1) << st.average
                              << " | 最高 " << st.max << " | 最低 " << st.min
                              << " | 及格 " << st.passCount << " 人 | 不及格 " << st.failCount
                              << " 人 | 及格率 " << st.passRate << "%\n";
                }
            }
            pause();
        }else if(choice == 6){
            // 排名表（总分/平均分 × 升降序）
            std::string classId;
            if(!pickClass(getTeacherClassIds(user.getAccount()), classId)) continue;
            printMenu("排序方式", {"按总分", "按平均分"});
            bool byTotal = (inputChoice("请选择: ", 1, 2) == 1);
            printMenu("顺序", {"从高到低", "从低到高"});
            bool ascending = (inputChoice("请选择: ", 1, 2) == 2);
            std::vector<StudentRankItem> list = getClassRankList(classId, byTotal, ascending);
            for(size_t i = 0; i < list.size(); i++){
                std::cout << i + 1 << ". " << list[i].student_name << "（" << list[i].student_id << "）"
                          << " | 总分 " << list[i].total
                          << " | 平均分 " << std::fixed << std::setprecision(2) << list[i].average << "\n";
            }
            pause();
        }else if(choice == 7){
            // 梯队分布（按平均分分档）
            std::string classId;
            if(!pickClass(getTeacherClassIds(user.getAccount()), classId)) continue;
            std::vector<int> tiers = getClassTiers(classId);
            std::cout << "优秀（90 以上）: " << tiers[0] << " 人\n";
            std::cout << "良好（80-89）: " << tiers[1] << " 人\n";
            std::cout << "中等（70-79）: " << tiers[2] << " 人\n";
            std::cout << "及格（60-69）: " << tiers[3] << " 人\n";
            std::cout << "不及格（60 以下）: " << tiers[4] << " 人\n";
            pause();
        }else if(choice == 8){
            // 导出班级报表（学生信息/成绩单/排名表/统计报表）
            std::string classId;
            if(!pickClass(getTeacherClassIds(user.getAccount()), classId)) continue;
            int exported = exportClassReports(classId);
            if(exported > 0){
                std::cout << "导出完成，共 " << exported << " 个文件（export/ 目录）\n";
            }else{
                std::cout << "该班级没有学生，导出失败\n";
            }
            pause();
        }else if(choice == 9){
            // 修改密码
            std::string oldPwd = inputString("请输入原密码: ");
            std::string newPwd = inputString("请输入新密码: ");
            if(changePassword(user.getAccount(), oldPwd, newPwd)){
                std::cout << "修改成功\n";
            }else{
                std::cout << "原密码错误，修改失败\n";
            }
            pause();
        }else{
            break; // 退出登录
        }
    }
}
