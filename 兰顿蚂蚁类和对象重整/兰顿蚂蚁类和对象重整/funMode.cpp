#include "funMode.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include<algorithm>//reverse
#include <graphics.h>// EasyX 图形库头文件
#include<Windows.h>
#include <conio.h>
using namespace std;

// 构造函数：初始化通用属性
funMode::funMode() {
    srand(time(0));
    size = rand() % 3 + 3; // 默认棋盘大小为3*3到5*5（可调整）
    initBoard();
    initObstacle();
    resetAnt();
}


//构造函数2，用来初始化觉醒之路
funMode::funMode(int n)
{
    srand(time(0));
    size = n;//棋盘大小人为控制
    initBoard();//随机生成棋盘
    initObstacle(n);//人为控制障碍的数量为棋盘边长，随机分布障碍在棋盘上的位置
    resetAnt();//随机生成蚂蚁的初始位置、初始朝向、步数用于模拟
}

void funMode::initObstacle(int n)//随机设置指定数量的障碍，觉醒之路模式
{
    obstacle = new char* [n];
    for (int i = 0; i < n; i++)
    {
        obstacle[i] = new char[n];
        for (int j = 0; j < n; j++)
        {
            obstacle[i][j] = ' ';  // 初始化所有位置为空
        }
    }
    // 随机放置 n 个障碍
    int count = 0;
    while (count < n)
    {
        int x = rand() % n;  // 生成 0 到 n-1 之间的随机数
        int y = rand() % n;

        if (obstacle[x][y] != '#')  // 如果该位置没有障碍才放，保证一个位置只放一个障碍
        {
            obstacle[x][y] = '#';    // 设置为障碍
            count++;
        }
    }
}

// 初始化棋盘
void funMode::initBoard() {
    board = new int* [size];
    originalBoard = new int* [size];
    finalBoard = new int* [size]; // 正确的初始棋盘
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        originalBoard[i] = new int[size];
        finalBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = rand() % 2; // 随机黑白格
            originalBoard[i][j] = board[i][j];
            finalBoard[i][j] = board[i][j];
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

// 重置蚂蚁状态，电脑在一定范围内随机生成
void funMode::resetAnt() {
    antX = rand() % size;
    antY = rand() % size;
    antDirection = rand() % 4 + 1; // 1-4
    steps = rand() % 11 + 5; // 5-15步
}

// 扭曲世界和碰壁走廊的题目或答案打印函数
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


// 输入棋盘状态
void funMode::inputBoard(int** arr) 
{
    cout << "请开始作答，输入" << size << "x" << size << "的初始棋盘（0=白格，1=黑格，#=障碍）：" << endl;
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

// 扭曲世界和碰壁走廊的答案判定函数
bool funMode::compareBoards(int** arr)//传入的参数是棋盘初始状态，即正确答案
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (obstacle[i][j] == '#')
            {
				arr[i][j] = 0; // 障碍格子默认为白格
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (originalBoard[i][j] != arr[i][j]) return false;//这里的originalBoard是用户输入的作答棋盘
        }
    }
    return true;
}

// 模拟函数（扭曲世界模式）
bool funMode::simulateTwistedWorld() //在初始棋盘的基础上顺序走完步数，看能否得到蚁行图，走的过程不越界就有解，board存储模拟完的蚁行图
{
    int x = antX, y = antY;
    int dir = antDirection;
    bool turnRight = (originalBoard[x][y] == 0); // 初始转向

    for (int i = 0; i < steps; i++) {
        // 反转颜色
        board[x][y] = !board[x][y];

        // 转向
        if (turnRight)
        {
            switch (dir)
            {
            case 1:
            {
                dir = 4;
                break;
            }
            case 2:
            {
                dir = 3;
                break;
            }
            case 3:
            {
                dir = 1;
                break;
            }
            case 4:
            {
                dir = 2;
                break;
            }
            }
        }
        else
        {
            switch (dir)
            {
            case 1:
            {
                dir = 3;
                break;
            }
            case 2:
            {
                dir = 4;
                break;
            }
            case 3:
            {
                dir = 2;
                break;
            }
            case 4:
            {
                dir = 1;
                break;
            }
            }
        }

        // 移动
        switch (dir)
        {
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

    antX = x; antY = y; antDirection = dir;//将模拟结束后蚂蚁的最终位置和朝向保存
    return true;
}

// 碰壁走廊模式模拟
bool funMode::simulateAntsHit()
{
    correctPath.clear(); // 清空之前的路径记录

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

    correctPath.emplace_back(x, y);//记录起始坐标位置

    for (int i = 0; i < steps; i++) {
        // 记录当前格子状态
        int color = tempBoard[x][y];

        // 转向
        if (color==0)//白格右转
        {
            switch (dir)
            {
            case 1:
            {
                dir = 4;
                break;
            }
            case 2:
            {
                dir = 3;
                break;
            }
            case 3:
            {
                dir = 1;
                break;
            }
            case 4:
            {
                dir = 2;
                break;
            }
            }
        }
        else//黑格左转
        {
            switch (dir)
            {
            case 1:
            {
                dir = 3;
                break;
            }
            case 2:
            {
                dir = 4;
                break;
            }
            case 3:
            {
                dir = 2;
                break;
            }
            case 4:
            {
                dir = 1;
                break;
            }
            }
        }

        // 处理障碍和墙（最多尝试4次右转）
        int attempts = 0;
        bool moved = false;
        while (attempts < 4)
        {
            int nx = x, ny = y;
            switch (dir) 
            {
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

            //遇到墙或障碍时就尝试右转
            switch (dir)
            {
            case 1:
            {
                dir = 4;
                break;
            }
            case 2:
            {
                dir = 3;
                break;
            }
            case 3:
            {
                dir = 1;
                break;
            }
            case 4:
            {
                dir = 2;
                break;
            }
            }
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

        correctPath.emplace_back(x, y);//记录移动一步后的坐标位置
    }

    // 保存模拟结果到最终棋盘
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            finalBoard[i][j] = tempBoard[i][j];
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
    std::string dire;
    switch (antDirection)
    {
    case 1:
    {
        dire = "UP";
        break;
    }
    case 2:
    {
        dire = "DOWN";
        break;
    }
    case 3:
    {
        dire = "LEFT";
        break;
    }
    case 4:
    {
        dire = "RIGHT";
        break;
    }
    }
    cout << "最终朝向：" << dire << endl;
    cout << "步数：" << steps << endl;
    cout << "最终棋盘：" << endl;
    printBoard(board);
}

// 用户自定义题目
bool funMode::generateUserQuestion() {
    cout << "\n=== 用户自定义初始的碰壁走廊 ===" << endl;
    cout << "请输入棋盘大小：";
    cin >> size;

    // 重新分配内存
    for (int i = 0; i < size; i++) {
        delete[] board[i];
        delete[] originalBoard[i];
        delete[] obstacle[i];
        delete[] finalBoard[i];
    }
    delete[] board;
    delete[] originalBoard;
    delete[] obstacle;
    delete[] finalBoard;

    initBoard();
    initObstacle();

    cout << "请输入蚂蚁初始位置 (x y)：";
    cin >> antX >> antY;

    cout << "请输入蚂蚁初始朝向 (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)：";
    cin >> antDirection;

    cout << "请输入蚂蚁走过的步数：";
    cin >> steps;//都是直接修改成员变量

    cout << "请输入含障碍的初始棋盘（" << size << "x" << size << "，0=白格，1=黑格，#=障碍）：" << endl;
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
                board[i][j] = (cell == '1') ? 1 : 0;//用board存储初始棋盘，即答案
            }
        }
    }

    // 模拟蚂蚁移动，计算最终棋盘
    if (!simulateAntsHit()) 
    {
        std::cout << "题目无效，蚂蚁会在某处陷入死循环！" << std::endl;
        return false;
    }//经过该模拟，finalBoard存蚁行图，board存答案的初始棋盘

    // 显示题目
    cout << "\n=== 已验证有解的碰壁走廊题目 ===" << endl;
    cout << "棋盘大小：" << size << "x" << size << endl;
    cout << "蚂蚁最终位置：(" << antX << ", " << antY << ")" << endl;
    std::string dire;
    switch (antDirection)
    {
    case 1:
    {
        dire = "UP";
        break;
    }
    case 2:
    {
        dire = "DOWN";
        break;
    }
    case 3:
    {
        dire = "LEFT";
        break;
    }
    case 4:
    {
        dire = "RIGHT";
        break;
    }
    }
    cout << "最终朝向：" << dire << endl;
    cout << "步数：" << steps << endl;
    cout << "最终棋盘（含障碍）：" << endl;
    printBoard(finalBoard);
    return true;
}

// 析构函数
funMode::~funMode() {
    for (int i = 0; i < size; i++) {
        delete[] board[i];
        delete[] originalBoard[i];
        delete[] obstacle[i];
        delete[] finalBoard[i];
    }
    delete[] board;
    delete[] originalBoard;
    delete[] obstacle;
    delete[] finalBoard;
}

void funMode::answerQues()
{
    cout << "欢迎来到觉醒之路的答题环节，每答对一题，你将获得一张带有说明书的道具卡！" << endl;
    obtainedTools.clear();//初始化清空

    int _year1 = 0;
    cout << "问题1：中国共产党的诞生时间" << endl;
    cin >> _year1;
    if (_year1 == year1)
    {
        obtainedTools.push_back(ToolType::DES);
        cout << "恭喜你获得道具卡——暴力拆迁" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          暴力拆迁:" << endl;
        cout << "开始答题前，选择性拆除部分障碍" << endl;
        cout << "程序自动更新答案，用户开始作答" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "很遗憾！本题未答对" << endl;
    }
    cout << endl;
    int _year2 = 0;
    cout << "问题2：新中国的成立时间" << endl;
    cin >> _year2;
    if (_year2 == year2)
    {
        obtainedTools.push_back(ToolType::PRE);
        cout << "恭喜你获得道具卡——预言大师" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          预言大师:" << endl;
        cout << "开始答题前，    你可以提前预知" << endl;
        cout << "最多 6个初始棋盘格子的正确颜色" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "很遗憾！本题未答对" << endl;
    }
    cout << endl;
    string _site ;
    cout << "问题3：中国的首都城市" << endl;
    cin >> _site;
    if (_site == site)
    {
        obtainedTools.push_back(ToolType::CONS);
        cout << "恭喜你获得道具卡——蚂蚁有灵" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          蚂蚁有灵:" << endl;
        cout << "作答期间，  蚂蚁觉醒了自我意识" << endl;
        cout << "主动纠正已作答，并自动填充 3步" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "很遗憾！本题未答对" << endl;
    }
    cout << endl;
    int _rank = 0;
    cout << "问题4：中国GDP的世界排名" << endl;
    cin >> _rank;
    if (_rank == rank)
    {
        obtainedTools.push_back(ToolType::BACK);
        cout << "恭喜你获得道具卡——落子有悔" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          落子有悔:" << endl;
        cout << "结束答题，系统若检测出答题有误" << endl;
        cout << "提示你在第几步出错，  再来一次" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "很遗憾！本题未答对" << endl;
    }
}

//生成觉醒之路题目
bool funMode::generateAwakenRoad()
{
    // 生成有效题目 - 添加尝试次数限制
    std::cout << "正在生成题目...\n";
    int** realOriginalBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        realOriginalBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            realOriginalBoard[i][j] = originalBoard[i][j];//提前保存正确的初始棋盘
        }
    }
    int maxAttempts = 1000; // 最大尝试次数
    int attempts = 1;
    while (!simulateAntsHit() && attempts < maxAttempts)//利用board的临时数组进行模拟，得到finalBoard
    {
        resetAnt();//重置蚂蚁的初始位置、初始朝向、步数
        attempts++;
    }

    if (attempts >= maxAttempts) {
        std::cout << "无法生成有效题目，请重试！" << std::endl;
        for (int i = 0; i < size; i++) {
            delete[] realOriginalBoard[i];
        }
        delete[] realOriginalBoard;
        return false;
    }
    std::cout << "有解题目已生成，尝试" << attempts << "次" << std::endl;
    // 显示棋盘和具体题目信息
     // 显示题目
    cout << "\n=== 已验证有解的题目 ===" << endl;
    cout << "棋盘大小：" << size << "x" << size << endl;
    cout << "蚂蚁最终位置：(" << antX << ", " << antY << ")" << endl;
    std::string dire;
    switch (antDirection)
    {
    case 1:
    {
        dire = "UP";
        break;
    }
    case 2:
    {
        dire = "DOWN";
        break;
    }
    case 3:
    {
        dire = "LEFT";
        break;
    }
    case 4:
    {
        dire = "RIGHT";
        break;
    }
    }
    cout << "最终朝向：" << dire << endl;
    cout << "步数：" << steps << endl;
    cout << "最终棋盘（含障碍）：" << endl;
    printBoard(finalBoard);//打印finalBoard和其他题目信息

    // 释放备份棋盘的内存
    for (int i = 0; i < size; i++) {
        delete[] realOriginalBoard[i];
    }
    delete[] realOriginalBoard;

    return true;
}

// 选择道具卡
void funMode::chooseTool() {
    if (obtainedTools.empty()) {
        cout << "你还没有获得任何道具卡！\n";
        return;
    }

    cout << "\n你已获得的道具卡（可选择多个，用空格分隔序号）：\n";
    vector<pair<int, ToolType>> toolOptions;
    for (int i = 0; i < obtainedTools.size(); i++) {
        ToolType type = obtainedTools[i];
        string name;
        switch (type) {
        case ToolType::BACK:   name = "落子有悔"; break;
        case ToolType::PRE:    name = "预言大师"; break;
        case ToolType::CONS:   name = "蚂蚁有灵"; break;
        case ToolType::DES:    name = "暴力拆迁"; break;
        default: continue;
        }
        toolOptions.emplace_back(i + 1, type);
        cout << i + 1 << ". " << name << endl;
    }

    cout << "\n请输入要使用的道具卡序号（如1 3）：(按回车结束选择)";
    vector<int> selectedIndices;
    int index;
    while (cin >> index) {
        selectedIndices.push_back(index);
        if (cin.get() == '\n') break;
    }

    for (int idx : selectedIndices) 
    {
        if (idx < 1 || idx > toolOptions.size()) {
            cout << "无效序号：" << idx << endl;
            continue;
        }
        ToolType type = toolOptions[idx - 1].second;
        useTool(type);
    }
}

// 使用单个道具卡
void funMode::useTool(ToolType type) {
    switch (type) {
    case ToolType::BACK:   BackOpera(); break;
    case ToolType::PRE:    PredictMaster(); break;
    case ToolType::CONS:   CreatCons(); break;
    case ToolType::DES:    Destroy(); break;
    default: break;
    }
}

//落子有悔道具卡
void funMode::BackOpera()
{
    cout << "正在使用落子有悔道具卡..." << endl;
    inputBoard(originalBoard);
    if (compareBoards(board))
    {
        cout << "提前恭喜你回答正确！不需要使用该卡了" << endl;
        return;
    }
    else
    {
        cout << "系统提前检测到你的作答有误，现在使用该卡" << endl;
        //逆序数组
        reverse(correctPath.begin(), correctPath.end());
        int step = 0;
        while (step < correctPath.size())
        {
            int x = correctPath[step].first;
            int y = correctPath[step].second;
            if (originalBoard[x][y] != board[x][y])
            {
                cout << "你在第" << step+1 << "步回溯时就已经发生错误！" << endl;
                break;
            }
            step++;
        }
        cout << "再来一次吧" << endl;
    }
}
//预言大师道具卡
void funMode::PredictMaster()
{
    cout << "正在使用预言大师道具卡..." << endl;
    int counter = 6;
    while (counter)
    {
        cout << "请输入你想查看的答案棋盘某位置的坐标(障碍柱位置已知)" << endl;
        int x = 0, y = 0;
        cin >> x >> y;
        cout << "预言结果如下：" << endl;
        string ch;
        if (board[x][y] == 0)
        {
            ch = "白";
        }
        else
        {
            ch = "黑";
        }
        cout <<"该格颜色为"<< ch <<"色" << endl;
        counter--;
        if (counter)
        {
            cout << "你的预言次数未用完，是否继续预言？(yes/no)" << endl;
            string choice;
            cin >> choice;
            if (choice == "yes")
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    cout << "你已知晓了部分格子的正确颜色，快来开始作答吧" << endl;
}

void funMode::inputBoard(vector<string>& userboard)
{
    cout << "请输入" << size << "x" << size << "的初始棋盘（0=白格，1=黑格，#=障碍）：" << endl;
    cout << "当你输入useTool时，开始使用蚂蚁有灵道具卡" << endl;
    string ch1;
    while (cin >> ch1)
    {
        if (ch1 == "useTool")
        {
            break;
        }
        userboard.push_back(ch1);
    }
}

//蚂蚁有灵道具卡
void funMode::CreatCons()
{
    // 清空所有相关容器，避免旧数据干扰
    userBoard.clear();
    answerBoard.clear();
    obstacleBoard.clear();

    inputBoard(userBoard);
    cout << "正在使用蚂蚁有灵道具卡..." << endl;
    //将原二维答案数组先降为一维数组
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            char ch2;
            if (board[i][j] == 0)
            {
                ch2 = '0';
            }
            else
            {
                ch2 = '1';
            }
            answerBoard.push_back(ch2);
            obstacleBoard.push_back(obstacle[i][j]);
        }
    }
 

    //  打印棋盘（限制在有效范围内，避免越界）
    int totalCells = userBoard.size() + 3;
    int maxValidIndex = min(totalCells, size * size); // 防止越界


    cout << "该道具卡使用结果如下,已回溯部分被校对，蚂蚁自动填充了3步，请继续作答" << endl;
    for (int i = 0; i < maxValidIndex ;i++)
    {
        if (obstacleBoard[i] == '#')
        {
            cout << "#";
        }
        else
        {
            cout << answerBoard[i];
        }

        // 控制空格和换行：每行前三个字符后加空格，第四个字符后换行
        if ((i + 1) % 4 == 0)  // 每行的最后一个字符后换行
        {
            cout << endl;
        }
        else  // 非行末字符后加空格
        {
            cout << " ";
        }
    }
    cout << endl;
}


//暴力拆迁道具卡
void funMode::Destroy()
{
    cout << "正在使用暴力拆迁道具卡..." << endl;
    string choice1;
    cout << "是否开始拆除障碍柱？（yes/no）" << endl;
    cin >> choice1;
    while (choice1 == "yes")
    {
        cout << "请输入你想拆除障碍柱的位置坐标" << endl;
        int x = 0, y = 0;
        cin >> x >> y;
        obstacle[x][y] = 0;
        cout << "原位置障碍柱被拆除，默认为白格" << endl;
        cout << "是否继续拆除？（yes/no）" << endl;
        cin >> choice1;
    }
    cout << "正在更新题目和答案..." << endl;

    //再次生成觉醒之路题目
    generateAwakenRoad();
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
            realOriginalBoard[i][j] = originalBoard[i][j];//提前保存正确的初始棋盘
        }
    }

    int maxAttempts = 1000; // 最大尝试次数
    int attempts = 1;
    while (!simulateTwistedWorld() && attempts < maxAttempts)//利用board进行模拟
    {
        resetAnt();//重置蚂蚁的初始位置、初始朝向、步数
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
    std::cout << "有解题目已生成，尝试" << attempts << "次" << std::endl;
    // 显示题目
    generateTwistedQuestion();//打印模拟完的board和其他题目信息

    // 获取用户答案
    inputBoard(originalBoard);//修改成员变量originalBoard作为作答棋盘

    // 验证答案
    if (compareBoards(realOriginalBoard))
    {
        std::cout << "恭喜！你的答案完全正确！\n";
    }
    else
    {
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

// 碰壁走廊模式 （用户自定义）
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

    // 生成用户自定义题目,判断是否有解
    if (generateUserQuestion())
    {
        // 获取用户答案
        inputBoard(originalBoard);//修改originalBoard作为用户作答棋盘

        // 验证答案
        if (compareBoards(board))
        {
            std::cout << "恭喜！你的答案完全正确！\n";
        }
        else
        {
            std::cout << "答案错误\n";
            std::cout << "正确初始棋盘为：\n";
            printBoard(board);
        }
    }
}

//觉醒之路模式（电脑出题）
void funMode::ToolsRoad()
{
    // 显示游戏介绍
    std::cout << "====欢迎来到觉醒之路！===" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << "背景:兰顿蚂蚁发现回溯越来越难，觉醒了外挂" << std::endl;
    std::cout << "新模式：答题获取道具卡，在游戏进行的过程中可使用来简化游戏" << std::endl;
    std::cout << "在新模式下，答对的题越多，获得的道具卡就越多，快来尝试吧！" << std::endl;
    std::cout << "蚂蚁走过n步形成蚁行图，你要根据蚁行图回溯出棋盘初始状态方为作答完毕" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << std::endl;
    std::cout << "请注意：本模式下，电脑随机生成含障碍的有解题目供你作答" << std::endl;
    cout << endl;
    //进入答题环节，获取道具卡
    answerQues();
    //生成觉醒之路题目
    if (generateAwakenRoad())
    {
        //选择道具
        chooseTool();
        inputBoard(originalBoard);
        if (compareBoards(board))
        {
            cout << "恭喜你回答正确！" << endl;
            return;
        }
        else
        {
            cout << "答案错误\n";
            cout << "正确初始棋盘为：\n";
            printBoard(board);
            return;
        }
    }
}

// 初始化静态成员变量
const std::vector<std::pair<int, int>> funMode::DIRECTIONS = {
    {-1, 1}, {1, 1}, {-2, 0}, {2, 0}, {-1, -1}, {1, -1} // OA, OB, OC, OD, OE, OF
};

int funMode::coordToIndex(int x, int y) const 
{
    if (x == -1 && y == 1) return 0;  // 顶部左
    if (x == 1 && y == 1) return 1;   // 顶部右
    if (x == -2 && y == 0) return 2;  // 左
    if (x == 0 && y == 0) return 3;   // 中
    if (x == 2 && y == 0) return 4;   // 右
    if (x == -1 && y == -1) return 5; // 底部左
    if (x == 1 && y == -1) return 6;  // 底部右
    return -1; // 无效坐标
}

std::pair<int, int> funMode::indexToCoord(int idx) const {
    std::vector<std::pair<int, int>> coords = {
        {-1, 1}, {1, 1}, {-2, 0}, {0, 0}, {2, 0}, {-1, -1}, {1, -1}
    };
    return coords[idx];
}

std::vector<int> funMode::simulateAntMovement(std::vector<int>& initialGrid,
    int& startX, int& startY,
    const std::vector<int>& directions) const {
    std::vector<int> grid = initialGrid;
    int x = startX, y = startY;

    for (int dir : directions) {
        int idx = coordToIndex(x, y);
        if (idx == -1) break; // 无效坐标，退出模拟

        // 翻转当前格子
        grid[idx] = !grid[idx];

        // 移动到下一个格子
        x += DIRECTIONS[dir].first;
        y += DIRECTIONS[dir].second;
    }
	startX = x;
	startY = y;
    return grid;
}

void funMode::printHexagon(const std::vector<int>& grid) const {
    std::cout << " " << grid[0] << " " << grid[1] << std::endl;
    std::cout << grid[2] << " " << grid[3] << " " << grid[4] << std::endl;
    std::cout << " " << grid[5] << " " << grid[6] << std::endl;
}

void funMode::displayImage(const string& imagePath)
{
    // Convert std::string to std::wstring
    int len = MultiByteToWideChar(CP_UTF8, 0, imagePath.c_str(), -1, NULL, 0);
    std::wstring wideImagePath(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, imagePath.c_str(), -1, &wideImagePath[0], len);

    // Load image
    IMAGE img;
    loadimage(&img, wideImagePath.c_str(), 0, 0, true);

    // Get window and image dimensions
    int winWidth = getwidth();
    int winHeight = getheight();
    int imgWidth = img.getwidth();
    int imgHeight = img.getheight();

    // Calculate centered position
    int x = (winWidth - imgWidth) / 2;
    int y = (winHeight - imgHeight) / 2;

    // Display image
    putimage(x, y, &img);
}

void funMode::HexagonalPath()
{
    // 程序员自定义初始状态
    std::vector<int> initialGrid = { 0, 1, 1, 0, 0, 1, 0 };

    // 程序员自定义三个移动方向
    std::vector<int> directions = { 2, 5, 3 }; // 

    // 模拟蚂蚁移动
    std::vector<int> finalGrid = simulateAntMovement(initialGrid, startX, startY, directions);

    // 显示题目
    std::cout << "====欢迎来到六方通道！===" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << "背景:兰顿蚂蚁掉进了一个格子都是六边形的棋盘，每一次有6个前进方向可以选择" << std::endl;
    std::cout << "新模式：题目会提供蚂蚁的最终位置和蚂蚁移动时使用的向量，根据提示图作答" << std::endl;
    std::cout << "蚂蚁走过n步形成蚁行图，你要根据蚁行图回溯出棋盘初始状态方为作答完毕" << std::endl;
    std::cout << "——————————————————————————————————————————" << std::endl;
    std::cout << std::endl;
    std::cout << "请注意：本模式下，电脑生成有解题目供你作答" << std::endl;
    cout << endl;


    // 初始化图形窗口
    initgraph(1000, 750, EX_SHOWCONSOLE);   // 创建一个800x600的窗口
    setbkcolor(WHITE);     // 设置背景色为白色
    cleardevice();         // 清屏

	std::string imagePath = "C:\\Users\\w\\Desktop\\tip.png"; 
    // 显示图片
    displayImage(imagePath);

    std::cout << "最终格子状态:" << std::endl;
    printHexagon(finalGrid);
    std::cout << "蚂蚁最终坐标: (" << startX << ", " << startY << ")" << std::endl;
    std::cout << "蚂蚁移动先后使用的向量坐标(0-5对应OA-OF): ";
    for (int dir : directions) {
        std::cout << dir << " ";
    }
    std::cout << std::endl;

    // 获取用户答案
    std::vector<int> userAnswer(7);
    std::cout << "请输入初始棋盘： ";
    for (int i = 0; i < 7; ++i) {
        std::cin >> userAnswer[i];
    }

    // 检查答案
    bool correct = true;
    for (int i = 0; i < 7; ++i) {
        if (userAnswer[i] != initialGrid[i]) {
            correct = false;
            break;
        }
    }
    std::cout << "正确答案: ";
    std::cout << endl;
	printHexagon(initialGrid);
    std::cout << (correct ? "恭喜，回答正确！" : "回答错误，再试一次！") << std::endl;

}

// 趣味模式选图
void funMode::chooseMap()
{
    std::cout << "欢迎来到趣味模式！" << std::endl;
    std::cout << "请选择地图" << std::endl;
    std::cout << "1. 扭曲世界" << std::endl;
    std::cout << "2. 碰壁走廊" << std::endl;
    std::cout << "3. 觉醒之路" << std::endl;
    std::cout << "4. 六方通道" << std::endl;
    std::cout << "请输入你想进入的地图对应的序号" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        funMode mode1;
        mode1.TwistedWorld();
        break;
    }
    case 2:
    {
        funMode mode2;
        mode2.AntsHit();
        break;
    }
    case 3:
    {
        funMode mode3(4);
        mode3.ToolsRoad();
        break;
    }
    case 4:
    {
        funMode mode4;
        mode4.HexagonalPath();
        break;
    }
    default:
        std::cout << "无效选择！" << std::endl;
    }
}