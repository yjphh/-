#ifndef GAME_RECORD_H
#define GAME_RECORD_H

#include <string>

class GameRecord 
{
public:
    GameRecord(const std::string& _username, int _stage, int _difficulty, double _elapsedTime, double _accuracy)
        : username(_username), stage(_stage), difficulty(_difficulty), elapsedTime(_elapsedTime), accuracy(_accuracy) {
    }

    std::string username;
    int stage;
    int difficulty;
    double elapsedTime;
    double accuracy;

    std::string timestamp;
};

#endif
