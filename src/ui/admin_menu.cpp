// ===== 管理员主菜单 =====
#include "admin_menu.h"
#include "account_service.h"
#include "auth_service.h"
#include "student_service.h"
#include "export_service.h"
#include "teacher_menu.h"
#include "console.h"
#include <iostream>
#include <vector>


// 学生信息管理子菜单（管理员：增删改查）
static void studentManageMenu(){
    while(true){
        clearScreen();
        printMenu("学生信息管理", {"学生列表", "新增学生", "删除学生", "编辑学生", "返回"});
        int choice = inputChoice("请选择: ", 1, 5);

        if(choice == 1){
            // 学生列表
            for(const StudentUser& s : getAllStudents()){
                std::cout << s.getAccount() << " | " << s.getStudentName() << " | "
                          << s.getStudentGender() << " | " << s.getStudentGrade() << " | "
                          << s.getStudentClass() << " | " << s.getStudentContact() << "\n";
            }
            pause();
        }else if(choice == 2){
            // 新增学生（学号即登录账号，账号本身在账号管理中创建）
            StudentUser s;
            s.setAccount(inputString("学号（即登录账号）: "));
            if(s.getAccount().empty()){
                std::cout << "学号不能为空\n";
                pause();
                continue;
            }
            s.setStudentName(inputString("姓名: "));
            s.setStudentGender(inputString("性别: "));
            s.setStudentGrade(inputString("年级: "));
            s.setStudentClass(inputString("班级编号: "));
            s.setStudentContact(inputString("联系方式: "));
            if(addStudent(s)){
                std::cout << "新增成功（登录账号请到账号管理中创建）\n";
            }else{
                std::cout << "学号已存在，新增失败\n";
            }
            pause();
        }else if(choice == 3){
            // 删除学生（只删档案，账号在账号管理中删除）
            std::string account = inputString("请输入要删除的学号: ");
            if(!confirm("确定删除学生 " + account + " 的档案吗？")){
                continue;
            }
            if(deleteStudent(account)){
                std::cout << "删除成功（登录账号请到账号管理中删除）\n";
            }else{
                std::cout << "学号不存在，删除失败\n";
            }
            pause();
        }else if(choice == 4){
            // 编辑学生（空行不修改）
            std::string account = inputString("请输入要编辑的学号: ");
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
            input = inputString("班级编号（空行不修改）: ");
            if(!input.empty()) s.setStudentClass(input);
            input = inputString("联系方式（空行不修改）: ");
            if(!input.empty()) s.setStudentContact(input);
            updateStudent(account, s);
            std::cout << "保存成功\n";
            pause();
        }else{
            break; // 返回
        }
    }
}

// 班级管理子菜单（管理员）
static void classManageMenu(){
    while(true){
        clearScreen();
        printMenu("班级管理", {"班级列表", "新增班级", "删除班级", "编辑班级", "返回"});
        int choice = inputChoice("请选择: ", 1, 5);

        if(choice == 1){
            // 班级列表
            for(const ClassInfo& c : getAllClasses()){
                std::cout << c.id << " | " << c.grade << " | 班主任工号 " << c.teacher_id << "\n";
            }
            pause();
        }else if(choice == 2){
            // 新增班级
            ClassInfo c;
            c.id = inputString("班级编号: ");
            if(c.id.empty()){
                std::cout << "班级编号不能为空\n";
                pause();
                continue;
            }
            c.grade = inputString("年级: ");
            c.teacher_id = inputString("班主任工号: ");
            if(addClass(c)){
                std::cout << "新增成功\n";
            }else{
                std::cout << "班级编号已存在，新增失败\n";
            }
            pause();
        }else if(choice == 3){
            // 删除班级
            std::string id = inputString("请输入要删除的班级编号: ");
            if(!confirm("确定删除班级 " + id + " 吗？")){
                continue;
            }
            if(deleteClass(id)){
                std::cout << "删除成功\n";
            }else{
                std::cout << "班级不存在，删除失败\n";
            }
            pause();
        }else if(choice == 4){
            // 编辑班级（空行不修改，班主任关联在此维护）
            std::string id = inputString("请输入要编辑的班级编号: ");
            ClassInfo c;
            if(!findClass(id, c)){
                std::cout << "班级不存在\n";
                pause();
                continue;
            }
            std::string input;
            input = inputString("年级（空行不修改）: ");
            if(!input.empty()) c.grade = input;
            input = inputString("班主任工号（空行不修改）: ");
            if(!input.empty()) c.teacher_id = input;
            updateClass(id, c);
            std::cout << "保存成功\n";
            pause();
        }else{
            break; // 返回
        }
    }
}

// 科目管理子菜单（管理员）
static void subjectManageMenu(){
    while(true){
        clearScreen();
        printMenu("科目管理", {"科目列表", "新增科目", "删除科目", "编辑科目", "返回"});
        int choice = inputChoice("请选择: ", 1, 5);

        if(choice == 1){
            // 科目列表
            for(const Subject& s : getAllSubjects()){
                std::cout << s.id << " | " << s.name << " | " << s.credit << " 学分\n";
            }
            pause();
        }else if(choice == 2){
            // 新增科目
            Subject s;
            s.id = inputString("科目编号: ");
            if(s.id.empty()){
                std::cout << "科目编号不能为空\n";
                pause();
                continue;
            }
            s.name = inputString("科目名称: ");
            s.credit = inputInt("学分: ");
            if(addSubject(s)){
                std::cout << "新增成功\n";
            }else{
                std::cout << "科目编号已存在，新增失败\n";
            }
            pause();
        }else if(choice == 3){
            // 删除科目
            std::string id = inputString("请输入要删除的科目编号: ");
            if(!confirm("确定删除科目 " + id + " 吗？")){
                continue;
            }
            if(deleteSubject(id)){
                std::cout << "删除成功\n";
            }else{
                std::cout << "科目不存在，删除失败\n";
            }
            pause();
        }else if(choice == 4){
            // 编辑科目
            std::string id = inputString("请输入要编辑的科目编号: ");
            Subject s;
            if(!findSubject(id, s)){
                std::cout << "科目不存在\n";
                pause();
                continue;
            }
            std::string input;
            input = inputString("科目名称（空行不修改）: ");
            if(!input.empty()) s.name = input;
            s.credit = inputInt("学分: ");
            updateSubject(id, s);
            std::cout << "保存成功\n";
            pause();
        }else{
            break; // 返回
        }
    }
}

void adminMenu(const User& user){
    while(true){
        clearScreen();
        printMenu("管理员主菜单", {"账号列表", "新增账号", "批量新增账号", "删除账号", "禁用/启用账号", "重置密码", "学生信息管理", "班级管理", "科目管理", "成绩录入", "成绩修改", "数据备份", "数据恢复", "修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 15);

        if(choice == 1){
            // 账号列表（按角色筛选）
            printMenu("选择角色", {"学生", "教师", "管理员"});
            int roleChoice = inputChoice("请选择: ", 1, 3);
            Role role = (roleChoice == 1) ? Role::Student : (roleChoice == 2) ? Role::Teacher : Role::Admin;
            for(const User& u : getUsersByRole(role)){
                std::cout << u.getAccount() << " | " << roleToString(u.getRole())
                          << " | " << (u.getActive() ? "正常" : "禁用") << "\n";
            }
            pause();
        }else if(choice == 2){
            // 新增账号（学生或教师）
            printMenu("选择角色", {"学生", "教师"});
            int roleChoice = inputChoice("请选择: ", 1, 2);
            Role role = (roleChoice == 1) ? Role::Student : Role::Teacher;
            std::string account = inputString("请输入账号: ");
            if(account.empty()){
                std::cout << "账号不能为空\n";
                pause();
                continue;
            }
            std::string password = inputString("请输入初始密码: ");
            if(addAccount(account, password, role)){
                std::cout << "新增成功\n";
            }else{
                std::cout << "账号已存在，新增失败\n";
            }
            pause();
        }else if(choice == 3){
            // 批量新增账号（统一初始密码，空行结束）
            printMenu("选择角色", {"学生", "教师"});
            int roleChoice = inputChoice("请选择: ", 1, 2);
            Role role = (roleChoice == 1) ? Role::Student : Role::Teacher;
            std::string password = inputString("请输入统一初始密码: ");
            while(true){
                std::string account = inputString("请输入账号（空行结束）: ");
                if(account.empty()) break;
                if(addAccount(account, password, role)){
                    std::cout << account << " 新增成功\n";
                }else{
                    std::cout << account << " 已存在，跳过\n";
                }
            }
            pause();
        }else if(choice == 4){
            // 删除账号
            std::string account = inputString("请输入要删除的账号: ");
            if(!confirm("确定删除账号 " + account + " 吗？")){
                continue;
            }
            if(deleteAccount(account)){
                std::cout << "删除成功\n";
            }else{
                std::cout << "账号不存在，删除失败\n";
            }
            pause();
        }else if(choice == 5){
            // 禁用/启用账号
            std::string account = inputString("请输入账号: ");
            printMenu("选择操作", {"禁用", "启用"});
            int op = inputChoice("请选择: ", 1, 2);
            bool active = (op == 2);
            if(setAccountActive(account, active)){
                std::cout << "操作成功\n";
            }else{
                std::cout << "账号不存在\n";
            }
            pause();
        }else if(choice == 6){
            // 重置密码
            std::string account = inputString("请输入账号: ");
            std::string newPwd = inputString("请输入新密码: ");
            if(resetPassword(account, newPwd)){
                std::cout << "重置成功\n";
            }else{
                std::cout << "账号不存在\n";
            }
            pause();
        }else if(choice == 7){
            studentManageMenu(); // 学生信息管理
        }else if(choice == 8){
            classManageMenu();   // 班级管理
        }else if(choice == 9){
            subjectManageMenu(); // 科目管理
        }else if(choice == 10){
            // 成绩录入（全部班级）
            std::vector<std::string> allClassIds;
            for(const ClassInfo& c : getAllClasses()) allClassIds.push_back(c.id);
            scoreEntryMenu(allClassIds);
        }else if(choice == 11){
            // 成绩修改（全部班级）
            std::vector<std::string> allClassIds;
            for(const ClassInfo& c : getAllClasses()) allClassIds.push_back(c.id);
            scoreEditMenu(allClassIds);
        }else if(choice == 12){
            // 数据备份（data/ → backup/）
            if(backupAllData()){
                std::cout << "备份成功（backup/ 目录）\n";
            }else{
                std::cout << "备份失败\n";
            }
            pause();
        }else if(choice == 13){
            // 数据恢复（backup/ → data/，覆盖现有数据）
            if(!confirm("恢复将覆盖当前全部数据，确定吗？")){
                continue;
            }
            if(restoreAllData()){
                std::cout << "恢复成功\n";
            }else{
                std::cout << "恢复失败（请先做一次备份）\n";
            }
            pause();
        }else if(choice == 14){
            // 修改自己的密码
            std::string oldPwd = inputString("请输入原密码: ");
            std::string newPwd = inputString("请输入新密码: ");
            if(newPwd.empty()){
                std::cout << "新密码不能为空\n";
                pause();
                continue;
            }
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
