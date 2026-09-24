// ===== 学生数据读写 =====
#include "student_repo.h"
#include "file_io.h"


// 读取 students.csv 文件
std::vector<StudentUser> loadStudents(){
    std::vector<StudentUser> students;
    for(const std::string& line : readLine("data/students.csv")){
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 6) continue; // 字段不足，跳过
        StudentUser s;
        s.setAccount(f[0]); // 学号即账号
        s.setStudentName(f[1]);
        s.setStudentGender(f[2]);
        s.setStudentGrade(f[3]);
        s.setStudentClass(f[4]);
        s.setStudentContact(f[5]);
        students.push_back(s);
    }
    return students;
}

// 写入 students.csv 文件
void saveStudents(const std::vector<StudentUser>& students){
    std::vector<std::string> lines;
    for(const StudentUser& s : students){
        lines.push_back(join({s.getAccount(), 
                             s.getStudentName(), 
                             s.getStudentGender(), 
                             s.getStudentGrade(), 
                             s.getStudentClass(),
                             s.getStudentContact(),
                            }, ','));
    }
    writeLines("data/students.csv", lines);
}