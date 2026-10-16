// ===== 科目数据读写 =====
#include "subject_repo.h"
#include "file_io.h"
#include <iostream>


// 读取 subjects.csv
std::vector<Subject> loadSubjects(){
    std::vector<Subject> subjects;
    bool first = true;
    for(const std::string& line : readLine("data/subjects.csv")){
        if(first){
            first = false;
            continue;
        } // 跳过表头
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 3) continue; // 字段不足跳过
        Subject s;
        s.id = f[0];
        s.name = f[1];
        try{
            s.credit = std::stoi(f[2]);
        }catch(...){
            std::cout << "subjects.csv 跳过坏行: " << line << "\n";
            continue;
        }
        subjects.push_back(s);
    }
    return subjects;
}

// 写入 subjects.csv
void saveSubjects(const std::vector<Subject>& subjects){
    std::vector<std::string> lines;
    for(const Subject& s : subjects){
        lines.push_back(join({s.id, s.name, std::to_string(s.credit)}, ','));
    }
    writeLines("data/subjects.csv", lines);
}