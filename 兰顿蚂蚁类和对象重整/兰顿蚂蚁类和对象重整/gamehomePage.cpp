#include "gameHomepage.h"
#include <iostream>
#include<fstream>
#include <windows.h>  // ���� ShellExecute ͷ�ļ�

GameHomepage::GameHomepage() {}

// ����������������������·����������,���ڴ��ⲿ����˺Ϳͻ�����Ŀ���жԿ�ģʽ
bool startProgram(const wchar_t* filePath, const wchar_t* args = NULL)
{
    HINSTANCE hInstance = ShellExecute(
        NULL,
        L"open",
        filePath,
        args,
        NULL,
        SW_SHOWNORMAL  // ������ʾģʽ
    );
    return (int)hInstance > 32;  // �ɹ��������� true
}

void GameHomepage::beginGame()
{
    std::cout << std::endl;
    std::cout << " ������������������������" << std::endl;
    std::cout << "|" << " ��ӭ��������������Ϸ" << "   |" << std::endl;
    std::cout << " ������������������������" << std::endl;
    bool shouldExit1 = false;
    while (!shouldExit1)
    {
        int firstChoice = 0;
        std::cout << "1��ע��" << std::endl;
        std::cout << "2����¼" << std::endl;
        std::cout << "3���˳�" << std::endl;
        std::cin >> firstChoice;
        switch (firstChoice)
        {
        case 1:
        {
            std::cout << "ע���У�" << std::endl;
            std::cout << "�������û���" << std::endl;
            std::string username2;
            std::cin >> username2;
            std::ifstream checkIn(username2 + ".txt");
            if (checkIn.is_open())
            {
                std::cout << "���û����Ѵ���" << std::endl;
            }
            else
            {
                std::cout << "����������" << std::endl;
                User user(username2);// �����û�����
                std::string password2 = user.getpassword();
                user.userRegister(username2, password2);
                std::cout << "��¼�У�" << std::endl;
                std::cout << "�������û���" << std::endl;
                std::string username;
                std::cin >> username;
                std::cout << "����������" << std::endl;
                user = User(username);
                std::string password = user.getpassword();
                if (user.userLogin(password))
                {
                    chooseMode(user);
                }
                shouldExit1 = true;
            }
            break;
        }
        case 2:
        {
            std::cout << "��¼�У�" << std::endl;
            std::cout << "�������û���" << std::endl;
            std::string username;
            std::cin >> username;
            std::cout << "����������" << std::endl;
            User user(username);
            std::string password = user.getpassword();
            if (user.userLogin(password))
            {
                chooseMode(user);
            }
            shouldExit1 = true;
            break;
        }
        case 3:
        {
            std::cout << "��Ϸ���˳�����ӭ�´�������" << std::endl;
            shouldExit1 = true;
            break;
        }
        }
    }
}


int input = 0;
bool shouldExit = false;

void GameHomepage::chooseMode(User& user)
{
    std::cout << "��ѡ����Ϸģʽ" << std::endl;
    std::cout << "1. ����ģʽ" << std::endl;
    std::cout << "2. ����ģʽ" << std::endl;
    std::cout << "3. Ȥζģʽ" << std::endl;
    std::cout << "4. �Կ�ģʽ" << std::endl;
    std::cout << "����������μӵ�ģʽ��Ӧ�����" << std::endl;
    std::cout << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice) 
    {
    case 1:
    {
        freedommode.freeMode( user);
        while (!shouldExit)
        {
            std::cout << std::endl;
            std::cout << "������������Ĳ�����" << std::endl;
            std::cout << "1������һ�α�ģʽ" << std::endl;
            std::cout << "2���˳���ģʽ���ص���ҳ�� " << std::endl;
            std::cout << "3���˳���Ϸ " << std::endl;
            std::cin >> input;
            switch (input)
            {
            case 1:
            {
                freedommode.freeMode(user);
                break;
            }
            case 2:
            {
                GameHomepage homepage2;
                homepage2.beginGame();
                shouldExit = true;
                break;
            }
            case 3:
            {
                std::cout << "��Ϸ���˳�����ӭ�´�������" << std::endl;
                shouldExit = true;
                break;
            }
            }
        }
        break;
    }
    case 2:
    {
        levelMode.chooseStage(user);
        while (!shouldExit)
        {
            std::cout << "������������Ĳ�����" << std::endl;
            std::cout << "1������һ�α�ģʽ" << std::endl;
            std::cout << "2���˳���ģʽ���ص���ҳ�� " << std::endl;
            std::cout << "3���˳���Ϸ " << std::endl;
            std::cin >> input;
            switch (input)
            {
            case 1:
            {
                levelMode.chooseStage(user);
                break;
            }
            case 2:
            {
                GameHomepage homepage2;
                homepage2.beginGame();
                shouldExit = true;
                break;
            }
            case 3:
            {
                std::cout << "��Ϸ���˳�����ӭ�´�������" << std::endl;
                shouldExit = true;
                break;
            }
            }
        }
        break;
    }
    case 3:
    {
        funmode.chooseMap();
        while (!shouldExit)
        {
            std::cout << "������������Ĳ�����" << std::endl;
            std::cout << "1������һ�α�ģʽ" << std::endl;
            std::cout << "2���˳���ģʽ���ص���ҳ�� " << std::endl;
            std::cout << "3���˳���Ϸ " << std::endl;
            std::cin >> input;
            switch (input)
            {
            case 1:
            {
                funmode.chooseMap();
                break;
            }
            case 2:
            {
                GameHomepage homepage2;
                homepage2.beginGame();
                shouldExit = true;
                break;
            }
            case 3:
            {
                std::cout << "��Ϸ���˳�����ӭ�´�������" << std::endl;
                shouldExit = true;
                break;
            }
            }
        }
        break;
    }
    case 4:
    {
        // ��������ˣ��滻Ϊʵ��·����
        const wchar_t* serverPath = L"D:\\VSLearn\\AntSever\\x64\\Debug\\AntSever.exe";
        startProgram(serverPath);
        int a = 0;
        std::cout << "��Ϊ�û�1������Ϸ��������1" << std::endl;
        std::cin >> a;
        const wchar_t* clientPath = L"D:\\VSLearn\\AntClient\\x64\\Debug\\AntClient.exe";
        if (a == 1)
        {
            // �����ͻ���1���滻Ϊʵ��·����
            startProgram(clientPath, L"Client1");  // ��ѡ�������ݸ��ͻ���
        }
        std::cout << "��Ϊ�û�2������Ϸ��������2" << std::endl;
        std::cin >> a;
        if (a == 2)
        {
            // �����ͻ���2
            startProgram(clientPath, L"Client2");
        }

        while (!shouldExit)
        {
            std::cout << "������������Ĳ�����" << std::endl;
            std::cout << "1������һ�α�ģʽ" << std::endl;
            std::cout << "2���˳���ģʽ���ص���ҳ�� " << std::endl;
            std::cout << "3���˳���Ϸ " << std::endl;
            std::cin >> input;
            switch (input)
            {
            case 1:
            {
                // ���������
                startProgram(serverPath);

                // �����ͻ���1
                int a = 0;
                std::cout << "��Ϊ�û�1������Ϸ��������1" << std::endl;
                std::cin >> a;
                if (a == 1)
                {
                    // �����ͻ���1���滻Ϊʵ��·����
                    startProgram(clientPath, L"Client1");  // ��ѡ�������ݸ��ͻ���
                }

                std::cout << "��Ϊ�û�2������Ϸ��������2" << std::endl;
                std::cin >> a;
                if (a == 2)
                {
                    // �����ͻ���2
                    startProgram(clientPath, L"Client2");
                }

                break;
            }
            case 2:
            {
                GameHomepage homepage2;
                homepage2.beginGame();
                shouldExit = true;
                break;
            }
            case 3:
            {
                std::cout << "��Ϸ���˳�����ӭ�´�������" << std::endl;
                shouldExit = true;
                break;
            }
            }
        }
        break;
    }
    default:
    {
        std::cout << "������Ч��������ѡ��" << std::endl;
        chooseMode(user);
    }
    }
}