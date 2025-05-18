#include "funMode.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

// ���캯������ʼ��ͨ������
funMode::funMode() {
    srand(time(0));
    size = rand() % 3 + 3; // Ĭ�����̴�СΪ4x4���ɵ�����
    initBoard();
    initObstacle();
    resetAnt();
}

// ��ʼ������
void funMode::initBoard() {
    board = new int* [size];
    originalBoard = new int* [size];
    correctInitialBoard = new int* [size]; // ��������ȷ�ĳ�ʼ����
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        originalBoard[i] = new int[size];
        correctInitialBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = rand() % 2; // ����ڰ׸�
            originalBoard[i][j] = board[i][j];
            correctInitialBoard[i][j] = board[i][j];
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

// ��������״̬
void funMode::resetAnt() {
    antX = rand() % size;
    antY = rand() % size;
    antDirection = rand() % 4 + 1; // 1-4
    steps = rand() % 11 + 5; // 5-15��
}

// ��ӡ��������
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

// ��ӡ�ַ�����
void funMode::printBoard(char** arr) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// ��������״̬ - �޸ĺ�֧��#
void funMode::inputBoard(int** arr) {
    cout << "������" << size << "x" << size << "�ĳ�ʼ���̣�0=�׸�1=�ڸ�#=�ϰ�����" << endl;
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

// �ȶ�����
bool funMode::compareBoards() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (originalBoard[i][j] != board[i][j]) return false;
        }
    }
    return true;
}

// ͨ��ģ�⺯����Ť������ģʽ��
bool funMode::simulateTwistedWorld() {
    int x = antX, y = antY;
    int dir = antDirection;
    bool turnRight = (originalBoard[x][y] == 0); // ��ʼת��

    for (int i = 0; i < steps; i++) {
        // ��ת��ɫ
        board[x][y] = !board[x][y];

        // ת��
        if (turnRight) dir = (dir % 4) + 1; // ��ת
        else dir = (dir + 2) % 4 == 0 ? 4 : (dir + 2) % 4; // ��ת

        // �ƶ�
        switch (dir) {
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

    antX = x; antY = y; antDirection = dir;
    return true;
}

// ��������ģʽģ��
bool funMode::simulateAntsHit() {
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

    for (int i = 0; i < steps; i++) {
        // ��¼��ǰ����״̬
        int color = tempBoard[x][y];

        // ����ת�򣨺ڰ׸����
        if (color == 0) dir = (dir % 4) + 1; // �׸���ת
        else dir = (dir + 2) % 4 == 0 ? 4 : (dir + 2) % 4; // �ڸ���ת

        // �����ϰ���ǽ����ೢ��4����ת��
        int attempts = 0;
        bool moved = false;
        while (attempts < 4) {
            int nx = x, ny = y;
            switch (dir) {
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

            dir = (dir % 4) + 1; // ��ת
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
    }

    // ����ģ��������ȷ�ĳ�ʼ����
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            correctInitialBoard[i][j] = tempBoard[i][j];
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
    cout << "���ճ���" << antDirection << endl;
    cout << "������" << steps << endl;
    cout << "�������̣�" << endl;
    printBoard(board);
}

// ��������������Ŀ - �޸ĺ�
void funMode::generateHitQuestion() {
    cout << "\n=== ����������Ŀ ===" << endl;
    cout << "���̴�С��" << size << "x" << size << endl;
    cout << "��������λ�ã�(" << antX << ", " << antY << ")" << endl;
    cout << "���ճ���" << antDirection << endl;
    cout << "������" << steps << endl;
    cout << "�������̣����ϰ�����" << endl;
    printBoard(board);
}

// ��֤�û��������Ŀ�Ƿ���Ч - �޸���
bool funMode::validateUserQuestion() {
    // ������ϳ�ʼλ���Ƿ���������
    if (antX < 0 || antX >= size || antY < 0 || antY >= size) {
        cout << "��������λ�ó������̷�Χ��" << endl;
        return false;
    }

    // ������ϳ�ʼλ���Ƿ�Ϊ�ϰ�
    if (obstacle[antX][antY] == '#') {
        cout << "�������ϳ�ʼλ�ò������ϰ���" << endl;
        return false;
    }

    // ������������״̬��Ϊģ�����
    int** tempBoard = new int* [size];
    for (int i = 0; i < size; i++) {
        tempBoard[i] = new int[size];
        for (int j = 0; j < size; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    // ���浱ǰ����״̬��Ϊ��ʼ����
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            originalBoard[i][j] = board[i][j];
        }
    }

    // ģ�������ƶ�������Ƿ���������в���
    int x = antX, y = antY;
    int dir = antDirection;

    // ��¼ÿ��λ�úͷ���ķ��ʴ�������ֹ��ѭ��
    int visited[100][100][5] = { 0 }; // �����������100x100��4������+1������

    for (int i = 0; i < steps; i++) {
        int color = board[x][y];

        // ����Ƿ����ѭ��
        if (++visited[x][y][dir] > 4) {
            cout << "���������ڵ�" << i + 1 << "��������ѭ����" << endl;

            // �ͷ���ʱ����
            for (int i = 0; i < size; i++) {
                delete[] tempBoard[i];
            }
            delete[] tempBoard;

            return false;
        }

        // ����ת��
        if (color == 0) dir = (dir % 4) + 1; // �׸���ת
        else dir = (dir + 2) % 4 == 0 ? 4 : (dir + 2) % 4; // �ڸ���ת

        // �����ҵ����ƶ�����
        int attempts = 0;
        bool moved = false;
        while (attempts < 4) {
            int nx = x, ny = y;
            switch (dir) {
            case 1: ny--; break;
            case 2: ny++; break;
            case 3: nx--; break;
            case 4: nx++; break;
            }

            if (nx >= 0 && nx < size && ny >= 0 && ny < size && obstacle[nx][ny] != '#') {
                x = nx; y = ny;
                moved = true;
                break;
            }

            dir = (dir % 4) + 1;
            attempts++;
        }

        if (!moved) {
            cout << "���������ڵ�" << i + 1 << "���޷��ƶ���" << endl;

            // �ͷ���ʱ����
            for (int i = 0; i < size; i++) {
                delete[] tempBoard[i];
            }
            delete[] tempBoard;

            return false;
        }

        // ��ת��ɫ - ���ݹ����޸�
        if (attempts == 0) {
            board[x][y] = !board[x][y];
        }
    }

    // �ָ��û��������������״̬
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = tempBoard[i][j];
        }
        delete[] tempBoard[i];
    }
    delete[] tempBoard;

    return true;
}

// �����û��Զ�����Ŀ - �޸ĺ�
void funMode::generateUserQuestion() {
    cout << "\n=== �û��Զ�������������Ŀ ===" << endl;
    cout << "���������̴�С��";
    cin >> size;

    // ���·����ڴ�
    for (int i = 0; i < size; i++) {
        delete[] board[i];
        delete[] originalBoard[i];
        delete[] obstacle[i];
        delete[] correctInitialBoard[i];
    }
    delete[] board;
    delete[] originalBoard;
    delete[] obstacle;
    delete[] correctInitialBoard;

    initBoard();
    initObstacle();

    cout << "��������������λ�� (x y)��";
    cin >> antX >> antY;

    cout << "�������������ճ��� (1=��, 2=��, 3=��, 4=��)��";
    cin >> antDirection;

    cout << "�����������߹��Ĳ�����";
    cin >> steps;

    cout << "�����뺬�ϰ����������̣�" << size << "x" << size << "��0=�׸�1=�ڸ�#=�ϰ�����" << endl;
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
                board[i][j] = (cell == '1') ? 1 : 0;
            }
        }
    }

    // ������������״̬��Ϊ��ȷ��ʼ���̵����
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            correctInitialBoard[i][j] = board[i][j];
        }
    }

    // ��֤��Ŀ��Ч��
    if (!validateUserQuestion())
    {
        cout << "��Ŀ��Ч�������¿�ʼ��" << endl;
        return;
    }

    // ��ʾ��Ŀ
    cout << "\n=== ����֤������������Ŀ ===" << endl;
    cout << "���̴�С��" << size << "x" << size << endl;
    cout << "��������λ�ã�(" << antX << ", " << antY << ")" << endl;
    cout << "���ճ���" << antDirection << endl;
    cout << "������" << steps << endl;
    cout << "�������̣����ϰ�����" << endl;
    printBoard(board);
}

// ��������
funMode::~funMode() {
    for (int i = 0; i < size; i++) {
        delete[] board[i];
        delete[] originalBoard[i];
        delete[] obstacle[i];
        delete[] correctInitialBoard[i];
    }
    delete[] board;
    delete[] originalBoard;
    delete[] obstacle;
    delete[] correctInitialBoard;
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
            realOriginalBoard[i][j] = originalBoard[i][j];
        }
    }

    int maxAttempts = 1000; // ����Դ���
    int attempts = 0;
    while (!simulateTwistedWorld() && attempts < maxAttempts) {
        resetAnt();
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

    // ��ʾ��Ŀ
    generateTwistedQuestion();

    // ��ȡ�û���
    inputBoard(originalBoard);

    // ��֤��
    if (compareBoards()) {
        std::cout << "��ϲ����Ĵ���ȫ��ȷ��\n";
    }
    else {
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

// ��������ģʽ 
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

    // �����û��Զ�����Ŀ
    generateUserQuestion();

    // ģ�������ƶ���������ȷ�ĳ�ʼ����
    if (!simulateAntsHit()) {
        std::cout << "��Ŀ��Ч���޷�ģ�������ƶ���" << std::endl;
        return;
    }

    // ��ȡ�û���
    inputBoard(originalBoard);

    // ��֤��
    if (compareBoards()) {
        std::cout << "��ϲ����Ĵ���ȫ��ȷ��\n";
    }
    else {
        std::cout << "�𰸴���\n";
        std::cout << "��ȷ��ʼ����Ϊ��\n";
        printBoard(correctInitialBoard); // ʹ����ȷ�ĳ�ʼ����
    }
}

// Ȥζģʽѡͼ
void funMode::chooseMap() {
    std::cout << "��ӭ����Ȥζģʽ��" << std::endl;
    std::cout << "��ѡ���ͼ" << std::endl;
    std::cout << "1. Ť������" << std::endl;
    std::cout << "2. ��������" << std::endl;
    std::cout << "�������������ĵ�ͼ��Ӧ�����" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        TwistedWorld();
        break;
    case 2:
        AntsHit();
        break;
    default:
        std::cout << "��Чѡ��" << std::endl;
    }
}