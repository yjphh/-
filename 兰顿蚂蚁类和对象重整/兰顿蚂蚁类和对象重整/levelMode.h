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
};

#endif
