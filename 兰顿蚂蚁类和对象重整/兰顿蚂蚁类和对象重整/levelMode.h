#ifndef LEVEL_MODE_H
#define LEVEL_MODE_H

#include "user.h"

class LevelMode 
{
public:
	void chooseStage(User& user);//选择关卡函数
	void stageBoard(int _stage, int _diffic, User& user);//生成关卡棋盘函数
	double compareBoard(int _userOne[], int _initialOne[], int _size, bool shouldPrint = true);//比较用户输入的棋盘和初始棋盘的函数，返回正确率
	int judgeBoard(int _userOne[], int _initialOne[], int _size);//判断用户输入的棋盘和初始棋盘的函数

	bool isBetter(const GameRecord& current, const GameRecord& others);//判断当前记录是否比其他记录更好
	std::vector<GameRecord>findAllBestRecords(const std::vector<GameRecord>& records);//查找个人最佳记录的函数
	void bubbleSort(std::vector<GameRecord>& records, int n);//冒泡排序函数，用于对游戏记录进行排序
	void printList(std::vector<GameRecord> records);//打印游戏记录列表函数
	void viewRanklist(int stage, int diff);//查看排行榜函数

};

#endif
