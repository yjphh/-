#ifndef FREEDOM_MODE_H
#define FREEDOM_MODE_H

#include <iostream>
#include<string>
#include<vector>
#include"User.h"
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void TurnRight(Direction& heading);
void TurnLeft(Direction& heading);

//定义题库内题目信息的结构体
struct  problemBank
{
    std::string username;
    int steps = 0;
    int finalX = 0;
    int finalY = 0;

    int finalDirec = 0;
    std::vector<bool>arr;//题目棋盘
    std::vector<bool>answer;//答案棋盘
};

class freedomMode 
{
private:
    int size;
    int steps;
    //用一维动态数组模拟正方形棋盘
    bool* board;//用于模拟蚂蚁移动
	bool* finalBoard;//用于存储蚂蚁走完所有步数后的最终棋盘
	bool* initialBoard;//用于存储题目棋盘（若题目有解，该棋盘则为答案棋盘）

    void initializeBoard(bool* board);//初始化棋盘都为白格
	void copyBoard(bool* src, bool* dest);//生成副本棋盘用于模拟
    bool moveAnt(int& x, int& y, Direction& heading);//蚂蚁行为函数，包括格子变色、转弯、前进一格
	int getIndex(int x, int y);//将二维坐标转换为一维索引

    std::vector<problemBank> bank;

    bool isfirstRead = true;

public:
    freedomMode(int size, int steps);//构造函数，生成初始棋盘（若题目有解，该棋盘则为答案棋盘）
    freedomMode();
    ~freedomMode();

	bool isValidInitialPosition(int x, int y, Direction heading);//电脑验证用户输入的初始位置和朝向是否合法，会模拟蚂蚁移动
	void generateFinalBoard(int& x, int& y, Direction& heading);//题目有解后，电脑生成有解的题目棋盘，会模拟蚂蚁移动，生成最终的题目棋盘
    void printFinalBoard();//打印题目棋盘
    bool checkSolution(bool* userBoard);
    void printInitialBoard();//打印答案棋盘
    bool suggestInitialPosition(int& x, int& y, Direction& heading);//电脑验证用户输入的初始位置和朝向不合法后，最多尝试1000次，若成功则提示用户合法的初始位置和朝向，若失败则题目无解
	int freeMode(User& user);//自由模式主函数，用户输入初始位置和朝向，电脑生成题目棋盘，用户输入答案棋盘，电脑验证答案是否正确

    bool isSameProblem(const problemBank& a, const problemBank& b);//比较题库中是否已经存在原题
    bool SavetoFile(const std::string username, int steps, int finakX, int finalY,int finalDirec, const std::vector<bool>arr, const std::vector<bool>answer);//将新的题目存入题库，存档
    void viewBank();//进入题库
	void viewProblem(int index, const std::vector<problemBank>bank);//查看题库中的题目

    const std::vector<problemBank>& getBank()const;

};
#endif