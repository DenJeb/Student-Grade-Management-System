// ===== 成绩数据读写 =====
#include "score_repo.h"
#include "file_io.h"
#include <iostream>


// 读取 scores.csv
std::vector<Score> loadScores(){
    std::vector<Score> scores;
    bool first = true;
    for(const std::string& line : readLine("data/scores.csv")){
        if(first){
            first = false;
            continue;
        } // 跳过表头
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 3) continue;   // 字段不足跳过
        Score s;
        s.student_id = f[0];
        s.subject_id = f[1];
        try{
            s.score = std::stoi(f[2]);
        }catch(...){
            std::cout << "scores.csv 跳过坏行: " << line << "\n";
            continue;
        }
        scores.push_back(s);
    }
    return scores;
}

// 写入 scores.csv
void saveScores(const std::vector<Score>& scores){
    std::vector<std::string> lines;
    for(const Score& s : scores){
        lines.push_back(join({s.student_id, s.subject_id, std::to_string(s.score)}, ','));
    }
    writeLines("data/scores.csv", lines);
}
