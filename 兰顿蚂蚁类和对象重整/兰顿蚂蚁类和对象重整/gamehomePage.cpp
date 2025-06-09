#include "gameHomepage.h"
#include <iostream>
#include<fstream>
#include <windows.h>  // 包含 ShellExecute 头文件

GameHomepage::GameHomepage() {}

// 启动程序函数（参数：程序路径、参数）,用于打开外部服务端和客户端项目进行对抗模式
bool startProgram(const wchar_t* filePath, const wchar_t* args = NULL)
{
    HINSTANCE hInstance = ShellExecute(
        NULL,
        L"open",
        filePath,
        args,
        NULL,
        SW_SHOWNORMAL  // 窗口显示模式
    );
    return (int)hInstance > 32;  // 成功启动返回 true
}

void GameHomepage::beginGame()
{
    std::cout << std::endl;
    std::cout << " ————————————" << std::endl;
    std::cout << "|" << " 欢迎来到兰顿蚂蚁游戏" << "   |" << std::endl;
    std::cout << " ————————————" << std::endl;
    bool shouldExit1 = false;
    while (!shouldExit1)
    {
        int firstChoice = 0;
        std::cout << "1、注册" << std::endl;
        std::cout << "2、登录" << std::endl;
        std::cout << "3、退出" << std::endl;
        std::cin >> firstChoice;
        switch (firstChoice)
        {
        case 1:
        {
            std::cout << "注册中：" << std::endl;
            std::cout << "请输入用户名" << std::endl;
            std::string username2;
            std::cin >> username2;
            std::ifstream checkIn(username2 + ".txt");
            if (checkIn.is_open())
            {
                std::cout << "该用户名已存在" << std::endl;
            }
            else
            {
                std::cout << "请输入密码" << std::endl;
                User user(username2);// 创建用户对象
                std::string password2 = user.getpassword();
                user.userRegister(username2, password2);
                std::cout << "登录中：" << std::endl;
                std::cout << "请输入用户名" << std::endl;
                std::string username;
                std::cin >> username;
                std::cout << "请输入密码" << std::endl;
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
            std::cout << "登录中：" << std::endl;
            std::cout << "请输入用户名" << std::endl;
            std::string username;
            std::cin >> username;
            std::cout << "请输入密码" << std::endl;
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
            std::cout << "游戏已退出，欢迎下次再来！" << std::endl;
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
    std::cout << "请选择游戏模式" << std::endl;
    std::cout << "1. 自由模式" << std::endl;
    std::cout << "2. 闯关模式" << std::endl;
    std::cout << "3. 趣味模式" << std::endl;
    std::cout << "4. 对抗模式" << std::endl;
    std::cout << "请输入你想参加的模式对应的序号" << std::endl;
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
            std::cout << "请输入接下来的操作：" << std::endl;
            std::cout << "1、再玩一次本模式" << std::endl;
            std::cout << "2、退出该模式并回到主页面 " << std::endl;
            std::cout << "3、退出游戏 " << std::endl;
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
                std::cout << "游戏已退出，欢迎下次再来！" << std::endl;
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
            std::cout << "请输入接下来的操作：" << std::endl;
            std::cout << "1、再玩一次本模式" << std::endl;
            std::cout << "2、退出该模式并回到主页面 " << std::endl;
            std::cout << "3、退出游戏 " << std::endl;
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
                std::cout << "游戏已退出，欢迎下次再来！" << std::endl;
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
            std::cout << "请输入接下来的操作：" << std::endl;
            std::cout << "1、再玩一次本模式" << std::endl;
            std::cout << "2、退出该模式并回到主页面 " << std::endl;
            std::cout << "3、退出游戏 " << std::endl;
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
                std::cout << "游戏已退出，欢迎下次再来！" << std::endl;
                shouldExit = true;
                break;
            }
            }
        }
        break;
    }
    case 4:
    {
        // 启动服务端（替换为实际路径）
        const wchar_t* serverPath = L"D:\\VSLearn\\AntSever\\x64\\Debug\\AntSever.exe";
        startProgram(serverPath);
        int a = 0;
        std::cout << "作为用户1参与游戏，请输入1" << std::endl;
        std::cin >> a;
        const wchar_t* clientPath = L"D:\\VSLearn\\AntClient\\x64\\Debug\\AntClient.exe";
        if (a == 1)
        {
            // 启动客户端1（替换为实际路径）
            startProgram(clientPath, L"Client1");  // 可选参数传递给客户端
        }
        std::cout << "作为用户2参与游戏，请输入2" << std::endl;
        std::cin >> a;
        if (a == 2)
        {
            // 启动客户端2
            startProgram(clientPath, L"Client2");
        }

        while (!shouldExit)
        {
            std::cout << "请输入接下来的操作：" << std::endl;
            std::cout << "1、再玩一次本模式" << std::endl;
            std::cout << "2、退出该模式并回到主页面 " << std::endl;
            std::cout << "3、退出游戏 " << std::endl;
            std::cin >> input;
            switch (input)
            {
            case 1:
            {
                // 启动服务端
                startProgram(serverPath);

                // 启动客户端1
                int a = 0;
                std::cout << "作为用户1参与游戏，请输入1" << std::endl;
                std::cin >> a;
                if (a == 1)
                {
                    // 启动客户端1（替换为实际路径）
                    startProgram(clientPath, L"Client1");  // 可选参数传递给客户端
                }

                std::cout << "作为用户2参与游戏，请输入2" << std::endl;
                std::cin >> a;
                if (a == 2)
                {
                    // 启动客户端2
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
                std::cout << "游戏已退出，欢迎下次再来！" << std::endl;
                shouldExit = true;
                break;
            }
            }
        }
        break;
    }
    default:
    {
        std::cout << "输入无效，请重新选择" << std::endl;
        chooseMode(user);
    }
    }
}