#ifndef LEVEL_MODE_H
#define LEVEL_MODE_H

#include "user.h"

class LevelMode 
{
public:
    void chooseStage(User& user);
    void stageBoard(int _stage, int _diffic, User& user);
    double compareBoard(int _userOne[], int _initialOne[], int _size,bool shouldPrint =true);
    int judgeBoard(int _userOne[], int _initialOne[], int _size);

    bool isBetter(const GameRecord& current, const GameRecord& others);
    std::vector<GameRecord>findAllBestRecords(const std::vector<GameRecord>& records);
    void bubbleSort(std::vector<GameRecord>& records, int n);
    void printList( std::vector<GameRecord> records);
    void viewRanklist(int stage, int diff);

};

#endif
