// ===== 绩点、统计与排名 =====
#include "stats_service.h"
#include "score_service.h"
#include "student_service.h"
#include <algorithm>


// 分数转绩点（分段表，见计划书 3.5）
double scoreToGpa(int score){
    if(score >= 90) return 4.0;
    if(score >= 85) return 3.7;
    if(score >= 82) return 3.3;
    if(score >= 78) return 3.0;
    if(score >= 75) return 2.7;
    if(score >= 72) return 2.3;
    if(score >= 68) return 2.0;
    if(score >= 64) return 1.5;
    if(score >= 60) return 1.0;
    return 0.0;
}

// 已录入成绩的明细：按科目表顺序，未录入的不出现
std::vector<SubjectScore> getStudentScoreDetail(const std::string& studentId){
    std::vector<SubjectScore> result;
    for(const Subject& sub : getAllSubjects()){
        Score sc;
        if(findScore(studentId, sub.id, sc)){
            SubjectScore d;
            d.subject_id = sub.id;
            d.subject_name = sub.name;
            d.credit = sub.credit;
            d.score = sc.score;
            result.push_back(d);
        }
    }
    return result;
}

int getStudentSubjectScore(const std::string& studentId, const std::string& subjectId){
    Score sc;
    if(findScore(studentId, subjectId, sc)) return sc.score;
    return -1; // 未录入
}

int getStudentTotal(const std::string& studentId){
    std::vector<SubjectScore> detail = getStudentScoreDetail(studentId);
    if(detail.empty()) return -1;
    int total = 0;
    for(const SubjectScore& d : detail) total += d.score;
    return total;
}

double getStudentAverage(const std::string& studentId){
    std::vector<SubjectScore> detail = getStudentScoreDetail(studentId);
    if(detail.empty()) return -1;
    int total = 0;
    for(const SubjectScore& d : detail) total += d.score;
    return (double)total / detail.size();
}

double getStudentGpa(const std::string& studentId){
    int totalCredit = 0;
    double totalPoints = 0;
    for(const SubjectScore& d : getStudentScoreDetail(studentId)){
        totalCredit += d.credit;
        totalPoints += scoreToGpa(d.score) * d.credit;
    }
    if(totalCredit == 0) return -1;
    return totalPoints / totalCredit;
}

int getClassSize(const std::string& studentId){
    StudentUser me;
    if(!findStudent(studentId, me)) return -1;
    int size = 0;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() == me.getStudentClass()) size++;
    }
    return size;
}

// 排名规则：数一数同班有几个人比我高，名次 = 比我高的人数 + 1（同分并列同名次）
int getClassTotalRank(const std::string& studentId){
    StudentUser me;
    if(!findStudent(studentId, me)) return -1;
    int myTotal = getStudentTotal(studentId);
    int rank = 1;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() != me.getStudentClass()) continue;
        if(getStudentTotal(s.getAccount()) > myTotal) rank++;
    }
    return rank;
}

int getClassAverageRank(const std::string& studentId){
    StudentUser me;
    if(!findStudent(studentId, me)) return -1;
    double myAvg = getStudentAverage(studentId);
    int rank = 1;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() != me.getStudentClass()) continue;
        if(getStudentAverage(s.getAccount()) > myAvg) rank++;
    }
    return rank;
}

int getSubjectRank(const std::string& studentId, const std::string& subjectId){
    StudentUser me;
    if(!findStudent(studentId, me)) return -1;
    int myScore = getStudentSubjectScore(studentId, subjectId);
    if(myScore < 0) return -1; // 未录入
    int rank = 1;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() != me.getStudentClass()) continue;
        if(getStudentSubjectScore(s.getAccount(), subjectId) > myScore) rank++;
    }
    return rank;
}

// 班级各科统计：平均/最高/最低/及格/不及格/及格率（未录入不参与）
std::vector<ClassSubjectStat> getClassSubjectStats(const std::string& classId){
    std::vector<ClassSubjectStat> result;
    for(const Subject& sub : getAllSubjects()){
        int count = 0, total = 0, max = -1, min = 101, pass = 0, fail = 0;
        for(const StudentUser& s : getAllStudents()){
            if(s.getStudentClass() != classId) continue;
            int score = getStudentSubjectScore(s.getAccount(), sub.id);
            if(score < 0) continue; // 未录入不参与
            count++;
            total += score;
            if(score > max) max = score;
            if(score < min) min = score;
            if(score >= 60) pass++; else fail++;
        }
        if(count == 0) continue; // 这科没人录过，不出现
        ClassSubjectStat stat;
        stat.subject_id = sub.id;
        stat.subject_name = sub.name;
        stat.average = (double)total / count;
        stat.max = max;
        stat.min = min;
        stat.passCount = pass;
        stat.failCount = fail;
        stat.count = count;
        stat.passRate = (double)pass / count * 100;
        result.push_back(stat);
    }
    return result;
}

// 班级排名表：按总分或平均分排序，升降序可选
std::vector<StudentRankItem> getClassRankList(const std::string& classId, bool byTotal, bool ascending){
    std::vector<StudentRankItem> list;
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() != classId) continue;
        StudentRankItem item;
        item.student_id = s.getAccount();
        item.student_name = s.getStudentName();
        item.total = getStudentTotal(s.getAccount());
        item.average = item.total < 0 ? -1 : getStudentAverage(s.getAccount());
        list.push_back(item);
    }
    std::sort(list.begin(), list.end(), [byTotal, ascending](const StudentRankItem& a, const StudentRankItem& b){
        double va = byTotal ? (double)a.total : a.average;
        double vb = byTotal ? (double)b.total : b.average;
        return ascending ? (va < vb) : (va > vb);
    });
    return list;
}

// 班级成绩梯队：按平均分分档，无成绩的不参与
std::vector<int> getClassTiers(const std::string& classId){
    std::vector<int> tiers(5, 0); // 优秀/良好/中等/及格/不及格
    for(const StudentUser& s : getAllStudents()){
        if(s.getStudentClass() != classId) continue;
        double avg = getStudentAverage(s.getAccount());
        if(avg < 0) continue;
        if(avg >= 90) tiers[0]++;
        else if(avg >= 80) tiers[1]++;
        else if(avg >= 70) tiers[2]++;
        else if(avg >= 60) tiers[3]++;
        else tiers[4]++;
    }
    return tiers;
}
