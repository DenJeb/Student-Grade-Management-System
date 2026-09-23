// ===== 通用文件读写 =====
#include "file_io.h"
#include <fstream>


// 读取文件行列表
std::vector<std::string> readLine(const std::string& path){
    std::vector<std::string> lines;
    std::ifstream in(path); // 读取文件
    if(!in) return lines; // 文件不存在返回空列表

    std::string line;
    bool first = true;
    while(std::getline(in, line)){
        if(first){
            first = false;
            if(line.size() >= 3 
            && (unsigned char)line[0] == 0xEF 
            && (unsigned char)line[1] == 0xBB 
            && (unsigned char)line[2] == 0xBF){
                line.erase(0, 3); // 移除BOM
            }
        }
        if(!line.empty()) lines.push_back(line);
    }
    return lines;
}

// 写文件
void writeLines(const std::string& path, const std::vector<std::string>& lines){
    std::ofstream out(path); // 写入文件
    for(const std::string& line : lines)
        out << line << "\n";
}

// 追加一行
void appendLine(const std::string& path, const std::string& line){
    std::ofstream out(path, std::ios::app); // 追加文件
    out << line << "\n";
}

// 按分隔符拆分字符串
std::vector<std::string> split(const std::string& s, char delimiter){
    std::vector<std::string> fields;
    size_t start = 0;
    while(start <= s.size()){
        size_t end = s.find(delimiter, start);
        if(end == std::string::npos) end = s.size(); // 找不到分隔符，直到字符串结束
        fields.push_back(s.substr(start, end - start)); // 提取字段
        start = end + 1;
    }
    return fields;
}

// 按分隔符合并字符串
std::string join(const std::vector<std::string>& fields, char delimiter){
    std::string result;
    for(size_t i = 0; i < fields.size(); i++){
        if(i > 0) result += delimiter;
        result += fields[i];
    }
    return result;
}