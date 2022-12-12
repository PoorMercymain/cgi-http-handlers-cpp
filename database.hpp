#ifndef DATABASE
#define DATABASE

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
/*
���������� ������, ��������, �������� ������, �������� ����� ������.
������ � ���� ������ �������� ��������� � �����, � ��������� ���� ������ ��������� ���������-�������������.
*/
template<typename KeyType, typename ValType>
class database {
public:
    database();
    ~database();

    // write record to db file
    int write(KeyType key, ValType value);
    // read one record from db file
    ValType read_one(KeyType key);
    // read all records from db file
    std::map<KeyType, ValType>* read_all();
    // erase record from db file
    int erase(KeyType key);
private:
    std::string databaseFilename;
};

#endif