#include "funMode.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

// 构造函数：初始化通用属性
funMode::funMode() {
    srand(time(0));
    size = rand() % 3 + 3; // 默认棋盘大小为4x4（可调整）
    initBoard();
    initObstacle();
    resetAnt();
}

// 初始化棋盘
void funMode::initBoard() {
    board = new int* [size];
    originalBoard = new int* [size];
    correctInitialBoard = new int* [size]; // 新增：正确的初始棋盘
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        originalBoard[i] = new int[size];
        correctInitialBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = rand() % 2; // 随机黑白格
            originalBoard[i][j] = board[i][j];
            correctInitialBoard[i][j] = board[i][j];
        }
    }
}

// 初始化障碍（碰壁模式专用）
void funMode::initObstacle() {
    obstacle = new char* [size];
    for (int i = 0; i < size; i++) {
        obstacle[i] = new char[size];
        for (int j = 0; j < size; j++) {
            obstacle[i][j] = ' '; // 默认无障碍
        }
    }
}

// 重置蚂蚁状态
void funMode::resetAnt() {
    antX = rand() % size;
    antY = rand() % size;
    antDirection = rand() % 4 + 1; // 1-4
    steps = rand() % 11 + 5; // 5-15步
}

// 打印整数棋盘
void funMode::printBoard(int** arr) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (obstacle[i][j] == '#') {
                cout << "# ";
            }
            else {
                cout << arr[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// 打印字符棋盘
void funMode::printBoard(char** arr) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// 输入棋盘状态 - 修改后支持#
void funMode::inputBoard(int** arr) {
    cout << "请输入" << size << "x" << size << "的初始棋盘（0=白格，1=黑格，#=障碍）：" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char cell;
            cin >> cell;

            if (cell == '#') {
                obstacle[i][j] = '#';
                arr[i][j] = 0; // 障碍所在位置默认为白格
            }
            else {
                obstacle[i][j] = ' ';
                arr[i][j] = (cell == '1') ? 1 : 0;
            }
        }
    }
}

// 比对棋盘
bool funMode::compareBoards() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (originalBoard[i][j] != board[i][j]) return false;
        }
    }
    return true;
}

// 通用模拟函数（扭曲世界模式）
bool funMode::simulateTwistedWorld() {
    int x = antX, y = antY;
    int dir = antDirection;
    bool turnRight = (originalBoard[x][y] == 0); // 初始转向

    for (int i = 0; i < steps; i++) {
        // 反转颜色
        board[x][y] = !board[x][y];

        // 转向
        if (turnRight) dir = (dir % 4) + 1; // 右转
        else dir = (dir + 2) % 4 == 0 ? 4 : (dir + 2) % 4; // 左转

        // 移动
        switch (dir) {
        case 1: y--; break;
        case 2: y++; break;
        case 3: x--; break;
        case 4: x++; break;
        }

        // 越界检查
        if (x < 0 || x >= size || y < 0 || y >= size) return false;

        // 切换转向规则
        turnRight = !turnRight;
    }

    antX = x; antY = y; antDirection = dir;
    return true;
}

// 碰壁走廊模式模拟
bool funMode::simulateAntsHit() {
    // 复制当前棋盘作为模拟起点
    int** tempBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        tempBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    int x = antX, y = antY;
    int dir = antDirection;

    for (int i = 0; i < steps; i++) {
        // 记录当前格子状态
        int color = tempBoard[x][y];

        // 基础转向（黑白格规则）
        if (color == 0) dir = (dir % 4) + 1; // 白格右转
        else dir = (dir + 2) % 4 == 0 ? 4 : (dir + 2) % 4; // 黑格左转

        // 处理障碍和墙（最多尝试4次右转）
        int attempts = 0;
        bool moved = false;
        while (attempts < 4) {
            int nx = x, ny = y;
            switch (dir) {
            case 1: ny--; break; // 上
            case 2: ny++; break; // 下
            case 3: nx--; break; // 左
            case 4: nx++; break; // 右
            }

            // 检查是否合法（非墙且非障碍）
            if (nx >= 0 && nx < size && ny >= 0 && ny < size && obstacle[nx][ny] != '#') {
                x = nx; y = ny;
                moved = true;
                break;
            }

            dir = (dir % 4) + 1; // 右转
            attempts++;
        }

        if (!moved) {
            // 释放临时数组
            for (int i = 0; i < size; i++) {
                delete[] tempBoard[i];
            }
            delete[] tempBoard;
            return false; // 无法移动，题目无效
        }

        // 反转颜色 - 根据规则修改：只有在正常移动时才变色
        if (attempts == 0) { // 没有遇到障碍，正常移动
            tempBoard[x][y] = !tempBoard[x][y];
        }
    }

    // 保存模拟结果到正确的初始棋盘
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            correctInitialBoard[i][j] = tempBoard[i][j];
        }
    }

    // 释放临时数组
    for (int i = 0; i < size; i++) {
        delete[] tempBoard[i];
    }
    delete[] tempBoard;

    antX = x; antY = y; antDirection = dir;
    return true;
}

// 生成扭曲世界题目
void funMode::generateTwistedQuestion() {
    cout << "\n=== 扭曲世界题目 ===" << endl;
    cout << "棋盘大小：" << size << "x" << size << endl;
    cout << "蚂蚁最终位置：(" << antX << ", " << antY << ")" << endl;
    cout << "最终朝向：" << antDirection << endl;
    cout << "步数：" << steps << endl;
    cout << "最终棋盘：" << endl;
    printBoard(board);
}

// 生成碰壁走廊题目 - 修改后
void funMode::generateHitQuestion() {
    cout << "\n=== 碰壁走廊题目 ===" << endl;
    cout << "棋盘大小：" << size << "x" << size << endl;
    cout << "蚂蚁最终位置：(" << antX << ", " << antY << ")" << endl;
    cout << "最终朝向：" << antDirection << endl;
    cout << "步数：" << steps << endl;
    cout << "最终棋盘（含障碍）：" << endl;
    printBoard(board);
}

// 验证用户输入的题目是否有效 - 修复后
bool funMode::validateUserQuestion() {
    // 检查蚂蚁初始位置是否在棋盘内
    if (antX < 0 || antX >= size || antY < 0 || antY >= size) {
        cout << "错误：蚂蚁位置超出棋盘范围！" << endl;
        return false;
    }

    // 检查蚂蚁初始位置是否为障碍
    if (obstacle[antX][antY] == '#') {
        cout << "错误：蚂蚁初始位置不能是障碍！" << endl;
        return false;
    }

    // 复制最终棋盘状态作为模拟起点
    int** tempBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        tempBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    // 保存当前棋盘状态作为初始棋盘
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            originalBoard[i][j] = board[i][j];
        }
    }

    // 模拟蚂蚁移动，检查是否能完成所有步数
    int x = antX, y = antY;
    int dir = antDirection;

    // 记录每个位置和方向的访问次数，防止死循环
    int visited[100][100][5] = { 0 }; // 假设最大棋盘100x100，4个方向+1个备用

    for (int i = 0; i < steps; i++) {
        int color = board[x][y];

        // 检查是否进入循环
        if (++visited[x][y][dir] > 4) {
            cout << "错误：蚂蚁在第" << i + 1 << "步进入了循环！" << endl;

            // 释放临时数组
            for (int i = 0; i < size; i++) {
                delete[] tempBoard[i];
            }
            delete[] tempBoard;

            return false;
        }

        // 基础转向
        if (color == 0) dir = (dir % 4) + 1; // 白格右转
        else dir = (dir + 2) % 4 == 0 ? 4 : (dir + 2) % 4; // 黑格左转

        // 尝试找到可移动方向
        int attempts = 0;
        bool moved = false;
        while (attempts < 4) {
            int nx = x, ny = y;
            switch (dir) {
            case 1: ny--; break;
            case 2: ny++; break;
            case 3: nx--; break;
            case 4: nx++; break;
            }

            if (nx >= 0 && nx < size && ny >= 0 && ny < size && obstacle[nx][ny] != '#') {
                x = nx; y = ny;
                moved = true;
                break;
            }

            dir = (dir % 4) + 1;
            attempts++;
        }

        if (!moved) {
            cout << "错误：蚂蚁在第" << i + 1 << "步无法移动！" << endl;

            // 释放临时数组
            for (int i = 0; i < size; i++) {
                delete[] tempBoard[i];
            }
            delete[] tempBoard;

            return false;
        }

        // 反转颜色 - 根据规则修改
        if (attempts == 0) {
            board[x][y] = !board[x][y];
        }
    }

    // 恢复用户输入的最终棋盘状态
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = tempBoard[i][j];
        }
        delete[] tempBoard[i];
    }
    delete[] tempBoard;

    return true;
}

// 生成用户自定义题目 - 修改后
void funMode::generateUserQuestion() {
    cout << "\n=== 用户自定义碰壁走廊题目 ===" << endl;
    cout << "请输入棋盘大小：";
    cin >> size;

    // 重新分配内存
    for (int i = 0; i < size; i++) {
        delete[] board[i];
        delete[] originalBoard[i];
        delete[] obstacle[i];
        delete[] correctInitialBoard[i];
    }
    delete[] board;
    delete[] originalBoard;
    delete[] obstacle;
    delete[] correctInitialBoard;

    initBoard();
    initObstacle();

    cout << "请输入蚂蚁最终位置 (x y)：";
    cin >> antX >> antY;

    cout << "请输入蚂蚁最终朝向 (1=上, 2=下, 3=左, 4=右)：";
    cin >> antDirection;

    cout << "请输入蚂蚁走过的步数：";
    cin >> steps;

    cout << "请输入含障碍的最终棋盘（" << size << "x" << size << "，0=白格，1=黑格，#=障碍）：" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char cell;
            cin >> cell;

            if (cell == '#') {
                obstacle[i][j] = '#';
                board[i][j] = 0; // 障碍所在位置默认为白格
            }
            else {
                obstacle[i][j] = ' ';
                board[i][j] = (cell == '1') ? 1 : 0;
            }
        }
    }

    // 保存最终棋盘状态作为正确初始棋盘的起点
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            correctInitialBoard[i][j] = board[i][j];
        }
    }

    // 验证题目有效性
    if (!validateUserQuestion())
    {
        cout << "题目无效！请重新开始。" << endl;
        return;
    }

    // 显示题目
    cout << "\n=== 已验证的碰壁走廊题目 ===" << endl;
    cout << "棋盘大小：" << size << "x" << size << endl;
    cout << "蚂蚁最终位置：(" << antX << ", " << antY << ")" << endl;
    cout << "最终朝向：" << antDirection << endl;
    cout << "步数：" << steps << endl;
    cout << "最终棋盘（含障碍）：" << endl;
    printBoard(board);
}

// 析构函数
funMode::~funMode() {
    for (int i = 0; i < size; i++) {
        delete[] board[i];
        delete[] originalBoard[i];
        delete[] obstacle[i];
        delete[] correctInitialBoard[i];
    }
    delete[] board;
    delete[] originalBoard;
    delete[] obstacle;
    delete[] correctInitialBoard;
}

// 扭曲世界模式（电脑出题） 
void funMode::TwistedWorld() {
    // 显示游戏介绍
    std::cout << "====欢迎来到扭曲世界！===" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << "背景:兰顿蚂蚁从自由模式离开来到这后发现这个世界的规则被扭曲了" << std::endl;
    std::cout << "新的规则：蚂蚁的第一次转弯方向仍由初始位置黑白格决定，但接下来每走一步，转弯方向逆转" << std::endl;
    std::cout << "在新的规则下，回溯难度大大提高，快来尝试吧！" << std::endl;
    std::cout << "蚂蚁走过n步形成蚁行图，你要根据蚁行图回溯出棋盘初始状态方为作答完毕" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << std::endl;
    std::cout << "请注意：本模式下，电脑随机生成有解题目供你作答" << std::endl;

    // 生成有效题目 - 添加尝试次数限制
    std::cout << "正在生成题目...\n";
    int** realOriginalBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        realOriginalBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            realOriginalBoard[i][j] = originalBoard[i][j];
        }
    }

    int maxAttempts = 1000; // 最大尝试次数
    int attempts = 0;
    while (!simulateTwistedWorld() && attempts < maxAttempts) {
        resetAnt();
        attempts++;
    }

    if (attempts >= maxAttempts) {
        std::cout << "无法生成有效题目，请重试！" << std::endl;
        for (int i = 0; i < size; i++) {
            delete[] realOriginalBoard[i];
        }
        delete[] realOriginalBoard;
        return;
    }

    // 显示题目
    generateTwistedQuestion();

    // 获取用户答案
    inputBoard(originalBoard);

    // 验证答案
    if (compareBoards()) {
        std::cout << "恭喜！你的答案完全正确！\n";
    }
    else {
        std::cout << "答案错误\n";
        std::cout << "正确初始棋盘为：\n";
        printBoard(realOriginalBoard);
    }
    // 释放备份棋盘的内存
    for (int i = 0; i < size; i++) {
        delete[] realOriginalBoard[i];
    }
    delete[] realOriginalBoard;
}

// 碰壁走廊模式 
void funMode::AntsHit() {
    // 显示游戏介绍
    std::cout << "====欢迎来到碰壁走廊！===" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << "背景:兰顿蚂蚁来到了一条充满障碍的走廊" << std::endl;
    std::cout << "新的规则：当蚂蚁遇到墙壁或障碍时，它会尝试向右转直到找到可移动的方向前进一格而不变色" << std::endl;
    std::cout << "在这条走廊中，你需要根据最终的蚁行图和障碍布局，回溯出初始棋盘状态" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << std::endl;
    std::cout << "请注意：本模式下，你可以自定义含障碍的题目" << std::endl;

    // 生成用户自定义题目
    generateUserQuestion();

    // 模拟蚂蚁移动，计算正确的初始棋盘
    if (!simulateAntsHit()) {
        std::cout << "题目无效，无法模拟蚂蚁移动！" << std::endl;
        return;
    }

    // 获取用户答案
    inputBoard(originalBoard);

    // 验证答案
    if (compareBoards()) {
        std::cout << "恭喜！你的答案完全正确！\n";
    }
    else {
        std::cout << "答案错误\n";
        std::cout << "正确初始棋盘为：\n";
        printBoard(correctInitialBoard); // 使用正确的初始棋盘
    }
}

// 趣味模式选图
void funMode::chooseMap() {
    std::cout << "欢迎来到趣味模式！" << std::endl;
    std::cout << "请选择地图" << std::endl;
    std::cout << "1. 扭曲世界" << std::endl;
    std::cout << "2. 碰壁走廊" << std::endl;
    std::cout << "请输入你想进入的地图对应的序号" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        TwistedWorld();
        break;
    case 2:
        AntsHit();
        break;
    default:
        std::cout << "无效选择！" << std::endl;
    }
}