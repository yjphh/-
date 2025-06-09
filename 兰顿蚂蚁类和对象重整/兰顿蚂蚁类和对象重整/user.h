#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "gameRecord.h"

class User
{
public:
    User(const std::string& _username) : username(_username) {}

    void userRegister(const std::string& _username, const std::string& _password);//用户注册函数
	bool userLogin(std::string& _password);//用户登录函数
	bool forgotPassword();//用户忘记密码函数
	void addRecord(const GameRecord& record);//添加游戏记录函数
	void displayRecords();//显示同一次登录中用户选择保存的游戏记录函数

    std::string getUsername() const { return username; }
    const std::vector<GameRecord>& getRecords() const { return records; }
	void printAllRecordsFromFile(const std::string& _username);//打印用户所有游戏记录函数
    std::string getpassword();//用于将用户输入的密码显示为*
	void isSave(const GameRecord& record); //询问用户是否保存游戏记录函数
	void deleteRecord(int index);//删除指定行的游戏记录函数

private:
    std::string username;
    std::string password;
    std::vector<GameRecord> records;
};

#endif
