#ifndef GAME_HOMEPAGE_H
#define GAME_HOMEPAGE_H

#include "user.h"
#include "levelMode.h"
#include "freedomMode.h"
#include"funMode.h"

class GameHomepage
{
public:
    GameHomepage();//�յĹ��캯��
    void beginGame();//�û���ע���¼����
	void chooseMode(User& user);//��ҳ���ѡ����Ϸģʽ����

private:
    freedomMode freedommode;
    LevelMode levelMode;
    funMode funmode;
};

#endif