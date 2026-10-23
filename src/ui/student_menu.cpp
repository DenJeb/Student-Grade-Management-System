// ===== 学生主菜单 =====
#include "student_menu.h"
#include "auth_service.h"
#include "student_service.h"
#include "stats_service.h"
#include "export_service.h"
#include "console.h"
#include <iostream>
#include <iomanip>
#include <vector>


void studentMenu(const User& user){
    while(true){
        clearScreen();
        printMenu("学生主菜单", {"个人信息", "个人成绩单", "班级排名", "单科排名", "导出成绩报表", "查看登录记录", "修改密码", "退出登录"});
        int choice = inputChoice("请选择: ", 1, 8);

        if(choice == 1){
            // 个人信息（只读）
            StudentUser s;
            if(!findStudent(user.getAccount(), s)){
                std::cout << "未找到你的档案，请联系管理员\n";
            }else{
                std::cout << "学号: " << s.getAccount() << "\n";
                std::cout << "姓名: " << s.getStudentName() << "\n";
                std::cout << "性别: " << s.getStudentGender() << "\n";
                std::cout << "年级: " << s.getStudentGrade() << "\n";
                std::cout << "班级: " << s.getStudentClass() << "\n";
                std::cout << "联系方式: " << s.getStudentContact() << "\n";
            }
            pause();
        }else if(choice == 2){
            // 个人成绩单：单科/总分/平均分/绩点
            std::vector<SubjectScore> detail = getStudentScoreDetail(user.getAccount());
            if(detail.empty()){
                std::cout << "暂无已录入成绩\n";
            }else{
                std::cout << "科目 | 学分 | 成绩 | 绩点\n";
                for(const SubjectScore& d : detail){
                    std::cout << d.subject_name << " | " << d.credit << " | " << d.score
                              << " | " << std::fixed << std::setprecision(1) << scoreToGpa(d.score) << "\n";
                }
                std::cout << "总分: " << getStudentTotal(user.getAccount()) << "\n";
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "平均分: " << getStudentAverage(user.getAccount()) << "\n";
                std::cout << "平均绩点: " << getStudentGpa(user.getAccount()) << "\n";
            }
            pause();
        }else if(choice == 3){
            // 班级排名（总分/平均分）
            int myTotal = getStudentTotal(user.getAccount());
            if(myTotal < 0){
                std::cout << "暂无已录入成绩，无法排名\n";
            }else{
                std::cout << "班级人数: " << getClassSize(user.getAccount()) << "\n";
                std::cout << "总分排名: 第 " << getClassTotalRank(user.getAccount()) << " 名\n";
                std::cout << "平均分排名: 第 " << getClassAverageRank(user.getAccount()) << " 名\n";
            }
            pause();
        }else if(choice == 4){
            // 单科排名
            std::vector<SubjectScore> detail = getStudentScoreDetail(user.getAccount());
            if(detail.empty()){
                std::cout << "暂无已录入成绩\n";
                pause();
                continue;
            }
            std::vector<std::string> options;
            for(const SubjectScore& d : detail) options.push_back(d.subject_name);
            printMenu("选择科目", options);
            int subChoice = inputChoice("请选择: ", 1, (int)options.size());
            const SubjectScore& picked = detail[subChoice - 1];
            int rank = getSubjectRank(user.getAccount(), picked.subject_id);
            std::cout << picked.subject_name << " 班级排名: 第 " << rank
                      << " 名（班级 " << getClassSize(user.getAccount()) << " 人）\n";
            pause();
        }else if(choice == 5){
            // 导出成绩报表（全部/单科）
            std::vector<SubjectScore> detail = getStudentScoreDetail(user.getAccount());
            if(detail.empty()){
                std::cout << "暂无已录入成绩，无可导出\n";
                pause();
                continue;
            }
            printMenu("导出范围", {"全部科目", "单科"});
            int scope = inputChoice("请选择: ", 1, 2);
            std::string subjectId;
            if(scope == 2){
                std::vector<std::string> options;
                for(const SubjectScore& d : detail) options.push_back(d.subject_name);
                printMenu("选择科目", options);
                subjectId = detail[inputChoice("请选择: ", 1, (int)options.size()) - 1].subject_id;
            }
            std::string path = exportStudentReport(user.getAccount(), subjectId);
            if(path.empty()){
                std::cout << "导出失败\n";
            }else{
                std::cout << "导出成功: " << path << "\n";
            }
            pause();
        }else if(choice == 6){
            // 查看登录记录
            std::vector<std::string> records = getLoginRecords(user.getAccount());
            if(records.empty()){
                std::cout << "暂无登录记录\n";
            }else{
                for(const std::string& r : records){
                    std::cout << r << "\n";
                }
            }
            pause();
        }else if(choice == 7){
            // 修改密码
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
