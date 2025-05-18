#ifndef FUNMODE_H
#define FUNMODE_H

class funMode {
private:
    int** board;          // 棋盘状态
    int** originalBoard;  // 初始棋盘状态
    int** correctInitialBoard; // 正确的初始棋盘状态
    char** obstacle;      // 障碍布局
    int size;             // 棋盘大小
    int antX, antY;       // 蚂蚁位置
    int antDirection;     // 蚂蚁朝向 (1=上, 2=下, 3=左, 4=右)
    int steps;            // 步数

    // 初始化棋盘
    void initBoard();
    // 初始化障碍
    void initObstacle();
    // 重置蚂蚁状态
    void resetAnt();
    // 打印棋盘
    void printBoard(int** arr);
    void printBoard(char** arr);
    // 输入棋盘状态
    void inputBoard(int** arr);
    // 比对棋盘
    bool compareBoards();
    // 通用模拟函数
    bool simulateTwistedWorld();
    // 碰壁走廊模式模拟
    bool simulateAntsHit();
    // 生成扭曲世界题目
    void generateTwistedQuestion();
    // 生成碰壁走廊题目
    void generateHitQuestion();
    // 验证用户输入的题目是否有效
    bool validateUserQuestion();
    // 生成用户自定义题目
    void generateUserQuestion();

public:
    // 构造函数
    funMode();
    // 析构函数
    ~funMode();
    // 扭曲世界模式
    void TwistedWorld();
    // 碰壁走廊模式
    void AntsHit();
    // 趣味模式选图
    void chooseMap();
};

#endif // FUNMODE_H      