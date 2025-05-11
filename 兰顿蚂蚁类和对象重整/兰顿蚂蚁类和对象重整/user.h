#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "gameRecord.h"

class User {
public:
    User(const std::string& _username) : username(_username) {}

    void userRegister(const std::string& _username, const std::string& _password);
    bool userLogin( std::string& _password);
    bool forgotPassword();
    void addRecord(const GameRecord& record);
    void displayRecords();

    std::string getUsername() const { return username; }
    const std::vector<GameRecord>& getRecords() const { return records; }
    void printAllRecordsFromFile(const std::string& _username);
    std::string getpassword();//用于将用户输入的密码显示为*
    void isSave(const GameRecord& record);

    void deleteRecord(int index);

private:
    std::string username;
    std::string password;
    std::vector<GameRecord> records;
};

#endif
