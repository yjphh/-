#ifndef FUNMODE_H
#define FUNMODE_H

class funMode {
private:
    int** board;          // ����״̬
    int** originalBoard;  // ��ʼ����״̬
    int** correctInitialBoard; // ��ȷ�ĳ�ʼ����״̬
    char** obstacle;      // �ϰ�����
    int size;             // ���̴�С
    int antX, antY;       // ����λ��
    int antDirection;     // ���ϳ��� (1=��, 2=��, 3=��, 4=��)
    int steps;            // ����

    // ��ʼ������
    void initBoard();
    // ��ʼ���ϰ�
    void initObstacle();
    // ��������״̬
    void resetAnt();
    // ��ӡ����
    void printBoard(int** arr);
    void printBoard(char** arr);
    // ��������״̬
    void inputBoard(int** arr);
    // �ȶ�����
    bool compareBoards();
    // ͨ��ģ�⺯��
    bool simulateTwistedWorld();
    // ��������ģʽģ��
    bool simulateAntsHit();
    // ����Ť��������Ŀ
    void generateTwistedQuestion();
    // ��������������Ŀ
    void generateHitQuestion();
    // ��֤�û��������Ŀ�Ƿ���Ч
    bool validateUserQuestion();
    // �����û��Զ�����Ŀ
    void generateUserQuestion();

public:
    // ���캯��
    funMode();
    // ��������
    ~funMode();
    // Ť������ģʽ
    void TwistedWorld();
    // ��������ģʽ
    void AntsHit();
    // Ȥζģʽѡͼ
    void chooseMap();
};

#endif // FUNMODE_H      