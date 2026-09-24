// ===== 班级数据读写 =====
#include "class_repo.h"
#include "file_io.h"


// 读取 classes.csv
std::vector<ClassInfo> loadClasses(){
    std::vector<ClassInfo> classes;
    for(const std::string& line : readLine("data/classes.csv")){
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 3) continue; // 字段不足跳过
        ClassInfo c;
        c.id = f[0];
        c.grade = f[1];
        c.teacher_id = f[2];
        classes.push_back(c);
    }
    return classes;
}

// 写入 classes.csv
void saveClasses(const std::vector<ClassInfo>& classes){
    std::vector<std::string> lines;
    for(const ClassInfo& c: classes){
        lines.push_back(join({c.id, c.grade, c.teacher_id}, ','));
    }
    writeLines("data/classes.csv", lines);
}