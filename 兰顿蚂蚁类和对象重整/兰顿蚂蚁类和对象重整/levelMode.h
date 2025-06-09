#ifndef LEVEL_MODE_H
#define LEVEL_MODE_H

#include "user.h"

class LevelMode 
{
public:
	void chooseStage(User& user);//ѡ��ؿ�����
	void stageBoard(int _stage, int _diffic, User& user);//���ɹؿ����̺���
	double compareBoard(int _userOne[], int _initialOne[], int _size, bool shouldPrint = true);//�Ƚ��û���������̺ͳ�ʼ���̵ĺ�����������ȷ��
	int judgeBoard(int _userOne[], int _initialOne[], int _size);//�ж��û���������̺ͳ�ʼ���̵ĺ���

	bool isBetter(const GameRecord& current, const GameRecord& others);//�жϵ�ǰ��¼�Ƿ��������¼����
	std::vector<GameRecord>findAllBestRecords(const std::vector<GameRecord>& records);//���Ҹ�����Ѽ�¼�ĺ���
	void bubbleSort(std::vector<GameRecord>& records, int n);//ð�������������ڶ���Ϸ��¼��������
	void printList(std::vector<GameRecord> records);//��ӡ��Ϸ��¼�б���
	void viewRanklist(int stage, int diff);//�鿴���а���

};

#endif
