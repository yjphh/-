#include "user.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include<conio.h>
#include <chrono>
#include<iomanip>
#include <cstdio> // ����remove��rename����


std::string User::getpassword() 
{
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r')//�û����»س���ʱֹͣ����
    {
        if (ch == '\b')//�����˸��
        {
            if (!password.empty())
            {
                password.pop_back();//ɾ�����һ���ַ�
                std::cout << "\b \b";//���˹��
            }
        }
        else
        {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}
void User::userRegister(const std::string& _username,const std::string& _password) {
    std::string filename = username + ".txt";
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << _password << std::endl;//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

        std::cout << "ע��ɹ�" << std::endl;
        outFile.close();
    }
    else {
        std::cout << "ע��ʧ��" << std::endl;
    }
}
bool User::forgotPassword()
{
    std::string newPassword;
    std::cout << "�������µ����루������ֱ���滻ԭ���룬����Ӱ��������Ϸ��¼��" << std::endl;
    newPassword=getpassword();
    std::string filename = username + ".txt";
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cout << "�޷����ļ�" << std::endl;
        return false;
    }
    std::vector<std::string>lines;//�����洢�µ������ԭ������Ϸ��¼
    std::string line;//����ifstream��ָ���Ƕ�ȡ����
    //��ȡ��һ�У����룩
    if (std::getline(inFile, line))
    {
        lines.push_back(newPassword);
    }
    //��ȡʣ���У��û�ԭ������Ϸ��¼��
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close();
    std::ofstream outFile(filename);//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
    if (!outFile.is_open())
    {
        std::cout << "�޷����ļ�����д��" << std::endl;
        return false;
    }
    //���޸ĺ���������´����ļ�
    for (const auto& l : lines)
    {
        outFile << l << std::endl;
    }
    outFile.close();
    std::cout << "�����޸ĳɹ�����ʹ���������¼" << std::endl;
    return true;
}

bool User::userLogin( std::string& _password) 
{
    // ����û����Ƿ��� allUsername.txt �У�����ļ��������򴴽�
    bool usernameExists = false;
    std::ifstream inFile("allUsername.txt");

    // ����ļ����ڣ�����û����Ƿ��Ѵ���
    if (inFile.is_open()) {
        std::string _username;
        while (inFile >> _username) {
            if (_username == username) {
                usernameExists = true;
                break;
            }
        }
        inFile.close();
    }

    // ����û��������ڣ�д�� allUsername.txt
    if (!usernameExists) {
        std::ofstream outFile("allUsername.txt", std::ios::app);
        if (!outFile.is_open()) {
            std::cout << "�޷�������д�� allUsername.txt" << std::endl;
            return false;
        }
        outFile << username << std::endl;
        outFile.close();
    }


    int attempts = 3;
    while (attempts > 0)
    {
        std::string filename = username + ".txt";
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cout << "��¼ʧ�ܣ��û�δע��" << std::endl;
            return false;
        }

        std::string  storedPassword;
        inFile >> storedPassword;
        inFile.close();

        if (storedPassword == _password) 
        {
            std::cout << "��¼�ɹ�����ӭ " << username << " �ĵ�����" << std::endl;
            return true;
        }
        else
        {
            attempts--;
            std::cout << "��¼ʧ�ܣ��������,�㻹��" <<attempts<<"�γ��Ի���" << std::endl;
            if (attempts > 0)
            {
                std::cout << "����������ѡ��" << std::endl;
                std::cout << "1����������" << std::endl;
                std::cout << "2����������" << std::endl;
                int choice = 0;
                std::cin >> choice;
                if (choice == 1)
                {
                    std::string password;
                    std::cout << "���ٴ���������:" << std::endl;
                    password = getpassword();
                    _password = password;
                }
                if (choice == 2)
                {
                    if (forgotPassword())
                    {
                        attempts = 3;//������������ĳ��Դ���
                        std::cout << "���ٴ��������룺" << std::endl;
                        std::string password;
                        password = getpassword();
                        _password = password;
                    }
                }
            }
        }
    }
    std::cout << "���Դ��������꣬��¼ʧ��,�û��޷�����������Ϸ" << std::endl;
    return false;
}

void User::addRecord(const GameRecord& record) 
{

    GameRecord recordwithTime = record;
    // ��ȡ��ǰʱ��
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // ��ʽ��ʱ�䣨���磺2023-10-25 14:30:45��
    std::tm tm_struct;
    if (localtime_s(&tm_struct, &now_time) != 0) {
        std::cerr << "�޷���ȡ����ʱ��" << std::endl;
        return;
    }
    std::stringstream time_stream;
    time_stream << std::put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    recordwithTime.timestamp = time_stream.str();

    records.push_back(recordwithTime);
    std::ofstream outFile(username + ".txt",std::ios::app);//11111111111111111111111111111111111111111111111111111111111111111111111
    if (outFile.is_open())
    {
        outFile <<username << " ";
        outFile << recordwithTime.stage <<" ";
        outFile << recordwithTime.difficulty <<" ";
        outFile << recordwithTime.elapsedTime <<" ";
        outFile << recordwithTime.accuracy << " ";
        outFile << recordwithTime.timestamp << std::endl;  // ���ʱ���
        outFile.close();
    }
    else
    {
        std::cerr << "�޷����ļ�������Ϸ��¼��" << std::endl;
    }
}

void User::displayRecords() //��ʾͬһ�ε�¼���û�ѡ�񱣴����Ϸ��¼
{
    if (records.empty())
    {
        std::cout << "������Ϸ���޼�¼" << std::endl;
    }
    else 
    {
        for (const auto& record : records)
        {
            for (auto record : records) 
            {
                std::cout << "�û�:" << std::setw(6) << std::left << record.username << " ";  // �̶��û������
                std::cout << "�ؿ�:��" << std::setw(1) << record.stage << "��" << " ";
                std::cout << "�Ѷ�(1�͡�2�С�3��):" << std::setw(1) << record.difficulty << " ";
                std::cout << "��ʱ:" << std::setw(6) << std::left << record.elapsedTime << "��  ";  // �̶���ʱ���
                std::cout << "��ȷ��:" << std::setw(6) << std::left << record.accuracy * 100 << "%" <<" ";
                std::cout << "ʱ��:" << record.timestamp << std::endl;
            }
        }
    }
}

void User::printAllRecordsFromFile(const std::string& _username) {
    std::ifstream readFile(_username + ".txt");
    if (!readFile.is_open()) {
        std::cerr << "�޷����ļ���ȡ��Ϸ��¼��" << std::endl;
        return;
    }
    // ������һ�У����룩
    std::string passwordLine;
    std::getline(readFile, passwordLine);  // ��ȡ��������һ��

    std::vector<GameRecord> Records;
    std::string line;
    while (std::getline(readFile, line))
    {  // ���ж�ȡʣ������
        std::istringstream iss(line);
        std::string name, timestamp;
        int stage, diff;
        double time, accuracy;

        // ��˳������ֶ�
        if (iss >> name >> stage >> diff >> time >> accuracy)
        {
            // ��ȡʱ�����ʣ�ಿ����Ϊ���壩
            std::getline(iss >> std::ws, timestamp);  // std::ws ����ǰ���ո�

            GameRecord record1(name, stage, diff, time, accuracy);
            record1.timestamp = timestamp;
            Records.push_back(record1);
        }
    }
    readFile.close();
    int a = 1;
    std::cout << "���û����д��ؼ�¼���£�" << std::endl;
    if (Records.empty())
    {
        std::cout << "���û����޴��ؼ�¼��" << std::endl;
        return;
    }
    for (auto record : Records)
    {
        std::cout << a++ << "��";
        std::cout << "�û�:" << std::setw(6) << std::left << record.username << " ";  // �̶��û������
        std::cout << "�ؿ�:��" << std::setw(1) << record.stage << "��" << " ";
        std::cout << "�Ѷ�(1�͡�2�С�3��):" << std::setw(1) << record.difficulty << " ";
        std::cout << "��ʱ:" << std::setw(6) << std::left << record.elapsedTime << "��  ";  // �̶���ʱ���
        std::cout << "��ȷ��:" << std::setw(6) << std::left << record.accuracy * 100 << "%"<<" ";
        std::cout << "ʱ��:" << record.timestamp << std::endl;
    }
}

void User::isSave(const GameRecord& record)
{
    std::cout << "�Ƿ񱣴棿��yes/no��" << std::endl;
    std::string choice;
    std::cin >> choice;
    if (choice == "yes")
    {
       addRecord(record);
       std::cout << "����ɹ���" << std::endl;
    }
    else
    {
        std::cout << "������Ϸ������" << std::endl;
        return;
    }
}

void User::deleteRecord(int _line)
{
    std::ifstream input(username + ".txt");
    if (!input.is_open()) {
        std::cerr << "�޷��������ļ�: " << username + ".txt" << std::endl;
        return;
    }
    //������ʱ�ļ�
    std::string filePath = username + ".txt";
    std::string tempFilePath = filePath + ".tmp";
    std::ofstream tempFile(tempFilePath);
    if (!tempFile.is_open()) {
        std::cerr << "�޷�������ʱ�ļ�" << std::endl;
        input.close();
        return;
    }

    std::string line;
    int currentLine = 1;
    bool lineDeleted = false;

    // ���ж�ȡԭ�ļ�
    while (std::getline(input, line)) {
        // �������Ҫɾ�����У���д����ʱ�ļ�
        if (currentLine != _line) 
        {
            tempFile << line << std::endl;
        }
        else 
        {
            lineDeleted = true;
        }
        currentLine++;
    }

    // �ر��ļ���
    input.close();
    tempFile.close();

    // ����ҵ���Ҫɾ�����У����滻ԭ�ļ�
    if (lineDeleted) {
        // ɾ��ԭ�ļ�
        if (std::remove(filePath.c_str()) != 0) {
            std::cerr << "ɾ��ԭ�ļ�ʧ��" << std::endl;
            return ;
        }
        else
        {
            std::cout << "��Ϸ��¼" << _line - 1 << "�ѱ�ɾ��" << std::endl;
        }

        // ��������ʱ�ļ�Ϊԭ�ļ���
        if (std::rename(tempFilePath.c_str(), filePath.c_str()) != 0) {
            std::cerr << "��������ʱ�ļ�ʧ��" << std::endl;
            return ;
        }
    }
    else 
    {
        // û���ҵ�Ҫɾ�����У�ɾ����ʱ�ļ�
        std::remove(tempFilePath.c_str());
        std::cerr << "������Ϸ��¼�����ڣ�" << std::endl;
        return ;
    }
}