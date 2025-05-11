#include "freedomMode.h"
#include "gameHomepage.h"
#include <cstdlib>
#include <ctime>
#include<windows.h>
#include<fstream>
#include<cmath>
#include<sstream>
#include<iomanip>

void TurnRight(Direction& heading) {
    switch (heading) {
    case DOWN:
        heading = LEFT;
        break;
    case UP:
        heading = RIGHT;
        break;
    case RIGHT:
        heading = DOWN;
        break;
    case LEFT:
        heading = UP;
        break;
    }
}

void TurnLeft(Direction& heading) {
    switch (heading) {
    case DOWN:
        heading = RIGHT;
        break;
    case UP:
        heading = LEFT;
        break;
    case RIGHT:
        heading = UP;
        break;
    case LEFT:
        heading = DOWN;
        break;
    }
}

bool freedomMode::isSameProblem(const problemBank& a, const problemBank& b)
{
    if (a.steps != b.steps || a.finalX != b.finalX || a.finalY != b.finalY ||a.finalDirec!=b.finalDirec|| a.arr.size() != b.arr.size()) {
        return false;
    }
    for (size_t i = 0; i < a.arr.size(); ++i) {
        if (a.arr[i] != b.arr[i]) {
            return false;
        }
    }
    return true;
}

bool freedomMode::SavetoFile(const std::string username, int steps, int finalX, int finalY,int finalDirec, const std::vector<bool> arr, const std::vector<bool> answer)
{
    std::ofstream file("question_bank.txt",std::ios::app);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�" << std::endl;
        return false;
    }

    // ����Ƿ����ظ���¼  
    std::ifstream inFile("question_bank.txt");
    if (!inFile.is_open()) {
        std::cerr << "�޷����ļ����м��" << std::endl;
        return false;
    }

    problemBank newProblem{ username, steps, finalX, finalY, finalDirec,arr };  //�洢�û��������Ŀ
    std::string storedUsername;
    int storedSteps, storedFinalX, storedFinalY,storedFinalDirec;  //�⼸�����������洢���ļ��ж�ȡ��������
    //��ȡ�ļ���һ�У��ѵ�һ����Ϣ���û�������Ϣ�Ƚϣ���ͬ����������������ͬ��������ȡ��һ�к����Ƚϣ�ֱ�������������ļ�
    while (inFile >> storedUsername >> storedSteps >> storedFinalX >> storedFinalY>> storedFinalDirec) //�ӵ�һ�п�ʼ����ȡһ���ַ�����4������������ȡ�������ݴ����⼸����������
    {
        std::vector<bool> storedArr;
        int val;
        while (inFile >> val)//���ļ����д�����Ŀ���̵�����������������
        {
            storedArr.push_back(static_cast<bool>(val));
            if (inFile.peek() == 'a')//����һ���ַ�Ϊa˵������Ŀ���������Ѷ��꣬����
            {
                break;
            }
        }
        problemBank storedProblem{ storedUsername, storedSteps, storedFinalX, storedFinalY,storedFinalDirec, storedArr};  //�洢�ļ������е���Ŀ
        if (isSameProblem(newProblem, storedProblem))
        {
            inFile.close();
            file.close();
            return false;
        }
    }
    inFile.close();

    // �����¼�¼  
    file << username << " " << steps << " " << finalX << " " << finalY<<" "<<finalDirec;
    for (bool b : arr) 
    {
        file <<" "<< static_cast<int>(b);
    }
    file <<'a';
    for (bool b : answer)
    {
        file << " " << static_cast<int>(b);
    }
    file << std::endl;
    file.close();
    return true;
}

void freedomMode::viewBank()
{
    std::cout << "������������������������������" << std::endl;
    std::cout << "����ģʽ��⣺" << std::endl;
    if (isfirstRead)
    {
        std::cout << std::endl;
        std::ifstream file("question_bank.txt");
        if (!file.is_open()) {
            std::cerr << "�޷����ļ�" << std::endl;
            return;
        }
        std::string username;
        int steps, finalX, finalY, finalDirec;
        while (file >> username >> steps >> finalX >> finalY >> finalDirec)
        {
            std::vector<bool> arr;
            std::vector<bool> answer;
            int val;
            while (file >> val)
            {
                arr.push_back(static_cast<bool>(val));
                if (file.peek() == 'a')
                {
                    file.get();
                    break;
                }
            }
            while (file >> val)
            {
                answer.push_back(static_cast<bool>(val));
                if (file.peek() == '\n')
                {
                    break;
                }
            }
            bank.push_back({ username, steps, finalX, finalY,finalDirec, arr,answer });
        }
        file.close();
    }
    isfirstRead = false;
    int counter = 0;
    // ��ӡ������Ŀ���
    for (size_t i = 0; i < bank.size(); ++i)
    {
        std::string fulltitle = "��Ŀ" + std::to_string(i + 1);
        if (counter % 3 == 0 && counter != 0)
        {
            std::cout << std::endl;
        }
        std::cout << std::left << std::setw(10) << fulltitle;
        counter++;
    }
    std::cout << std::endl;
    std::cout << "������������������������������" << std::endl;
}

const std::vector<problemBank>& freedomMode::getBank()const
{
    return bank;
}


void freedomMode::viewProblem(int i,std::vector<problemBank>bank)
{
    int c = bank[i-1].finalDirec;
    std::string c1;
    switch (c)
    {
    case 0:
    {
        c1 = "UP";
        break;
    }
    case 1:
    {
        c1 = "DOWN";
        break;
    }
    case 2:
    {
        c1 = "LEFT";
        break;
    }
    case 3:
    {
        c1 = "RIGHT";
        break;
    }
    }

    std::cout << "��Ŀ" << i <<"��Ϣ����" <<std::endl;
    std::cout << "�ṩ��: " << bank[i-1].username << std::endl;
    std::cout << "����: " << bank[i-1].steps << std::endl;
    std::cout << "����λ��: " << "(" << bank[i-1].finalX << "," << bank[i-1].finalY << ")" << std::endl;
    std::cout << "���ճ���:" << c1 << std::endl;
    std::cout << "����ͼ: " << std::endl;
    int counter = 0;
    for (bool b : bank[i-1].arr)
    {
        if (counter % int(sqrt(bank[i-1].arr.size())) == 0 && counter != 0)
        {
            std::cout << std::endl;
        }
        std::cout << (b ? "1" : "0") << " ";
        counter++;
    }
    std::cout << std::endl;
    std::cout << "��: ";
    for (bool b : bank[i-1].answer)
    {
        if (counter % int(sqrt(bank[i-1].answer.size())) == 0 && counter != 0)
        {
            std::cout << std::endl;
        }
        std::cout << (b ? "1" : "0") << " ";
        counter++;
    }
}


freedomMode::freedomMode(int size, int steps) : size(size), steps(steps) {
    board = new bool[size * size];
    finalBoard = new bool[size * size];
    initialBoard = new bool[size * size];
    initializeBoard(board);
    initializeBoard(finalBoard);
    initializeBoard(initialBoard);
    srand(time(0));
    // ����������̸���(0�׸�1�ڸ�)
    for (int i = 0; i < size * size; ++i) {
        board[i] = rand() % 2 == 0;
        initialBoard[i] = board[i];
    }
}

freedomMode::freedomMode() : size(0), steps(0), board(nullptr), finalBoard(nullptr), initialBoard(nullptr) {
    // Ĭ�Ϲ��캯��
}

freedomMode::~freedomMode() {
    delete[] board;
    delete[] finalBoard;
    delete[] initialBoard;
}

void freedomMode::initializeBoard(bool* board) {
    for (int i = 0; i < size * size; ++i) {
        board[i] = false;
    }
}

void freedomMode::copyBoard(bool* src, bool* dest) {
    for (int i = 0; i < size * size; ++i) {
        dest[i] = src[i];
    }
}

int freedomMode::getIndex(int x, int y) {
    return x * size + y;
}

bool freedomMode::moveAnt(int& x, int& y, Direction& heading) {
    int index = getIndex(x, y);
    if (board[index]) {
        TurnLeft(heading);
        board[index] = false;
    }
    else {
        TurnRight(heading);
        board[index] = true;
    }

    switch (heading) {
    case UP:
        if (x - 1 < 0) return false;
        x--;
        break;
    case DOWN:
        if (x + 1 >= size) return false;
        x++;
        break;
    case LEFT:
        if (y - 1 < 0) return false;
        y--;
        break;
    case RIGHT:
        if (y + 1 >= size) return false;
        y++;
        break;
    }
    return true;
}

bool freedomMode::isValidInitialPosition(int x, int y, Direction heading) {
    copyBoard(board, finalBoard);
    for (int i = 0; i < steps; ++i) {
        if (!moveAnt(x, y, heading)) {
            copyBoard(finalBoard, board);
            return false;
        }
    }
    copyBoard(finalBoard, board);
    return true;
}

void freedomMode::generateFinalBoard(int& x, int& y, Direction& heading) {
    copyBoard(initialBoard, board);
    for (int i = 0; i < steps; ++i) {
        moveAnt(x, y, heading);
    }
    copyBoard(board, finalBoard);
}

void freedomMode::printFinalBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << finalBoard[getIndex(i, j)] << " ";
        }
        std::cout << std::endl;
    }
}

bool freedomMode::checkSolution(bool* userBoard) {
    for (int i = 0; i < size * size; ++i) {
        if (userBoard[i] != initialBoard[i]) {
            return false;
        }
    }
    return true;
}

void freedomMode::printInitialBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << initialBoard[getIndex(i, j)] << " ";
        }
        std::cout << std::endl;
    }
}

bool freedomMode::suggestInitialPosition(int& x, int& y, Direction& heading) {
    const int MAX_ATTEMPTS = 1000; // ����Դ���
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        x = rand() % size;
        y = rand() % size;
        heading = static_cast<Direction>(rand() % 4);
        if (isValidInitialPosition(x, y, heading)) {
            return true;
        }
    }
    return false;
}

int freedomMode::freeMode(User& user)
{
    std::cout << "��ӭ��������ģʽ" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "��ģʽ��Ϸ�����飺" << std::endl;
    std::cout << "��һ���ɺڰ׸���ɵ����������̣�0����׸�1����ڸ񣩺�һֻ����" << std::endl;
    std::cout << "�������ڰ׸��ϣ���->�ڣ���ת90�㲢ǰ��һ��" << std::endl;
    std::cout << "�������ںڸ��ϣ���->�ף���ת90�㲢ǰ��һ��" << std::endl;
    std::cout << "�����߹�n���γ�����ͼ����Ҫ��������ͼ���ݳ����̳�ʼ״̬��Ϊ�������" << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << std::endl;
    std::cout << "��ע�⣺��ģʽ�£����Ի��������������̱߳�����������̸��ӣ��������������ϵĳ�ʼλ�úͳ�����߹����������Լ��������Ч����ӡ����ͼ��������" << std::endl;
    int size = 0;
    int steps = 0;
    while (true) {
        std::cout << "���������̵ı߳�: ";
        std::cin >> size;
        std::cout << "���������ɱ�������" << std::endl;
        std::cout << "������Ҫ�ߵĲ���: ";
        std::cin >> steps;
        freedomMode game(size, steps);

        int x = 0, y = 0;
        Direction heading;
        int invalidAttempts = 0;

        while (true) {
            if (invalidAttempts >= 3) {
                if (!game.suggestInitialPosition(x, y, heading)) {
                    std::cout << "�������޽⣬���Խ�����Ҫ�����������̱߳������µ����̡�" << std::endl;
                    break;
                }
                std::cout << "��������3����Чλ�ã�Ϊ������������Ϸ�����Ը����ĺ����ʼλ�úͳ������£�" << std::endl;
                std::cout << "��ʼλ��: (" << x << ", " << y << ")" << std::endl;
                std::cout << "��ʼ����: ";
                switch (heading) {
                case UP:
                    std::cout << "UP";
                    break;
                case DOWN:
                    std::cout << "DOWN";
                    break;
                case LEFT:
                    std::cout << "LEFT";
                    break;
                case RIGHT:
                    std::cout << "RIGHT";
                    break;
                }
                std::cout << std::endl;
                std::cout << "��ʹ�õ��Ը�������ʾ�����������ϵĳ�ʼλ�� (x y) �ͳ��� (0: UP, 1: DOWN, 2: LEFT, 3: RIGHT): ";
                std::cin >> x >> y;
                int headingInput = 0;
                std::cin >> headingInput;
                heading = static_cast<Direction>(headingInput);
            }
            else {
                std::cout << "���������ϵĳ�ʼλ�� (x y): ";
                std::cin >> x >> y;
                std::cout << "���������ϵĳ�ʼ���� (0: UP, 1: DOWN, 2: LEFT, 3: RIGHT): ";
                int headingInput;
                std::cin >> headingInput;
                heading = static_cast<Direction>(headingInput);
            }

            if (game.isValidInitialPosition(x, y, heading)) {
                std::cout << "����������Ч������ͼ���£�" << std::endl;
                int finalX = x, finalY = y;
                Direction finalHeading = heading;
                game.generateFinalBoard(finalX, finalY, finalHeading);
                game.printFinalBoard();

                std::cout << "�����������в���������λ��: (" << finalX << ", " << finalY << ")" << std::endl;
                std::cout << "�����������в��������ճ���: ";
                switch (finalHeading) {
                case UP:
                    std::cout << "UP";
                    break;
                case DOWN:
                    std::cout << "DOWN";
                    break;
                case LEFT:
                    std::cout << "LEFT";
                    break;
                case RIGHT:
                    std::cout << "RIGHT";
                    break;
                }
                std::cout << std::endl;

                bool* userBoard = new bool[size * size];
                while (true) {
                    std::cout << "������ԭʼ���� (0 ��ʾ�׸�, 1 ��ʾ�ڸ�):" << std::endl;
                    for (int i = 0; i < size; ++i) {
                        for (int j = 0; j < size; ++j) {
                            std::cin >> userBoard[i * size + j];
                        }
                    }

                    if (game.checkSolution(userBoard))
                    {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        // �����ı���ɫΪ��ɫ
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        std::cout << "�ش���ȷ����Ϸ����" << std::endl;
                        // �ָ�Ĭ����ɫ
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        delete[] userBoard;
                        // ѯ���Ƿ񱣴�
                        std::string choice1;
                        std::cout << "�Ƿ�浵��(yes/no): ";
                        std::cin >> choice1;
                        if (choice1 == "yes")
                        {
                            std::vector<bool> arr;
                            for (int i = 0; i < size * size; ++i) {
                                arr.push_back(game.finalBoard[i]);
                            }
                            std::vector<bool> answer;
                            for (int i = 0; i < size * size; ++i) {
                                answer.push_back(game.initialBoard[i]);
                            }
                            std::string username1 = user.getUsername();
                            if (game.SavetoFile(username1, steps, finalX, finalY,finalHeading, arr,answer))
                            {
                                std::cout << "�浵�ɹ���" << std::endl;
                            }
                            else
                            {
                                std::cout << "��������и��⣬���ظ�����" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "���⽫����������" << std::endl;
                        }

                        // ѯ���Ƿ�鿴���
                        std::string choice;
                        std::cout << "�Ƿ������⣿(yes/no): ";
                        std::cin >> choice;
                        while (choice == "yes")
                        {
                            game.viewBank();
                            std::cout << "����������鿴����Ŀ���: ";
                            int index;
                            std::cin >> index;
                            viewProblem(index, game.getBank());
                            std::cout << std::endl;
                            std::cout << "�Ƿ��ٴν�����⣿��yes/no��";
                            std::cin >> choice;
                        }
                        return 0;
                    }
                    else
                    {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        // �����ı���ɫΪ��ɫ
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                        std::cout << "�ش����" << std::endl;
                        // �ָ�Ĭ����ɫ
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        int choice;
                        std::cout << "���� 1 ����������⣬���� 2 ����ֱ�Ӹ�����ʼ���̴�: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            continue;
                        }
                        else if (choice == 2) {
                            game.printInitialBoard();
                            std::cout << "��Ϸ����" << std::endl;
                            // ѯ���Ƿ񱣴�
                            std::string choice1;
                            std::cout << "�Ƿ�浵��(yes/no): ";
                            std::cin >> choice1;
                            if (choice1 == "yes")
                            {
                                std::vector<bool> arr;
                                for (int i = 0; i < size * size; ++i) {
                                    arr.push_back(game.finalBoard[i]);
                                }
                                std::vector<bool> answer;
                                for (int i = 0; i < size * size; ++i) {
                                    answer.push_back(game.initialBoard[i]);
                                }
                                std::string username1 = user.getUsername();
                                if (game.SavetoFile(username1, steps, finalX, finalY,finalHeading, arr,answer))
                                {
                                    std::cout << "�浵�ɹ���" << std::endl;
                                }
                                else
                                {
                                    std::cout << "��������и��⣬���ظ�����" << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "���⽫����������" << std::endl;
                            }

                            // ѯ���Ƿ�鿴���
                            std::string choice;
                            std::cout << "�Ƿ�鿴��⣿(yes/no): ";
                            std::cin >> choice;
                            while (choice == "yes")
                            {
                                game.viewBank();
                                std::cout << "����������鿴����Ŀ���: ";
                                int index;
                                std::cin >> index;
                                viewProblem(index, game.getBank());
                                std::cout << std::endl;
                                std::cout << "�Ƿ��ٴν�����⣿��yes/no��";
                                std::cin >> choice;
                            }
                            delete[] userBoard;
                            return 0;
                        }
                    }
                }
            }
            else {
                std::cout << "����������Ч���������������ϵĳ�ʼλ�úͳ���" << std::endl;
                invalidAttempts++;
            }
        }
    }
}

