#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <graphics.h>
#include <conio.h>
#include <ws2tcpip.h>
#include <codecvt>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "EasyXw.lib")
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define GRAY RGB(128, 128, 128)
#define ORANGE RGB(255, 165, 0)
using namespace std;

const int BOARD_SIZE = 6;
const int CELL_SIZE = 60;
const int WINDOW_WIDTH = BOARD_SIZE * CELL_SIZE + 400;
const int WINDOW_HEIGHT = BOARD_SIZE * CELL_SIZE + 150;

const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 40;
const int BUTTON_X = WINDOW_WIDTH - 150;
const int START_BUTTON_Y = WINDOW_HEIGHT - 120;
const int SUBMIT_BUTTON_Y = WINDOW_HEIGHT - 70;

// 音乐控制全局变量
const wchar_t* backgroundMusicPath = L"C:\\Users\\w\\Desktop\\background.wav";
bool isMusicPlaying = false;
bool isFirstClientActive = false;
bool isSecondClientActive = false;

struct Board {
    bool grid[BOARD_SIZE][BOARD_SIZE];
    int antX, antY;
    int antDir; // 0-上, 1-右, 2-下, 3-左
};

wstring string2wstring(const string& str) {
    using convert_type = codecvt_utf8<wchar_t>;
    wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(str);
}

Board deserializeBoard(const string& data) {
    Board board;
    size_t comma1 = data.find(',');
    size_t comma2 = data.find(',', comma1 + 1);
    size_t comma3 = data.find(',', comma2 + 1);

    string gridStr = data.substr(0, comma1);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.grid[i][j] = gridStr[i * BOARD_SIZE + j] == '1';
        }
    }

    board.antX = stoi(data.substr(comma1 + 1, comma2 - comma1 - 1));
    board.antY = stoi(data.substr(comma2 + 1, comma3 - comma2 - 1));
    board.antDir = stoi(data.substr(comma3 + 1));

    return board;
}

void playBackgroundMusic() {
    if (!isMusicPlaying) {
        PlaySound(backgroundMusicPath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        isMusicPlaying = true;
    }
}

void stopBackgroundMusic() {
    if (isMusicPlaying) {
        PlaySound(NULL, NULL, 0);
        isMusicPlaying = false;
    }
}

void drawBoard(const Board& board, bool isProblem, int steps, const string& username,
    bool isStarted, bool isSubmitted, double timeUsed) {
    BeginBatchDraw();

    cleardevice();
    settextstyle(20, 0, L"黑体");
    settextcolor(BLACK);

    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 3);
    rectangle(45, 45, 50 + BOARD_SIZE * CELL_SIZE + 5, 50 + BOARD_SIZE * CELL_SIZE + 5);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            setfillcolor(board.grid[i][j] ? WHITE : BLACK);
            setlinecolor(DARKGRAY);
            setlinestyle(PS_SOLID, 1);
            fillrectangle(j * CELL_SIZE + 50, i * CELL_SIZE + 50,
                (j + 1) * CELL_SIZE + 50, (i + 1) * CELL_SIZE + 50);

            if (isProblem && i == board.antX && j == board.antY) {
                setfillcolor(RED);
                int centerX = j * CELL_SIZE + 80;
                int centerY = i * CELL_SIZE + 80;
                switch (board.antDir) {
                case 0: fillcircle(centerX, centerY - 10, 8); break;
                case 1: fillcircle(centerX + 10, centerY, 8); break;
                case 2: fillcircle(centerX, centerY + 10, 8); break;
                case 3: fillcircle(centerX - 10, centerY, 8); break;
                }
            }
        }
    }

    wchar_t info[256];
    if (isSubmitted) {
        swprintf_s(info, 256, L"已完成 - 用时: %.1f秒 (步数: %d)", timeUsed, steps);
    }
    else if (isStarted) {
        swprintf_s(info, 256, L"答题中 - 已用时间: %.1f秒 (步数: %d)", timeUsed, steps);
    }
    else {
        swprintf_s(info, 256, L"等待开始 (步数: %d)", steps);
    }
    outtextxy(50, 20, info);

    int rightPanelX = BOARD_SIZE * CELL_SIZE + 100;
    setfillcolor(RGB(240, 240, 240));
    fillrectangle(rightPanelX, 40, WINDOW_WIDTH - 50, WINDOW_HEIGHT - 80);

    settextstyle(24, 0, L"幼圆");
    settextcolor(BLUE);
    outtextxy(rightPanelX + 20, 50, L"对抗模式");

    settextstyle(20, 0, L"黑体");
    settextcolor(BLACK);

    outtextxy(rightPanelX + 20, 90, L"用户:");
    if (!username.empty()) {
        outtextxy(rightPanelX + 100, 90, string2wstring(username).c_str());
    }

    const wchar_t* directions[] = { L"上", L"右", L"下", L"左" };
    outtextxy(rightPanelX + 20, 130, L"最终朝向:");
    outtextxy(rightPanelX + 100, 130, directions[board.antDir]);

    wchar_t stepsText[256];
    swprintf_s(stepsText, 256, L"%d", steps);
    outtextxy(rightPanelX + 20, 170, L"回溯步数:");
    outtextxy(rightPanelX + 100, 170, stepsText);

    IMAGE antImg;
    const wchar_t* antImagePath = L"C:\\Users\\w\\Desktop\\Ant.png";
    loadimage(&antImg, antImagePath, 140, 140);
    if (antImg.getwidth() > 0 && antImg.getheight() > 0) {
        int antX = BOARD_SIZE * CELL_SIZE + 155;
        int antY = WINDOW_HEIGHT - 270;
        putimage(antX, antY, &antImg);
    }
    else {
        setfillcolor(RGB(200, 150, 100));
        fillcircle(BOARD_SIZE * CELL_SIZE + 100, WINDOW_HEIGHT - 180, 15);
        setfillcolor(BLACK);
        fillcircle(BOARD_SIZE * CELL_SIZE + 95, WINDOW_HEIGHT - 185, 3);
        fillcircle(BOARD_SIZE * CELL_SIZE + 105, WINDOW_HEIGHT - 185, 3);
    }

    setfillcolor(isStarted ? GRAY : GREEN);
    fillrectangle(BUTTON_X, START_BUTTON_Y,
        BUTTON_X + BUTTON_WIDTH, START_BUTTON_Y + BUTTON_HEIGHT);
    outtextxy(BUTTON_X + 30, START_BUTTON_Y + 10,
        isStarted ? L"已开始" : L"开始");

    setfillcolor(!isStarted || isSubmitted ? GRAY : ORANGE);
    fillrectangle(BUTTON_X, SUBMIT_BUTTON_Y,
        BUTTON_X + BUTTON_WIDTH, SUBMIT_BUTTON_Y + BUTTON_HEIGHT);
    outtextxy(BUTTON_X + 30, SUBMIT_BUTTON_Y + 10,
        isSubmitted ? L"已提交" : L"提交");

    EndBatchDraw();
}

void showResult(const vector<string>& results) {
    BeginBatchDraw();
    cleardevice();
    settextstyle(24, 0, L"黑体");
    settextcolor(BLACK);

    outtextxy(50, 50, L"游戏结果:");

    wstring player1Result = string2wstring(results[0]) + L": " +
        (results[1] == "1" ? L"正确" : L"错误") + L", 用时: " +
        string2wstring(results[2]) + L"秒";
    wstring player2Result = string2wstring(results[3]) + L": " +
        (results[4] == "1" ? L"正确" : L"错误") + L", 用时: " +
        string2wstring(results[5]) + L"秒";
    wstring winnerText = L"获胜者: " + string2wstring(results[6]);

    settextstyle(20, 0, L"黑体");
    outtextxy(50, 100, player1Result.c_str());
    outtextxy(50, 150, player2Result.c_str());
    outtextxy(50, 200, winnerText.c_str());
    outtextxy(50, 250, L"点击空格退出...");

    EndBatchDraw();
}

int main() {
    // 初始化音乐状态
    isMusicPlaying = false;
    isFirstClientActive = false;
    isSecondClientActive = false;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed." << endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1) {
        cerr << "Invalid IP address." << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    serverAddr.sin_port = htons(12345);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Connection failed." << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    string username;
    cout << "Enter your username: ";
    getline(cin, username);
    send(clientSocket, username.c_str(), username.size(), 0);

    char problemData[1024] = { 0 };
    int bytesReceived = recv(clientSocket, problemData, sizeof(problemData) - 1, 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive problem data." << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    problemData[bytesReceived] = '\0';
    string problemStr(problemData);

    size_t stepsPos = problemStr.find_last_of(',');
    int steps = stoi(problemStr.substr(stepsPos + 1));
    Board problemBoard = deserializeBoard(problemStr.substr(0, stepsPos));

    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(WHITE);

    Board answerBoard = problemBoard;
    bool isStarted = false;
    bool isSubmitted = false;
    clock_t startTime = 0;
    double timeUsed = 0.0;

    drawBoard(answerBoard, true, steps, username, isStarted, isSubmitted, timeUsed);

    while (!isSubmitted) {
        ExMessage msg;
        while (peekmessage(&msg, EM_MOUSE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                bool redraw = false;

                if (msg.x >= 50 && msg.x < 50 + BOARD_SIZE * CELL_SIZE &&
                    msg.y >= 50 && msg.y < 50 + BOARD_SIZE * CELL_SIZE) {
                    int i = (msg.y - 50) / CELL_SIZE;
                    int j = (msg.x - 50) / CELL_SIZE;
                    if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
                        answerBoard.grid[i][j] = !answerBoard.grid[i][j];
                        redraw = true;
                    }
                }

                if (!isStarted &&
                    msg.x >= BUTTON_X && msg.x <= BUTTON_X + BUTTON_WIDTH &&
                    msg.y >= START_BUTTON_Y && msg.y <= START_BUTTON_Y + BUTTON_HEIGHT) {
                    isStarted = true;
                    startTime = clock();

                    // 音乐控制逻辑
                    if (!isFirstClientActive && !isSecondClientActive) {
                        isFirstClientActive = true;
                        playBackgroundMusic();
                    }
                    else if (isFirstClientActive && !isMusicPlaying) {
                        isSecondClientActive = true;
                        playBackgroundMusic();
                    }

                    redraw = true;
                }

                if (isStarted && !isSubmitted &&
                    msg.x >= BUTTON_X && msg.x <= BUTTON_X + BUTTON_WIDTH &&
                    msg.y >= SUBMIT_BUTTON_Y && msg.y <= SUBMIT_BUTTON_Y + BUTTON_HEIGHT) {
                    isSubmitted = true;
                    timeUsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;

                    // 音乐控制逻辑
                    if (isFirstClientActive || isSecondClientActive) {
                        stopBackgroundMusic();
                        if (isFirstClientActive) {
                            isFirstClientActive = false;
                        }
                        else {
                            isSecondClientActive = false;
                        }
                    }

                    redraw = true;
                }

                if (redraw) {
                    drawBoard(answerBoard, true, steps, username, isStarted, isSubmitted, timeUsed);
                }
            }
        }

        if (isStarted && !isSubmitted) {
            timeUsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
            drawBoard(answerBoard, true, steps, username, isStarted, isSubmitted, timeUsed);
        }

        Sleep(10);
    }

    string answerData;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            answerData += answerBoard.grid[i][j] ? '1' : '0';
        }
    }
    send(clientSocket, answerData.c_str(), answerData.size(), 0);

    string timeStr = to_string(timeUsed);
    send(clientSocket, timeStr.c_str(), timeStr.size(), 0);

    char resultBuffer[1024] = { 0 };
    bytesReceived = recv(clientSocket, resultBuffer, sizeof(resultBuffer) - 1, 0);
    if (bytesReceived <= 0) {
        cerr << "Failed to receive result." << endl;
    }
    else {
        resultBuffer[bytesReceived] = '\0';
        string resultStr(resultBuffer);

        vector<string> results;
        size_t pos = 0;
        while ((pos = resultStr.find(',')) != string::npos) {
            results.push_back(resultStr.substr(0, pos));
            resultStr.erase(0, pos + 1);
        }
        results.push_back(resultStr);

        if (results.size() >= 7) {
            showResult(results);
            _getch();
        }
        else {
            cerr << "Invalid result format." << endl;
        }
    }

    // 确保程序退出前停止音乐
    stopBackgroundMusic();
    closegraph();
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}