#ifndef GAME_HOMEPAGE_H
#define GAME_HOMEPAGE_H

#include "user.h"
#include "levelMode.h"
#include "freedomMode.h"
#include"funMode.h"

class GameHomepage
{
public:
    GameHomepage();
    void beginGame();
    void chooseMode(User& user);

private:
    freedomMode freedommode;
    LevelMode levelMode;
    funMode funmode;
};

#endif