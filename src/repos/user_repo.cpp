// ===== 账号与登录记录读写 =====
#include "user_repo.h"
#include "file_io.h"
#include <fstream>


// 读取 accounts.csv 文件
std::vector<User> loadUsers(){
    std::vector<User> users;
    bool first = true;
    for(const std::string& line : readLine("data/accounts.csv")){
        if(first){
            first = false;
            continue;
        } // 跳过表头
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 5) continue;
        User u(f[0], f[1], stringToRole(f[2]), f[3] == "1", f[4]);
        users.push_back(u);
    }
    return users;
}

// 写入 accounts.csv 文件
void saveUsers(const std::vector<User>& users){
    std::vector<std::string> lines;
    for(const User& u : users){
        lines.push_back(join({u.getAccount(), 
                             u.getPassword(), 
                             roleToString(u.getRole()), 
                             u.getActive() ? "1" : "0", 
                             u.getCreateTime()}, 
                            ','));
    }
    writeLines("data/accounts.csv", lines);
}

// 读取 login_records.csv 文件
std::vector<std::string> loadLoginRecords(){
    std::vector<std::string> records;
    bool first = true;
    for(const std::string& line : readLine("data/login_records.csv")){
        if(first){
            first = false;
            continue;
        } // 跳过表头
        records.push_back(line);
    }
    return records;
}

// 追加登录记录（文件不存在时先补表头，避免第一条记录被当表头跳过）
void appendLoginRecords(const std::string& account, const std::string& time, const std::string& result){
    std::ifstream check("data/login_records.csv");
    if(!check.good()) appendLine("data/login_records.csv", "账号,时间,登录结果");
    check.close();
    appendLine("data/login_records.csv", join({account, time, result}, ','));
}