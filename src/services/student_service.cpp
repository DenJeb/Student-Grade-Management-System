// ===== 学生、班级、科目维护 =====
#include "student_service.h"
#include "student_repo.h"
#include "class_repo.h"
#include "subject_repo.h"


// ==================== 学生 ====================

std::vector<StudentUser> getAllStudents(){
    return loadStudents();
}

// 模糊检索：学号或姓名包含关键字
std::vector<StudentUser> searchStudents(const std::string& keyword){
    std::vector<StudentUser> result;
    for(const StudentUser& s : loadStudents()){
        if(s.getAccount().find(keyword) != std::string::npos ||
           s.getStudentName().find(keyword) != std::string::npos){
            result.push_back(s);
        }
    }
    return result;
}

bool findStudent(const std::string& account, StudentUser& out){
    for(const StudentUser& s : loadStudents()){
        if(s.getAccount() == account){
            out = s;
            return true;
        }
    }
    return false;
}

bool addStudent(const StudentUser& s){
    std::vector<StudentUser> students = loadStudents();
    for(const StudentUser& x : students){
        if(x.getAccount() == s.getAccount()) return false; // 学号已存在
    }
    students.push_back(s);
    saveStudents(students);
    return true;
}

bool deleteStudent(const std::string& account){
    std::vector<StudentUser> students = loadStudents();
    for(size_t i = 0; i < students.size(); i++){
        if(students[i].getAccount() == account){
            students.erase(students.begin() + i);
            saveStudents(students);
            return true;
        }
    }
    return false;
}

bool updateStudent(const std::string& account, const StudentUser& s){
    std::vector<StudentUser> students = loadStudents();
    for(StudentUser& x : students){
        if(x.getAccount() == account){
            x = s; // 整体替换
            saveStudents(students);
            return true;
        }
    }
    return false;
}

// ==================== 教师边界 ====================

// 教师所辖班级编号（classes.csv 里班主任工号 = 教师账号）
std::vector<std::string> getTeacherClassIds(const std::string& teacherId){
    std::vector<std::string> ids;
    for(const ClassInfo& c : loadClasses()){
        if(c.teacher_id == teacherId) ids.push_back(c.id);
    }
    return ids;
}

// 教师是否管辖该学生：学生所在班级的班主任是不是他
bool teacherOwnsStudent(const std::string& teacherId, const std::string& account){
    StudentUser s;
    if(!findStudent(account, s)) return false;
    for(const ClassInfo& c : loadClasses()){
        if(c.id == s.getStudentClass() && c.teacher_id == teacherId) return true;
    }
    return false;
}

// 教师检索：先模糊检索，再过滤掉非所辖班级的学生
std::vector<StudentUser> teacherSearchStudents(const std::string& keyword, const std::string& teacherId){
    std::vector<std::string> classIds = getTeacherClassIds(teacherId);
    std::vector<StudentUser> result;
    for(const StudentUser& s : searchStudents(keyword)){
        for(const std::string& id : classIds){
            if(s.getStudentClass() == id){
                result.push_back(s);
                break;
            }
        }
    }
    return result;
}

// ==================== 班级 ====================

std::vector<ClassInfo> getAllClasses(){
    return loadClasses();
}

bool findClass(const std::string& id, ClassInfo& out){
    for(const ClassInfo& c : loadClasses()){
        if(c.id == id){
            out = c;
            return true;
        }
    }
    return false;
}

bool addClass(const ClassInfo& c){
    std::vector<ClassInfo> classes = loadClasses();
    for(const ClassInfo& x : classes){
        if(x.id == c.id) return false; // 编号已存在
    }
    classes.push_back(c);
    saveClasses(classes);
    return true;
}

bool deleteClass(const std::string& id){
    std::vector<ClassInfo> classes = loadClasses();
    for(size_t i = 0; i < classes.size(); i++){
        if(classes[i].id == id){
            classes.erase(classes.begin() + i);
            saveClasses(classes);
            return true;
        }
    }
    return false;
}

bool updateClass(const std::string& id, const ClassInfo& c){
    std::vector<ClassInfo> classes = loadClasses();
    for(ClassInfo& x : classes){
        if(x.id == id){
            x = c; // 整体替换（含班主任关联）
            saveClasses(classes);
            return true;
        }
    }
    return false;
}

// ==================== 科目 ====================

std::vector<Subject> getAllSubjects(){
    return loadSubjects();
}

bool findSubject(const std::string& id, Subject& out){
    for(const Subject& s : loadSubjects()){
        if(s.id == id){
            out = s;
            return true;
        }
    }
    return false;
}

bool addSubject(const Subject& s){
    std::vector<Subject> subjects = loadSubjects();
    for(const Subject& x : subjects){
        if(x.id == s.id) return false; // 编号已存在
    }
    subjects.push_back(s);
    saveSubjects(subjects);
    return true;
}

bool deleteSubject(const std::string& id){
    std::vector<Subject> subjects = loadSubjects();
    for(size_t i = 0; i < subjects.size(); i++){
        if(subjects[i].id == id){
            subjects.erase(subjects.begin() + i);
            saveSubjects(subjects);
            return true;
        }
    }
    return false;
}

bool updateSubject(const std::string& id, const Subject& s){
    std::vector<Subject> subjects = loadSubjects();
    for(Subject& x : subjects){
        if(x.id == id){
            x = s; // 整体替换
            saveSubjects(subjects);
            return true;
        }
    }
    return false;
}
