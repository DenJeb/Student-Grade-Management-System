// ===== 管理员账号管理 =====
#include "account_service.h"
#include "user_repo.h"
#include "auth_service.h"


// 新增账号：账号已存在则失败
bool addAccount(const std::string& account, const std::string& password, Role role){
    std::vector<User> users = loadUsers();
    for(const User& u : users){
        if(u.getAccount() == account) return false;
    }
    User u(account, password, role, true, currentTime());
    users.push_back(u);
    saveUsers(users);
    return true;
}

// 删除账号
bool deleteAccount(const std::string& account){
    std::vector<User> users = loadUsers();
    for(size_t i = 0; i < users.size(); i++){
        if(users[i].getAccount() == account){
            users.erase(users.begin() + i);
            saveUsers(users);
            return true;
        }
    }
    return false;
}

// 禁用/启用账号
bool setAccountActive(const std::string& account, bool active){
    std::vector<User> users = loadUsers();
    for(User& u : users){
        if(u.getAccount() == account){
            u.setActive(active);
            saveUsers(users);
            return true;
        }
    }
    return false;
}

// 重置密码
bool resetPassword(const std::string& account, const std::string& newPassword){
    std::vector<User> users = loadUsers();
    for(User& u : users){
        if(u.getAccount() == account){
            u.setPassword(newPassword);
            saveUsers(users);
            return true;
        }
    }
    return false;
}

// 按角色查账号列表
std::vector<User> getUsersByRole(Role role){
    std::vector<User> result;
    for(const User& u : loadUsers()){
        if(u.getRole() == role) result.push_back(u);
    }
    return result;
}
