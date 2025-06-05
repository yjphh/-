#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

const int BOARD_SIZE = 6;
const int STEPS = 0;

// ���̽ṹ��
struct Board {
    bool grid[BOARD_SIZE][BOARD_SIZE]; // true��ʾ�׸�false��ʾ�ڸ�
    int antX, antY; // ����λ��
    int antDir; // ���Ϸ���: 0-��, 1-��, 2-��, 3-�� 
};

// ��ʼ���������
Board initRandomBoard() 
{
    Board board;
    srand(time(NULL));

    // �����������
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.grid[i][j] = rand() % 2 == 0;
        }
    }

    // ������ϳ�ʼλ�úͷ���
    board.antX = rand() % BOARD_SIZE;
    board.antY = rand() % BOARD_SIZE;
    board.antDir = rand() % 4;

    return board;
}

// ģ�������ƶ�
Board simulateAntMovement(Board initialBoard, int steps) {
    Board board = initialBoard;

    for (int s = 0; s < steps; s++) {
        bool isWhite = board.grid[board.antX][board.antY];

        // �ı䵱ǰ������ɫ
        board.grid[board.antX][board.antY] = !isWhite;

        // �ı䷽��
        if (isWhite) 
        {
            board.antDir = (board.antDir + 1) % 4; // ��ת
        }
        else
        {
            board.antDir = (board.antDir - 1 + 4) % 4; // ��ת
        }

        // �ƶ�����
        switch (board.antDir) 
        {
        case 0: // ��
            board.antX = (board.antX - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case 1: // ��
            board.antY = (board.antY + 1) % BOARD_SIZE;
            break;
        case 2: // ��
            board.antX = (board.antX + 1) % BOARD_SIZE;
            break;
        case 3: // ��
            board.antY = (board.antY - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        }
    }

    return board;
}

// ���л�����Ϊ�ַ���
string serializeBoard(const Board& board) {
    string result;

    // �������״̬
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            result += board.grid[i][j] ? '1' : '0';
        }
    }

    // �������λ�úͷ���
    result += ',' + to_string(board.antX) + ',' + to_string(board.antY) + ',' + to_string(board.antDir);

    return result;
}

// �����л��ַ���Ϊ����
Board deserializeBoard(const string& data) {
    Board board;
    size_t pos = 0;
    size_t comma1 = data.find(',');
    size_t comma2 = data.find(',', comma1 + 1);
    size_t comma3 = data.find(',', comma2 + 1);

    // ��������״̬
    string gridStr = data.substr(0, comma1);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.grid[i][j] = gridStr[i * BOARD_SIZE + j] == '1';
        }
    }

    // ��������λ�úͷ���
    board.antX = stoi(data.substr(comma1 + 1, comma2 - comma1 - 1));
    board.antY = stoi(data.substr(comma2 + 1, comma3 - comma2 - 1));
    board.antDir = stoi(data.substr(comma3 + 1));

    return board;
}

// �Ƚ����������Ƿ���ͬ
bool compareBoards(const Board& board1, const Board& board2) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board1.grid[i][j] != board2.grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // ��ʼ��Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed." << endl;
        return 1;
    }

    // �����׽���
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    // ���׽���
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // ����
    if (listen(serverSocket, 2) == SOCKET_ERROR) {
        cerr << "Listen failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server started, waiting for players..." << endl;

    // �ȴ����1����
    sockaddr_in client1Addr;
    int client1AddrSize = sizeof(client1Addr);
    SOCKET client1Socket = accept(serverSocket, (sockaddr*)&client1Addr, &client1AddrSize);
    if (client1Socket == INVALID_SOCKET) {
        cerr << "Accept failed for player 1." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "Player 1 connected." << endl;

    // ��ȡ���1�û���
    char username1[256];
    int bytesReceived = recv(client1Socket, username1, sizeof(username1), 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive username from player 1." << endl;
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    username1[bytesReceived] = '\0';
    cout << "Player 1 username: " << username1 << endl;

    // �ȴ����2����
    sockaddr_in client2Addr;
    int client2AddrSize = sizeof(client2Addr);
    SOCKET client2Socket = accept(serverSocket, (sockaddr*)&client2Addr, &client2AddrSize);
    if (client2Socket == INVALID_SOCKET) {
        cerr << "Accept failed for player 2." << endl;
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "Player 2 connected." << endl;

    // ��ȡ���2�û���
    char username2[256];
    bytesReceived = recv(client2Socket, username2, sizeof(username2), 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive username from player 2." << endl;
        closesocket(client2Socket);
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    username2[bytesReceived] = '\0';
    cout << "Player 2 username: " << username2 << endl;

    // ���ɳ�ʼ���̺���Ŀ����
    Board initialBoard = initRandomBoard();
    Board problemBoard = simulateAntMovement(initialBoard, STEPS);

    // ������Ŀ��Ϣ���������
    string problemData = serializeBoard(problemBoard) + "," + to_string(STEPS);
    send(client1Socket, problemData.c_str(), problemData.size() + 1, 0);
    send(client2Socket, problemData.c_str(), problemData.size() + 1, 0);

    // �������1�Ĵ�
    char answer1Data[BOARD_SIZE * BOARD_SIZE + 1];
    bytesReceived = recv(client1Socket, answer1Data, sizeof(answer1Data), 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive answer from player 1." << endl;
        closesocket(client2Socket);
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    answer1Data[bytesReceived] = '\0';

    // �������1����ʱ
    char time1Str[16];
    bytesReceived = recv(client1Socket, time1Str, sizeof(time1Str), 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive time from player 1." << endl;
        closesocket(client2Socket);
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    time1Str[bytesReceived] = '\0';
    double time1 = stod(time1Str);

    // �������2�Ĵ�
    char answer2Data[BOARD_SIZE * BOARD_SIZE + 1];
    bytesReceived = recv(client2Socket, answer2Data, sizeof(answer2Data), 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive answer from player 2." << endl;
        closesocket(client2Socket);
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    answer2Data[bytesReceived] = '\0';

    // �������2����ʱ
    char time2Str[16];
    bytesReceived = recv(client2Socket, time2Str, sizeof(time2Str), 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive time from player 2." << endl;
        closesocket(client2Socket);
        closesocket(client1Socket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    time2Str[bytesReceived] = '\0';
    double time2 = stod(time2Str);
    // �������1�Ĵ�����
    Board answer1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            answer1.grid[i][j] = answer1Data[i * BOARD_SIZE + j] == '1';
        }
    }

    // �������2�Ĵ�����
    Board answer2;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            answer2.grid[i][j] = answer2Data[i * BOARD_SIZE + j] == '1';
        }
    }

    // �Ƚϴ�
    bool correct1 = compareBoards(answer1, initialBoard);
    bool correct2 = compareBoards(answer2, initialBoard);

    // ȷ����ʤ��
    string winner;
    if (correct1 && correct2) {
        if (time1 < time2) {
            winner = username1;
        }
        else if (time2 < time1) {
            winner = username2;
        }
        else {
            winner = "Tie";
        }
    }
    else if (correct1) {
        winner = username1;
    }
    else if (correct2) {
        winner = username2;
    }
    else {
        winner = "Tie";
    }

    // ���ͽ�����������
    string result = string(username1) + "," + (correct1 ? "1" : "0") + "," + to_string(time1) + "," +
        string(username2) + "," + (correct2 ? "1" : "0") + "," + to_string(time2) + "," +
        winner;

    send(client1Socket, result.c_str(), result.size() + 1, 0);
    send(client2Socket, result.c_str(), result.size() + 1, 0);

    // �ر��׽���
    closesocket(client1Socket);
    closesocket(client2Socket);
    closesocket(serverSocket);
    WSACleanup();

    cout << "Game finished. Winner: " << winner << endl;

    return 0;
}