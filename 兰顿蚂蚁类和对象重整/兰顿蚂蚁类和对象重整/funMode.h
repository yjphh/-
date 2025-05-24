#ifndef FUNMODE_H
#define FUNMODE_H

#include<string>
#include<utility>
#include<vector>
using namespace std;


class funMode {
private:
    int** board;          // ��ǰ����״̬������ģ��
    int** originalBoard;  // ��ʼ����״̬
    int** finalBoard; // ���ڴ洢��������ģ������������
    char** obstacle;      // �ϰ�����
    int size;             // ���̴�С
    int antX, antY;       // ����λ��
    int antDirection;     // ���ϳ��� (1=��, 2=��, 3=��, 4=��)
    int steps;            // ����

    int year1 = 1921;     //��Ŀһ��
    int year2 = 1949;     //��Ŀ����
    std::string site = "BeiJing";  //��Ŀ����
    int rank = 2;     //��Ŀ�Ĵ�
 
    // ���߿�ϵͳ�ع�
    enum ToolType { NONE, BACK, PRE, CONS, DES }; // ��������
    vector<ToolType> obtainedTools; // �ѻ�õĵ��߿�

    vector<string>userBoard;//���ڴ洢����������߿����û�����Ĳ�������
    vector<char>answerBoard;//���ڴ洢����������߿��еĴ����̣�תΪһά�����
    vector<char>obstacleBoard;//���ڴ洢��ά����ϰ����飻
    //�����лڵ��߿���������õڼ������ݴ���
    vector<pair<int, int>>correctPath;//��¼��ȷ·���ϵ����ɸ�����

    // ��ʼ������
    void initBoard();
    // ��ʼ��Ť��������������ȵ��ϰ�
    void initObstacle();
    //��ʼ������֮·���ϰ�
    void initObstacle(int n);
    //���������е��û�����
    void inputBoard(vector<string>& userboard);
    // ��������״̬
    void resetAnt();
    // ͨ�ô�ӡ����
    void printBoard(int** arr);
    // ͨ���û���������
    void inputBoard(int** arr);
    // ͨ�ñȶ�����
    bool compareBoards(int** arr);
    // Ť������ģʽģ��
    bool simulateTwistedWorld();
    // ��������ģʽģ��
    bool simulateAntsHit();
    // ����Ť��������Ŀ
    void generateTwistedQuestion();
    // ��������������Ŀ
    bool generateUserQuestion();
    //����֮·���⻷��
    void answerQues();
    //���ɾ���֮·��Ŀ
    bool generateAwakenRoad();

    //ѡ����߿�
    void chooseTool();
    // ʹ�õ������߿�
    void useTool(ToolType type);

    //�����лڵ��߿�
    void BackOpera();
    //Ԥ�Դ�ʦ���߿�
    void PredictMaster();
    //����������߿�
    void CreatCons();
    //������Ǩ���߿�
    void Destroy();

public:
    // ���캯��1��������ʼ��Ť����������ڳ���
    funMode();
    //���캯��2��������ʼ������֮·
    funMode(int n);
    // ��������
    ~funMode();
    // Ť������ģʽ
    void TwistedWorld();
    // ��������ģʽ
    void AntsHit();
    // ����֮·ģʽ
    void ToolsRoad();
    // Ȥζģʽѡͼ
    void chooseMap();
};

#endif // FUNMODE_H      