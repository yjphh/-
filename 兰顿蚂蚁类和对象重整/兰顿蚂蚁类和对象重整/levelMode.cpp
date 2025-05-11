#include"levelMode.h"
#include"gameHomepage.h"
#include <iostream> 
#include<windows.h>
#include<iomanip>


double LevelMode::compareBoard(int _userOne[], int _initialOne[], int _size,bool shouldPrint)
{
    if (shouldPrint==true)
    {
        std::cout << "初始棋盘如下：" << std::endl;
        for (int i = 0; i < _size; i++)
        {
            for (int j = 0; j < _size; j++)
            {
                std::cout << _initialOne[i * _size + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "用户作答如下：" << std::endl;
        for (int i = 0; i < _size; i++)
        {
            for (int j = 0; j < _size; j++)
            {
                std::cout << _userOne[i * _size + j] << " ";
            }
            std::cout << std::endl;
        }
    }
        double counter = 0;
        for (int i = 0; i < _size * _size; i++)
        {
            if (_userOne[i] == _initialOne[i])
            {
                counter++;
            }
        }
        double accuracyRate = counter / (_size * _size);
        if (shouldPrint==true)
        {
            std::cout << "相似率为：" <<std::fixed<<std::setprecision(3)<< accuracyRate << std::endl;
        }
    return accuracyRate;
}


int LevelMode::judgeBoard(int _userOne[], int _initialOne[], int _size)
{
    for (int i = 0; i < _size * _size; i++)
    {
        if (_userOne[i] != _initialOne[i])
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // 设置文本颜色为红色
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::cout << "回答错误！" << std::endl;
            // 恢复默认颜色
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return 0;
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 设置文本颜色为绿色
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    std::cout << "恭喜您，回答正确！" << std::endl;
    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 1;
}

void LevelMode::stageBoard(int _stage, int _diffic, User& user)
{
    switch (_stage)
    {
    case 1:
    {
        switch (_diffic)
        {
        case 1:
        {
            int initialOne1[4] = { 0,0,0,0 };
            int finalOne1[4] = { 0,1,1,1 };
            int userOne1[4] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cout << finalOne1[i * 2 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：2*2棋盘，已走5步，蚂蚁位置（1，0），蚂蚁朝向UP" << std::endl;
            std::cout << "请用户开始作答，输入原始棋盘" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cin >> userOne1[i * 2 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 2);
            compareBoard(userOne1, initialOne1, 2);
            std::cout << "游戏用时：" <<std::fixed<<std::setprecision(2)<< elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 2,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        case 2:
        {
            int initialOne1[4] = { 0,0,0,0 };
            int finalOne1[4] = { 1,0,1,0 };
            int userOne1[4] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cout << finalOne1[i * 2 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：2*2棋盘，已走10步，蚂蚁位置（1，1），蚂蚁朝向LEFT" << std::endl;
            std::cout << "请用户开始作答，输入原始棋盘" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cin >> userOne1[i * 2 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 2);
            compareBoard(userOne1, initialOne1, 2);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 2,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        case 3:
        {
            int initialOne1[4] = { 0,0,0,0 };
            int finalOne1[4] = { 1,1,1,1 };
            int userOne1[4] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cout << finalOne1[i * 2 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：2*2棋盘，已走20步，蚂蚁位置（0，0），蚂蚁朝向RIGHT" << std::endl;
            std::cout << "请用户开始作答，输入原始棋盘" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cin >> userOne1[i * 2 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 2);
            compareBoard(userOne1, initialOne1, 2);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 2,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        }
        break;
    }
    case 2:
    {
        switch (_diffic)
        {
        case 1:
        {
            int initialOne1[9] = { 0,0,1,0,0,1,1,0,1 };
            int finalOne1[9] = { 1,0,1,0,0,1,0,1,1 };
            int userOne1[9] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << finalOne1[i * 3 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：3*3棋盘，已走5步，蚂蚁位置（2，1），蚂蚁朝向DOWN" << std::endl;
            std::cout << "请用户开始作答，输入原始棋盘" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cin >> userOne1[i * 3 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 3);
            compareBoard(userOne1, initialOne1, 3);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 3,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        case 2:
        {
            int initialOne1[9] = { 0,0,1,0,0,1,1,0,1 };
            int finalOne1[9] = { 1,1,1,0,1,0,0,0,0 };
            int userOne1[9] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << finalOne1[i * 3 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：3*3棋盘，已走10步，蚂蚁位置（0，2），蚂蚁朝向RIGHT" << std::endl;
            std::cout << "请用户开始作答" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cin >> userOne1[i * 3 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 3);
            compareBoard(userOne1, initialOne1, 3);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 3,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        case 3:
        {
            int initialOne1[9] = { 0,0,1,0,0,1,1,0,1 };
            int finalOne1[9] = { 1,1,1,0,1,0,0,0,0 };
            int userOne1[9] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << finalOne1[i * 3 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：3*3棋盘，已走20步，蚂蚁位置（0，2），蚂蚁朝向RIGHT" << std::endl;
            std::cout << "请用户开始作答" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cin >> userOne1[i * 3 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 3);
            compareBoard(userOne1, initialOne1, 3);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 3,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        }
        break;
    }
    case 3:
    {
        switch (_diffic)
        {
        case 1:
        {
            int initialOne1[16] = { 0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0 };
            int finalOne1[16] = { 1,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0 };
            int userOne1[16] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << finalOne1[i * 4 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：4*4棋盘，已走5步，蚂蚁位置（3,0），蚂蚁朝向DOWN" << std::endl;
            std::cout << "请用户开始作答" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cin >> userOne1[i * 4 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 4);
            compareBoard(userOne1, initialOne1, 4);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 4,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        case 2:
        {
            int initialOne1[16] = { 0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0 };
            int finalOne1[16] = { 1,0,0,0,0,0,1,0,0,1,1,1,1,0,1,0 };
            int userOne1[16] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << finalOne1[i * 4 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：4*4棋盘，已走10步，蚂蚁位置（3，0），蚂蚁朝向LEFT" << std::endl;
            std::cout << "请用户开始作答" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cin >> userOne1[i * 4 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 4);
            compareBoard(userOne1, initialOne1, 4);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 4,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        case 3:
        {
            int initialOne1[16] = { 0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0 };
            int finalOne1[16] = { 1,0,0,0,0,0,1,0,0,1,1,1,1,0,1,0 };
            int userOne1[16] = { 0 };
            std::cout << "蚁行图如下" << std::endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << finalOne1[i * 4 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "已知：4*4棋盘，已走20步，蚂蚁位置（3,0），蚂蚁朝向LEFT" << std::endl;
            std::cout << "请用户开始作答" << std::endl;
            std::clock_t start_time = std::clock();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cin >> userOne1[i * 4 + j];
                }
            }
            std::clock_t end_time = std::clock();
            double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            judgeBoard(userOne1, initialOne1, 4);
            compareBoard(userOne1, initialOne1, 4);
            std::cout << "游戏用时：" << std::fixed << std::setprecision(2) << elapsed_time << "秒" << std::endl;
            double accuracy = compareBoard(userOne1, initialOne1, 4,0);
            GameRecord record(user.getUsername(), _stage, _diffic, elapsed_time, accuracy);
            user.isSave(record);
            break;
        }
        }
        break;
    }
    }
}

void LevelMode::chooseStage(User& user)
{
    std::cout << "欢迎来到闯关模式" << std::endl;
    std::cout << "请注意：本模式下，请选择您想参与的关卡和难度，然后电脑会打印对应的蚁行图供您作答" << std::endl;
    std::cout << "请输入您想参与的关卡（输入阿拉伯数字1、2、3)和难度（1低、2中、3高）" << std::endl;
    int stages = 0;
    int difficulty = 0;
    std::cin >> stages >> difficulty;
    switch (stages)
    {
    case 1:
    {
        std::cout << "您选择的是第一关" << std::endl;
        switch (difficulty)
        {
        case 1:
        {
            std::cout << "您选择的是低难度" << std::endl;
            stageBoard(1, 1, user);
            user.displayRecords();
            break;
        }
        case 2:
        {
            std::cout << "您选择的是中难度" << std::endl;
            stageBoard(1, 2, user);
            user.displayRecords();
            break;
        }
        case 3:
        {
            std::cout << "您选择的是高难度" << std::endl;
            stageBoard(1, 3, user);
            user.displayRecords();
            break;
        }
        }
        break;
    }
    case 2:
    {
        std::cout << "您选择的是第二关" << std::endl;
        switch (difficulty)
        {
        case 1:
        {
            std::cout << "您选择的是低难度" << std::endl;
            stageBoard(2, 1, user);
            user.displayRecords();
            break;
        }
        case 2:
        {
            std::cout << "您选择的是中难度" << std::endl;
            stageBoard(2, 2, user);
            user.displayRecords();
            break;
        }
        case 3:
        {
            std::cout << "您选择的是高难度" << std::endl;
            stageBoard(2, 3, user);
            user.displayRecords();
            break;
        }
        }
        break;
    }
    case 3:
    {
        std::cout << "您选择的是第三关" << std::endl;
        switch (difficulty)
        {
        case 1:
        {
            std::cout << "您选择的是低难度" << std::endl;
            stageBoard(3, 1, user);
            user.displayRecords();
            break;
        }
        case 2:
        {
            std::cout << "您选择的是中难度" << std::endl;
            stageBoard(3, 2, user);
            user.displayRecords();
            break;
        }
        case 3:
        {
            std::cout << "您选择的是高难度" << std::endl;
            stageBoard(3, 3, user);
            user.displayRecords();
            break;
        }
        }
        break;
    }
    default:
    {
        std::cout << "您输入的关卡不存在，请重新输入" << std::endl;
        chooseStage(user);
    }
    }
    
    std::cout << "是否查看你的所有闯关记录？（yes/no）" << std::endl;
    std::string choice;
    std::cin >> choice;
    std::string username1 = user.getUsername();
    while(choice == "yes")
    {
        user.printAllRecordsFromFile(username1);
        std::cout << "是否删除某条游戏记录？（yes/no）" << std::endl;
        std::cin >> choice;
        while (choice == "yes")
        {
            std::cout << "请输入你想删除的游戏记录序号" << std::endl;
            int index;
            std::cin >> index;
            user.deleteRecord(index + 1);
            std::cout << "是否继续删除？（yes/no）" << std::endl;
            std::cin >> choice;
        }
        std::cout << "是否再次查看你的所有闯关记录？（yes/no）" << std::endl;
        std::cin >> choice;
    }
}