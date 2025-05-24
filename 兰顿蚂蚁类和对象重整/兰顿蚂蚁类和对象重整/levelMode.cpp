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
        std::cout << "��ʼ�������£�" << std::endl;
        for (int i = 0; i < _size; i++)
        {
            for (int j = 0; j < _size; j++)
            {
                std::cout << _initialOne[i * _size + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "�û��������£�" << std::endl;
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
            std::cout << "������Ϊ��" <<std::fixed<<std::setprecision(3)<< accuracyRate << std::endl;
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
            // �����ı���ɫΪ��ɫ
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::cout << "�ش����" << std::endl;
            // �ָ�Ĭ����ɫ
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return 0;
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �����ı���ɫΪ��ɫ
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    std::cout << "��ϲ�����ش���ȷ��" << std::endl;
    // �ָ�Ĭ����ɫ
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cout << finalOne1[i * 2 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��2*2���̣�����5��������λ�ã�1��0�������ϳ���UP" << std::endl;
            std::cout << "���û���ʼ��������ԭʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" <<std::fixed<<std::setprecision(2)<< elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cout << finalOne1[i * 2 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��2*2���̣�����10��������λ�ã�1��1�������ϳ���LEFT" << std::endl;
            std::cout << "���û���ʼ��������ԭʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::cout << finalOne1[i * 2 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��2*2���̣�����20��������λ�ã�0��0�������ϳ���RIGHT" << std::endl;
            std::cout << "���û���ʼ��������ԭʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << finalOne1[i * 3 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��3*3���̣�����5��������λ�ã�2��1�������ϳ���DOWN" << std::endl;
            std::cout << "���û���ʼ��������ԭʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << finalOne1[i * 3 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��3*3���̣�����10��������λ�ã�0��2�������ϳ���RIGHT" << std::endl;
            std::cout << "���û���ʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << finalOne1[i * 3 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��3*3���̣�����20��������λ�ã�0��2�������ϳ���RIGHT" << std::endl;
            std::cout << "���û���ʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << finalOne1[i * 4 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��4*4���̣�����5��������λ�ã�3,0�������ϳ���DOWN" << std::endl;
            std::cout << "���û���ʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << finalOne1[i * 4 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��4*4���̣�����10��������λ�ã�3��0�������ϳ���LEFT" << std::endl;
            std::cout << "���û���ʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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
            std::cout << "����ͼ����" << std::endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << finalOne1[i * 4 + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "��֪��4*4���̣�����20��������λ�ã�3,0�������ϳ���LEFT" << std::endl;
            std::cout << "���û���ʼ����" << std::endl;
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
            std::cout << "��Ϸ��ʱ��" << std::fixed << std::setprecision(2) << elapsed_time << "��" << std::endl;
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

//����һ�����飬�������������û��ڸùؿ����Ѷ��µ���Ѽ�¼
std::vector<GameRecord> LevelMode::findAllBestRecords(const std::vector<GameRecord>& records)
{
    std::map<std::string, GameRecord>bestRecord;//��ӳ���ϵ�洢��ͬ�û�����Ѽ�¼
    for (const auto& record : records)
    {
        //������û���û�м�¼�����ߵ�ǰ��¼���ã������
        if (bestRecord.find(record.username) == bestRecord.end() || isBetter(bestRecord[record.username], record))
        {
            bestRecord[record.username] = record;
        }
    }

    //��map�е�ֵ��ȡ��vector��
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
            // �ȱȽ���ȷ�ʣ�����
            if (records[j].accuracy < records[j + 1].accuracy) {
                // ������¼
                GameRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
            // �����ȷ����ͬ���Ƚ���ʱ������
            else if (records[j].accuracy == records[j + 1].accuracy && records[j].elapsedTime > records[j + 1].elapsedTime) 
            {
                // ������¼
                GameRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
        }
        // ���û�з�����������ǰ�˳�
        if (!swapped)
        {
            break;
        }
    }
}

//����Ѽ�¼�������δ�ӡ���õ����а�
void LevelMode::printList( std::vector<GameRecord> records)
{
    if (records.empty())
    {
        std::cout << "�����а���ʱΪ��" << std::endl;
        return;
    }
    // ����������
    bubbleSort(records, records.size());
    int a = 1;
    std::cout << "����鿴������������" << std::endl;
    for (auto record : records) {
        std::cout <<"����" << a++ << " ";
        std::cout << "�û�:" << std::setw(6) << std::left << record.username << " ";  // �̶��û������
        std::cout << "�ؿ�:��" << std::setw(1) << record.stage << "��" << " ";
        std::cout << "�Ѷ�(1�͡�2�С�3��):" << std::setw(1) << record.difficulty << " ";
        std::cout << "��ʱ:" << std::setw(6) << std::left << record.elapsedTime << "��  ";  // �̶���ʱ���
        std::cout << "��ȷ��:" << std::setw(6) << std::left << record.accuracy * 100 << "%" << " ";
        std::cout << "ʱ��:" << record.timestamp << std::endl;
    }
}

void LevelMode::viewRanklist(int stage, int diff)
{
    std::ifstream _file("allUsername.txt");
    if (!_file.is_open())
    {
        std::cerr << "�ļ��޷��򿪣�" << std::endl;
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
            std::cerr << "�޷����ļ���ȡ��Ϸ��¼��" << std::endl;
            return;
        }
        // ������һ�У����룩
        std::string passwordLine;
        std::getline(file, passwordLine);  // ��ȡ��������һ��

        std::vector<GameRecord> Records;
        std::string line;
        while (std::getline(file, line))
        {  // ���ж�ȡʣ������
            std::istringstream iss(line);
            std::string name, timestamp;
            int stage, diff;
            double time, accuracy;

            // ��˳������ֶ�
            if (iss >> name >> stage >> diff >> time >> accuracy)
            {
                // ��ȡʱ�����ʣ�ಿ����Ϊ���壩
                std::getline(iss >> std::ws, timestamp);  // std::ws ����ǰ���ո�

                GameRecord record1(name, stage, diff, time, accuracy);
                record1.timestamp = timestamp;
                UserAndRecords[i].push_back(record1);
            }
        }
        file.close();
    }

    //��ĳ�û���������Ϸ��¼��������������vector
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
    std::cout << "��ӭ��������ģʽ" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "��ģʽ��Ϸ�����飺" << std::endl;
    std::cout << "��������������ģʽһ��" << std::endl;
    std::cout << "������3���ؿ���3���Ѷ�" << std::endl;
    std::cout << "��ͬ�ؿ���Ӧ��ͬ�����̴�С����ͬ�Ѷȶ�Ӧ��ͬ�Ļ��ݲ���" << std::endl;
    std::cout << "�û�������Ϸ���ѡ���Ա��桢ɾ�����鿴���˼�¼������ĸ��������Ϸ��¼�����������" << std::endl;
    std::cout << "�����߹�n���γ�����ͼ����Ҫ��������ͼ���ݳ����̳�ʼ״̬��Ϊ�������" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << std::endl;
    std::cout << "��ע�⣺��ģʽ�£���ѡ���������Ĺؿ����Ѷȣ�Ȼ����Ի��ӡ��Ӧ������ͼ��������" << std::endl;
    std::cout << "�������������Ĺؿ������밢��������1��2��3)���Ѷȣ�1�͡�2�С�3�ߣ�" << std::endl;
    int stages = 0;
    int difficulty = 0;
    std::cin >> stages >> difficulty;
    switch (stages)
    {
    case 1:
    {
        std::cout << "��ѡ����ǵ�һ��" << std::endl;
        switch (difficulty)
        {
        case 1:
        {
            std::cout << "��ѡ����ǵ��Ѷ�" << std::endl;
            stageBoard(1, 1, user);
            user.displayRecords();
            break;
        }
        case 2:
        {
            std::cout << "��ѡ��������Ѷ�" << std::endl;
            stageBoard(1, 2, user);
            user.displayRecords();
            break;
        }
        case 3:
        {
            std::cout << "��ѡ����Ǹ��Ѷ�" << std::endl;
            stageBoard(1, 3, user);
            user.displayRecords();
            break;
        }
        }
        break;
    }
    case 2:
    {
        std::cout << "��ѡ����ǵڶ���" << std::endl;
        switch (difficulty)
        {
        case 1:
        {
            std::cout << "��ѡ����ǵ��Ѷ�" << std::endl;
            stageBoard(2, 1, user);
            user.displayRecords();
            break;
        }
        case 2:
        {
            std::cout << "��ѡ��������Ѷ�" << std::endl;
            stageBoard(2, 2, user);
            user.displayRecords();
            break;
        }
        case 3:
        {
            std::cout << "��ѡ����Ǹ��Ѷ�" << std::endl;
            stageBoard(2, 3, user);
            user.displayRecords();
            break;
        }
        }
        break;
    }
    case 3:
    {
        std::cout << "��ѡ����ǵ�����" << std::endl;
        switch (difficulty)
        {
        case 1:
        {
            std::cout << "��ѡ����ǵ��Ѷ�" << std::endl;
            stageBoard(3, 1, user);
            user.displayRecords();
            break;
        }
        case 2:
        {
            std::cout << "��ѡ��������Ѷ�" << std::endl;
            stageBoard(3, 2, user);
            user.displayRecords();
            break;
        }
        case 3:
        {
            std::cout << "��ѡ����Ǹ��Ѷ�" << std::endl;
            stageBoard(3, 3, user);
            user.displayRecords();
            break;
        }
        }
        break;
    }
    default:
    {
        std::cout << "������Ĺؿ������ڣ�����������" << std::endl;
        chooseStage(user);
    }
    }
    
    std::cout << "�Ƿ�鿴������д��ؼ�¼����yes/no��" << std::endl;
    std::string choice;
    std::cin >> choice;
    std::string username1 = user.getUsername();
    while(choice == "yes")
    {
        user.printAllRecordsFromFile(username1);
        std::cout << "�Ƿ�ɾ��ĳ����Ϸ��¼����yes/no��" << std::endl;
        std::cin >> choice;
        while (choice == "yes")
        {
            std::cout << "����������ɾ������Ϸ��¼���" << std::endl;
            int index;
            std::cin >> index;
            user.deleteRecord(index + 1);
            std::cout << "�Ƿ����ɾ������yes/no��" << std::endl;
            std::cin >> choice;
        }
        std::cout << "�Ƿ��ٴβ鿴������д��ؼ�¼����yes/no��" << std::endl;
        std::cin >> choice;
    }

    std::string choice1;
    std::cout << "�Ƿ�鿴ĳ�������񣿣�yes/no��" << std::endl;
    std::cin >> choice1;
    while (choice1 == "yes")
    {
        std::cout << "����������鿴�Ĺؿ����Ѷȵȼ�" << std::endl;
        int stage1 = 0; int diff1 = 0;
        std::cin >> stage1 >> diff1;
        viewRanklist(stage1, diff1);
        std::cout << "�Ƿ�鿴���������񣿣�yes/no��" << std::endl;
        std::cin >> choice1;
    }
}