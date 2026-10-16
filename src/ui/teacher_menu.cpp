// ===== 教师主菜单 =====
#include "teacher_menu.h"
#include "auth_service.h"
#include "student_service.h"
#include "score_service.h"
#include "console.h"
#include <iostream>
#include <vector>


// 选班级+科目（教师与管理员共用），成功把结果写入 classId / subjectId
static bool pickClassAndSubject(const std::vector<std::string>& classIds, std::string& classId, std::string& subjectId){
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

    std::vector<Subject> subjects = getAllSubjects();
    if(subjects.empty()){
        std::cout << "没有科目，请管理员先维护科目\n";
        pause();
        return false;
    }
    options.clear();
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
        printMenu("教师主菜单", {"查询学生", "编辑学生信息", "成绩录入", "成绩修改", "修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 6);

        if(choice == 1){
            // 模糊检索（仅所辖班级）
            std::string keyword = inputString("请输入学号或姓名关键字: ");
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
