// ===== 成绩数据读写 =====
#include "score_repo.h"
#include "file_io.h"


// 读取 scores.csv
std::vector<Score> loadScores(){
    std::vector<Score> scores;
    for(const std::string& line : readLine("data/scores.csv")){
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 3) continue;   // 字段不足跳过
        Score s;
        s.student_id = f[0];
        s.subject_id = f[1];
        s.score = std::stoi(f[2]);
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
