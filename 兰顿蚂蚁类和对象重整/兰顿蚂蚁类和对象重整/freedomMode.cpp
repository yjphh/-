#include "freedomMode.h"
#include "gameHomepage.h"
#include <cstdlib>
#include <ctime>
#include<windows.h>
#include<fstream>
#include<cmath>
#include<sstream>
#include<iomanip>

void TurnRight(Direction& heading) {
    switch (heading) {
    case DOWN:
        heading = LEFT;
        break;
    case UP:
        heading = RIGHT;
        break;
    case RIGHT:
        heading = DOWN;
        break;
    case LEFT:
        heading = UP;
        break;
    }
}

void TurnLeft(Direction& heading) {
    switch (heading) {
    case DOWN:
        heading = RIGHT;
        break;
    case UP:
        heading = LEFT;
        break;
    case RIGHT:
        heading = UP;
        break;
    case LEFT:
        heading = DOWN;
        break;
    }
}

bool freedomMode::isSameProblem(const problemBank& a, const problemBank& b)
{
    if (a.steps != b.steps || a.finalX != b.finalX || a.finalY != b.finalY ||a.finalDirec!=b.finalDirec|| a.arr.size() != b.arr.size()) {
        return false;
    }
    for (size_t i = 0; i < a.arr.size(); ++i) {
        if (a.arr[i] != b.arr[i]) {
            return false;
        }
    }
    return true;
}

bool freedomMode::SavetoFile(const std::string username, int steps, int finalX, int finalY,int finalDirec, const std::vector<bool> arr, const std::vector<bool> answer)
{
    std::ofstream file("question_bank.txt",std::ios::app);
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return false;
    }

    // 检查是否有重复记录  
    std::ifstream inFile("question_bank.txt");
    if (!inFile.is_open()) {
        std::cerr << "无法打开文件进行检查" << std::endl;
        return false;
    }

    problemBank newProblem{ username, steps, finalX, finalY, finalDirec,arr };  //存储用户输入的题目
    std::string storedUsername;
    int storedSteps, storedFinalX, storedFinalY,storedFinalDirec;  //这几个变量用来存储从文件中读取到的数据
    //读取文件第一行，把第一行信息和用户存入信息比较，若同，跳出函数，若不同，继续读取下一行和它比较，直至遍历完整个文件
    while (inFile >> storedUsername >> storedSteps >> storedFinalX >> storedFinalY>> storedFinalDirec) //从第一行开始，读取一个字符串和4个整数，将读取到的数据存入这几个变量当中
    {
        std::vector<bool> storedArr;
        int val;
        while (inFile >> val)//将文件该行代表题目棋盘的整数读入棋盘数组
        {
            storedArr.push_back(static_cast<bool>(val));
            if (inFile.peek() == 'a')//当下一个字符为a说明该题目棋盘数组已读完，跳出
            {
                break;
            }
        }
        problemBank storedProblem{ storedUsername, storedSteps, storedFinalX, storedFinalY,storedFinalDirec, storedArr};  //存储文件中已有的题目
        if (isSameProblem(newProblem, storedProblem))
        {
            inFile.close();
            file.close();
            return false;
        }
    }
    inFile.close();

    // 保存新记录  
    file << username << " " << steps << " " << finalX << " " << finalY<<" "<<finalDirec;
    for (bool b : arr) 
    {
        file <<" "<< static_cast<int>(b);
    }
    file <<'a';
    for (bool b : answer)
    {
        file << " " << static_cast<int>(b);
    }
    file << std::endl;
    file.close();
    return true;
}

void freedomMode::viewBank()
{
    std::cout << "———————————————" << std::endl;
    std::cout << "自由模式题库：" << std::endl;
    if (isfirstRead)
    {
        std::cout << std::endl;
        std::ifstream file("question_bank.txt");
        if (!file.is_open()) {
            std::cerr << "无法打开文件" << std::endl;
            return;
        }
        std::string username;
        int steps, finalX, finalY, finalDirec;
        while (file >> username >> steps >> finalX >> finalY >> finalDirec)
        {
            std::vector<bool> arr;
            std::vector<bool> answer;
            int val;
            while (file >> val)
            {
                arr.push_back(static_cast<bool>(val));
                if (file.peek() == 'a')
                {
                    file.get();
                    break;
                }
            }
            while (file >> val)
            {
                answer.push_back(static_cast<bool>(val));
                if (file.peek() == '\n')
                {
                    break;
                }
            }
            bank.push_back({ username, steps, finalX, finalY,finalDirec, arr,answer });
        }
        file.close();
    }
    isfirstRead = false;
    int counter = 0;
    // 打印所有题目序号
    for (size_t i = 0; i < bank.size(); ++i)
    {
        std::string fulltitle = "题目" + std::to_string(i + 1);
        if (counter % 3 == 0 && counter != 0)
        {
            std::cout << std::endl;
        }
        std::cout << std::left << std::setw(10) << fulltitle;
        counter++;
    }
    std::cout << std::endl;
    std::cout << "———————————————" << std::endl;
}

const std::vector<problemBank>& freedomMode::getBank()const
{
    return bank;
}


void freedomMode::viewProblem(int i,std::vector<problemBank>bank)
{
    int c = bank[i-1].finalDirec;
    std::string c1;
    switch (c)
    {
    case 0:
    {
        c1 = "UP";
        break;
    }
    case 1:
    {
        c1 = "DOWN";
        break;
    }
    case 2:
    {
        c1 = "LEFT";
        break;
    }
    case 3:
    {
        c1 = "RIGHT";
        break;
    }
    }

    std::cout << "题目" << i <<"信息如下" <<std::endl;
    std::cout << "提供者: " << bank[i-1].username << std::endl;
    std::cout << "步数: " << bank[i-1].steps << std::endl;
    std::cout << "最终位置: " << "(" << bank[i-1].finalX << "," << bank[i-1].finalY << ")" << std::endl;
    std::cout << "最终朝向:" << c1 << std::endl;
    std::cout << "蚁行图: " << std::endl;
    int counter = 0;
    for (bool b : bank[i-1].arr)
    {
        if (counter % int(sqrt(bank[i-1].arr.size())) == 0 && counter != 0)
        {
            std::cout << std::endl;
        }
        std::cout << (b ? "1" : "0") << " ";
        counter++;
    }
    std::cout << std::endl;
    std::cout << "答案: ";
    for (bool b : bank[i-1].answer)
    {
        if (counter % int(sqrt(bank[i-1].answer.size())) == 0 && counter != 0)
        {
            std::cout << std::endl;
        }
        std::cout << (b ? "1" : "0") << " ";
        counter++;
    }
}


freedomMode::freedomMode(int size, int steps) : size(size), steps(steps) {
    board = new bool[size * size];
    finalBoard = new bool[size * size];
    initialBoard = new bool[size * size];
    initializeBoard(board);
    initializeBoard(finalBoard);
    initializeBoard(initialBoard);
    srand(time(0));
    // 随机设置棋盘格子(0白格，1黑格)
    for (int i = 0; i < size * size; ++i) {
        board[i] = rand() % 2 == 0;
        initialBoard[i] = board[i];
    }
}

freedomMode::freedomMode() : size(0), steps(0), board(nullptr), finalBoard(nullptr), initialBoard(nullptr) {
    // 默认构造函数
}

freedomMode::~freedomMode() {
    delete[] board;
    delete[] finalBoard;
    delete[] initialBoard;
}

void freedomMode::initializeBoard(bool* board) {
    for (int i = 0; i < size * size; ++i) {
        board[i] = false;
    }
}

void freedomMode::copyBoard(bool* src, bool* dest) {
    for (int i = 0; i < size * size; ++i) {
        dest[i] = src[i];
    }
}

int freedomMode::getIndex(int x, int y) {
    return x * size + y;
}

bool freedomMode::moveAnt(int& x, int& y, Direction& heading) {
    int index = getIndex(x, y);
    if (board[index]) {
        TurnLeft(heading);
        board[index] = false;
    }
    else {
        TurnRight(heading);
        board[index] = true;
    }

    switch (heading) {
    case UP:
        if (x - 1 < 0) return false;
        x--;
        break;
    case DOWN:
        if (x + 1 >= size) return false;
        x++;
        break;
    case LEFT:
        if (y - 1 < 0) return false;
        y--;
        break;
    case RIGHT:
        if (y + 1 >= size) return false;
        y++;
        break;
    }
    return true;
}

bool freedomMode::isValidInitialPosition(int x, int y, Direction heading) {
    copyBoard(board, finalBoard);
    for (int i = 0; i < steps; ++i) {
        if (!moveAnt(x, y, heading)) {
            copyBoard(finalBoard, board);
            return false;
        }
    }
    copyBoard(finalBoard, board);
    return true;
}

void freedomMode::generateFinalBoard(int& x, int& y, Direction& heading) {
    copyBoard(initialBoard, board);
    for (int i = 0; i < steps; ++i) {
        moveAnt(x, y, heading);
    }
    copyBoard(board, finalBoard);
}

void freedomMode::printFinalBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << finalBoard[getIndex(i, j)] << " ";
        }
        std::cout << std::endl;
    }
}

bool freedomMode::checkSolution(bool* userBoard) {
    for (int i = 0; i < size * size; ++i) {
        if (userBoard[i] != initialBoard[i]) {
            return false;
        }
    }
    return true;
}

void freedomMode::printInitialBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << initialBoard[getIndex(i, j)] << " ";
        }
        std::cout << std::endl;
    }
}

bool freedomMode::suggestInitialPosition(int& x, int& y, Direction& heading) {
    const int MAX_ATTEMPTS = 1000; // 最大尝试次数
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        x = rand() % size;
        y = rand() % size;
        heading = static_cast<Direction>(rand() % 4);
        if (isValidInitialPosition(x, y, heading)) {
            return true;
        }
    }
    return false;
}

int freedomMode::freeMode(User& user)
{
    std::cout << "欢迎来到自由模式" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << "本模式游戏规则简介：" << std::endl;
    std::cout << "有一个由黑白格组成的正方形棋盘（0代表白格，1代表黑格）和一只蚂蚁" << std::endl;
    std::cout << "若蚂蚁在白格上，白->黑，右转90°并前进一格" << std::endl;
    std::cout << "若蚂蚁在黑格上，黑->白，左转90°并前进一格" << std::endl;
    std::cout << "蚂蚁走过n步形成蚁行图，你要根据蚁行图回溯出棋盘初始状态方为作答完毕" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << std::endl;
    std::cout << "请注意：本模式下，电脑会根据您输入的棋盘边长随机生成棋盘格子，您还需输入蚂蚁的初始位置和朝向和走过步数，电脑检测输入有效后会打印蚁行图供您作答" << std::endl;
    int size = 0;
    int steps = 0;
    while (true) {
        std::cout << "请输入棋盘的边长: ";
        std::cin >> size;
        std::cout << "电脑已生成本次棋盘" << std::endl;
        std::cout << "请输入要走的步数: ";
        std::cin >> steps;
        freedomMode game(size, steps);

        int x = 0, y = 0;
        Direction heading;
        int invalidAttempts = 0;

        while (true) {
            if (invalidAttempts >= 3) {
                if (!game.suggestInitialPosition(x, y, heading)) {
                    std::cout << "该棋盘无解，电脑将重新要求您输入棋盘边长生成新的棋盘。" << std::endl;
                    break;
                }
                std::cout << "您已输入3个无效位置，为帮助您参与游戏，电脑给出的合理初始位置和朝向如下：" << std::endl;
                std::cout << "初始位置: (" << x << ", " << y << ")" << std::endl;
                std::cout << "初始朝向: ";
                switch (heading) {
                case UP:
                    std::cout << "UP";
                    break;
                case DOWN:
                    std::cout << "DOWN";
                    break;
                case LEFT:
                    std::cout << "LEFT";
                    break;
                case RIGHT:
                    std::cout << "RIGHT";
                    break;
                }
                std::cout << std::endl;
                std::cout << "请使用电脑给出的提示重新输入蚂蚁的初始位置 (x y) 和朝向 (0: UP, 1: DOWN, 2: LEFT, 3: RIGHT): ";
                std::cin >> x >> y;
                int headingInput = 0;
                std::cin >> headingInput;
                heading = static_cast<Direction>(headingInput);
            }
            else {
                std::cout << "请输入蚂蚁的初始位置 (x y): ";
                std::cin >> x >> y;
                std::cout << "请输入蚂蚁的初始朝向 (0: UP, 1: DOWN, 2: LEFT, 3: RIGHT): ";
                int headingInput;
                std::cin >> headingInput;
                heading = static_cast<Direction>(headingInput);
            }

            if (game.isValidInitialPosition(x, y, heading)) {
                std::cout << "您的输入有效，蚁行图如下：" << std::endl;
                int finalX = x, finalY = y;
                Direction finalHeading = heading;
                game.generateFinalBoard(finalX, finalY, finalHeading);
                game.printFinalBoard();

                std::cout << "蚂蚁走完所有步数的最终位置: (" << finalX << ", " << finalY << ")" << std::endl;
                std::cout << "蚂蚁走完所有步数的最终朝向: ";
                switch (finalHeading) {
                case UP:
                    std::cout << "UP";
                    break;
                case DOWN:
                    std::cout << "DOWN";
                    break;
                case LEFT:
                    std::cout << "LEFT";
                    break;
                case RIGHT:
                    std::cout << "RIGHT";
                    break;
                }
                std::cout << std::endl;

                bool* userBoard = new bool[size * size];
                while (true) {
                    std::cout << "请输入原始棋盘 (0 表示白格, 1 表示黑格):" << std::endl;
                    for (int i = 0; i < size; ++i) {
                        for (int j = 0; j < size; ++j) {
                            std::cin >> userBoard[i * size + j];
                        }
                    }

                    if (game.checkSolution(userBoard))
                    {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        // 设置文本颜色为绿色
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        std::cout << "回答正确！游戏结束" << std::endl;
                        // 恢复默认颜色
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        delete[] userBoard;
                        // 询问是否保存
                        std::string choice1;
                        std::cout << "是否存档？(yes/no): ";
                        std::cin >> choice1;
                        if (choice1 == "yes")
                        {
                            std::vector<bool> arr;
                            for (int i = 0; i < size * size; ++i) {
                                arr.push_back(game.finalBoard[i]);
                            }
                            std::vector<bool> answer;
                            for (int i = 0; i < size * size; ++i) {
                                answer.push_back(game.initialBoard[i]);
                            }
                            std::string username1 = user.getUsername();
                            if (game.SavetoFile(username1, steps, finalX, finalY,finalHeading, arr,answer))
                            {
                                std::cout << "存档成功！" << std::endl;
                            }
                            else
                            {
                                std::cout << "题库中已有该题，不重复保存" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "本题将不会存入题库" << std::endl;
                        }

                        // 询问是否查看题库
                        std::string choice;
                        std::cout << "是否进入题库？(yes/no): ";
                        std::cin >> choice;
                        while (choice == "yes")
                        {
                            game.viewBank();
                            std::cout << "请输入你想查看的题目序号: ";
                            int index;
                            std::cin >> index;
                            viewProblem(index, game.getBank());
                            std::cout << std::endl;
                            std::cout << "是否再次进入题库？（yes/no）";
                            std::cin >> choice;
                        }
                        return 0;
                    }
                    else
                    {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        // 设置文本颜色为红色
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                        std::cout << "回答错误！" << std::endl;
                        // 恢复默认颜色
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        int choice;
                        std::cout << "输入 1 重新作答该题，输入 2 电脑直接给出初始棋盘答案: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            continue;
                        }
                        else if (choice == 2) {
                            game.printInitialBoard();
                            std::cout << "游戏结束" << std::endl;
                            // 询问是否保存
                            std::string choice1;
                            std::cout << "是否存档？(yes/no): ";
                            std::cin >> choice1;
                            if (choice1 == "yes")
                            {
                                std::vector<bool> arr;
                                for (int i = 0; i < size * size; ++i) {
                                    arr.push_back(game.finalBoard[i]);
                                }
                                std::vector<bool> answer;
                                for (int i = 0; i < size * size; ++i) {
                                    answer.push_back(game.initialBoard[i]);
                                }
                                std::string username1 = user.getUsername();
                                if (game.SavetoFile(username1, steps, finalX, finalY,finalHeading, arr,answer))
                                {
                                    std::cout << "存档成功！" << std::endl;
                                }
                                else
                                {
                                    std::cout << "题库中已有该题，不重复保存" << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "本题将不会存入题库" << std::endl;
                            }

                            // 询问是否查看题库
                            std::string choice;
                            std::cout << "是否查看题库？(yes/no): ";
                            std::cin >> choice;
                            while (choice == "yes")
                            {
                                game.viewBank();
                                std::cout << "请输入你想查看的题目序号: ";
                                int index;
                                std::cin >> index;
                                viewProblem(index, game.getBank());
                                std::cout << std::endl;
                                std::cout << "是否再次进入题库？（yes/no）";
                                std::cin >> choice;
                            }
                            delete[] userBoard;
                            return 0;
                        }
                    }
                }
            }
            else {
                std::cout << "您的输入无效，请重新输入蚂蚁的初始位置和朝向" << std::endl;
                invalidAttempts++;
            }
        }
    }
}

