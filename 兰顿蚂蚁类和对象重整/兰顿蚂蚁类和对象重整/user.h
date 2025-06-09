#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "gameRecord.h"

class User
{
public:
    User(const std::string& _username) : username(_username) {}

    void userRegister(const std::string& _username, const std::string& _password);//�û�ע�ắ��
	bool userLogin(std::string& _password);//�û���¼����
	bool forgotPassword();//�û��������뺯��
	void addRecord(const GameRecord& record);//�����Ϸ��¼����
	void displayRecords();//��ʾͬһ�ε�¼���û�ѡ�񱣴����Ϸ��¼����

    std::string getUsername() const { return username; }
    const std::vector<GameRecord>& getRecords() const { return records; }
	void printAllRecordsFromFile(const std::string& _username);//��ӡ�û�������Ϸ��¼����
    std::string getpassword();//���ڽ��û������������ʾΪ*
	void isSave(const GameRecord& record); //ѯ���û��Ƿ񱣴���Ϸ��¼����
	void deleteRecord(int index);//ɾ��ָ���е���Ϸ��¼����

private:
    std::string username;
    std::string password;
    std::vector<GameRecord> records;
};

#endif
