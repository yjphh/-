#ifndef GAME_HOMEPAGE_H
#define GAME_HOMEPAGE_H

#include "user.h"
#include "levelMode.h"
#include "freedomMode.h"
#include"funMode.h"

class GameHomepage
{
public:
    GameHomepage();//空的构造函数
    void beginGame();//用户的注册登录函数
	void chooseMode(User& user);//主页面的选择游戏模式函数

private:
    freedomMode freedommode;
    LevelMode levelMode;
    funMode funmode;
};

#endif