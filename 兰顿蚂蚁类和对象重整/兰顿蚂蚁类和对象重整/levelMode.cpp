#include"levelMode.h"
#include"gameHomepage.h"
#include <iostream> 
#include<windows.h>
#include<iomanip>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include<algorithm>


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

bool LevelMode::isBetter(const GameRecord& current, const GameRecord& others)
{
    if (others.accuracy > current.accuracy)
    {
        return true;
    }
    if (others.accuracy == current.accuracy && others.elapsedTime < current.elapsedTime)
    {
        return true;
    }
    return false;
}

//返回一个数组，该数组是所有用户在该关卡和难度下的最佳记录
std::vector<GameRecord> LevelMode::findAllBestRecords(const std::vector<GameRecord>& records)
{
    std::map<std::string, GameRecord>bestRecord;//用映射关系存储不同用户的最佳记录
    for (const auto& record : records)
    {
        //如果该用户还没有记录，或者当前记录更好，则更新
        if (bestRecord.find(record.username) == bestRecord.end() || isBetter(bestRecord[record.username], record))
        {
            bestRecord[record.username] = record;
        }
    }

    //将map中的值提取到vector中
    std::vector<GameRecord>resultList;
    for (const auto& pair : bestRecord)
    {
        resultList.push_back(pair.second);
    }
    return resultList;
}

void LevelMode::bubbleSort(std::vector<GameRecord>& records, int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            // 先比较正确率（降序）
            if (records[j].accuracy < records[j + 1].accuracy) {
                // 交换记录
                GameRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
            // 如果正确率相同，比较用时（升序）
            else if (records[j].accuracy == records[j + 1].accuracy && records[j].elapsedTime > records[j + 1].elapsedTime) 
            {
                // 交换记录
                GameRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
        }
        // 如果没有发生交换，提前退出
        if (!swapped)
        {
            break;
        }
    }
}

//将最佳记录排序，依次打印，得到排行榜
void LevelMode::printList( std::vector<GameRecord> records)
{
    if (records.empty())
    {
        std::cout << "该排行榜暂时为空" << std::endl;
        return;
    }
    // 调用排序函数
    bubbleSort(records, records.size());
    int a = 1;
    std::cout << "你想查看的排名榜如下" << std::endl;
    for (auto record : records) {
        std::cout <<"排名" << a++ << " ";
        std::cout << "用户:" << std::setw(6) << std::left << record.username << " ";  // 固定用户名宽度
        std::cout << "关卡:第" << std::setw(1) << record.stage << "关" << " ";
        std::cout << "难度(1低、2中、3高):" << std::setw(1) << record.difficulty << " ";
        std::cout << "用时:" << std::setw(6) << std::left << record.elapsedTime << "秒  ";  // 固定用时宽度
        std::cout << "正确率:" << std::setw(6) << std::left << record.accuracy * 100 << "%" << " ";
        std::cout << "时间:" << record.timestamp << std::endl;
    }
}

void LevelMode::viewRanklist(int stage, int diff)
{
    std::ifstream _file("allUsername.txt");
    if (!_file.is_open())
    {
        std::cerr << "文件无法打开！" << std::endl;
    }
    std::vector<std::string>allusers;
    std::string username2;
    while (_file >> username2)
    {
        allusers.push_back(username2);
    }
    _file.close();

    std::vector<std::vector<GameRecord>>UserAndRecords(allusers.size());

    for (size_t i = 0; i < allusers.size(); i++)
    {
        std::ifstream file(allusers[i] + ".txt");
        if (!file.is_open()) {
            std::cerr << "无法打开文件读取游戏记录。" << std::endl;
            return;
        }
        // 跳过第一行（密码）
        std::string passwordLine;
        std::getline(file, passwordLine);  // 读取并丢弃第一行

        std::vector<GameRecord> Records;
        std::string line;
        while (std::getline(file, line))
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
                UserAndRecords[i].push_back(record1);
            }
        }
        file.close();
    }

    //将某用户的所有游戏记录分类后存入排名榜vector
    std::vector<GameRecord>record_1_1;
    std::vector<GameRecord>record_1_2;
    std::vector<GameRecord>record_1_3;

    std::vector<GameRecord>record_2_1;
    std::vector<GameRecord>record_2_2;
    std::vector<GameRecord>record_2_3;

    std::vector<GameRecord>record_3_1;
    std::vector<GameRecord>record_3_2;
    std::vector<GameRecord>record_3_3;

    for (int i = 0; i < allusers.size(); i++)
    {
        for (int j = 0; j < UserAndRecords[i].size(); j++)
        {
            if (UserAndRecords[i][j].stage == 1 && UserAndRecords[i][j].difficulty == 1)
            {
                record_1_1.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 1 && UserAndRecords[i][j].difficulty == 2)
            {
                record_1_2.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 1 && UserAndRecords[i][j].difficulty == 3)
            {
                record_1_3.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 2 && UserAndRecords[i][j].difficulty == 1)
            {
                record_2_1.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 2 && UserAndRecords[i][j].difficulty == 2)
            {
                record_2_2.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 2 && UserAndRecords[i][j].difficulty == 3)
            {
                record_2_3.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 3 && UserAndRecords[i][j].difficulty == 1)
            {
                record_3_1.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 3 && UserAndRecords[i][j].difficulty == 2)
            {
                record_3_2.push_back(UserAndRecords[i][j]);
            }
            if (UserAndRecords[i][j].stage == 3 && UserAndRecords[i][j].difficulty == 3)
            {
                record_3_3.push_back(UserAndRecords[i][j]);
            }
        }
    }

    if (stage == 1 && diff == 1)
    {
        printList(findAllBestRecords(record_1_1));
    }
    if (stage == 1 && diff == 2)
    {
        printList(findAllBestRecords(record_1_2));
    }
    if (stage == 1 && diff == 3)
    {
        printList(findAllBestRecords(record_1_3));
    }
    if (stage == 2 && diff == 1)
    {
        printList(findAllBestRecords(record_2_1));
    }
    if (stage == 2 && diff == 2)
    {
        printList(findAllBestRecords(record_2_2));
    }
    if (stage == 2 && diff == 3)
    {
        printList(findAllBestRecords(record_2_3));
    }
    if (stage == 3 && diff == 1)
    {
        printList(findAllBestRecords(record_3_1));
    }
    if (stage == 3 && diff == 2)
    {
        printList(findAllBestRecords(record_3_2));
    }
    if (stage == 3 && diff == 3)
    {
        printList(findAllBestRecords(record_3_3));
    }
}



void LevelMode::chooseStage(User& user)
{
    std::cout << "欢迎来到闯关模式" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << "本模式游戏规则简介：" << std::endl;
    std::cout << "背景与规则和自由模式一样" << std::endl;
    std::cout << "设置了3个关卡和3种难度" << std::endl;
    std::cout << "不同关卡对应不同的棋盘大小，不同难度对应不同的回溯步数" << std::endl;
    std::cout << "用户结束游戏后可选择性保存、删除、查看个人记录，保存的个人最佳游戏记录会进入排名榜" << std::endl;
    std::cout << "蚂蚁走过n步形成蚁行图，你要根据蚁行图回溯出棋盘初始状态方为作答完毕" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << std::endl;
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

    std::string choice1;
    std::cout << "是否查看某个排名榜？（yes/no）" << std::endl;
    std::cin >> choice1;
    while (choice1 == "yes")
    {
        std::cout << "请输入你想查看的关卡和难度等级" << std::endl;
        int stage1 = 0; int diff1 = 0;
        std::cin >> stage1 >> diff1;
        viewRanklist(stage1, diff1);
        std::cout << "是否查看其他排名榜？（yes/no）" << std::endl;
        std::cin >> choice1;
    }
}