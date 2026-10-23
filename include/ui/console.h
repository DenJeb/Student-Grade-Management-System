// ===== 控制台工具：菜单、输入、清屏、暂停 =====
#pragma once
#include <string>
#include <vector>


void printMenu(const std::string& title, const std::vector<std::string>& options); // 打印带标题的菜单
std::string inputString(const std::string& prompt);                                // 读一行文本
int inputInt(const std::string& prompt);                                           // 读整数，非数字重输
int inputChoice(const std::string& prompt, int min, int max);                      // 读 [min,max] 选项
void pause();                                                                      // 按回车继续
void clearScreen();                                                                // 清屏
bool confirm(const std::string& message);                                          // 危险操作确认：输入 y/Y 返回 true