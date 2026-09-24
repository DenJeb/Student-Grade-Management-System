// ===== 账号与登录记录读写 =====
#include "user_repo.h"
#include "file_io.h"


// 读取 account.csv 文件
std::vector<User> loadUsers(){
    std::vector<User> users;
    for(const std::string& line : readLine("data/accounts.csv")){
        std::vector<std::string> f = split(line, ',');
        if(f.size() < 5) continue;
        User u(f[0], f[1], stringToRole(f[2]), f[3] == "1", f[4]);
        users.push_back(u);
    }
    return users;
}

// 写入 account.csv 文件
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
    return readLine("data/login_records.csv");
}

// 追加登录记录
void appendLoginRecords(const std::string& account, const std::string& time, const std::string& result){
    appendLine("data/login_records.csv", join({account, time, result}, ','));
}