// ===== 成绩录入、修改与校验 =====
#include "score_service.h"
#include "score_repo.h"


// 查某学生某科目的成绩
bool findScore(const std::string& studentId, const std::string& subjectId, Score& out){
    for(const Score& s : loadScores()){
        if(s.student_id == studentId && s.subject_id == subjectId){
            out = s;
            return true;
        }
    }
    return false;
}

// 录入或修改：已有该生该科成绩则覆盖，没有则新增（0-100 校验由调用方用 inputChoice 保证）
void saveScore(const std::string& studentId, const std::string& subjectId, int score){
    std::vector<Score> scores = loadScores();
    for(Score& s : scores){
        if(s.student_id == studentId && s.subject_id == subjectId){
            s.score = score; // 已有则修改
            saveScores(scores);
            return;
        }
    }
    Score s;
    s.student_id = studentId;
    s.subject_id = subjectId;
    s.score = score;
    scores.push_back(s); // 没有则新增
    saveScores(scores);
}
