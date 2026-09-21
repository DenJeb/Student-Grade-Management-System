// ===== 数字与区间校验 =====
#include "validation.h"


// 判断字符串是否为纯整数
bool isInt(const std::string& text){
    if(text.empty()) return false;

    size_t start = (text[0] == '-') ? 1 : 0;
    if(start >= text.size()) return false;

    for(size_t i = start; i < text.size(); i++)
        if(text[i] < '0' || text[i] > '9')
            return false;

    return true;
}

// 判断字符串是否为整数
bool isNumber(const std::string& text){
    if(text.empty()) return false;

    bool dot = false; // 小数点
    size_t start = (text[0] == '-') ? 1 : 0;
    if(start >= text.size()) return false;

    for(size_t i = start; i < text.size(); i++){
        if(text[i] >= '0' && text[i] <= '9') continue;
        if(text[i] == '.' && !dot){
            dot = true;
            continue;
        }
        return false;
    }

    return true;
}

// 判断值是否在 [min, max] 内
bool inRange(int value, int min, int max){
    return (value >= min && value <= max);
}