#include "user.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include<conio.h>
#include <chrono>
#include<iomanip>
#include <cstdio> // 用于remove和rename函数


std::string User::getpassword() 
{
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r')//用户按下回车键时停止输入
    {
        if (ch == '\b')//处理退格键
        {
            if (!password.empty())
            {
                password.pop_back();//删除最后一个字符
                std::cout << "\b \b";//回退光标
            }
        }
        else
        {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}
void User::userRegister(const std::string& _username,const std::string& _password) {
    std::string filename = username + ".txt";
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << _password << std::endl;//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

        std::cout << "注册成功" << std::endl;
        outFile.close();
    }
    else {
        std::cout << "注册失败" << std::endl;
    }
}
bool User::forgotPassword()
{
    std::string newPassword;
    std::cout << "请输入新的密码（该密码直接替换原密码，不会影响您的游戏记录）" << std::endl;
    newPassword=getpassword();
    std::string filename = username + ".txt";
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cout << "无法打开文件" << std::endl;
        return false;
    }
    std::vector<std::string>lines;//用来存储新的密码和原来的游戏记录
    std::string line;//用于ifstream的指针标记读取行数
    //读取第一行（密码）
    if (std::getline(inFile, line))
    {
        lines.push_back(newPassword);
    }
    //读取剩余行（用户原来的游戏记录）
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close();
    std::ofstream outFile(filename);//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
    if (!outFile.is_open())
    {
        std::cout << "无法打开文件进行写入" << std::endl;
        return false;
    }
    //将修改后的内容重新传入文件
    for (const auto& l : lines)
    {
        outFile << l << std::endl;
    }
    outFile.close();
    std::cout << "密码修改成功，请使用新密码登录" << std::endl;
    return true;
}

bool User::userLogin( std::string& _password) 
{
    // 检查用户名是否在 allUsername.txt 中，如果文件不存在则创建
    bool usernameExists = false;
    std::ifstream inFile("allUsername.txt");

    // 如果文件存在，检查用户名是否已存在
    if (inFile.is_open()) {
        std::string _username;
        while (inFile >> _username) {
            if (_username == username) {
                usernameExists = true;
                break;
            }
        }
        inFile.close();
    }

    // 如果用户名不存在，写入 allUsername.txt
    if (!usernameExists) {
        std::ofstream outFile("allUsername.txt", std::ios::app);
        if (!outFile.is_open()) {
            std::cout << "无法创建或写入 allUsername.txt" << std::endl;
            return false;
        }
        outFile << username << std::endl;
        outFile.close();
    }


    int attempts = 3;
    while (attempts > 0)
    {
        std::string filename = username + ".txt";
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cout << "登录失败！用户未注册" << std::endl;
            return false;
        }

        std::string  storedPassword;
        inFile >> storedPassword;
        inFile.close();

        if (storedPassword == _password) 
        {
            std::cout << "登录成功！欢迎 " << username << " 的到来！" << std::endl;
            return true;
        }
        else
        {
            attempts--;
            std::cout << "登录失败！密码错误,你还有" <<attempts<<"次尝试机会" << std::endl;
            if (attempts > 0)
            {
                std::cout << "请输入您的选择：" << std::endl;
                std::cout << "1、重新输入" << std::endl;
                std::cout << "2、忘记密码" << std::endl;
                int choice = 0;
                std::cin >> choice;
                if (choice == 1)
                {
                    std::string password;
                    std::cout << "请再次输入密码:" << std::endl;
                    password = getpassword();
                    _password = password;
                }
                if (choice == 2)
                {
                    if (forgotPassword())
                    {
                        attempts = 3;//重置输入密码的尝试次数
                        std::cout << "请再次输入密码：" << std::endl;
                        std::string password;
                        password = getpassword();
                        _password = password;
                    }
                }
            }
        }
    }
    std::cout << "尝试次数已用完，登录失败,用户无法正常开启游戏" << std::endl;
    return false;
}

void User::addRecord(const GameRecord& record) 
{

    GameRecord recordwithTime = record;
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // 格式化时间（例如：2023-10-25 14:30:45）
    std::tm tm_struct;
    if (localtime_s(&tm_struct, &now_time) != 0) {
        std::cerr << "无法获取本地时间" << std::endl;
        return;
    }
    std::stringstream time_stream;
    time_stream << std::put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    recordwithTime.timestamp = time_stream.str();

    records.push_back(recordwithTime);
    std::ofstream outFile(username + ".txt",std::ios::app);//11111111111111111111111111111111111111111111111111111111111111111111111
    if (outFile.is_open())
    {
        outFile <<username << " ";
        outFile << recordwithTime.stage <<" ";
        outFile << recordwithTime.difficulty <<" ";
        outFile << recordwithTime.elapsedTime <<" ";
        outFile << recordwithTime.accuracy << " ";
        outFile << recordwithTime.timestamp << std::endl;  // 添加时间戳
        outFile.close();
    }
    else
    {
        std::cerr << "无法打开文件保存游戏记录。" << std::endl;
    }
}

void User::displayRecords() //显示同一次登录中用户选择保存的游戏记录
{
    if (records.empty())
    {
        std::cout << "本次游戏暂无记录" << std::endl;
    }
    else 
    {
        for (const auto& record : records)
        {
            for (auto record : records) 
            {
                std::cout << "用户:" << std::setw(6) << std::left << record.username << " ";  // 固定用户名宽度
                std::cout << "关卡:第" << std::setw(1) << record.stage << "关" << " ";
                std::cout << "难度(1低、2中、3高):" << std::setw(1) << record.difficulty << " ";
                std::cout << "用时:" << std::setw(6) << std::left << record.elapsedTime << "秒  ";  // 固定用时宽度
                std::cout << "正确率:" << std::setw(6) << std::left << record.accuracy * 100 << "%" <<" ";
                std::cout << "时间:" << record.timestamp << std::endl;
            }
        }
    }
}

void User::printAllRecordsFromFile(const std::string& _username) {
    std::ifstream readFile(_username + ".txt");
    if (!readFile.is_open()) {
        std::cerr << "无法打开文件读取游戏记录。" << std::endl;
        return;
    }
    // 跳过第一行（密码）
    std::string passwordLine;
    std::getline(readFile, passwordLine);  // 读取并丢弃第一行

    std::vector<GameRecord> Records;
    std::string line;
    while (std::getline(readFile, line))
    {  // 逐行读取剩余内容
        std::istringstream iss(line);
        std::string name, timestamp;
        int stage, diff;
        double time, accuracy;

        // 按顺序解析字段
        if (iss >> name >> stage >> diff >> time >> accuracy)
        {
            // 读取时间戳（剩余部分作为整体）
            std::getline(iss >> std::ws, timestamp);  // std::ws 跳过前导空格

            GameRecord record1(name, stage, diff, time, accuracy);
            record1.timestamp = timestamp;
            Records.push_back(record1);
        }
    }
    readFile.close();
    int a = 1;
    std::cout << "该用户所有闯关记录如下：" << std::endl;
    if (Records.empty())
    {
        std::cout << "该用户暂无闯关记录！" << std::endl;
        return;
    }
    for (auto record : Records)
    {
        std::cout << a++ << "、";
        std::cout << "用户:" << std::setw(6) << std::left << record.username << " ";  // 固定用户名宽度
        std::cout << "关卡:第" << std::setw(1) << record.stage << "关" << " ";
        std::cout << "难度(1低、2中、3高):" << std::setw(1) << record.difficulty << " ";
        std::cout << "用时:" << std::setw(6) << std::left << record.elapsedTime << "秒  ";  // 固定用时宽度
        std::cout << "正确率:" << std::setw(6) << std::left << record.accuracy * 100 << "%"<<" ";
        std::cout << "时间:" << record.timestamp << std::endl;
    }
}

void User::isSave(const GameRecord& record)
{
    std::cout << "是否保存？（yes/no）" << std::endl;
    std::string choice;
    std::cin >> choice;
    if (choice == "yes")
    {
       addRecord(record);
       std::cout << "保存成功！" << std::endl;
    }
    else
    {
        std::cout << "本次游戏不保存" << std::endl;
        return;
    }
}

void User::deleteRecord(int _line)
{
    std::ifstream input(username + ".txt");
    if (!input.is_open()) {
        std::cerr << "无法打开输入文件: " << username + ".txt" << std::endl;
        return;
    }
    //创建临时文件
    std::string filePath = username + ".txt";
    std::string tempFilePath = filePath + ".tmp";
    std::ofstream tempFile(tempFilePath);
    if (!tempFile.is_open()) {
        std::cerr << "无法创建临时文件" << std::endl;
        input.close();
        return;
    }

    std::string line;
    int currentLine = 1;
    bool lineDeleted = false;

    // 逐行读取原文件
    while (std::getline(input, line)) {
        // 如果不是要删除的行，则写入临时文件
        if (currentLine != _line) 
        {
            tempFile << line << std::endl;
        }
        else 
        {
            lineDeleted = true;
        }
        currentLine++;
    }

    // 关闭文件流
    input.close();
    tempFile.close();

    // 如果找到了要删除的行，则替换原文件
    if (lineDeleted) {
        // 删除原文件
        if (std::remove(filePath.c_str()) != 0) {
            std::cerr << "删除原文件失败" << std::endl;
            return ;
        }
        else
        {
            std::cout << "游戏记录" << _line - 1 << "已被删除" << std::endl;
        }

        // 重命名临时文件为原文件名
        if (std::rename(tempFilePath.c_str(), filePath.c_str()) != 0) {
            std::cerr << "重命名临时文件失败" << std::endl;
            return ;
        }
    }
    else 
    {
        // 没有找到要删除的行，删除临时文件
        std::remove(tempFilePath.c_str());
        std::cerr << "该条游戏记录不存在！" << std::endl;
        return ;
    }
}