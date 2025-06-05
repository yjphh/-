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

// 棋盘结构体
struct Board {
    bool grid[BOARD_SIZE][BOARD_SIZE]; // true表示白格，false表示黑格
    int antX, antY; // 蚂蚁位置
    int antDir; // 蚂蚁方向: 0-上, 1-右, 2-下, 3-左 
};

// 初始化随机棋盘
Board initRandomBoard() 
{
    Board board;
    srand(time(NULL));

    // 随机生成棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.grid[i][j] = rand() % 2 == 0;
        }
    }

    // 随机蚂蚁初始位置和方向
    board.antX = rand() % BOARD_SIZE;
    board.antY = rand() % BOARD_SIZE;
    board.antDir = rand() % 4;

    return board;
}

// 模拟蚂蚁移动
Board simulateAntMovement(Board initialBoard, int steps) {
    Board board = initialBoard;

    for (int s = 0; s < steps; s++) {
        bool isWhite = board.grid[board.antX][board.antY];

        // 改变当前格子颜色
        board.grid[board.antX][board.antY] = !isWhite;

        // 改变方向
        if (isWhite) 
        {
            board.antDir = (board.antDir + 1) % 4; // 右转
        }
        else
        {
            board.antDir = (board.antDir - 1 + 4) % 4; // 左转
        }

        // 移动蚂蚁
        switch (board.antDir) 
        {
        case 0: // 上
            board.antX = (board.antX - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case 1: // 右
            board.antY = (board.antY + 1) % BOARD_SIZE;
            break;
        case 2: // 下
            board.antX = (board.antX + 1) % BOARD_SIZE;
            break;
        case 3: // 左
            board.antY = (board.antY - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        }
    }

    return board;
}

// 序列化棋盘为字符串
string serializeBoard(const Board& board) {
    string result;

    // 添加棋盘状态
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            result += board.grid[i][j] ? '1' : '0';
        }
    }

    // 添加蚂蚁位置和方向
    result += ',' + to_string(board.antX) + ',' + to_string(board.antY) + ',' + to_string(board.antDir);

    return result;
}

// 反序列化字符串为棋盘
Board deserializeBoard(const string& data) {
    Board board;
    size_t pos = 0;
    size_t comma1 = data.find(',');
    size_t comma2 = data.find(',', comma1 + 1);
    size_t comma3 = data.find(',', comma2 + 1);

    // 解析棋盘状态
    string gridStr = data.substr(0, comma1);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.grid[i][j] = gridStr[i * BOARD_SIZE + j] == '1';
        }
    }

    // 解析蚂蚁位置和方向
    board.antX = stoi(data.substr(comma1 + 1, comma2 - comma1 - 1));
    board.antY = stoi(data.substr(comma2 + 1, comma3 - comma2 - 1));
    board.antDir = stoi(data.substr(comma3 + 1));

    return board;
}

// 比较两个棋盘是否相同
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
    // 初始化Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed." << endl;
        return 1;
    }

    // 创建套接字
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    // 绑定套接字
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

    // 监听
    if (listen(serverSocket, 2) == SOCKET_ERROR) {
        cerr << "Listen failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server started, waiting for players..." << endl;

    // 等待玩家1连接
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

    // 获取玩家1用户名
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

    // 等待玩家2连接
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

    // 获取玩家2用户名
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

    // 生成初始棋盘和题目棋盘
    Board initialBoard = initRandomBoard();
    Board problemBoard = simulateAntMovement(initialBoard, STEPS);

    // 发送题目信息给两个玩家
    string problemData = serializeBoard(problemBoard) + "," + to_string(STEPS);
    send(client1Socket, problemData.c_str(), problemData.size() + 1, 0);
    send(client2Socket, problemData.c_str(), problemData.size() + 1, 0);

    // 接收玩家1的答案
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

    // 接收玩家1的用时
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

    // 接收玩家2的答案
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

    // 接收玩家2的用时
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
    // 构建玩家1的答案棋盘
    Board answer1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            answer1.grid[i][j] = answer1Data[i * BOARD_SIZE + j] == '1';
        }
    }

    // 构建玩家2的答案棋盘
    Board answer2;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            answer2.grid[i][j] = answer2Data[i * BOARD_SIZE + j] == '1';
        }
    }

    // 比较答案
    bool correct1 = compareBoards(answer1, initialBoard);
    bool correct2 = compareBoards(answer2, initialBoard);

    // 确定获胜者
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

    // 发送结果给两个玩家
    string result = string(username1) + "," + (correct1 ? "1" : "0") + "," + to_string(time1) + "," +
        string(username2) + "," + (correct2 ? "1" : "0") + "," + to_string(time2) + "," +
        winner;

    send(client1Socket, result.c_str(), result.size() + 1, 0);
    send(client2Socket, result.c_str(), result.size() + 1, 0);

    // 关闭套接字
    closesocket(client1Socket);
    closesocket(client2Socket);
    closesocket(serverSocket);
    WSACleanup();

    cout << "Game finished. Winner: " << winner << endl;

    return 0;
}