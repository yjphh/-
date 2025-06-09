#ifndef FUNMODE_H
#define FUNMODE_H

#include<string>
#include<utility>
#include<vector>
using namespace std;


class funMode {
private:
    int** board;          // 当前棋盘状态，用于模拟
    int** originalBoard;  // 初始棋盘状态
    int** finalBoard; // 用于存储碰壁走廊模拟后的最终棋盘
    char** obstacle;      // 障碍布局
    int size;             // 棋盘大小
    int antX, antY;       // 蚂蚁位置
    int antDirection;     // 蚂蚁朝向 (1=上, 2=下, 3=左, 4=右)
    int steps;            // 步数

    int year1 = 1921;     //题目一答案
    int year2 = 1949;     //题目二答案
    std::string site = "BeiJing";  //题目三答案
    int rank = 2;     //题目四答案
 
    // 道具卡系统重构
    enum ToolType { NONE, BACK, PRE, CONS, DES }; // 道具类型
    vector<ToolType> obtainedTools; // 已获得的道具卡

    vector<string>userBoard;//用于存储蚂蚁有灵道具卡中用户输入的部分数据
    vector<char>answerBoard;//用于存储蚂蚁有灵道具卡中的答案棋盘（转为一维数组后）
    vector<char>obstacleBoard;//用于存储降维后的障碍数组；
    //落子有悔道具卡中用来获得第几步回溯错误
    vector<pair<int, int>>correctPath;//记录正确路径上的若干个坐标

    // 初始化棋盘
    void initBoard();
    // 初始化扭曲世界和碰壁走廊的障碍
    void initObstacle();
    //初始化觉醒之路的障碍
    void initObstacle(int n);
    //蚂蚁有灵中的用户输入
    void inputBoard(vector<string>& userboard);
    // 重置蚂蚁状态
    void resetAnt();
    // 通用打印棋盘
    void printBoard(int** arr);
    // 通用用户输入棋盘
    void inputBoard(int** arr);
    // 通用比对棋盘
    bool compareBoards(int** arr);
    // 扭曲世界模式模拟
    bool simulateTwistedWorld();
    // 碰壁走廊模式模拟
    bool simulateAntsHit();
    // 生成扭曲世界题目
    void generateTwistedQuestion();
    // 生成碰壁走廊题目
    bool generateUserQuestion();
    //觉醒之路答题环节
    void answerQues();
    //生成觉醒之路题目
    bool generateAwakenRoad();

    //选择道具卡
    void chooseTool();
    // 使用单个道具卡
    void useTool(ToolType type);

    //落子有悔道具卡
    void BackOpera();
    //预言大师道具卡
    void PredictMaster();
    //蚂蚁有灵道具卡
    void CreatCons();
    //暴力拆迁道具卡
    void Destroy();


    // 程序员自定义起始位置（示例：中心位置(0,0)，对应索引3）
    int startX = 0;
    int startY = 0;
    // 定义向量坐标（A-F六个方向）
    static const std::vector<std::pair<int, int>> DIRECTIONS;
    // 坐标转换为一维数组索引
    int coordToIndex(int x, int y) const;
    // 一维数组索引转换为坐标
    std::pair<int, int> indexToCoord(int idx) const;

public:
    // 构造函数1，用来初始化扭曲世界和碰壁长廊
    funMode();
    //构造函数2，用来初始化觉醒之路
    funMode(int n);
    // 析构函数
    ~funMode();
    // 扭曲世界模式
    void TwistedWorld();
    // 碰壁走廊模式
    void AntsHit();
    // 觉醒之路模式
    void ToolsRoad();
	// 六方通道模式
	void HexagonalPath();

    // 趣味模式选图
    void chooseMap();

    // 六方通道模式模拟蚂蚁移动
    std::vector<int> simulateAntMovement(std::vector<int>& initialGrid,
        int& startX, int& startY,
        const std::vector<int>& directions) const;
    // 打印六边形格子状态
    void printHexagon(const std::vector<int>& grid) const;
    //六方通道模式答题的辅助图片
    void displayImage(const string& imagePath);
};

#endif // FUNMODE_H      