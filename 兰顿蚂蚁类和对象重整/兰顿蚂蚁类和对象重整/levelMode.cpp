#include"levelMode.h"
#include"gameHomepage.h"
#include <iostream> 
#include<windows.h>
#include<iomanip>


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

void LevelMode::chooseStage(User& user)
{
    std::cout << "��ӭ��������ģʽ" << std::endl;
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
}