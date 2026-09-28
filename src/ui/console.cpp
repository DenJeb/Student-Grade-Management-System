// ===== 控制台工具：菜单、输入、清屏、暂停 =====
#include "console.h"
#include "validation.h"
#include <iostream>
#include <cstdlib>


// 打印带标题的菜单
void printMenu(const std::string& title, const std::vector<std::string>& options){
    std::cout << "===== " << title << " =====\n";
    for(size_t i = 0; i < options.size(); i++)
        std::cout << i + 1 << ". " << options[i] << "\n";
}

// 读一行文本
std::string inputString(const std::string& prompt){
    std::cout << prompt;
    std::string text;
    std::getline(std::cin, text);
    return text;
}

// 读整数，非数字重输
int inputInt(const std::string& prompt){
    while(true){
        std::string text = inputString(prompt);
        if(isInt(text)) return std::stoi(text);
        std::cout << "输入无效，请输入整数\n";
    }
}

// 读 [min,max] 选项
int inputChoice(const std::string& prompt, int min, int max){
    while(true){
        int choice = inputInt(prompt);
        if(choice >= min && choice <= max) return choice;
        std::cout << "输入无效，请输入 " << min << "~" << max << " 之间的数字\n";
    }
}

// 按回车继续
void pause(){
    inputString("按回车键继续...");
}

// 清屏
void clearScreen(){
    system("cls");
}