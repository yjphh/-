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

//�����������Ŀ��Ϣ�Ľṹ��
struct  problemBank
{
    std::string username;
    int steps = 0;
    int finalX = 0;
    int finalY = 0;

    int finalDirec = 0;
    std::vector<bool>arr;//��Ŀ����
    std::vector<bool>answer;//������
};

class freedomMode 
{
private:
    int size;
    int steps;
    //��һά��̬����ģ������������
    bool* board;//����ģ�������ƶ�
	bool* finalBoard;//���ڴ洢�����������в��������������
	bool* initialBoard;//���ڴ洢��Ŀ���̣�����Ŀ�н⣬��������Ϊ�����̣�

    void initializeBoard(bool* board);//��ʼ�����̶�Ϊ�׸�
	void copyBoard(bool* src, bool* dest);//���ɸ�����������ģ��
    bool moveAnt(int& x, int& y, Direction& heading);//������Ϊ�������������ӱ�ɫ��ת�䡢ǰ��һ��
	int getIndex(int x, int y);//����ά����ת��Ϊһά����

    std::vector<problemBank> bank;

    bool isfirstRead = true;

public:
    freedomMode(int size, int steps);//���캯�������ɳ�ʼ���̣�����Ŀ�н⣬��������Ϊ�����̣�
    freedomMode();
    ~freedomMode();

	bool isValidInitialPosition(int x, int y, Direction heading);//������֤�û�����ĳ�ʼλ�úͳ����Ƿ�Ϸ�����ģ�������ƶ�
	void generateFinalBoard(int& x, int& y, Direction& heading);//��Ŀ�н�󣬵��������н����Ŀ���̣���ģ�������ƶ����������յ���Ŀ����
    void printFinalBoard();//��ӡ��Ŀ����
    bool checkSolution(bool* userBoard);
    void printInitialBoard();//��ӡ������
    bool suggestInitialPosition(int& x, int& y, Direction& heading);//������֤�û�����ĳ�ʼλ�úͳ��򲻺Ϸ�����ೢ��1000�Σ����ɹ�����ʾ�û��Ϸ��ĳ�ʼλ�úͳ�����ʧ������Ŀ�޽�
	int freeMode(User& user);//����ģʽ���������û������ʼλ�úͳ��򣬵���������Ŀ���̣��û���������̣�������֤���Ƿ���ȷ

    bool isSameProblem(const problemBank& a, const problemBank& b);//�Ƚ�������Ƿ��Ѿ�����ԭ��
    bool SavetoFile(const std::string username, int steps, int finakX, int finalY,int finalDirec, const std::vector<bool>arr, const std::vector<bool>answer);//���µ���Ŀ������⣬�浵
    void viewBank();//�������
	void viewProblem(int index, const std::vector<problemBank>bank);//�鿴����е���Ŀ

    const std::vector<problemBank>& getBank()const;

};
#endif