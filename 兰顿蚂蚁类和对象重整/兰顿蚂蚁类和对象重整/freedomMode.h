#ifndef FREEDOM_MODE_H
#define FREEDOM_MODE_H

#include <iostream>
#include<string>
#include<vector>
#include"User.h"
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void TurnRight(Direction& heading);
void TurnLeft(Direction& heading);

//�����������Ŀ��Ϣ�Ľṹ��
struct  problemBank
{
    std::string username;
    int steps = 0;
    int finalX = 0;
    int finalY = 0;

    int finalDirec = 0;
    std::vector<bool>arr;
    std::vector<bool>answer;
};

class freedomMode 
{
private:
    int size;
    int steps;
    bool* board;
    bool* finalBoard;
    bool* initialBoard;

    void initializeBoard(bool* board);
    void copyBoard(bool* src, bool* dest);
    bool moveAnt(int& x, int& y, Direction& heading);
    int getIndex(int x, int y);

    std::vector<problemBank> bank;

    bool isfirstRead = true;

public:
    freedomMode(int size, int steps);
    freedomMode();
    ~freedomMode();

    bool isValidInitialPosition(int x, int y, Direction heading);
    void generateFinalBoard(int& x, int& y, Direction& heading);
    void printFinalBoard();
    bool checkSolution(bool* userBoard);
    void printInitialBoard();
    bool suggestInitialPosition(int& x, int& y, Direction& heading);
    int freeMode(User& user);

    bool isSameProblem(const problemBank& a, const problemBank& b);//�Ƚ�������Ƿ��Ѿ�����ԭ��
    bool SavetoFile(const std::string username, int steps, int finakX, int finalY,int finalDirec, const std::vector<bool>arr, const std::vector<bool>answer);//���µ���Ŀ������⣬�浵
    void viewBank();//�������
    void viewProblem(int index,const std::vector<problemBank>bank);

    const std::vector<problemBank>& getBank()const;

};
#endif