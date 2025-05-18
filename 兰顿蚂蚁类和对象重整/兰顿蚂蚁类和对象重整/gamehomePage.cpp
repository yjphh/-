#include "gameHomepage.h"
#include <iostream>
#include<fstream>
#include<conio.h>

GameHomepage::GameHomepage() {}

std::string getPassword()
{
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r')//�û����»س���ʱֹͣ����
    {
        if (ch == '\b')//�����˸��
        {
            if (!password.empty())
            {
                password.pop_back();//ɾ�����һ���ַ�
                std::cout << "\b \b";//���˹��
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
                std::string password2 = getPassword();
                User user(username2);
                user.userRegister(username2, password2);
                std::cout << "��¼�У�" << std::endl;
                std::cout << "�������û���" << std::endl;
                std::string username;
                std::cin >> username;
                std::cout << "����������" << std::endl;
                std::string password = getPassword();
                user = User(username);
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
            std::string password = getPassword();
            User user(username);
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
    std::cout << "����������μӵ�ģʽ��Ӧ�����" << std::endl;
    std::cout << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice) {
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
    default:
    {
        std::cout << "������Ч��������ѡ��" << std::endl;
        chooseMode(user);
    }
    }
}