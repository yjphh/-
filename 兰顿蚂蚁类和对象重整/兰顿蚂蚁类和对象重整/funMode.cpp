#include "funMode.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include<algorithm>//reverse
#include <graphics.h>// EasyX ͼ�ο�ͷ�ļ�
#include<Windows.h>
#include <conio.h>
using namespace std;

// ���캯������ʼ��ͨ������
funMode::funMode() {
    srand(time(0));
    size = rand() % 3 + 3; // Ĭ�����̴�СΪ3*3��5*5���ɵ�����
    initBoard();
    initObstacle();
    resetAnt();
}


//���캯��2��������ʼ������֮·
funMode::funMode(int n)
{
    srand(time(0));
    size = n;//���̴�С��Ϊ����
    initBoard();//�����������
    initObstacle(n);//��Ϊ�����ϰ�������Ϊ���̱߳�������ֲ��ϰ��������ϵ�λ��
    resetAnt();//����������ϵĳ�ʼλ�á���ʼ���򡢲�������ģ��
}

void funMode::initObstacle(int n)//�������ָ���������ϰ�������֮·ģʽ
{
    obstacle = new char* [n];
    for (int i = 0; i < n; i++)
    {
        obstacle[i] = new char[n];
        for (int j = 0; j < n; j++)
        {
            obstacle[i][j] = ' ';  // ��ʼ������λ��Ϊ��
        }
    }
    // ������� n ���ϰ�
    int count = 0;
    while (count < n)
    {
        int x = rand() % n;  // ���� 0 �� n-1 ֮��������
        int y = rand() % n;

        if (obstacle[x][y] != '#')  // �����λ��û���ϰ��ŷţ���֤һ��λ��ֻ��һ���ϰ�
        {
            obstacle[x][y] = '#';    // ����Ϊ�ϰ�
            count++;
        }
    }
}

// ��ʼ������
void funMode::initBoard() {
    board = new int* [size];
    originalBoard = new int* [size];
    finalBoard = new int* [size]; // ��ȷ�ĳ�ʼ����
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        originalBoard[i] = new int[size];
        finalBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = rand() % 2; // ����ڰ׸�
            originalBoard[i][j] = board[i][j];
            finalBoard[i][j] = board[i][j];
        }
    }
}

// ��ʼ���ϰ�������ģʽר�ã�
void funMode::initObstacle() {
    obstacle = new char* [size];
    for (int i = 0; i < size; i++) {
        obstacle[i] = new char[size];
        for (int j = 0; j < size; j++) {
            obstacle[i][j] = ' '; // Ĭ�����ϰ�
        }
    }
}

// ��������״̬��������һ����Χ���������
void funMode::resetAnt() {
    antX = rand() % size;
    antY = rand() % size;
    antDirection = rand() % 4 + 1; // 1-4
    steps = rand() % 11 + 5; // 5-15��
}

// Ť��������������ȵ���Ŀ��𰸴�ӡ����
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


// ��������״̬
void funMode::inputBoard(int** arr) 
{
    cout << "�뿪ʼ��������" << size << "x" << size << "�ĳ�ʼ���̣�0=�׸�1=�ڸ�#=�ϰ�����" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char cell;
            cin >> cell;

            if (cell == '#') {
                obstacle[i][j] = '#';
                arr[i][j] = 0; // �ϰ�����λ��Ĭ��Ϊ�׸�
            }
            else {
                obstacle[i][j] = ' ';
                arr[i][j] = (cell == '1') ? 1 : 0;
            }
        }
    }
}

// Ť��������������ȵĴ��ж�����
bool funMode::compareBoards(int** arr)//����Ĳ��������̳�ʼ״̬������ȷ��
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (obstacle[i][j] == '#')
            {
				arr[i][j] = 0; // �ϰ�����Ĭ��Ϊ�׸�
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (originalBoard[i][j] != arr[i][j]) return false;//�����originalBoard���û��������������
        }
    }
    return true;
}

// ģ�⺯����Ť������ģʽ��
bool funMode::simulateTwistedWorld() //�ڳ�ʼ���̵Ļ�����˳�����경�������ܷ�õ�����ͼ���ߵĹ��̲�Խ����н⣬board�洢ģ���������ͼ
{
    int x = antX, y = antY;
    int dir = antDirection;
    bool turnRight = (originalBoard[x][y] == 0); // ��ʼת��

    for (int i = 0; i < steps; i++) {
        // ��ת��ɫ
        board[x][y] = !board[x][y];

        // ת��
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

        // �ƶ�
        switch (dir)
        {
        case 1: y--; break;
        case 2: y++; break;
        case 3: x--; break;
        case 4: x++; break;
        }

        // Խ����
        if (x < 0 || x >= size || y < 0 || y >= size) return false;

        // �л�ת�����
        turnRight = !turnRight;
    }

    antX = x; antY = y; antDirection = dir;//��ģ����������ϵ�����λ�úͳ��򱣴�
    return true;
}

// ��������ģʽģ��
bool funMode::simulateAntsHit()
{
    correctPath.clear(); // ���֮ǰ��·����¼

    // ���Ƶ�ǰ������Ϊģ�����
    int** tempBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        tempBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    int x = antX, y = antY;
    int dir = antDirection;

    correctPath.emplace_back(x, y);//��¼��ʼ����λ��

    for (int i = 0; i < steps; i++) {
        // ��¼��ǰ����״̬
        int color = tempBoard[x][y];

        // ת��
        if (color==0)//�׸���ת
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
        else//�ڸ���ת
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

        // �����ϰ���ǽ����ೢ��4����ת��
        int attempts = 0;
        bool moved = false;
        while (attempts < 4)
        {
            int nx = x, ny = y;
            switch (dir) 
            {
            case 1: ny--; break; // ��
            case 2: ny++; break; // ��
            case 3: nx--; break; // ��
            case 4: nx++; break; // ��
            }

            // ����Ƿ�Ϸ�����ǽ�ҷ��ϰ���
            if (nx >= 0 && nx < size && ny >= 0 && ny < size && obstacle[nx][ny] != '#') {
                x = nx; y = ny;
                moved = true;
                break;
            }

            //����ǽ���ϰ�ʱ�ͳ�����ת
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
            // �ͷ���ʱ����
            for (int i = 0; i < size; i++) {
                delete[] tempBoard[i];
            }
            delete[] tempBoard;
            return false; // �޷��ƶ�����Ŀ��Ч
        }

        // ��ת��ɫ - ���ݹ����޸ģ�ֻ���������ƶ�ʱ�ű�ɫ
        if (attempts == 0) { // û�������ϰ��������ƶ�
            tempBoard[x][y] = !tempBoard[x][y];
        }

        correctPath.emplace_back(x, y);//��¼�ƶ�һ���������λ��
    }

    // ����ģ��������������
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            finalBoard[i][j] = tempBoard[i][j];
        }
    }

    // �ͷ���ʱ����
    for (int i = 0; i < size; i++) {
        delete[] tempBoard[i];
    }
    delete[] tempBoard;

    antX = x; antY = y; antDirection = dir;
    return true;
}

// ����Ť��������Ŀ
void funMode::generateTwistedQuestion() {
    cout << "\n=== Ť��������Ŀ ===" << endl;
    cout << "���̴�С��" << size << "x" << size << endl;
    cout << "��������λ�ã�(" << antX << ", " << antY << ")" << endl;
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
    cout << "���ճ���" << dire << endl;
    cout << "������" << steps << endl;
    cout << "�������̣�" << endl;
    printBoard(board);
}

// �û��Զ�����Ŀ
bool funMode::generateUserQuestion() {
    cout << "\n=== �û��Զ����ʼ���������� ===" << endl;
    cout << "���������̴�С��";
    cin >> size;

    // ���·����ڴ�
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

    cout << "���������ϳ�ʼλ�� (x y)��";
    cin >> antX >> antY;

    cout << "���������ϳ�ʼ���� (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)��";
    cin >> antDirection;

    cout << "�����������߹��Ĳ�����";
    cin >> steps;//����ֱ���޸ĳ�Ա����

    cout << "�����뺬�ϰ��ĳ�ʼ���̣�" << size << "x" << size << "��0=�׸�1=�ڸ�#=�ϰ�����" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char cell;
            cin >> cell;

            if (cell == '#') {
                obstacle[i][j] = '#';
                board[i][j] = 0; // �ϰ�����λ��Ĭ��Ϊ�׸�
            }
            else {
                obstacle[i][j] = ' ';
                board[i][j] = (cell == '1') ? 1 : 0;//��board�洢��ʼ���̣�����
            }
        }
    }

    // ģ�������ƶ���������������
    if (!simulateAntsHit()) 
    {
        std::cout << "��Ŀ��Ч�����ϻ���ĳ��������ѭ����" << std::endl;
        return false;
    }//������ģ�⣬finalBoard������ͼ��board��𰸵ĳ�ʼ����

    // ��ʾ��Ŀ
    cout << "\n=== ����֤�н������������Ŀ ===" << endl;
    cout << "���̴�С��" << size << "x" << size << endl;
    cout << "��������λ�ã�(" << antX << ", " << antY << ")" << endl;
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
    cout << "���ճ���" << dire << endl;
    cout << "������" << steps << endl;
    cout << "�������̣����ϰ�����" << endl;
    printBoard(finalBoard);
    return true;
}

// ��������
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
    cout << "��ӭ��������֮·�Ĵ��⻷�ڣ�ÿ���һ�⣬�㽫���һ�Ŵ���˵����ĵ��߿���" << endl;
    obtainedTools.clear();//��ʼ�����

    int _year1 = 0;
    cout << "����1���й��������ĵ���ʱ��" << endl;
    cin >> _year1;
    if (_year1 == year1)
    {
        obtainedTools.push_back(ToolType::DES);
        cout << "��ϲ���õ��߿�����������Ǩ" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          ������Ǩ:" << endl;
        cout << "��ʼ����ǰ��ѡ���Բ�������ϰ�" << endl;
        cout << "�����Զ����´𰸣��û���ʼ����" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "���ź�������δ���" << endl;
    }
    cout << endl;
    int _year2 = 0;
    cout << "����2�����й��ĳ���ʱ��" << endl;
    cin >> _year2;
    if (_year2 == year2)
    {
        obtainedTools.push_back(ToolType::PRE);
        cout << "��ϲ���õ��߿�����Ԥ�Դ�ʦ" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          Ԥ�Դ�ʦ:" << endl;
        cout << "��ʼ����ǰ��    �������ǰԤ֪" << endl;
        cout << "��� 6����ʼ���̸��ӵ���ȷ��ɫ" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "���ź�������δ���" << endl;
    }
    cout << endl;
    string _site ;
    cout << "����3���й����׶�����" << endl;
    cin >> _site;
    if (_site == site)
    {
        obtainedTools.push_back(ToolType::CONS);
        cout << "��ϲ���õ��߿�������������" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          ��������:" << endl;
        cout << "�����ڼ䣬  ���Ͼ�����������ʶ" << endl;
        cout << "�������������𣬲��Զ���� 3��" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "���ź�������δ���" << endl;
    }
    cout << endl;
    int _rank = 0;
    cout << "����4���й�GDP����������" << endl;
    cin >> _rank;
    if (_rank == rank)
    {
        obtainedTools.push_back(ToolType::BACK);
        cout << "��ϲ���õ��߿����������л�" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          �����л�:" << endl;
        cout << "�������⣬ϵͳ��������������" << endl;
        cout << "��ʾ���ڵڼ�������  ����һ��" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "���ź�������δ���" << endl;
    }
}

//���ɾ���֮·��Ŀ
bool funMode::generateAwakenRoad()
{
    // ������Ч��Ŀ - ��ӳ��Դ�������
    std::cout << "����������Ŀ...\n";
    int** realOriginalBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        realOriginalBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            realOriginalBoard[i][j] = originalBoard[i][j];//��ǰ������ȷ�ĳ�ʼ����
        }
    }
    int maxAttempts = 1000; // ����Դ���
    int attempts = 1;
    while (!simulateAntsHit() && attempts < maxAttempts)//����board����ʱ�������ģ�⣬�õ�finalBoard
    {
        resetAnt();//�������ϵĳ�ʼλ�á���ʼ���򡢲���
        attempts++;
    }

    if (attempts >= maxAttempts) {
        std::cout << "�޷�������Ч��Ŀ�������ԣ�" << std::endl;
        for (int i = 0; i < size; i++) {
            delete[] realOriginalBoard[i];
        }
        delete[] realOriginalBoard;
        return false;
    }
    std::cout << "�н���Ŀ�����ɣ�����" << attempts << "��" << std::endl;
    // ��ʾ���̺;�����Ŀ��Ϣ
     // ��ʾ��Ŀ
    cout << "\n=== ����֤�н����Ŀ ===" << endl;
    cout << "���̴�С��" << size << "x" << size << endl;
    cout << "��������λ�ã�(" << antX << ", " << antY << ")" << endl;
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
    cout << "���ճ���" << dire << endl;
    cout << "������" << steps << endl;
    cout << "�������̣����ϰ�����" << endl;
    printBoard(finalBoard);//��ӡfinalBoard��������Ŀ��Ϣ

    // �ͷű������̵��ڴ�
    for (int i = 0; i < size; i++) {
        delete[] realOriginalBoard[i];
    }
    delete[] realOriginalBoard;

    return true;
}

// ѡ����߿�
void funMode::chooseTool() {
    if (obtainedTools.empty()) {
        cout << "�㻹û�л���κε��߿���\n";
        return;
    }

    cout << "\n���ѻ�õĵ��߿�����ѡ�������ÿո�ָ���ţ���\n";
    vector<pair<int, ToolType>> toolOptions;
    for (int i = 0; i < obtainedTools.size(); i++) {
        ToolType type = obtainedTools[i];
        string name;
        switch (type) {
        case ToolType::BACK:   name = "�����л�"; break;
        case ToolType::PRE:    name = "Ԥ�Դ�ʦ"; break;
        case ToolType::CONS:   name = "��������"; break;
        case ToolType::DES:    name = "������Ǩ"; break;
        default: continue;
        }
        toolOptions.emplace_back(i + 1, type);
        cout << i + 1 << ". " << name << endl;
    }

    cout << "\n������Ҫʹ�õĵ��߿���ţ���1 3����(���س�����ѡ��)";
    vector<int> selectedIndices;
    int index;
    while (cin >> index) {
        selectedIndices.push_back(index);
        if (cin.get() == '\n') break;
    }

    for (int idx : selectedIndices) 
    {
        if (idx < 1 || idx > toolOptions.size()) {
            cout << "��Ч��ţ�" << idx << endl;
            continue;
        }
        ToolType type = toolOptions[idx - 1].second;
        useTool(type);
    }
}

// ʹ�õ������߿�
void funMode::useTool(ToolType type) {
    switch (type) {
    case ToolType::BACK:   BackOpera(); break;
    case ToolType::PRE:    PredictMaster(); break;
    case ToolType::CONS:   CreatCons(); break;
    case ToolType::DES:    Destroy(); break;
    default: break;
    }
}

//�����лڵ��߿�
void funMode::BackOpera()
{
    cout << "����ʹ�������лڵ��߿�..." << endl;
    inputBoard(originalBoard);
    if (compareBoards(board))
    {
        cout << "��ǰ��ϲ��ش���ȷ������Ҫʹ�øÿ���" << endl;
        return;
    }
    else
    {
        cout << "ϵͳ��ǰ��⵽���������������ʹ�øÿ�" << endl;
        //��������
        reverse(correctPath.begin(), correctPath.end());
        int step = 0;
        while (step < correctPath.size())
        {
            int x = correctPath[step].first;
            int y = correctPath[step].second;
            if (originalBoard[x][y] != board[x][y])
            {
                cout << "���ڵ�" << step+1 << "������ʱ���Ѿ���������" << endl;
                break;
            }
            step++;
        }
        cout << "����һ�ΰ�" << endl;
    }
}
//Ԥ�Դ�ʦ���߿�
void funMode::PredictMaster()
{
    cout << "����ʹ��Ԥ�Դ�ʦ���߿�..." << endl;
    int counter = 6;
    while (counter)
    {
        cout << "����������鿴�Ĵ�����ĳλ�õ�����(�ϰ���λ����֪)" << endl;
        int x = 0, y = 0;
        cin >> x >> y;
        cout << "Ԥ�Խ�����£�" << endl;
        string ch;
        if (board[x][y] == 0)
        {
            ch = "��";
        }
        else
        {
            ch = "��";
        }
        cout <<"�ø���ɫΪ"<< ch <<"ɫ" << endl;
        counter--;
        if (counter)
        {
            cout << "���Ԥ�Դ���δ���꣬�Ƿ����Ԥ�ԣ�(yes/no)" << endl;
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
    cout << "����֪���˲��ָ��ӵ���ȷ��ɫ��������ʼ�����" << endl;
}

void funMode::inputBoard(vector<string>& userboard)
{
    cout << "������" << size << "x" << size << "�ĳ�ʼ���̣�0=�׸�1=�ڸ�#=�ϰ�����" << endl;
    cout << "��������useToolʱ����ʼʹ������������߿�" << endl;
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

//����������߿�
void funMode::CreatCons()
{
    // ������������������������ݸ���
    userBoard.clear();
    answerBoard.clear();
    obstacleBoard.clear();

    inputBoard(userBoard);
    cout << "����ʹ������������߿�..." << endl;
    //��ԭ��ά�������Ƚ�Ϊһά����
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
 

    //  ��ӡ���̣���������Ч��Χ�ڣ�����Խ�磩
    int totalCells = userBoard.size() + 3;
    int maxValidIndex = min(totalCells, size * size); // ��ֹԽ��


    cout << "�õ��߿�ʹ�ý������,�ѻ��ݲ��ֱ�У�ԣ������Զ������3�������������" << endl;
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

        // ���ƿո�ͻ��У�ÿ��ǰ�����ַ���ӿո񣬵��ĸ��ַ�����
        if ((i + 1) % 4 == 0)  // ÿ�е����һ���ַ�����
        {
            cout << endl;
        }
        else  // ����ĩ�ַ���ӿո�
        {
            cout << " ";
        }
    }
    cout << endl;
}


//������Ǩ���߿�
void funMode::Destroy()
{
    cout << "����ʹ�ñ�����Ǩ���߿�..." << endl;
    string choice1;
    cout << "�Ƿ�ʼ����ϰ�������yes/no��" << endl;
    cin >> choice1;
    while (choice1 == "yes")
    {
        cout << "�������������ϰ�����λ������" << endl;
        int x = 0, y = 0;
        cin >> x >> y;
        obstacle[x][y] = 0;
        cout << "ԭλ���ϰ����������Ĭ��Ϊ�׸�" << endl;
        cout << "�Ƿ�����������yes/no��" << endl;
        cin >> choice1;
    }
    cout << "���ڸ�����Ŀ�ʹ�..." << endl;

    //�ٴ����ɾ���֮·��Ŀ
    generateAwakenRoad();
}


// Ť������ģʽ�����Գ��⣩ 
void funMode::TwistedWorld() {
    // ��ʾ��Ϸ����
    std::cout << "====��ӭ����Ť�����磡===" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "����:�������ϴ�����ģʽ�뿪����������������Ĺ���Ť����" << std::endl;
    std::cout << "�µĹ������ϵĵ�һ��ת�䷽�����ɳ�ʼλ�úڰ׸��������������ÿ��һ����ת�䷽����ת" << std::endl;
    std::cout << "���µĹ����£������Ѷȴ����ߣ��������԰ɣ�" << std::endl;
    std::cout << "�����߹�n���γ�����ͼ����Ҫ��������ͼ���ݳ����̳�ʼ״̬��Ϊ�������" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << std::endl;
    std::cout << "��ע�⣺��ģʽ�£�������������н���Ŀ��������" << std::endl;

    // ������Ч��Ŀ - ��ӳ��Դ�������
    std::cout << "����������Ŀ...\n";
    int** realOriginalBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        realOriginalBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            realOriginalBoard[i][j] = originalBoard[i][j];//��ǰ������ȷ�ĳ�ʼ����
        }
    }

    int maxAttempts = 1000; // ����Դ���
    int attempts = 1;
    while (!simulateTwistedWorld() && attempts < maxAttempts)//����board����ģ��
    {
        resetAnt();//�������ϵĳ�ʼλ�á���ʼ���򡢲���
        attempts++;
    }

    if (attempts >= maxAttempts) {
        std::cout << "�޷�������Ч��Ŀ�������ԣ�" << std::endl;
        for (int i = 0; i < size; i++) {
            delete[] realOriginalBoard[i];
        }
        delete[] realOriginalBoard;
        return;
    }
    std::cout << "�н���Ŀ�����ɣ�����" << attempts << "��" << std::endl;
    // ��ʾ��Ŀ
    generateTwistedQuestion();//��ӡģ�����board��������Ŀ��Ϣ

    // ��ȡ�û���
    inputBoard(originalBoard);//�޸ĳ�Ա����originalBoard��Ϊ��������

    // ��֤��
    if (compareBoards(realOriginalBoard))
    {
        std::cout << "��ϲ����Ĵ���ȫ��ȷ��\n";
    }
    else
    {
        std::cout << "�𰸴���\n";
        std::cout << "��ȷ��ʼ����Ϊ��\n";
        printBoard(realOriginalBoard);
    }
    // �ͷű������̵��ڴ�
    for (int i = 0; i < size; i++) {
        delete[] realOriginalBoard[i];
    }
    delete[] realOriginalBoard;
}

// ��������ģʽ ���û��Զ��壩
void funMode::AntsHit() {
    // ��ʾ��Ϸ����
    std::cout << "====��ӭ�����������ȣ�===" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "����:��������������һ�������ϰ�������" << std::endl;
    std::cout << "�µĹ��򣺵���������ǽ�ڻ��ϰ�ʱ�����᳢������תֱ���ҵ����ƶ��ķ���ǰ��һ�������ɫ" << std::endl;
    std::cout << "�����������У�����Ҫ�������յ�����ͼ���ϰ����֣����ݳ���ʼ����״̬" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << std::endl;
    std::cout << "��ע�⣺��ģʽ�£�������Զ��庬�ϰ�����Ŀ" << std::endl;

    // �����û��Զ�����Ŀ,�ж��Ƿ��н�
    if (generateUserQuestion())
    {
        // ��ȡ�û���
        inputBoard(originalBoard);//�޸�originalBoard��Ϊ�û���������

        // ��֤��
        if (compareBoards(board))
        {
            std::cout << "��ϲ����Ĵ���ȫ��ȷ��\n";
        }
        else
        {
            std::cout << "�𰸴���\n";
            std::cout << "��ȷ��ʼ����Ϊ��\n";
            printBoard(board);
        }
    }
}

//����֮·ģʽ�����Գ��⣩
void funMode::ToolsRoad()
{
    // ��ʾ��Ϸ����
    std::cout << "====��ӭ��������֮·��===" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "����:�������Ϸ��ֻ���Խ��Խ�ѣ����������" << std::endl;
    std::cout << "��ģʽ�������ȡ���߿�������Ϸ���еĹ����п�ʹ��������Ϸ" << std::endl;
    std::cout << "����ģʽ�£���Ե���Խ�࣬��õĵ��߿���Խ�࣬�������԰ɣ�" << std::endl;
    std::cout << "�����߹�n���γ�����ͼ����Ҫ��������ͼ���ݳ����̳�ʼ״̬��Ϊ�������" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << std::endl;
    std::cout << "��ע�⣺��ģʽ�£�����������ɺ��ϰ����н���Ŀ��������" << std::endl;
    cout << endl;
    //������⻷�ڣ���ȡ���߿�
    answerQues();
    //���ɾ���֮·��Ŀ
    if (generateAwakenRoad())
    {
        //ѡ�����
        chooseTool();
        inputBoard(originalBoard);
        if (compareBoards(board))
        {
            cout << "��ϲ��ش���ȷ��" << endl;
            return;
        }
        else
        {
            cout << "�𰸴���\n";
            cout << "��ȷ��ʼ����Ϊ��\n";
            printBoard(board);
            return;
        }
    }
}

// ��ʼ����̬��Ա����
const std::vector<std::pair<int, int>> funMode::DIRECTIONS = {
    {-1, 1}, {1, 1}, {-2, 0}, {2, 0}, {-1, -1}, {1, -1} // OA, OB, OC, OD, OE, OF
};

int funMode::coordToIndex(int x, int y) const 
{
    if (x == -1 && y == 1) return 0;  // ������
    if (x == 1 && y == 1) return 1;   // ������
    if (x == -2 && y == 0) return 2;  // ��
    if (x == 0 && y == 0) return 3;   // ��
    if (x == 2 && y == 0) return 4;   // ��
    if (x == -1 && y == -1) return 5; // �ײ���
    if (x == 1 && y == -1) return 6;  // �ײ���
    return -1; // ��Ч����
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
        if (idx == -1) break; // ��Ч���꣬�˳�ģ��

        // ��ת��ǰ����
        grid[idx] = !grid[idx];

        // �ƶ�����һ������
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
    // ����Ա�Զ����ʼ״̬
    std::vector<int> initialGrid = { 0, 1, 1, 0, 0, 1, 0 };

    // ����Ա�Զ��������ƶ�����
    std::vector<int> directions = { 2, 5, 3 }; // 

    // ģ�������ƶ�
    std::vector<int> finalGrid = simulateAntMovement(initialGrid, startX, startY, directions);

    // ��ʾ��Ŀ
    std::cout << "====��ӭ��������ͨ����===" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "����:�������ϵ�����һ�����Ӷ��������ε����̣�ÿһ����6��ǰ���������ѡ��" << std::endl;
    std::cout << "��ģʽ����Ŀ���ṩ���ϵ�����λ�ú������ƶ�ʱʹ�õ�������������ʾͼ����" << std::endl;
    std::cout << "�����߹�n���γ�����ͼ����Ҫ��������ͼ���ݳ����̳�ʼ״̬��Ϊ�������" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << std::endl;
    std::cout << "��ע�⣺��ģʽ�£����������н���Ŀ��������" << std::endl;
    cout << endl;


    // ��ʼ��ͼ�δ���
    initgraph(1000, 750, EX_SHOWCONSOLE);   // ����һ��800x600�Ĵ���
    setbkcolor(WHITE);     // ���ñ���ɫΪ��ɫ
    cleardevice();         // ����

	std::string imagePath = "C:\\Users\\w\\Desktop\\tip.png"; 
    // ��ʾͼƬ
    displayImage(imagePath);

    std::cout << "���ո���״̬:" << std::endl;
    printHexagon(finalGrid);
    std::cout << "������������: (" << startX << ", " << startY << ")" << std::endl;
    std::cout << "�����ƶ��Ⱥ�ʹ�õ���������(0-5��ӦOA-OF): ";
    for (int dir : directions) {
        std::cout << dir << " ";
    }
    std::cout << std::endl;

    // ��ȡ�û���
    std::vector<int> userAnswer(7);
    std::cout << "�������ʼ���̣� ";
    for (int i = 0; i < 7; ++i) {
        std::cin >> userAnswer[i];
    }

    // ����
    bool correct = true;
    for (int i = 0; i < 7; ++i) {
        if (userAnswer[i] != initialGrid[i]) {
            correct = false;
            break;
        }
    }
    std::cout << "��ȷ��: ";
    std::cout << endl;
	printHexagon(initialGrid);
    std::cout << (correct ? "��ϲ���ش���ȷ��" : "�ش��������һ�Σ�") << std::endl;

}

// Ȥζģʽѡͼ
void funMode::chooseMap()
{
    std::cout << "��ӭ����Ȥζģʽ��" << std::endl;
    std::cout << "��ѡ���ͼ" << std::endl;
    std::cout << "1. Ť������" << std::endl;
    std::cout << "2. ��������" << std::endl;
    std::cout << "3. ����֮·" << std::endl;
    std::cout << "4. ����ͨ��" << std::endl;
    std::cout << "�������������ĵ�ͼ��Ӧ�����" << std::endl;

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
        std::cout << "��Чѡ��" << std::endl;
    }
}